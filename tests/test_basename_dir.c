#include "fsio.h"
#include "test.h"
#include <stdlib.h>
#include <string.h>


void test_impl()
{
  char *path = fsio_basename("/dir1/dir2/");

  assert_true(!strcmp(path, ""));

  free(path);
}


int main()
{
  test_run(test_impl);
}
