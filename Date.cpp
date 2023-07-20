/****************************************************************************
FILE          : Date.cpp
LAST REVISED  : 2023-07-20
SUBJECT       : Implementation of date handling abstract data type
PROGRAMMER    : (C) Copyright 2023 by Peter Chapin

The implementation is based on the "obvious" representation. This representation makes it easy
to do I/O on dates (the construction and access functions are trivial), but difficult to do
calculations on dates (the math functions are complicated and slow).

This class artificially limits the Date to the range Jan 1, 1800 through Dec 31, 2099. There is
no technical reason for this range. It is aribitrary. The assumption is that dates outside of
this range are probably errors and should be handled as such. Also this range avoids the
calendar reform issue.

The constructors ensure that the Date object is initialized to be inside the required range.
However, the advance() method does not deal with out of range errors. This is a bug and should
be fixed.

This implementation is rather crude. The math functions do not have to be as slow as they are,
but to do better would require thought. On the other hand, this class is very easy to use
because it is so simple.
****************************************************************************/

#include <iostream>
#include <iomanip>

#include "Date.hpp"

namespace vtsu {

    //------------------------------------
    //           Private Methods
    //------------------------------------

    //
    // Date::is_leap( ) const
    //
    // This function returns true if the year is a leap year.
    //
    bool Date::is_leap( ) const
    {
        bool result = false;

        if(           (Y %   4 == 0) ) result = true;
        if( result && (Y % 100 == 0) ) result = false;
        if(!result && (Y % 400 == 0) ) result = true;

        return result;
    }


    //
    // Date::month_length( ) const
    //
    // This function returns the number of days in the current month.
    //
    int Date::month_length( ) const
    {
        // Lookup table gives number of days in each month.
        static const int month_lengths[] = {
            31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
        };

        int length = month_lengths[M - 1];

        // Now perhaps make a correction if the month is Feb.
        if ( M == 2 && is_leap( ) ) length++;

        return length;
    }


    //
    // Date::next( )
    //
    // This function has to deal with the fact that the number of days in each month is
    // different. Furthermore, the number of days in Feb is a function of the year.
    //
    void Date::next( )
    {
        // Try incrememting the day. If it overflows the month, make a correction.
        if( ++D > month_length( ) ) {
            D = 1;
            if( ++M > 12 ) {
                M = 1;
                ++Y;
            }
        }
    }
    

    //
    // Date::previous( )
    //
    // This function works similarly to Date::next().
    //
    void Date::previous( )
    {
        bool fix_day = false;

        // Try decrementing the day.
        if( --D < 1 ) {
            fix_day = true;
            if( --M < 1 ) {
                M = 12;
                --Y;
            }
        }

        // If we wrapped over a month boundary, set the day to the last day of the new (and now
        // current) month.
        //   
        if( fix_day ) D = month_length( );
    }


    //-----------------------------------
    //           Public Methods
    //-----------------------------------

    //
    // Date::set( int, int, int )
    //
    // This function initializes the Date to values given to us by the client. We don't trust
    // the client to give us sensible values.
    //
    void Date::set( int day, int month, int year )
    {
        D = day; M = month; Y = year;

        // If we get a year < 100 it probably means the client is giving us just a two digit
        // year. We will take any two digit year below 50 to mean 2000 to 2050. This hack will
        // help make this date class well behaved even when two digit years are used.
        //
        if( Y < 100 ) {
            if( Y < 50 ) Y += 2000;
            else Y += 1900;
        }

        // Year check. If the client gives us a year that's really far off, it's probably an
        // error. We'll deal with that by just artificially restricting the year.

        if( Y < 1800 ) Y = 1800;
        if( Y > 2099 ) Y = 2099;

        // Month Check. It would be cooler to advance the Date appropriately so that, for
        // example, the 13th month would end up being the first month of the next year. However,
        // I don't see why we should make excuses for the client's errors. :)
        
        if( M <  1 ) M =  1;
        if( M > 12 ) M = 12;

        // Day Check.

        if( D < 1 ) D = 1; 
        if( D > month_length( ) ) D = month_length( );
    }
    

    //
    // Date::advance( long )
    //
    // This function advances (or backs up) a Date by the specified number of days. This
    // implementation is highly inefficient although it will come up with the right answer
    // eventually.
    //
    void Date::advance( long delta )
    {
        long count;

        // If delta == 0 we're done already.
        if( delta == 0 ) return;

        // If we're trying to step forward...
        if( delta >  0 ) {
            for( count = delta; count > 0; count-- ) next( );
        }

        // We're trying to step backward... 
        else {
            for( count = -delta; count > 0; count-- ) previous( );
        }
    }


    //-----------------------------------
    //           Free Functions
    //-----------------------------------

    //
    // operator==( const date &, const date & )
    //
    // Returns true if two dates are equal. This function does not need to be a friend because
    // it does not attempt to access the private section of Date. It will continue to work even
    // if the implementation of Date is changed.
    //
    bool operator==( const date &left, const date &right )
    {
        if(left.year( )  == right.year( )  &&
           left.month( ) == right.month( ) &&
           left.day( )   == right.day( )     ) return 1;
        
        return 0;
    }


    //
    // operator<( const date &, const date & )
    //
    // Returns true if the left operand is before the right operand.
    //
    bool operator<( const date &left, const date &right )
    {
        if( left.year( ) <  right.year( ) ) return 1;
        if( left.year( ) == right.year( ) ) {
            if( left.month( ) <  right.month( ) ) return 1;
            if( left.month( ) == right.month( ) ) {
                if( left.day( ) <  right.day( ) ) return 1;
            }
        }
        return 0;
    }


    //
    // operator-( const date &, const date & )
    //
    // This function is also way slow. But it will come up with the right answer.
    //
    long operator-( const date &left, const date &right )
    {
        long result = 0;

        // Handle the simple case first.
        if( left == right ) return 0;

        // Make copies of the parameters that I can change.
        Date my_left  = left;
        Date my_right = right;

        // If my_right is small, advance it until it matches my_left.
        while( my_left > my_right ) {
            my_right.advance( 1 );
            result++;
        }

        // If my_left is small, advance it until it matches my_right.
        while( my_right > my_left ) {
            my_left.advance( 1 );
            result--;
        }

        return result;
    }


    //
    // operator<<( std::ostream &, const date & )
    //
    // This function writes a Date object onto the given output stream using the format
    // yyyy-mm-dd. Four digit years are used for y2k reasons. This format can't currently be
    // controlled.

    // Notice also that this function changes the fill character setting for the stream. This is
    // an undesirable side effect. A future version should probably manage all relevant settings
    // more appropriately.
    //
    std::ostream &operator<<( std::ostream &output, const date &right )
    {
        output << std::setfill( '0' );
        output << std::setw( 4 ) << right.year( )  << '-';
        output << std::setw( 2 ) << right.month( ) << '-';
        output << std::setw( 2 ) << right.day( );

        return output;
    }


    //
    // operator>>( std::istream &, date & )
    //
    // This function reads a Date object from an input stream. It expects the same format as is
    // used by the output function (see above). We should probably verify that we got '-'
    // characters for dummy. On the other hand, this function's ability to accept a variety of
    // different separators could be regarded as a feature!
    //
    std::istream &operator>>( std::istream &input, date &right )
    {
        int  day, month, year;
        char dummy;

        input >> year >> dummy >> month >> dummy >> day;
        right.set( day, month, year );

        return input;
    }

} // namespace vtc
