#include "fsio.h"
#include "test.h"
#include <stdlib.h>
#include <string.h>


void test_impl()
{
  char *path = fsio_basename("file.txt");

  assert_string_equal(path, "file.txt");

  free(path);
}


int main()
{
  test_run(test_impl);
}
