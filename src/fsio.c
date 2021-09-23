#include "fsio.h"
#include "string_buffer.h"
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


const mode_t FSIO_MODE_ALL = S_IRWXU | S_IRWXG | S_IRWXO;


bool _fsio_load_stat(char *, struct stat *);
bool _fsio_write_file(char *, char *, char *);
char *_fsio_read_file_with_options(char *, char *, struct FsIOReadFileOptions);
bool _fsio_remove_callback(struct FsIORecursiveCallbackInfo);
bool _fsio_chmod_recursive_callback(struct FsIORecursiveCallbackInfo);
bool _fsio_recursive_operation(char *, bool (*callback)(struct FsIORecursiveCallbackInfo), void *, struct StringBuffer *);


long fsio_file_size(char *file)
{
  if (!fsio_file_exists(file))
  {
    return(-1);
  }

  FILE *fp = fopen(file, "rb");
  if (fp == NULL)
  {
    return(-1);
  }

  long current_position = ftell(fp);

  fseek(fp, 0L, SEEK_END);
  long size = ftell(fp);

  // set back to original position
  fseek(fp, current_position, SEEK_SET);

  fclose(fp);

  return(size);
}


bool fsio_write_text_file(char *file, char *text)
{
  return(_fsio_write_file(file, text, "w"));
}


bool fsio_append_text_file(char *file, char *text)
{
  return(_fsio_write_file(file, text, "a"));
}


char *fsio_read_text_file(char *file)
{
  struct FsIOReadFileOptions options;

  options.max_read_limit = 0;
  options.tail           = false;

  return(fsio_read_text_file_with_options(file, options));
}


char *fsio_read_text_file_with_options(char *file, struct FsIOReadFileOptions options)
{
  return(_fsio_read_file_with_options(file, "r", options));
}


bool fsio_write_binary_file(char *file, char *content)
{
  return(_fsio_write_file(file, content, "wb"));
}


bool fsio_append_binary_file(char *file, char *content)
{
  return(_fsio_write_file(file, content, "ab"));
}


char *fsio_read_binary_file(char *file)
{
  struct FsIOReadFileOptions options;

  options.max_read_limit = 0;
  options.tail           = false;

  return(fsio_read_binary_file_with_options(file, options));
}


char *fsio_read_binary_file_with_options(char *file, struct FsIOReadFileOptions options)
{
  return(_fsio_read_file_with_options(file, "rb", options));
}


bool fsio_create_empty_file(char *file)
{
  return(fsio_write_binary_file(file, ""));
}


bool fsio_copy_file(char *source, char *target)
{
  struct FsIOCopyFileOptions options;

  options.write_retries          = 0;
  options.retry_interval_seconds = 0;

  return(fsio_copy_file_with_options(source, target, options));
}


bool fsio_copy_file_with_options(char *source, char *target, struct FsIOCopyFileOptions options)
{
  if (source == NULL || target == NULL)
  {
    return(false);
  }

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

  int          character;
  bool         delete_file   = false;
  unsigned int write_retries = options.write_retries + 1;
  while ((character = getc(source_fp)) != EOF)
  {
    bool written = false;
    for (unsigned int index = 0; index < write_retries; index++)
    {
      if (fputc(character, target_fp) != EOF)
      {
        written = true;
        break;
      }
      else if (options.retry_interval_seconds)
      {
        sleep(options.retry_interval_seconds);
      }
    }

    if (!written)
    {
      delete_file = true;
      break;
    }
  }

  fclose(source_fp);
  fclose(target_fp);
  if (delete_file)
  {
    remove(target);
  }

  return(true);
}   /* fsio_copy_file_with_options */


bool fsio_move_file(char *source, char *target)
{
  struct FsIOMoveFileOptions options;

  options.force_copy             = false;
  options.write_retries          = 0;
  options.retry_interval_seconds = 0;

  enum FsIOError error = fsio_move_file_with_options(source, target, options);

  return(error == FSIO_ERROR_NONE);
}


enum FsIOError fsio_move_file_with_options(char *source, char *target, struct FsIOMoveFileOptions options)
{
  if (source == NULL || target == NULL)
  {
    return(FSIO_ERROR_INVALID_INPUT);
  }
  if (!fsio_file_exists(source))
  {
    return(FSIO_ERROR_PATH_NOT_FOUND);
  }

  if (!options.force_copy)
  {
    if (!rename(source, target))
    {
      return(FSIO_ERROR_NONE);
    }

    if (errno != EXDEV)
    {
      return(FSIO_ERROR_SEE_ERRNO);
    }
  }

  struct FsIOCopyFileOptions copy_options;
  copy_options.write_retries          = options.write_retries;
  copy_options.retry_interval_seconds = options.retry_interval_seconds;
  bool copy_done = fsio_copy_file_with_options(source, target, copy_options);
  if (copy_done)
  {
    fsio_remove(source);
  }

  if (!copy_done)
  {
    return(FSIO_ERROR_COPY_FAILED);
  }

  return(FSIO_ERROR_NONE);
} /* fsio_move_file_with_options */


char *fsio_join_paths(char *path1, char *path2)
{
  if (path1 == NULL)
  {
    if (path2 == NULL)
    {
      return(NULL);
    }

    return(strdup(path2));
  }
  if (path2 == NULL)
  {
    return(strdup(path1));
  }

  size_t len1 = strlen(path1);
  if (!len1)
  {
    return(strdup(path2));
  }
  size_t len2 = strlen(path2);
  if (!len2)
  {
    return(strdup(path1));
  }

  bool   path1_ends_with_separator   = path1[len1 - 1] == '/' || path1[len1 - 1] == '\\';
  bool   path2_starts_with_separator = path2[0] == '/' || path2[0] == '\\';
  bool   need_to_add_separator       = !path1_ends_with_separator && !path2_starts_with_separator;
  bool   need_to_remove_separator    = path1_ends_with_separator && path2_starts_with_separator;

  size_t concat_len = len1 + len2;
  if (need_to_add_separator)
  {
    concat_len = concat_len + 1;
  }
  else if (need_to_remove_separator)
  {
    concat_len = concat_len - 1;
  }

  char *concat_path = malloc(sizeof(char *) * (concat_len + 1));

  for (size_t index = 0; index < len1; index++)
  {
    concat_path[index] = path1[index];
  }
  size_t offset = len1;
  if (need_to_add_separator)
  {
    concat_path[len1] = '/';
    offset            = offset + 1;
  }
  else if (need_to_remove_separator)
  {
    offset = offset - 1;
  }
  for (size_t index = 0; index < len2; index++)
  {
    concat_path[offset + index] = path2[index];
  }

  concat_path[concat_len] = 0;

  return(concat_path);
} /* fsio_join_paths */


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

  if (result == 0 || errno == EEXIST)
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

      if (strlen(directory_mutable))
      {
        if (!fsio_mkdir(directory_mutable, mode))
        {
          free(directory_mutable);
          return(false);
        }
      }

      *path = '/';
    }
  }

  free(directory_mutable);

  return(fsio_mkdir(directory, mode));
}


bool fsio_mkdirs_parent(char *path, mode_t mode)
{
  if (path == NULL)
  {
    return(false);
  }

  char *path_clone = strdup(path);
  char *directory  = dirname(path_clone);

  if (directory == NULL)
  {
    free(path_clone);
    return(false);
  }

  bool done = fsio_mkdirs(directory, mode);
  free(path_clone);

  return(done);
}


bool fsio_remove(char *path)
{
  if (path == NULL)
  {
    return(true);
  }

  return(fsio_recursive_operation(path, _fsio_remove_callback, NULL));
}


bool fsio_chmod_recursive(char *path, mode_t mode)
{
  mode_t mode_ptr[1];

  mode_ptr[0] = mode;

  return(fsio_recursive_operation(path, _fsio_chmod_recursive_callback, mode_ptr));
}


bool fsio_recursive_operation(char *path, bool (*callback)(struct FsIORecursiveCallbackInfo), void *context)
{
  if (path == NULL)
  {
    return(false);
  }

  struct StringBuffer *buffer = string_buffer_new();
  bool                done    = _fsio_recursive_operation(path, callback, context, buffer);
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


bool _fsio_write_file(char *file, char *content, char *mode)
{
  if (file == NULL || content == NULL)
  {
    return(false);
  }

  bool directory_created = fsio_mkdirs_parent(file, FSIO_MODE_ALL);
  if (!directory_created)
  {
    return(false);
  }

  FILE *fp = fopen(file, mode);
  if (fp == NULL)
  {
    return(false);
  }

  if (fputs(content, fp) == EOF)
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


char *_fsio_read_file_with_options(char *file, char *mode, struct FsIOReadFileOptions options)
{
  long file_size = fsio_file_size(file);

  if (file_size < 0)
  {
    return(NULL);
  }
  if (!file_size)
  {
    return(strdup(""));
  }

  FILE *fp = fopen(file, mode);
  if (fp == NULL)
  {
    return(NULL);
  }

  long left_to_read = file_size;
  if (options.max_read_limit > 0 && left_to_read > options.max_read_limit)
  {
    left_to_read = options.max_read_limit;

    if (options.tail)
    {
      fseek(fp, (-1) * left_to_read, SEEK_END);
    }
  }

  int                 character;
  struct StringBuffer *buffer = string_buffer_new();
  while ((character = getc(fp)) != EOF && left_to_read > 0)
  {
    string_buffer_append(buffer, (char)character);
    left_to_read--;
  }

  fclose(fp);

  char *text = string_buffer_to_string(buffer);

  string_buffer_release(buffer);

  return(text);
} /* _fsio_read_file_with_options */


bool _fsio_remove_callback(struct FsIORecursiveCallbackInfo info)
{
  return(remove(info.path) == 0);
}


bool _fsio_chmod_recursive_callback(struct FsIORecursiveCallbackInfo info)
{
  mode_t *mode = (mode_t *)info.context;

  return(chmod(info.path, mode[0]) == 0);
}


bool _fsio_recursive_operation(char *path, bool (*callback)(struct FsIORecursiveCallbackInfo), void *context, struct StringBuffer *buffer)
{
  struct FsIORecursiveCallbackInfo info;

  info.context = context;
  info.path    = path;
  info.is_file = true;

  if (fsio_file_exists(path))
  {
    return(callback(info));
  }

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

      bool done = false;
      if (fsio_dir_exists(entry_path))
      {
        done = _fsio_recursive_operation(entry_path, callback, context, buffer);
      }
      else
      {
        info.path    = entry_path;
        info.is_file = true;
        done         = callback(info);
      }
      free(entry_path);

      if (!done)
      {
        closedir(directory);
        return(false);
      }
    }

    closedir(directory);

    info.path    = path;
    info.is_file = false;
    return(callback(info));
  }

  return(false);
}   /* _fsio_recursive_operation */

