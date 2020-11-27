#include "fsio.h"
#include "test.h"
#include <stdlib.h>
#include <string.h>


void test_impl()
{
  char *path = fsio_dirname("/dir1/dir2/file.txt");

  assert_true(!strcmp(path, "/dir1/dir2/"));

  free(path);
}


int main()
{
  test_run(test_impl);
}

