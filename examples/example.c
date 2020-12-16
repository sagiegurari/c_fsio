#include "fsio.h"
#include <stdbool.h>
#include <stdio.h>


int main()
{
  // simple examples of writing/appending/reading text files
  char *file = "./somedir/myfile.txt";
  bool done  = fsio_write_text_file(file, "some text\n");

  printf("Text file written: %d\n", done);
  done = fsio_append_text_file(file, "more text\n");
  printf("Text file appended: %d\n", done);
  char *text = fsio_read_text_file(file);
  printf("Read text:\n%s\n", text);

  // creating a full directory path
  done = fsio_mkdirs("./somedir/dir1/dir2/dir3", FSIO_MODE_ALL);
  printf("Created directories: %d\n", done);

  // chmod to all permissions recursively
  done = fsio_chmod_recursive("./somedir/", FSIO_MODE_ALL);
  printf("Chmod done: %d\n", done);

  // recursive delete or files and directories
  done = fsio_remove("./somedir");
  printf("Deleted somedir and all content.\n");
}
