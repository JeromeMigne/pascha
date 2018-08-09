# Pascha

Compute easter date for a given year from 1583, using Lilius/Clavius algorithm.<br>
Actually the Gregorian easter Sunday date.

In many countries, those of Christian traditions, some public holidays depend
on easter date. The date of this movable feast is defined to be the first
Sunday that follows the 14th day of moon (full moon) that occurs on March&nbsp;21 or
just after; where the days of moon are not determined by astronomical
observations but by a computed calendar.

In the context of the Gregorian calendar reform, mathematician Clavius
established, from previous works of astronomer LiLius, the method for computing
the easter date.

This program, written in C++11, use this algorithm to compute the easter date
for any year from 1583.
The Gregorian calendar was instituted in October 1582, and easter falls either
in March or in April, so the first year for which a Gregorian easter date can
be computed is 1583.

For unit tests, boost version 1.59 or higher is needed.

Licensed under GPLv3.
