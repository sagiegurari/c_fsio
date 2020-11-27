#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  char *file1 = "./copy_file_exists1.txt";
  char *file2 = "./copy_file_exists2.txt";
  bool done   = fsio_write_text_file(file1, "some\ncontent");

  assert_true(done);

  done = fsio_copy_file(file1, file2);
  assert_true(done);

  char *text = fsio_read_text_file(file2);

  remove(file1);
  remove(file2);

  assert_string_equal(text, "some\ncontent");
  free(text);
}


int main()
{
  test_run(test_impl);
}

