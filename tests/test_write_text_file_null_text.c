#include "fsio.h"
#include "test.h"
#include <stdio.h>


void test_impl()
{
  char *file = "./write_text_file_null_text.txt";
  bool done  = fsio_write_text_file(file, NULL);
  char *text = fsio_read_text_file(file);

  assert_true(!done);
  assert_true(text == NULL);
}


int main()
{
  test_run(test_impl);
}

