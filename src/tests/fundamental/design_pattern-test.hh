// design_pattern-test.hh
//
//
// $Id$
// VCSN_HEADER

#ifndef DESIGN_PATTERN_TEST_HH
# define DESIGN_PATTERN_TEST_HH

# include <vaucanson/fundamental/element.hh>

template <class Tset, class Tvalue> 
void test_design_pattern()
{
  vcsn::Element<Tset, Tvalue> a;
  vcsn::Element<Tset, Tvalue> b;
  Tvalue		      sample;

  // Comparison operators.
  a == b;
  a != b;
  a < b;
  a > b;
  a <= b;
  a >= b;

  // Comparison operators with implementation.
  a == sample;
  sample == a;
  a != sample;
  sample != a;
  a < sample;
  sample < a;
  a > sample;
  sample > a;
  a <= sample;
  sample <= a;
  a >= sample;
  sample >= a;

  // Arithmetic operators.
  a + b;
  a - b;
  a * b;
  a / b;
  a % b;
  -a;

  // swap(a,a) is ambigus.
}

#endif // DESIGN_PATTERN_TEST_HH
