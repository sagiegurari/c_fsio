#include "fsio.h"
#include "test.h"
#include <unistd.h>


void test_impl()
{
  bool exists = fsio_mkdirs_parent("./mkdirs_parent_dir/1/2/3/", 0777);

  assert_true(exists);

  bool is_directory = fsio_dir_exists("./mkdirs_parent_dir/1/2/3/");
  assert_true(is_directory);

  bool deleted = fsio_remove("./mkdirs_parent_dir");
  assert_true(deleted);
}


int main()
{
  test_run(test_impl);
}

