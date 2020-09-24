#include "fsio.h"
#include "test.h"


void test_impl()
{
  bool exists = fsio_dir_exists(NULL);

  assert_true(!exists);
}


int main()
{
  test_run(test_impl);
}

