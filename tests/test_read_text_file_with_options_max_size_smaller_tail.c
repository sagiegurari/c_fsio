#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  char *file = "./read_text_file_with_optoins_max_size_smaller_tail.txt";
  bool done  = fsio_write_text_file(file, "123456789");

  assert_true(done);

  struct FsIOReadTextFileOptions options;

  options.max_read_limit = 3;
  options.tail           = true;

  char *text = fsio_read_text_file_with_options(file, options);

  remove(file);

  assert_string_equal(text, "789");
  free(text);
}


int main()
{
  test_run(test_impl);
}

