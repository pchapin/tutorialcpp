/*! \file   Probe.cpp
 *  \brief  A class that makes visible the action of the various special methods.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 *
 * This file contains an implementation of the Probe class. This version is not very useful for
 * real programs because it just spits out messages onto the standard output device. However,
 * one can imagine a production version of this class that logs messages to a file or that has
 * options regarding message disposition. Probe objects could be attached to objects either by
 * class membership, in cases where a new class is being defined, or by multiple inheritance in
 * cases where an existing class must be used. Could a useful debugging facility be created from
 * this? Perhaps.
 *
 * No "normal" Probe object has an ID of zero. Such objects are created when they are the source
 * of a move operation. Thus, the destruction of an object with ID 0 means a moved-from object
 * is being destroyed. All such objects have the same ID.
 *
 * Moving an object also moves the ID number. The destination of a move assumes the ID of the
 * source object. Its orginal ID number is lost (and won't appear during destruction).
 */

#include <iostream>
#include "Probe.hpp"

static int master_ID = 0;

Probe::Probe( )
{
    ID_number   = ++master_ID;
    std::cout << "Default constructor: (new) ID = "
              << ID_number << std::endl;
}

Probe::Probe( const Probe &existing )
{
    ID_number = ++master_ID;
    std::cout << "Copy constructor: (new) ID = "
              << ID_number
              << ". Copying from "
              << existing.ID_number << std::endl;
}

Probe &Probe::operator=( const Probe &other )
{
    // Ignore self-assignment.
    if( this != &other ) {
        std::cout << "Copy assignment: ID = "
                  << ID_number
                  << ". Copying from "
                  << other.ID_number << std::endl;
    }
    return *this;
}

Probe::~Probe( )
{
    std::cout << "Destructor: " << ID_number << std::endl;
}


Probe::Probe( Probe &&existing )
{
    std::cout << "Move constructor: ID = "
              << "(assuming source ID)"
              << ". Moving from "
              << existing.ID_number << std::endl;
    ID_number = existing.ID_number;
    existing.ID_number = 0;
}


Probe &Probe::operator=( Probe &&other )
{
    // Ignore self-assignment.
    if( this != &other ) {
        std::cout << "Move assignment: ID = "
                  << ID_number
                  << ". Moving from "
                  << other.ID_number
                  << " (assuming source ID)" << std::endl;
        ID_number = other.ID_number;
        other.ID_number = 0;
    }
    return *this;
}
