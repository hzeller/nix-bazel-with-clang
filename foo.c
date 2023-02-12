#include <stdio.h>

#include "foo.h"

// using C++ keyword as variable to make sure we're really compiled with $CC
int foo(int number) {
  int class = 2 * number;
  printf("in C   function foo() -> %d\n", class);
  return class;
}
