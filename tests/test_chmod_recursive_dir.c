#include "fsio.h"
#include "test.h"


void test_impl()
{
  char *dir = "./_test_chmod_recursive_dir/1/2/3/4/5/";

  bool exists = fsio_mkdirs(dir, S_IRWXU);

  assert_true(exists);
  exists = fsio_dir_exists(dir);
  assert_true(exists);

  bool done = fsio_chmod_recursive("./_test_chmod_recursive_dir", FSIO_MODE_ALL);
  assert_true(done);

  struct stat info;
  stat("./_test_chmod_recursive_dir", &info);
  mode_t      mode = info.st_mode & 0777;
  assert_mode_equal(mode, FSIO_MODE_ALL);
  stat(dir, &info);
  mode = info.st_mode & 0777;
  assert_mode_equal(mode, FSIO_MODE_ALL);

  fsio_remove("./_test_chmod_recursive_dir");
}


int main()
{
  test_run(test_impl);
}

