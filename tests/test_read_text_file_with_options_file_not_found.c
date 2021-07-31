#include "fsio.h"
#include "test.h"


void test_impl()
{
  struct FsIOReadTextFileOptions options;

  options.max_read_limit = 0;
  options.tail           = false;

  char *text = fsio_read_text_file_with_options("./bad.txt", options);

  assert_true(text == NULL);
}


int main()
{
  test_run(test_impl);
}

