#include "fsio.h"
#include "string_buffer.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new();

  for (unsigned int index = 0; index < 1000; index++)
  {
    string_buffer_append_string(buffer, "another line of content.\n");
  }
  char *content = string_buffer_to_string(buffer);
  string_buffer_release(buffer);

  char *file = "./write_binary_file_long_content.bin";
  bool done  = fsio_write_binary_file(file, content);
  char *text = fsio_read_binary_file(file);

  remove(file);

  assert_true(done);
  assert_string_equal(text, content);

  free(text);
  free(content);
}


int main()
{
  test_run(test_impl);
}

