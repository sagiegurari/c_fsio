#include "fsio.h"
#include "test.h"
#include <stdlib.h>


void test_impl()
{
  char *path = fsio_join_paths("", "");

  assert_string_equal(path, "");

  free(path);
}


int main()
{
  test_run(test_impl);
}

