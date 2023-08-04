/**************************************************************************
FILE          : BigInt.hpp
PROGRAMMER    : Peter Chapin

(C) Copyright 2006 by Peter C. Chapin

This file contains the interface to a "big" integer class. Objects of this class act just like
normal integers but they can hold far larger values.
**************************************************************************/

#ifndef BIGINT_HPP
#define BIGINT_HPP
// This insures that this header will only be processed once even if it is #included multiple
// times. The first time this header is processed, BIGINT_H will not be defined. As part of
// processing this header, BIGINT_H becomes defined. The next time this header is seen, it will
// effectively be skipped. This is necessary because certain constructions can only be processed
// once by the compiler. If the compiler processes this header multiple times, there might be
// errors.

#include <iosfwd>
// This header contains forward declarations of the classes std::ostream and std::istream
// without bringing in all the gory details of the iostreams header. It thus compiles faster and
// is the better choice when one only wants to declare references (or pointers) to certain
// stream classes.

namespace vtsu {

    class BigInt {

        // I/O operations.
        friend std::ostream &operator<<( std::ostream &, const BigInt & );
        friend std::istream &operator>>( std::istream &, BigInt & );

        // Relational operators.
        friend bool operator==( const BigInt &, const BigInt & );
        friend bool operator< ( const BigInt &, const BigInt & );

    public:
        // Default constructor.
        BigInt( );

        // Allows a BigInt to be initialized with a normal int.
        BigInt( long number );

        void operator+=( const BigInt & );
        void operator-=( const BigInt & );
        void operator*=( const BigInt & );
        void operator/=( const BigInt & );
        void operator%=( const BigInt & );
        // All the usual math operations.
        
    private:
        int   sign;          // -1 for negative, +1 for zero or positive.
        short digits[256];   // digits[0] is the least significant digit.
        // The value 256 should not be hard coded here. Instead a constant needs to be created
        // and used consistently. In BigInt.cpp there are many places where '256' or '255'
        // appear that would need to be edited if it is later decided to change the size of the
        // digits array.
    };


    // The binary math operators are easily expressed in terms of the in place operators
    // declared above.
    //
    inline BigInt operator+( const BigInt &left, const BigInt &right )
        { BigInt temp( left ); temp += right; return temp; }

    inline BigInt operator-( const BigInt &left, const BigInt &right )
        { BigInt temp( left ); temp -= right; return temp; }

    inline BigInt operator*( const BigInt &left, const BigInt &right )
        { BigInt temp( left ); temp *= right; return temp; }

    inline BigInt operator/( const BigInt &left, const BigInt &right )
        { BigInt temp( left ); temp /= right; return temp; }

    inline BigInt operator%( const BigInt &left, const BigInt &right )
        { BigInt temp( left ); temp %= right; return temp; }


    // The other four relational operators are easily expressed in terms of the two declared
    // above.
    //
    inline bool operator!=( const BigInt &left, const BigInt &right )
        { return !( left == right ); }

    inline bool operator>=( const BigInt &left, const BigInt &right )
        { return !( left < right ); }

    inline bool operator>( const BigInt &left, const BigInt &right )
        { return right < left; }

    inline bool operator<=( const BigInt &left, const BigInt &right )
        { return right >= left; }

} // End of namespace vtsu

#endif
