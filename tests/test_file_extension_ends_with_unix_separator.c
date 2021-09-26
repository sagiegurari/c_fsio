#include "fsio.h"
#include "test.h"


void test_impl()
{
  char *extension = fsio_file_extension("/test/test/");

  assert_true(extension == NULL);
}


int main()
{
  test_run(test_impl);
}

