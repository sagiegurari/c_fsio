#include "fsio.h"
#include "test.h"
#include <unistd.h>


void test_impl()
{
  char *file = "./file_exists_dir";

  fsio_mkdir(file, 0777);
  bool exists = fsio_file_exists(file);
  rmdir(file);

  assert_true(!exists);
}


int main()
{
  test_run(test_impl);
}

