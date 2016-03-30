
#include <iostream>

class X {
public:
  virtual void f();
};

void X::f()
{
  std::cout << "X::f\n";
}

X *helper()
{
  int A = 42;

  class Y : public X {
  public:
    virtual void f()
      { std::cout << "Y::f (with A = " << A << ")\n"; }
  };

  return new Y;
}

int main()
{
  X *ptr = helper();
  ptr->f();
  return 0;
}
