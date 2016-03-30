/****************************************************************************
FILE          : memclass-test.cpp
LAST REVISED  : September 24, 2001
SUBJECT       : Program to demonstrate class-specific new.
PROGRAMMER    : (C) Copyright 2001 by Peter Chapin

This program dynamically allocates some objects of type MemClass to
exercise that class's operator new and operator delete. It's way cool.

     Peter Chapin
     c/o Vermont Technical College
     Randolph Center, VT 05061
     Peter.Chapin@vtc.edu
****************************************************************************/

#include <iostream>
#include "memclass.h"

int main()
{
  MemClass *p = new MemClass(1);

  std::cout << "Created a MemClass object at address " << p << "\n";
  std::cout << "Value stored in object is " << p->get_value() << "\n";

  delete p;

  return 0;
}
