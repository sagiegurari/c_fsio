#include "fsio.h"
#include "test.h"
#include <stdio.h>


void test_impl()
{
  bool done = fsio_write_text_file(NULL, "test");

  assert_true(!done);
}


int main()
{
  test_run(test_impl);
}

