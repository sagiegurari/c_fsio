#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  char *file1 = "./move_file_exists_null_target.txt";
  bool done   = fsio_write_text_file(file1, "some\ncontent");

  assert_true(done);

  done = fsio_move_file(file1, NULL);
  assert_true(!done);

  char *text = fsio_read_text_file(file1);
  assert_string_equal(text, "some\ncontent");
  free(text);

  remove(file1);
}


int main()
{
  test_run(test_impl);
}

