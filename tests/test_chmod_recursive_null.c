#include "fsio.h"
#include "test.h"
#include <sys/stat.h>


void test_impl()
{
  bool done = fsio_chmod_recursive(NULL, S_IRWXU | S_IRWXG | S_IRWXO);

  assert_true(!done);
}


int main()
{
  test_run(test_impl);
}

