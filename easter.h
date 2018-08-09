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

namespace pascha {

namespace gregorian {

/** Minimum year for which a gregorian easter date is available.
 *  Gregorian calendar was instituted in October 1582, and easter falls either
 *  in March or in April, so the first year for which a gregorian easter date
 *  can be computed is 1583.
 */
constexpr int min_easter_year = 1583;

/** Maximum year for which a gregorian easter date can be computed.
 *  This value is theorical (the computing rules may change),
 *  and is for avoiding overflow.
 */
constexpr int max_easter_year = INT_MAX / 5;

/** Compute gregorian easter sunday date for a given year.
 *
 * @param[in]  year   The year for which the easter date is computed.
 * @param[out] month  The resulted easter month either 3 for March or 4 for April.
 * @param[out] day    The resulted day of month, between 1 and 31.
 *
 * @return 0 for success or -1 when year is not valid.
 */
int get_easter_date(int year, int& month, int& day);

}

}
