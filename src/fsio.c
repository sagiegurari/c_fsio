#include "fsio.h"
#include "string_buffer.h"
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>


bool fsio_write_text_file(char *file, char *text)
{
  if (file == NULL || text == NULL)
  {
    return(false);
  }

  FILE *fp = fopen(file, "w");
  if (fp == NULL)
  {
    return(false);
  }

  if (fputs(text, fp) == EOF)
  {
    fclose(fp);
    remove(file); // prevent partially written file to be

    return(false);
  }

  fclose(fp);

  return(true);
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


bool fsio_mkdir(char *directory, mode_t mode)
{
  int result = mkdir(directory, mode);

  if (result == 0 || result == EEXIST)
  {
    return(true);
  }

  return(false);
}

