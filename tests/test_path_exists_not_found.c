#include "fsio.h"
#include "test.h"


void test_impl()
{
  bool exists = fsio_dir_exists("./path_exists_not_found");

  assert_true(!exists);
}


int main()
{
  test_run(test_impl);
}

