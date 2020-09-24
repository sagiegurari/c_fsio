#include "fsio.h"
#include "test.h"
#include <stdio.h>


void test_impl()
{
  char *file = "./write_text_file_overwrite.txt";
  bool done  = fsio_write_text_file(file, "1");
  char *text = fsio_read_text_file(file);

  assert_true(done);
  assert_string_equal(text, "1");

  done = fsio_write_text_file(file, "2");
  text = fsio_read_text_file(file);

  remove(file);

  assert_true(done);
  assert_string_equal(text, "2");
}


int main()
{
  test_run(test_impl);
}

