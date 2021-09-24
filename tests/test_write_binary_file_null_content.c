#include "fsio.h"
#include "test.h"
#include <stdio.h>


void test_impl()
{
  char *file = "./write_binary_file_null_text.bin";
  bool done  = fsio_write_binary_file(file, NULL, 0);
  char *text = fsio_read_binary_file(file);

  assert_true(!done);
  assert_true(text == NULL);
}


int main()
{
  test_run(test_impl);
}

