#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  bool done = fsio_move_file(NULL, "./test.txt");

  assert_true(!done);

  struct FsIOMoveFileOptions options;

  options.force_copy             = false;
  options.write_retries          = 0;
  options.retry_interval_seconds = 0;

  enum FsIOError result = fsio_move_file_with_options(NULL, "./test.txt", options);

  assert_num_equal(result, FSIO_ERROR_INVALID_INPUT);
}


int main()
{
  test_run(test_impl);
}

