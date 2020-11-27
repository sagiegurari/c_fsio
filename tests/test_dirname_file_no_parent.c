#include "fsio.h"
#include "test.h"
#include <stdlib.h>
#include <string.h>


void test_impl()
{
  char *path = fsio_dirname("file.txt");

  assert_string_equal(path, ".");

  free(path);
}


int main()
{
  test_run(test_impl);
}

