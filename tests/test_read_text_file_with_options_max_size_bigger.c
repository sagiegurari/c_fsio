#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  char *file = "./read_text_file_with_optoins_max_size_bigger.txt";
  bool done  = fsio_write_text_file(file, "123456789");

  assert_true(done);

  struct FsIOReadTextFileOptions options;

  options.max_read_limit = 100;
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

