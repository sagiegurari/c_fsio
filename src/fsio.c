#include "fsio.h"
#include "string_buffer.h"
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

bool _fsio_load_stat(char *, struct stat *);
bool _fsio_write_text_file(char *, char *, char *);
bool _fsio_remove(char *, struct StringBuffer *);


char *fsio_basename(char *path)
{
  if (path == NULL)
  {
    return(NULL);
  }

  size_t len = strlen(path);
  if (!len)
  {
    return(strdup(""));
  }

  if (path[len - 1] == '/')
  {
    return(strdup(""));
  }

  char *ptr = strrchr(path, '/');
  if (ptr == NULL)
  {
    return(strdup(path));
  }

  return(strdup(ptr + 1));
}


char *fsio_dirname(char *path)
{
  if (path == NULL)
  {
    return(NULL);
  }

  size_t len = strlen(path);
  if (!len)
  {
    return(strdup("."));
  }

  if (path[len - 1] == '/')
  {
    return(strdup(path));
  }

  char *ptr = strrchr(path, '/');
  if (ptr == NULL)
  {
    return(strdup("."));
  }

  char *directory = strdup(path);
  directory[len - strlen(ptr) + 1] = '\0';

  return(directory);
}


bool fsio_write_text_file(char *file, char *text)
{
  return(_fsio_write_text_file(file, text, "w"));
}


bool fsio_append_text_file(char *file, char *text)
{
  return(_fsio_write_text_file(file, text, "a"));
}


char *fsio_read_text_file(char *file)
{
  FILE *fp = fopen(file, "r");

  if (fp == NULL)
  {
    return(NULL);
  }

  int                 character;
  struct StringBuffer *buffer = string_buffer_new();
  while ((character = getc(fp)) != EOF)
  {
    string_buffer_append(buffer, (char)character);
  }

  fclose(fp);

  char *text = string_buffer_to_string(buffer);

  string_buffer_release(buffer);

  return(text);
}


bool fsio_create_empty_file(char *file)
{
  return(fsio_write_text_file(file, ""));
}


bool fsio_copy_file(char *source, char *target)
{
  FILE *source_fp = fopen(source, "r");

  if (source_fp == NULL)
  {
    return(false);
  }

  FILE *target_fp = fopen(target, "w");
  if (target_fp == NULL)
  {
    fclose(source_fp);
    return(false);
  }

  int character;
  while ((character = getc(source_fp)) != EOF)
  {
    if (fputc(character, target_fp) == EOF)
    {
      fclose(source_fp);
      fclose(target_fp);
      remove(target);
      break;
    }
  }

  fclose(source_fp);
  fclose(target_fp);

  return(true);
}


bool fsio_path_exists(char *path)
{
  struct stat info;

  return(_fsio_load_stat(path, &info));
}


bool fsio_file_exists(char *path)
{
  struct stat info;

  if (!_fsio_load_stat(path, &info))
  {
    return(false);
  }

  return(S_ISREG(info.st_mode));
}


bool fsio_dir_exists(char *path)
{
  struct stat info;

  if (!_fsio_load_stat(path, &info))
  {
    return(false);
  }

  return(S_ISDIR(info.st_mode));
}


bool fsio_mkdir(char *directory, mode_t mode)
{
  if (directory == NULL)
  {
    return(false);
  }

  if (fsio_dir_exists(directory))
  {
    return(true);
  }

  int result = mkdir(directory, mode);

  if (result == 0 || result == EEXIST)
  {
    return(true);
  }

  return(false);
}


bool fsio_mkdirs(char *directory, mode_t mode)
{
  if (directory == NULL)
  {
    return(false);
  }

  if (fsio_mkdir(directory, mode))
  {
    return(true);
  }

  char *directory_mutable = strdup(directory);

  for (char *path = directory_mutable; *path != 0; path++)
  {
    if (*path == '/')
    {
      *path = '\0';

      if (!fsio_mkdir(directory_mutable, mode))
      {
        free(directory_mutable);
        return(false);
      }

      *path = '/';
    }
  }

  free(directory_mutable);

  return(fsio_mkdir(directory, mode));
}


bool fsio_mkdirs_parent(char *path, mode_t mode)
{
  char *directory = fsio_dirname(path);

  if (directory == NULL)
  {
    return(false);
  }

  bool done = fsio_mkdirs(directory, mode);
  free(directory);

  return(done);
}


bool fsio_remove(char *path)
{
  if (path == NULL)
  {
    return(true);
  }

  struct StringBuffer *buffer = string_buffer_new();
  bool                done    = _fsio_remove(path, buffer);
  string_buffer_release(buffer);

  return(done);
}


bool _fsio_load_stat(char *path, struct stat *info)
{
  if (path == NULL)
  {
    return(false);
  }

  if (stat(path, info) != 0)
  {
    return(false);
  }

  return(true);
}


bool _fsio_write_text_file(char *file, char *text, char *mode)
{
  if (file == NULL || text == NULL)
  {
    return(false);
  }

  char *file_clone       = strdup(file);
  char *directory        = dirname(file_clone);
  bool directory_created = fsio_mkdirs(directory, S_IRWXU | S_IRWXG);
  free(file_clone);
  if (!directory_created)
  {
    return(false);
  }

  FILE *fp = fopen(file, mode);
  if (fp == NULL)
  {
    return(false);
  }

  if (fputs(text, fp) == EOF)
  {
    fclose(fp);

    // prevent partially written file to be
    remove(file);

    return(false);
  }

  fflush(fp);
  fclose(fp);

  return(true);
}


bool _fsio_remove(char *path, struct StringBuffer *buffer)
{
  if (fsio_file_exists(path))
  {
    return(remove(path) == 0);
  }

  bool done = true;
  if (fsio_dir_exists(path))
  {
    DIR *directory = opendir(path);
    if (directory == NULL)
    {
      return(false);
    }

    struct dirent *entry;
    while ((entry = readdir(directory)))
    {
      if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
      {
        // skip special directories
        continue;
      }

      string_buffer_append_string(buffer, path);
      string_buffer_append(buffer, '/');
      string_buffer_append_string(buffer, entry->d_name);

      char *entry_path = string_buffer_to_string(buffer);
      string_buffer_clear(buffer);

      if (fsio_dir_exists(entry_path))
      {
        done = _fsio_remove(entry_path, buffer);
      }
      else
      {
        done = remove(entry_path) == 0;
      }
      free(entry_path);

      if (!done)
      {
        closedir(directory);
        return(false);
      }
    }

    closedir(directory);

    done = remove(path) == 0;
  }

  return(done);
} /* _fsio_remove */

