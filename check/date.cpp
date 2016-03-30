/****************************************************************************
FILE          : date.cpp
LAST REVISED  : 2006-05-26
SUBJECT       : Implementation of date abstract data type
PROGRAMMER    : (C) Copyright 2006 by Peter C. Chapin

The implementation is based on the "obvious" representation. This
representation makes it easy to do I/O on dates (the construction and
access functions are trivial), but difficult to do calculations on dates
(the math functions are complicated and slow).

This class artificially limits the date to the range Jan 1, 1800 through
Dec 31, 2099. There is no technical reason for this range. It is
aribitrary. The assumption is that dates outside of this range are
probably errors and should be handled as such. Also this range avoids
the whole calendar reform issue.

The constructor functions insure that the date object is initialized to
be inside the required range. However, the advance() function does not
deal with out of range errors. This is a bug and should be fixed.

This implementation is rather crude. The math functions do not have to
be as slow as they are, but to do better would be too much like work. On
the other hand, this class is very easy to use because it is so simple
(some might say stupid).

LICENSE

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANT-
ABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

Please send comments or bug reports to

     Peter C. Chapin
     Electrical and Computer Engineering Technology Department
     Vermont Technical College
     Randolph Center, VT 05061
     Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include <iostream>
#include <iomanip>

#include "date.h"

  //---------------------------------------------
  //           Private Member Functions
  //---------------------------------------------
    
  //
  // Date::is_leap() const
  //
  // This function returns true if the year is a leap year.
  //
    bool Date::is_leap() const
  {
    bool result = false;

    if (           (Y %   4 == 0)) result = true;
    if ( result && (Y % 100 == 0)) result = false;
    if (!result && (Y % 400 == 0)) result = true;

    return result;
  }


  //
  // Date::month_length() const
  //
  // This function returns the number of days in the current month.
  //
  int Date::month_length() const
  {
    // Lookup table gives number of days in each month.
    static const int month_lengths[] = {
      31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    int length = month_lengths[M - 1];

    // Now perhaps make a correction if the month is Feb.
    if (M == 2 && is_leap()) length++;

    return length;
  }


  //
  // Date::next()
  //
  // This function has to deal with the fact that the number of days in
  // each month is different. Furthermore, the number of days in Feb is a
  // function of the year.
  //
  void Date::next()
  {
    // Try incrememting the day. If it overflows the month, make a correction.
    if (++D > month_length()) {
      D = 1;
      if (++M > 12) {
        M = 1;
        ++Y;
      }
    }
  }


  //
  // Date::previous()
  //
  // This function works similarly to Date::next().
  //
  void Date::previous()
  {
    bool fix_day = false;

    // Try decrementing the day.
    if (--D < 1) {
      fix_day = true;
      if (--M < 1) {
        M = 12;
        --Y;
      }
    }

    // If we wrapped over a month boundary, set the day to the last day of
    // the new (and now current) month.
    //   
    if (fix_day) D = month_length();
  }


  //--------------------------------------------
  //           Public Member Functions
  //--------------------------------------------

  //
  // Date::set(int, int, int)
  //
  // This function initializes the date to values given to us by the
  // client. We don't trust the client to give us sensible values.
  //
  void Date::set(int year, int month, int day)
  {
    Y = year; M = month; D = day;

    // If we get a year < 100 it probably means the client is giving us
    // just a two digit year. We will take any two digit year below 50 to
    // mean 2000 to 2050. This hack will help make this date class well
    // behaved even when two digit years are used (by silly people).
    //
    if (Y < 100) {
      if (Y < 50) Y += 2000;
      else Y += 1900;
    }

    // Year check. If the client gives us a year that's really far off,
    // it's probably an error. We'll deal with that by just artificially
    // restricting the year.

    if (Y < 1800) Y = 1800;
    if (Y > 2099) Y = 2099;

    // Month Check. It would be cooler to advance the date appropriately so
    // that, for example, the 13th month would end up being the first month
    // of the next year. However, I don't see why we should make excuses
    // for the client's errors. The point of this is just to be sure that
    // our class doesn't get blamed for dumping core.

    if (M <  1) M =  1;
    if (M > 12) M = 12;

    // Day Check.

    if (D < 1 ) D = 1;
    if (D > month_length()) D = month_length();
  }


  //
  // Date::advance(long)
  //
  // This function advances (or backs up) a date by the specified number of
  // days. This implementation is highly inefficient although it will come
  // up with the right answer eventually.
  //
  void Date::advance(long delta)
  {
    long count;

    // If delta == 0 we're done already.
    if (delta == 0) return;

    // If we're trying to step forward...
    if (delta >  0) {
      for (count = delta; count > 0; count--) next();
    }

    // We're trying to step backward... 
    else {
      for (count = -delta; count > 0; count--) previous();
    }
  }


  //-----------------------------------------
  //           Non-Member Functions
  //-----------------------------------------

  //
  // operator==(const Date &, const Date &)
  //
  // Returns true if two dates are equal. This function does not need to be
  // a friend because it does not attempt to access the private section of
  // date. It will continue to work even if the implementation of date is
  // changed.
  //
  bool operator==(const Date &left, const Date &right)
  {
    if (left.year()  == right.year()  &&
        left.month() == right.month() &&
        left.day()   == right.day()     ) return 1;

    return 0;
  }


  //
  // operator<(const Date &, const Date &)
  //
  // Returns true if the left operand is before the right operand.
  //
  bool operator<(const Date &left, const Date &right)
  {
    if (left.year() <  right.year()) return 1;
    if (left.year() == right.year()) {
      if (left.month() <  right.month()) return 1;
      if (left.month() == right.month()) {
        if (left.day() <  right.day()) return 1;
      }
    }
    return 0;
  }


  //
  // operator-(const Date &, const Date &)
  //
  // This function is also way slow. But it will come up with the right
  // answer.
  //
  long operator-(const Date &left, const Date &right)
  {
    long result = 0;

    // Handle the simple case first.
    if (left == right) return 0;

    // Make copies of the parameters that I can change.
    Date my_left  = left;
    Date my_right = right;

    // If my_right is small, advance it until it matches my_left.
    while (my_left > my_right) {
      my_right.advance(1);
      result++;
    }

    // If my_left is small, advance it until it matches my_right.
    while (my_right > my_left) {
      my_left.advance(1);
      result--;
    }

    return result;
  }


	//
	// operator<<( std::ostream &, const Date & )
	//
	// This function writes a date object onto the given output stream using
	// the format yyyy-mm-dd. Four digit years are used for y2k reasons. This
	// format can't currently be controlled.
	//
	std::ostream &operator<<( std::ostream &output, const Date &right )
	{
		char original_fill = output.fill( );
		int  overall_width = output.width( );

		output << std::setfill( '0' );
		output << std::setw( 4 ) << right.year( )  << '-';
		output << std::setw( 2 ) << right.month( ) << '-';
		output << std::setw( 2 ) << right.day( );
		output << std::setfill( original_fill );

		for( int i = 10; i < overall_width; ++i ) {
			output << original_fill;
		}

		return output;
	}


  //
  // operator>>(std::istream &, Date &)
  //
  // This function reads a date from an input stream. It expects the same
  // format as is used by the output function (see above). We should
  // probably at least verify that we got '-' characters for dummy, but I'm
  // too lazy. On the other hand, this function's ability to accept a
  // variety of different separators could be regarded as a feature!
  //
  std::istream &operator>>(std::istream &input, Date &right)
  {
    int  day, month, year;
    char dummy;

    input >> year >> dummy >> month >> dummy >> day;
    right.set(year, month, day);

    return input;
  }
