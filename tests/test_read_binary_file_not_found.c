#include "fsio.h"
#include "test.h"


void test_impl()
{
  char *text = fsio_read_binary_file("./bad.bin");

  assert_true(text == NULL);
}


int main()
{
  test_run(test_impl);
}

