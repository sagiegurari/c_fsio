#include "fsio.h"
#include "test.h"
#include <unistd.h>


void test_impl()
{
  bool exists = fsio_mkdirs_parent("./mkdirs_parent_dir/1/2/3/", 0777);

  assert_true(exists);

  bool is_directory = fsio_dir_exists("./mkdirs_parent_dir/1/2/3/");
  assert_true(is_directory);
}


int main()
{
  test_run(test_impl);
}

