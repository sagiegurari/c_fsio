#include "fsio.h"
#include "test.h"


void test_impl()
{
  char *path = fsio_dirname(NULL);

  assert_true(path == NULL);
}


int main()
{
  test_run(test_impl);
}

