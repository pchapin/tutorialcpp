/****************************************************************************
FILE          : memclass.h
LAST REVISED  : September 24, 2001
SUBJECT       : Class to demonstrate how to provide a class specific new.
PROGRAMMER    : (C) Copyright 2001 by Peter Chapin

C++ allows the program to provide his/her own allocators on a class by
class basis. This simple class illustrates the technique. See
memclass.cpp for more details.

     Peter Chapin
     c/o Vermont Technical College
     Randolph Center, VT 05061
     Peter.Chapin@vtc.edu
****************************************************************************/

#ifndef MEMCLASS_H
#define MEMCLASS_H

#include <memory>

class MemClass {

  private:
    int value;

  public:
    // Simple constructor.
    MemClass(int v = 0) : value(v) { }

    // Simple accessor methods.
    void set_value(int v) { value = v;    }
    int  get_value()      { return value; }

    // These are static methods even if not explicitly declared as such.
    void *operator new(std::size_t) throw(std::bad_alloc);
    void  operator delete(void *);

};

#endif
