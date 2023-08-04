/**************************************************************************
FILE          : BigInt.cpp
PROGRAMMER    : Peter Chapin

(C) Copyright 2006 by Peter C. Chapin

This file contains the implementation of the big_int class. See the header file for more
information.
**************************************************************************/

#include <iostream>
#include "BigInt.hpp"

namespace vtsu {

    //
    // BigInt::BigInt
    //
    // The default constructor sets the BigInt to zero.
    //
    BigInt::BigInt( )
    {
        sign = 1;  // Zero is positive.

        for( int i = 0; i < 256; i++ ) {
            digits[i] = 0;
        }
    }


    //
    // BigInt::BigInt( long )
    //
    // This contructor initializes a BigInt with the given number. Negative values are fully
    // supported.
    //
    BigInt::BigInt( long number )
    {
        int i;

        // Set the sign flag appropriately. Make sure number is positive.
        sign = 1;
        if( number < 0 ) {
            sign = -1;
            number = -number;   // TODO: The most negative value has no positive representation.
        }

        // Zero out ALL the digits to start.
        for( i = 0; i < 256; i++ ) {
            digits[i] = 0;
        }

        // Now get the individual digits of number, one at a time.
        i = 0;
        while( number != 0 ) {
            digits[i] = static_cast<short>( number % 10 );
            i++;
            number /= 10;
        }
    }


    //
    // void BigInt::operator+=( const BigInt & )
    //
    // This function adds the right operand into the implicit object It will eventually handle
    // negative numbers correctly as well.
    //
    void BigInt::operator+=(const BigInt &right)
    {
        // If both operands are positive or if both are negative, we just add their absolute
        // values and leave the sign alone. Notice below how I access the left operand's members
        // directly and the right operands members using the dot operator.
        //
        if( sign == right.sign ) {
            short sum, carry = 0;
            for( int i = 0; i < 256; i++ ) {
                sum       = digits[i] + right.digits[i] + carry;
                digits[i] = sum % 10;
                carry     = sum / 10;
            }
            // TODO: Add overflow checking!
        }

        // The signs are different. In that case I really need to subtract.
        else {
            std::cerr << "BigInt::operator+=( ): "
                "Addition of unlike signs not yet implemented!\n";
        }
    }


    //
    // bool operator==( const BigInt &, const BigInt & )
    //
    // Returns true if the two operands are equal.
    //
    bool operator==( const BigInt &left, const BigInt &right )
    {
        // To be equal, they must have the same sign.
        if( left.sign != right.sign ) return false;

        // They must also have all identical digits.
        for( int i = 0; i < 256; i++ ) {
            if( left.digits[i] != right.digits[i] ) return false;
        }
        
        // If I get here, they must be equal.
        return true;
    }

    //
    // bool operator<( const BigInt &, const BigInt & )
    //
    // This function returns true if the left operand is strictly less than the right operand.
    //
    bool operator<( const BigInt &left, const BigInt &right )
    {
        if( left.sign < right.sign ) return true;
        if( left.sign > right.sign ) return false;
        // Here I use the fact that -1 < 1 to check for situations where the two numbers have a
        // different sign. After getting through this the two numbers must have the same sign.

        if( left.sign == 1 ) {
            // The two numbers are both positive.
            for( int i = 255; i >=0; i-- ) {
                if( left.digits[i] < right.digits[i] ) return true;
                if( left.digits[i] > right.digits[i] ) return false;
                // Otherwise these two digits are equal. Let's try the next pair.
            }
        }
        else {
            // The two numbers are both negative.
            for( int i = 255; i >=0; i-- ) {
                if( left.digits[i] < right.digits[i] ) return false;
                if( left.digits[i] > right.digits[i] ) return true;
                // Otherwise these two digits are equal. Let's try the next pair.
            }
        }

        // If I get here the two numbers must have had all equal digits.
        return false;
    }

  
    // 
    // std::ostream &operator<<( std::ostream &os, const BigInt &right )
    //
    // This function writes a BigInt into the given output stream. It properly displays a
    // negative sign, if appropriate. However, it does not deal with the stream's formatting
    // state very well.
    //
    std::ostream &operator<<( std::ostream &os, const BigInt &right )
    {
        int i;

        // Print a minus sign if the number is negative.
        if( right.sign == -1 ) os << "-";

        // Find the first non-zero digit.
        for( i = 255; i >= 0; i-- ) {
            if( right.digits[i] != 0 ) break;
        }

        // If the above loop didn't break, then there were no non-zero digits. Thus the number
        // is 0.
        //
        if( i == -1 ) os << "0";
        else {
            // Print the number, one digit at a time.
            while( i >= 0 ) {
                os << right.digits[i];
                i--;
            }
        }
    }

} // End of namespace vtsu
