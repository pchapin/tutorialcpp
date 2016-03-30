/**************************************************************************
FILE          : big_int.hpp
PROGRAMMER    : Peter C. Chapin
LAST REVISION : 2006-05-26

(C) Copyright 2006 by Peter C. Chapin

This file contains the interface to a "big" integer class. Objects of this class act just like
normal integers but they can hold far larger values.

Please send comments or bug reports to

     Peter C. Chapin
     Computer Information Systems
     Vermont Technical College
     Williston, VT 05495
     PChapin@vtc.vsc.edu
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
// This header contains declarations of the classes std::ostream and std::istream without
// bringing in all the gory details of the iostreams header. It thus compiles faster and is the
// better choice when one only wants to declare references to certain stream classes.

namespace vtc {

    class big_int {
        // I/O operations.
        friend std::ostream &operator<<(std::ostream &, const big_int &);
        friend std::istream &operator>>(std::istream &, big_int &);

        // Relational operators.
        friend bool operator==(const big_int &, const big_int &);
        friend bool operator< (const big_int &, const big_int &);

    public:
        // Default constructor.
        big_int();

        // Allows a big_int to be initialized with a normal int.
        big_int(long number);

        void operator+=(const big_int &);
        void operator-=(const big_int &);
        void operator*=(const big_int &);
        void operator/=(const big_int &);
        void operator%=(const big_int &);
        // All the usual math operations.
        
    private:
        int   sign;          // -1 for negative, +1 for zero or positive.
        short digits[256];   // digits[0] is the least significant digit.
    };


    // The binary math operators are easily expressed in terms of the in place operators
    // declared above.
    //
    inline big_int operator+(const big_int &left, const big_int &right)
        { big_int temp(left); temp += right; return temp; }

    inline big_int operator-(const big_int &left, const big_int &right)
        { big_int temp(left); temp -= right; return temp; }

    inline big_int operator*(const big_int &left, const big_int &right)
        { big_int temp(left); temp *= right; return temp; }

    inline big_int operator/(const big_int &left, const big_int &right)
        { big_int temp(left); temp /= right; return temp; }

    inline big_int operator%(const big_int &left, const big_int &right)
        { big_int temp(left); temp %= right; return temp; }


    // The other four relational operators are easily expressed in terms of the two declared
    // above.
    //
    inline bool operator!=(const big_int &left, const big_int &right)
        { return !(left == right); }

    inline bool operator>=(const big_int &left, const big_int &right)
        { return !(left < right); }

    inline bool operator>(const big_int &left, const big_int &right)
        { return right < left; }

    inline bool operator<=(const big_int &left, const big_int &right)
        { return right >= left; }

} // End of namespace vtc

#endif
