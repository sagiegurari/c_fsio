#include "fsio.h"
#include "string_buffer.h"
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


bool write_text_file(char *, char *, char *);


bool fsio_write_text_file(char *file, char *text)
{
  return(write_text_file(file, text, "w"));
}


bool fsio_append_text_file(char *file, char *text)
{
  return(write_text_file(file, text, "a"));
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


bool fsio_dir_exists(char *directory)
{
  if (directory == NULL)
  {
    return(false);
  }

  struct stat info;

  if (stat(directory, &info) != 0)
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


bool write_text_file(char *file, char *text, char *mode)
{
  if (file == NULL || text == NULL)
  {
    return(false);
  }

  char *file_clone = strdup(file);
  char *directory  = dirname(file_clone);
  if (!fsio_mkdirs(directory, S_IRWXU | S_IRWXG))
  {
    return(false);
  }
  free(file_clone);

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

  fclose(fp);

  return(true);
}

