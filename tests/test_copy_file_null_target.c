#include "fsio.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>


void test_impl()
{
  char *file1 = "./copy_file_null_target.txt";
  bool done   = fsio_write_text_file(file1, "some\ncontent");

  assert_true(done);

  done = fsio_copy_file(file1, NULL);
  assert_true(!done);

  remove(file1);
}


int main()
{
  test_run(test_impl);
}

