#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void test_impl()
{
  char *file = "./dir1/dir2/dir3/write_text_file_dir_not_exists.txt";
  bool done  = fsio_write_text_file(file, "some\ncontent");
  char *text = fsio_read_text_file(file);

  remove(file);
  rmdir("./dir1/dir2/dir3");
  rmdir("./dir1/dir2");
  rmdir("./dir1");

  assert_true(done);
  assert_string_equal(text, "some\ncontent");
  free(text);
}


int main()
{
  test_run(test_impl);
}

