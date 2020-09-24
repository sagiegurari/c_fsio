#include "fsio.h"
#include "test.h"
#include <stdio.h>


void test_impl()
{
  char *file = "./baddir/write_text_file_dir_not_exists.txt";
  bool done  = fsio_write_text_file(file, "some\ncontent");
  char *text = fsio_read_text_file(file);

  remove(file);

  assert_true(!done);
  assert_true(text == NULL);
}


int main()
{
  test_run(test_impl);
}

