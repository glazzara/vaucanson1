// tests_stuff.cc
//
//
//

#include "tests_stuff.hh"

namespace tests {

  Tester::Tester(int verbose_level) : 
    passed(0),
    non_passed(0),
    verbose(verbose_level)
  {}

  bool 
  Tester::all_passed() 
  {
    return (non_passed == 0);
  }

  void 
  Tester::ok(const std::string& test_label)
  {
    if (verbose == 1)
      {
	std::cerr << "TEST: ";
	std::cerr.fill(' ') ;
	int last = std::cerr.width(40);
	std::cerr << test_label;
	std::cerr << " : OK" << std::endl;
	std::cerr.width(last);
      }
    passed++;
  }

  void 
  Tester::ko(const std::string& test_label)
  {
    if (verbose == 1)
      {
	std::cerr << "TEST: ";
	std::cerr.fill(' ') ;
	int last = std::cerr.width(40);
	std::cerr << test_label;
	std::cerr << " : KO" << std::endl;
	std::cerr.width(last);
      }
    non_passed++;
  }
  
  // FIXME: Add statistics stuff.

} // tests
