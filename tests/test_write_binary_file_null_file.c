#include "fsio.h"
#include "test.h"
#include <stdio.h>


void test_impl()
{
  bool done = fsio_write_binary_file(NULL, "test", 4);

  assert_true(!done);
}


int main()
{
  test_run(test_impl);
}

