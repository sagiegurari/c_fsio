#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  char *file = "./create_empty_file_parent_dir_not_exists/dir1/dir2/file.txt";
  bool done  = fsio_create_empty_file(file);
  char *text = fsio_read_text_file(file);

  assert_true(done);
  assert_string_equal(text, "");
  free(text);

  done = fsio_remove("./create_empty_file_parent_dir_not_exists");
  assert_true(done);

  bool exists = fsio_dir_exists("./create_empty_file_parent_dir_not_exists");
  assert_true(!exists);
}


int main()
{
  test_run(test_impl);
}

