#include "fsio.h"
#include "test.h"


void test_impl()
{
  char *path = fsio_join_paths(NULL, NULL);

  assert_true(path == NULL);
}


int main()
{
  test_run(test_impl);
}

