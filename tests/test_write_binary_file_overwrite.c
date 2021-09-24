#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  char *file = "./write_binary_file_overwrite.bin";
  bool done  = fsio_write_binary_file(file, "1", 1);
  char *text = fsio_read_binary_file(file);

  assert_true(done);
  assert_string_equal(text, "1");
  free(text);

  done = fsio_write_binary_file(file, "2", 1);
  text = fsio_read_binary_file(file);

  remove(file);

  assert_true(done);
  assert_string_equal(text, "2");
  free(text);
}


int main()
{
  test_run(test_impl);
}

