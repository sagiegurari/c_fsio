#include "fsio.h"
#include "stringbuffer.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  struct StringBuffer *buffer = stringbuffer_new();

  for (unsigned int index = 0; index < 1000; index++)
  {
    stringbuffer_append_string(buffer, "another line of content.\n");
  }
  char *content = stringbuffer_to_string(buffer);
  stringbuffer_release(buffer);

  char *file = "./write_text_file_long_content.txt";
  bool done  = fsio_write_text_file(file, content);
  char *text = fsio_read_text_file(file);

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

