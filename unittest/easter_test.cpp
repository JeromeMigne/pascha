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
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp> // needs boost version 1.59 or higher

#include "../easter.h"
#include <array>
#include <iomanip>

using namespace std;
using namespace boost;
using namespace pascha::gregorian;

BOOST_AUTO_TEST_SUITE(test_gregorian_easter)

BOOST_AUTO_TEST_SUITE(test_invalid_years)

const array<int, 5> invalid_years = {
    INT_MIN, -1, 0, 1582, INT_MAX
};

BOOST_DATA_TEST_CASE(test_invalid_year, unit_test::data::make(invalid_years))
{
    int month = 0, day = 0;
    BOOST_CHECK_LT(get_easter_date(sample, month, day), 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(sample_easters)

struct Date {
    int year, month, day;
};

bool operator==(const Date& lhs, const Date& rhs)
{
    return lhs.year == rhs.year && lhs.month == rhs.month
        && lhs.day == rhs.day;
}

ostream& operator<<(ostream& ostr, const Date& d)
{
    auto flags = ostr.flags();
    ostr << d.year << '-' << setfill('0')
         << setw(2) << d.month << '-' << setw(2) << d.day;
    ostr.flags(flags);
    return ostr;
}

const array<Date, 33> easter_dates{{
    // https://www.census.gov/srd/www/genhol/easter500.html
    // http://tlarsen2.tripod.com/thomaslarsen/easterdates.html
    // https://www.staff.science.uu.nl/~gent0113/easter/easter_text2b.htm
    {1583, 4, 10},
    {1598, 3, 22},
    {1600, 4,  2},
    {1666, 4, 25},
    {1693, 3, 22},
    {1734, 4, 25},
    {1789, 4, 12},
    {1804, 4,  1},
    {1830, 4, 11},
    {1848, 4, 23},
    {1870, 4, 17},
    {1958, 4,  6},
    {1973, 4, 22},
    {2000, 4, 23},
    {2002, 3, 31},
    {2005, 3, 27},
    {2008, 3, 23},
    {2013, 3, 31},
    {2016, 3, 27},
    {2017, 4, 16},
    {2018, 4,  1},
    {2019, 4, 21},
    {2020, 4, 12},
    {2025, 4, 20},
    {2030, 4, 21},
    {2040, 4,  1},
    {2050, 4, 10},
    {2100, 3, 28},
    {2150, 4, 12},
    {2200, 4,  6},
    {2250, 4, 21},
    {2299, 4, 16},

    // D. Knuth: The Art of Computer Programming Volume 1, 1.3.2 exercise 15
    {14250, 4, 14}
}};

BOOST_DATA_TEST_CASE(test_sample, unit_test::data::make(easter_dates))
{
    Date d{sample.year};
    BOOST_CHECK_GE(get_easter_date(d.year, d.month, d.day), 0);
    BOOST_CHECK_EQUAL(d, sample);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
