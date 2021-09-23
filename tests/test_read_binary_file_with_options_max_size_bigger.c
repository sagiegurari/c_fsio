#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  char *file = "./read_binary_file_with_options_max_size_bigger.bin";
  bool done  = fsio_write_binary_file(file, "123456789");

  assert_true(done);

  struct FsIOReadFileOptions options;

  options.max_read_limit = 100;
  options.tail           = false;

  char *text = fsio_read_binary_file_with_options(file, options);

  remove(file);

  assert_string_equal(text, "123456789");
  free(text);
}


int main()
{
  test_run(test_impl);
}

