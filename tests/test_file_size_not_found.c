#include "fsio.h"
#include "test.h"


void test_impl()
{
  long size = fsio_file_size("./bad.txt");

  assert_num_equal(size, -1);
}


int main()
{
  test_run(test_impl);
}

