// element-full-test.cc
//
// $Id$
// VCSN_HEADER

// Goal: 
// - to instantiate all services of element parameterized by dummy classes.
//

#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/alphabets/set_alphabet.hh>

#include <check/tests_stuff.hh>
#include <fundamental/design_pattern-test.hh>

namespace vcsn {

  struct Natural : public Structure<Natural> 
  { 
    Natural() 
    {}

    bool operator == (const Natural& other) const 
    { 
      return true; 
    }
  };
  
  template<typename T>
  struct MetaElement<Natural, T>
    : MetaElement<Structure<Natural>, T>
  {
  protected:
    MetaElement() 
    {};

    MetaElement(const MetaElement& other) :
      MetaElement<Structure<Natural>, T>(other)
    {};
  };

  int op_add(const vcsn::Natural& set, int v1, int v2)
  { 
    return v1 + v2; 
  }

  int op_sub(const vcsn::Natural& set, int v1, int v2)
  { 
    return v1 - v2; 
  }

  int op_mul(const vcsn::Natural& set, int v1, int v2)
  { 
    return v1 * v2; 
  }

  int op_div(const vcsn::Natural& set, int v1, int v2)
  { 
    // To avoid "floating-point exception."
    return v1 / 1; 
  }

  int op_mod(const vcsn::Natural& set, int v1, int v2)
  { 
    // To avoid "floating-point exception."
    return v1 % 1; 
  }

  vcsn::Element<Natural, int> op_neg(const vcsn::Natural& set, int v)
  { 
    return Element<Natural, int>(-v); 
  } 

} // vcsn

using namespace vcsn;

int main(int argc, char **argv)
{
  test_design_pattern<Natural, int>();  
  
  return EXIT_SUCCESS;
}

