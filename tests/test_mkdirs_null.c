#include "fsio.h"
#include "test.h"
#include <unistd.h>


void test_impl()
{
  bool exists = fsio_mkdirs(NULL, 0777);

  assert_true(!exists);
}


int main()
{
  test_run(test_impl);
}

