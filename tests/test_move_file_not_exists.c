#include "fsio.h"
#include "test.h"


void test_impl()
{
  char *file1 = "./move_file_not_exists1.txt";
  char *file2 = "./move_file_not_exists2.txt";

  bool done = fsio_move_file(file1, file2);

  assert_true(!done);

  bool exists = fsio_path_exists(file2);
  assert_true(!exists);
}


int main()
{
  test_run(test_impl);
}

