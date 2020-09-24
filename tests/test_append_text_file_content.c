#include "fsio.h"
#include "test.h"
#include <stdio.h>


void test_impl()
{
  char *file = "./write_append_file_content.txt";
  bool done  = fsio_write_text_file(file, "some\ncontent\n");
  char *text = fsio_read_text_file(file);

  assert_true(done);
  assert_string_equal(text, "some\ncontent\n");

  done = fsio_append_text_file(file, "more content");
  text = fsio_read_text_file(file);

  remove(file);

  assert_true(done);
  assert_string_equal(text, "some\ncontent\nmore content");
}


int main()
{
  test_run(test_impl);
}

