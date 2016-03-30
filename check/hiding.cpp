
#include <iostream>

class B {
public:
  int f(int x)
  {
    std::cout << "Inside B::f(int)\n";
    return x + 1;
  }
};

class D : public B {
public:
  // This function hides, not overloads the f(int) in the base class.
  int f(int x, int y)
  {
    std::cout << "Inside D::f(int, int)\n";
    return x + y;
  }
};

int main()
{
  D object;

  object.f(1);   // Error: no such function. See hiding.adb in ..\Ada
  return 0;
}
