#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  char *file = "./read_text_file_with_options_max_size_same.txt";
  bool done  = fsio_write_text_file(file, "123456789");

  assert_true(done);

  struct FsIOReadFileOptions options;

  options.max_read_limit = 9;
  options.tail           = false;

  char *text = fsio_read_text_file_with_options(file, options);

  remove(file);

  assert_string_equal(text, "123456789");
  free(text);
}


int main()
{
  test_run(test_impl);
}

