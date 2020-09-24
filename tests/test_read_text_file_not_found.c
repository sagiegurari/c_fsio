#include "fsio.h"
#include "test.h"


void test_impl()
{
  char *text = fsio_read_text_file("./bad.txt");

  assert_true(text == NULL);
}


int main()
{
  test_run(test_impl);
}

