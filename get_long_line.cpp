/**************************************************************************
FILE          : getlongline.cpp
PROGRAMMER    : Peter Chapin

(C) Copyright 2007 by Peter C. Chapin

This file contains the definition of a function that can read arbitrarily long lines from the
standard input device. It returns a pointer to a buffer containing the line. The calling program
must do a delete on that pointer when it no longer needs the line. If the calling program fails
to delete the pointer appropriately, memory leaks will occur. This function returns the null
pointer if there is no more input.
**************************************************************************/

#include <cstring>  // Same as C's <string.h> but with everything in std::
#include <iostream>

namespace vtsu {

    char *get_long_line( )
    {
        char ch;               // A single character of input.

        char *buffer;
        char *new_buffer;
        int   buffer_size;     // Total amount of space in the buffer.
        int   character_count; // Number of characters in the buffer.

        // Create an initial buffer.
        buffer          = new char[16];
        buffer_size     = 16;
        character_count = 0;

        // Read the input.
        while( std::cin.get( ch )) {
            if( ch == '\n' ) break;

            // If there is more space in the buffer...
            if( character_count != buffer_size ) {
                buffer[character_count++] = ch;
            }

            // Otherwise, allocate a bigger buffer.
            else {
                buffer_size *= 2;
                new_buffer = new char[buffer_size];
                std::memcpy( new_buffer, buffer, character_count );
                delete [] buffer;
                buffer = new_buffer;
                
                // Don't forget to put the character into it too!
                buffer[character_count++] = ch;
            }
            
        }

        // I get here if a '\n' is found *or* if EOF occurs on stdin. If I didn't put any
        // characters into the buffer at all, I should tell my caller that there is nothing
        // more.
        //
        if( std::cin.eof( ) && character_count == 0 ) {
            delete [] buffer;
            return 0;
        }

        // Otherwise, null terminate the buffer and hand it back. Let the caller delete it.
        // Notice how I also size buffer to be exactly the necessary size. This insures that no
        // memory is wasted.
        //
        new_buffer = new char[character_count + 1];
        std::memcpy( new_buffer, buffer, character_count );
        delete [] buffer;
        buffer = new_buffer;
        buffer[character_count] = '\0';
        return buffer;
    }

}
