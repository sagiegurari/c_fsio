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

  struct FsIOMoveFileOptions options;
  options.force_copy             = false;
  options.write_retries          = 0;
  options.retry_interval_seconds = 0;

  enum FsIOError result = fsio_move_file_with_options(file1, NULL, options);

  assert_num_equal(result, FSIO_ERROR_INVALID_INPUT);

  remove(file1);
}


int main()
{
  test_run(test_impl);
}

