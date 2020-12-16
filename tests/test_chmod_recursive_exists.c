#include "fsio.h"
#include "test.h"


void test_impl()
{
  bool done = fsio_chmod_recursive("./test_chmod_recursive_exists", FSIO_MODE_ALL);

  assert_true(done);

  struct stat info;
  stat("./test_chmod_recursive_exists", &info);
  mode_t      mode = info.st_mode & 0777;
  assert_mode_equal(mode, FSIO_MODE_ALL);
}


int main()
{
  test_run(test_impl);
}

