#include "fsio.h"
#include "test.h"


void test_impl()
{
  bool done = fsio_chmod_recursive("./test_chmod_recursive_not_exists_dir", S_IRWXU | S_IRWXG | S_IRWXO);

  assert_true(!done);
}


int main()
{
  test_run(test_impl);
}

