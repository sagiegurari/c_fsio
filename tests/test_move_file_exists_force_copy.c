#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  char *file1 = "./move_file_exists_force_copy1.txt";
  char *file2 = "./move_file_exists_force_copy2.txt";
  bool done   = fsio_write_text_file(file1, "some\ncontent");

  assert_true(done);

  struct FsIOMoveFileOptions options;
  options.force_copy             = true;
  options.write_retries          = 0;
  options.retry_interval_seconds = 0;

  struct FsIOResult result = fsio_move_file_with_options(file1, file2, options);
  assert_true(result.done);

  char *text = fsio_read_text_file(file2);

  remove(file2);

  bool exists = fsio_path_exists(file1);
  assert_true(!exists);
  assert_string_equal(text, "some\ncontent");
  free(text);
}


int main()
{
  test_run(test_impl);
}

