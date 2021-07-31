#include "fsio.h"
#include "test.h"
#include <stdlib.h>


void test_impl()
{
  char *path = fsio_join_paths("/dir1/dir2", "\\dir3/file.txt");

  assert_string_equal(path, "/dir1/dir2\\dir3/file.txt");

  free(path);
}


int main()
{
  test_run(test_impl);
}

