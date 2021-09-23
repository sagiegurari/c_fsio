#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  char *file = "./write_binary_file_content.bin";
  bool done  = fsio_write_binary_file(file, "some\ncontent");
  char *text = fsio_read_binary_file(file);

  remove(file);

  assert_true(done);
  assert_string_equal(text, "some\ncontent");
  free(text);
}


int main()
{
  test_run(test_impl);
}

