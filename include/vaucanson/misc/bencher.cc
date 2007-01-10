# if TEST_BENCHER

# include <iostream>
# include <vaucanson/misc/bencher.hh>
# include <fstream>

using namespace vcsn;
using namespace misc;
using namespace std;

/// Test the bencher.
int
main ()
{
  Bencher b;
  misc::Timer timer;
  enum timevar
    {
      One = 1,
      Two,
      Three,
      Four
    };

  ofstream outfile;
  outfile.open ("test.plot", ofstream::out | ofstream::trunc);

  for (int i = 1; i <= 2; i++)
  {
    timer.clear();

    timer.name (One, "One");
    timer.name (Two, "Two");
    timer.name (Three, "Three");
    timer.name (Four, "Four");

    timer.start ();

    timer.push (One);
    sleep (1);

    timer.push ("Two");
    sleep (1);
    timer.push ("Four");
    sleep (1);

    timer.pop ("Four");
    timer.pop ("Two");
    timer.pop (1);

    timer.push ("Three");
    sleep (1);
    timer.pop (Three);

    timer.stop ();
    b.push (timer);
  }
  b.finalize();
  b.print(std::cerr);
  b.plot(outfile);

  outfile.close();
  return 0;
}

# endif

/// g++ -I ../.. -I ../../../_build/include -DTEST_BENCHER timer.cc bencher.cc -o test-bencher -Wall && ./test-bencher
