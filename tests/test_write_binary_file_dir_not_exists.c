#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void test_impl()
{
  char *file    = "./write_binary_file_dir_not_exists/dir1/dir2/dir3/write_binary_file_dir_not_exists.bin";
  char *content = "some\ncontent";
  bool done     = fsio_write_binary_file(file, content, strlen(content));
  char *text    = fsio_read_binary_file(file);

  assert_true(done);
  assert_string_equal(text, "some\ncontent");
  free(text);

  done = fsio_remove("./write_binary_file_dir_not_exists");
  assert_true(done);

  bool exists = fsio_dir_exists("./write_binary_file_dir_not_exists");
  assert_true(!exists);
}


int main()
{
  test_run(test_impl);
}

