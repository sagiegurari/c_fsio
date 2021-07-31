#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  bool done = fsio_copy_file(NULL, "./test.txt");

  assert_true(!done);
}


int main()
{
  test_run(test_impl);
}

