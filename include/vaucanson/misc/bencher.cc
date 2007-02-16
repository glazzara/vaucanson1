/*
 * Copyright (C) 2007  The Vaucanson Group.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
 * USA.
 */

# if TEST_BENCHER

# include <iostream>
# include <vaucanson/misc/bencher.hh>
# include <fstream>

# define msleep(MilliSecond) usleep(MilliSecond * 1000)

/// Test the bencher.
int
main ()
{
  misc::Bencher b;
  misc::Timer timer;
  enum timevar
    {
      One = 1,
      Two,
      Three,
      Four
    };

  std::ofstream outfile;
  outfile.open ("test.plot", std::ofstream::out | std::ofstream::trunc);

  for (int i = 0; i < 10; i++)
  {
    timer.clear();

    timer.name (One, "One");
    timer.name (Two, "Two");
    timer.name (Three, "Three");
    timer.name (Four, "Four");

    timer.start ();

    timer.push (One);
    msleep (i * 10);

    timer.push ("Two");
    msleep (i * 10);
    timer.push ("Four");
    msleep (i * 10);

    timer.pop ("Four");
    timer.pop ("Two");
    timer.pop (1);

    timer.push ("Three");
    msleep (i * 10);
    timer.pop (Three);

    timer.stop ();
    b.push (timer);
  }
  b.print(std::cerr);
  b.plot(outfile);

  outfile.close();
  return 0;
}

# endif

/// Local Variables:
/// compile-command: "g++ -I ../.. -I ../../../_build/include -DTEST_BENCHER timer.cc bencher.cc -o test-bencher -Wall && ./test-bencher"
/// End:
