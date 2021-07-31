#include "fsio.h"
#include "test.h"
#include <stdio.h>


void test_impl()
{
  char *file = "./file_size_exists.txt";
  bool done  = fsio_write_text_file(file, "123456789");

  assert_true(done);

  long size = fsio_file_size(file);

  remove(file);

  assert_num_equal(size, 9);
}


int main()
{
  test_run(test_impl);
}

