#include "fsio.h"
#include "test.h"
#include <stdlib.h>


void test_impl()
{
  char *extension = fsio_file_extension("dir.dir/temp");

  assert_true(extension == NULL);

  extension = fsio_file_extension("dir.dir\\temp");

  assert_true(extension == NULL);
}


int main()
{
  test_run(test_impl);
}

