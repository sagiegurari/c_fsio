#include "fsio.h"
#include "test.h"
#include <stdlib.h>


void test_impl()
{
  char *extension = fsio_file_extension("dir/.test");

  assert_string_equal(extension, ".test");
  free(extension);

  extension = fsio_file_extension("dir\\.test");

  assert_string_equal(extension, ".test");
  free(extension);
}


int main()
{
  test_run(test_impl);
}

