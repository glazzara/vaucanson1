// element-full-test.cc
//
// VCSN_HEADER

// Goal: 
// - to instantiate all services of element parameterized by empty classes.
//

#include <set>
#include <check/tests_stuff.hh>
#include <fundamental/template_element-test.hh>
#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/alphabets/set_alphabet.hh>


using namespace vcsn;


int main(int argc, char **argv)
{
  
  test_design_pattern<sugar::Alphabets, std::set<char> >(std::set<char>());

//   if (t.all_passed())
//     return EXIT_SUCCESS;
//   else
//     return EXIT_FAILURE;
}

