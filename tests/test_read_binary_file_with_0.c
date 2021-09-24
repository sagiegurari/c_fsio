#include "fsio.h"
#include "test.h"
#include <stdlib.h>
#include <string.h>


void test_impl()
{
  char content[500];

  for (int index = 0; index < 500; index++)
  {
    content[index] = index - 100;
  }

  char *filename = "./read_write_binary_with_0.bin";
  fsio_write_binary_file(filename, content, 500);
  char *text = fsio_read_binary_file(filename);

  for (size_t index = 0; index < 500; index++)
  {
    assert_true(content[index] == text[index]);
  }
  assert_true(strlen(text) < 500);

  free(text);

  fsio_remove(filename);
}


int main()
{
  test_run(test_impl);
}

