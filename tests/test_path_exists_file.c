#include "fsio.h"
#include "test.h"
#include <stdio.h>


void test_impl()
{
  char *file = "./path_exists_file.txt";

  fsio_create_empty_file(file);
  bool exists = fsio_file_exists(file);
  remove(file);

  assert_true(exists);
}


int main()
{
  test_run(test_impl);
}

