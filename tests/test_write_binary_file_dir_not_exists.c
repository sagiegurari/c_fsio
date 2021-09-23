#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void test_impl()
{
  char *file = "./write_binary_file_dir_not_exists/dir1/dir2/dir3/write_binary_file_dir_not_exists.bin";
  bool done  = fsio_write_binary_file(file, "some\ncontent");
  char *text = fsio_read_binary_file(file);

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

