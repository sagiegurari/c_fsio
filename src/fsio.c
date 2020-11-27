#include "fsio.h"
#include "string_buffer.h"
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

bool _fsio_load_stat(char *, struct stat *);
bool _fsio_write_text_file(char *, char *, char *);


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

