/****************************************************************************
FILE          : memclass.cpp
LAST REVISED  : September 24, 2001
SUBJECT       : Class to demonstrate how to provide a class specific new.
PROGRAMMER    : (C) Copyright 2001 by Peter Chapin

C++ allows the program to provide his/her own allocators on a class by
class basis. This simple class illustrates the technique.

     Peter Chapin
     c/o Vermont Technical College
     Randolph Center, VT 05061
     Peter.Chapin@vtc.edu
****************************************************************************/

#include <iostream>
#include "memclass.h"

//
// For now, just pass through to the global allocators. The I/O would not
// normally be in these methods, of course. It is included just to
// help illustrate what is happening.
//

void *MemClass::operator new(std::size_t size) throw(std::bad_alloc)
{
  void *p;

  std::cout << "MemClass::operator new(" << size << ").";
  p = ::new char[size];
  std::cout << " Pointer returned: " << p << "\n";
  return p;
}

void MemClass::operator delete(void *p)
{
  std::cout << "MemClass::operator delete(" << p << ")\n";
  ::delete [] p;
}
