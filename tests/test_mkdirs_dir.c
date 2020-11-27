#include "fsio.h"
#include "test.h"
#include <unistd.h>


void test_impl()
{
  char *dir = "./mkdirs_dir/1/2/3/4/5/";

  bool exists = fsio_mkdirs(dir, 0777);

  assert_true(exists);
  exists = fsio_dir_exists(dir);
  assert_true(exists);

  bool done = fsio_remove(dir);
  assert_true(done);
  exists = fsio_dir_exists(dir);
  assert_true(!exists);
}


int main()
{
  test_run(test_impl);
}

