/*
 * Copyright (C) 2018 Jerome Migne
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "easter.h"
#include <cassert>

namespace {

// function used to compute remainder of euclidian division
// when the dividend may be negative and the divisor is positive
// % operator give not the mathematical remainder for negative dividends
inline int get_euclidian_remainder(int dividend, int positive_divisor)
{
    assert (positive_divisor > 0);
    // use C99 and C++11 round towards zero feature
    int r = dividend % positive_divisor;
    return r < 0 ? r + positive_divisor : r;
}

}

namespace pascha {

namespace gregorian {

int get_easter_date(int year, int& month, int& day)
{
    if (year < min_easter_year || max_easter_year < year) return -1;

    /*
     * Lilius/Clavius algorithm
     * Reference:
     *   D. Knuth: The Art of Computer Programming Volume 1, 1.3.2 algorithm E.
     */

    // golden number, indicates the year position in a 19-years Metonic cycle
    int g = year % 19 + 1;

    // century number
    int c = year / 100 + 1;

    // correction for leap years: number of dropped leap years
    // one dropped lead year every 100 years except every 400 years
    // offset -12 to obtain 0 for 16th century
    int x = 3 * c / 4 - 12;

    // correction for Metonic cycle which is not exactly 19 years
    int z = (8 * c + 5) / 25 - 5;

    // d modulo 7 gives the weekday number (0 for sunday) of March 21
    // advance 5 days every 4 years,
    // substract one day for each dropped leap years
    // for the offset:
    //   (5 * 1583 / 4) % 7 = 4 which is the weekday number of March 31, 1583
    //   and March 21, 1583 is 10 days before
    int d = 5 * year / 4 - x - 10;

    // epact: age of the ecclesiastical moon on January 1
    int e = get_euclidian_remainder(11 * g + 20 + z - x, 30);
    if (e == 25 && g > 11 || e == 24) {
        e++;
    }

    // full (ecclesiastical not astronomical) moon
    // that occurs on March 21 or just after
    // day number from March 1, counting from 1
    int n = 44 - e;
    if (n < 21) {
        // when before March 21 append one synodic month of 30 days
        n += 30;
    }

    // first sunday just after the full moon
    // to obtain first sunday just after n:
    //   advance 7 days and substract weekday number (offset from sunday) of n
    // the weekday number (0 for sunday) of n is (d + n) modulo 7:
    //   weekday number of n is weekday number of March 21 plus number of days
    //   elapsed for n since March 21, modulo 7
    //   and n - 21 = n modulo 7
    // NB d and n are positive so (d + n) % 7 is the mathematical remainder
    //   for n: 0 <= e < 29 so 21 <= n < 50
    //   for d:
    //     c = floor(year/100.0) + 1
    //     so c <= year / 100.0 + 1
    //     so floor(3 * c / 4.0) <= (3 * year / 100.0 + 3) / 4.0
    //     so -x >= -(3 * year / 100.0 + 3) / 4.0 + 12
    //     floor(5 * year / 4.0) + 1 > 5 * year / 4.0
    //     so floor(5 * year / 4.0) + 1 - x - 11 >
    //        5 * year / 4.0 - (3 * year / 100.0 + 3) / 4.0 + 12 - 11
    //     so d > 497 * year / 400.0 + 1.75 > 0
    n += 7 - (d + n) % 7;

    if (n <= 31) {
        month = 3;
        day = n;
    }
    else {
        month = 4;
        day = n - 31;
    }

    return 0;
}

}

}
