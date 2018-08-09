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
#include <climits>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include "easter.h"

using namespace std;
using namespace pascha::gregorian;

namespace {

void print_help()
{
    cout << "Compute Gregorian easter Sunday date given a year,"
            " using Lilius/Clavius algorithm.\n"
            "Argument: the year for which the easter date is computed,\n"
            "should be between " << min_easter_year << " and "
         << max_easter_year << " inclusive." << endl;
}

}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        print_help();
        return EXIT_FAILURE;
    }

    char* end = nullptr;
    auto input = strtol(argv[1], &end, 10);
    if (end == argv[1]) {
        print_help();
        return EXIT_FAILURE;
    }
    // saturate in case sizeof(long) > sizeof(int)
    int year = max<long>(INT_MIN, min<long>(input, INT_MAX));

    int month = 0, day = 0;
    if (get_easter_date(year, month, day) < 0) {
        print_help();
        return EXIT_FAILURE;
    }

    cout << year << '-' << setfill('0')
         << setw(2) << month << '-'
         << setw(2) << day << endl;

    return EXIT_SUCCESS;
}
