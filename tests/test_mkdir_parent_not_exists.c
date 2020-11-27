#include "fsio.h"
#include "test.h"
#include <unistd.h>


void test_impl()
{
  char *dir = "./mkdir_dir_parent_not_exists/1/2/3/";

  bool exists = fsio_mkdir(dir, 0777);

  assert_true(!exists);
  exists = fsio_dir_exists(dir);
  assert_true(!exists);
}


int main()
{
  test_run(test_impl);
}

