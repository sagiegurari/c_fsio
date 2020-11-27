#include "fsio.h"
#include "test.h"
#include <stdlib.h>
#include <string.h>


void test_impl()
{
  char *path = fsio_dirname("./dir_1/dir_2/file.txt");

  assert_string_equal(path, "./dir_1/dir_2/");

  char *d = fsio_dirname("./mkdirs_parent_file/1/2/3/file.txt");
  assert_string_equal(d, "./mkdirs_parent_file/1/2/3/");


  free(path);
}


int main()
{
  test_run(test_impl);
}

