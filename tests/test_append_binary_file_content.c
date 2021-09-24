#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void test_impl()
{
  char *file    = "./_test_append/write_append_file_content.bin";
  char *content = "some\ncontent\n";
  bool done     = fsio_write_binary_file(file, content, strlen(content));
  char *text    = fsio_read_binary_file(file);

  assert_true(done);
  assert_string_equal(text, "some\ncontent\n");
  free(text);

  content = "more content";
  done    = fsio_append_binary_file(file, content, strlen(content));
  text    = fsio_read_binary_file(file);

  remove("./_test_append");

  assert_true(done);
  assert_string_equal(text, "some\ncontent\nmore content");
  free(text);
}


int main()
{
  test_run(test_impl);
}

