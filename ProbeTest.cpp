/*! \file   main.cpp
 *  \brief  A demonstration program that illustrates how class Probe works.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <iostream>
#include "Probe.hpp"

Probe global_object;  // ID == 1

Probe f( Probe incoming )  // ID == 3 (incoming is copied from ID == 2).
{
    Probe result;  // ID == 4

    result = incoming;
    return result;  // Move assignment from ID == 4 directly into `answer`.
                    // Destroy ID == 0 (the moved-from object, `result`)
                    // Destroy ID == 3 (the parameter)
}

int main( )
{
    Probe answer;  // ID == 2

    answer = f( answer );  // `answer` assumes the ID of the object being moved out of `f`.
    return 0;  // Destory ID == 4 (`answer`)
               // Destory ID == 1 (the global object).
}
