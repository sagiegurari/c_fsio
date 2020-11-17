#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  char *file = "./write_text_file_empty.txt";
  bool done  = fsio_write_text_file(file, "");
  char *text = fsio_read_text_file(file);

  remove(file);

  assert_true(done);
  assert_string_equal(text, "");
  free(text);
}


int main()
{
  test_run(test_impl);
}

