#include "fsio.h"
#include "test.h"
#include <stdio.h>


void test_impl()
{
  char *file = "./dir_exists_file";

  fsio_create_empty_file(file);
  bool exists = fsio_dir_exists(file);
  remove(file);

  assert_true(!exists);
}


int main()
{
  test_run(test_impl);
}

