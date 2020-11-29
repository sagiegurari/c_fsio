#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void test_run(void (*fn)(void))
{
  printf("Test ... ");
  fn();
  printf("Done\n");
}


void test_fail()
{
  printf(" Error\n");
  exit(1);
}


void assert_true(bool value)
{
  if (!value)
  {
    test_fail();
  }
}


void assert_string_equal(char *value1, char *value2)
{
  if (strcmp(value1, value2) != 0)
  {
    printf("Assert Failed, value: %s not equals to value: %s", value1, value2);
    test_fail();
  }
}
