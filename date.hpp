/****************************************************************************
FILE          : date.h
LAST REVISED  : 2007-07-23
SUBJECT       : Interface to a simple date class
PROGRAMMER    : (C) Copyright 2007 by Peter C. Chapin

This file defines a simple date abstract data type. Date objects will handle dates between Jan
1, 1800 and Dec 31, 2099. Any attempt to set a date object outside that range, either directly
or by way of a computation, will have undefined effects.

The interface to date objects uses 1-based numbering: January is month 1, February is month 2,
and so on. Furthermore, the first day of the month is day 1. Years must be full, four digit
years. Someday it might be nice to make this into a really useful class. For now it makes a good
demonstration of the basics of classes and information hiding.

LICENSE

This program is free software; you can redistribute it and/or modify it under the terms of the
GNU General Public License as published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if
not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307 USA

Please send comments or bug reports to

     Peter C. Chapin
     Computer Information Systems
     Vermont Technical College
     Williston, VT 05495
     PChapin@vtc.vsc.edu
****************************************************************************/

#ifndef DATE_HPP
#define DATE_HPP

#include <iosfwd>

namespace vtc {

    class date {

    public:

        // Default constructor initializes the date to Jan 1, 1970.
        date() { D = 1; M = 1; Y = 1970; }

        // Allows initializing dates to some other value. Note that the year should be a full
        // four digits. This function also performs some sanity checks. It will force the D, M,
        // and Y values into range.
        //
        date(int day, int month, int year)
            { set(day, month, year); }

        // Allows setting a date after it's been constructed. Semantics are just like those of
        // the constructor above.
        //
        void set(int day, int month, int year);

        // Access functions.
        int day()   const { return D; }
        int month() const { return M; }
        int year()  const { return Y; }

        // Operations.

        // Advance the date by given number of days. If delta is negative this function will
        // back the date up.
        //
        void advance(long delta = 1);

    private:

        // The "obvious" implementation.
        int D, M, Y;

        bool is_leap() const;       // True if the current year is a leap year.
        int  month_length() const;  // Number of days in the current month.
        void next();                // Advances the date by one day.
        void previous();            // Backs up the date by one day.

    };

    //
    // Non-member Functions
    //

    bool operator==(const date &left, const date &right);
    bool operator< (const date &left, const date &right);

    // The other relationals can be implemented in terms of the two above.

    inline bool operator!=(const date &left, const date &right)
        { return !(left == right); }

    inline bool operator<=(const date &left, const date &right)
        { return left < right || left == right; }

    inline bool operator>(const date &left, const date &right)
        { return !(left <= right); }

    inline bool operator>=(const date &left, const date &right)
        { return !(left < right); }


    // This function figures out how many days difference there is between two dates.
    //
    long operator-(const date &left, const date &right);

    // I suppose we'll want to do I/O operations too.
    std::ostream &operator<<(std::ostream &output, const date &right);
    std::istream &operator>>(std::istream &input, date &right);
    
} // namespace vtc

#endif
