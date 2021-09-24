#include "fsio.h"
#include "string_buffer.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void test_impl()
{
  struct StringBuffer *buffer = string_buffer_new();

  for (unsigned int index = 0; index < 1000; index++)
  {
    string_buffer_append_string(buffer, "another line of content.\n");
  }
  char *content = string_buffer_to_string(buffer);
  string_buffer_append_string(buffer, content);
  char *double_content = string_buffer_to_string(buffer);
  string_buffer_release(buffer);

  char *file = "./stress1/stress2/write_binary_file_stress.bin";

  for (unsigned int index = 0; index < 50; index++)
  {
    bool done  = fsio_write_binary_file(file, content, strlen(content));
    char *text = fsio_read_binary_file(file);

    assert_true(done);
    assert_string_equal(text, content);
    free(text);

    done = fsio_append_binary_file(file, content, strlen(content));
    text = fsio_read_binary_file(file);

    remove(file);
    rmdir("./stress1/stress2");
    rmdir("./stress1");

    assert_true(done);
    assert_string_equal(text, double_content);
    free(text);
  }

  free(double_content);
  free(content);
}


int main()
{
  test_run(test_impl);
}

