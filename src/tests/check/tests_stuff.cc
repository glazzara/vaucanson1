// tests_stuff.cc
//
//
//

#include "tests_stuff.hh"

namespace tests {

  const unsigned Tester::nb_col_msg = 60;

  Tester::Tester(verbose_level_e verbose_level) : 
    passed_ (0),
    non_passed_(0),
    verbose_(verbose_level)
  {}

  bool 
  Tester::all_passed() 
  {
    return (non_passed_ == 0);
  }

  void 
  Tester::ok(std::string test_label)
  {
    if (verbose_ != none)
      {
	std::cout << "TEST: ";
	std::cout.fill(' ') ;
	int last = std::cout.width(nb_col_msg);
	std::cout << test_label;
	std::cout << " : OK" << std::endl;
	std::cout.width(last);
      }
    passed_++;
  }

  void 
  Tester::ko(std::string test_label)
  {
    if (verbose_ != none)
      {
	std::cout << "TEST: ";
	std::cout.fill(' ') ;
	int last = std::cout.width(nb_col_msg);
	std::cout << test_label;
	std::cout << " : KO" << std::endl;
	std::cout.width(last);
      }
    non_passed_++;
  }
  
  verbose_level_e Tester::verbose() const
  {
    return verbose_;
  }

  // FIXME: Add statistics stuff.

} // tests
