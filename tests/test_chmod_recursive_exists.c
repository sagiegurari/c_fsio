#include "fsio.h"
#include "test.h"


void test_impl()
{
  char *file = "./_test_chmod_empty_file.txt";
  bool done  = fsio_create_empty_file(file);

  assert_true(done);

  done = fsio_chmod_recursive("./_test_chmod_empty_file.txt", FSIO_MODE_ALL);

  assert_true(done);

  struct stat info;
  stat("./_test_chmod_empty_file.txt", &info);
  mode_t      mode = info.st_mode & 0777;
  assert_mode_equal(mode, FSIO_MODE_ALL);

  fsio_remove("./_test_chmod_empty_file.txt");
}


int main()
{
  test_run(test_impl);
}

