#include <iostream>

#include "foo.h"
#include "bar.h"

int main() {
  const int a = foo(21);
  const int b = bar(21);
  std::cout << "\n== SUCCESS ==\ngot values " << a << " and " << b << std::endl;
}
