#include <iostream>

#include "bar.h"

// Using basic c++ features to make sure we're compiled with $CXX

class A {
public:
  A(int number) : number_(2 * number) {}
  int value() const { return number_; }
private:
  const int number_;
};

int bar(int number) {
  const A x(number);
  std::cout << "in C++ function bar() -> " << x.value() << "\n";
  return x.value();
}
