#include "fsio.h"
#include "test.h"


void test_impl()
{
  char *file1 = "./move_file_not_exists1.txt";
  char *file2 = "./move_file_not_exists2.txt";

  bool done = fsio_move_file(file1, file2);

  assert_true(!done);

  bool exists = fsio_path_exists(file2);
  assert_true(!exists);

  struct FsIOMoveFileOptions options;
  options.force_copy             = false;
  options.write_retries          = 0;
  options.retry_interval_seconds = 0;

  enum FsIOError result = fsio_move_file_with_options(file1, file2, options);

  assert_num_equal(result, FSIO_ERROR_PATH_NOT_FOUND);
}


int main()
{
  test_run(test_impl);
}

