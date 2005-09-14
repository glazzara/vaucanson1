// element-full-test.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#include <vaucanson/design_pattern/design_pattern.hh>

#include <check/tester.hh>
#include <design_pattern/design_pattern-test.hh>

namespace vcsn_test {

  struct Natural : public vcsn::Structure<Natural>
  {
    Natural()
    {}

    bool operator == (const Natural&) const
    {
      return true;
    }
  };

}

namespace vcsn {

  template <>
  struct dynamic_traits<vcsn_test::Natural> :
    public dynamic_traits< Structure<vcsn_test::Natural> >
  {
  };

  template<typename T>
  struct MetaElement<vcsn_test::Natural, T>
    : MetaElement<Structure<vcsn_test::Natural>, T>
  {
  protected:
    MetaElement()
    {};

    MetaElement(const MetaElement& other) :
      MetaElement<Structure<vcsn_test::Natural>, T>(other)
    {};
  };

  int op_add(const vcsn_test::Natural&, int v1, int v2)
  {
    return v1 + v2;
  }

  int op_sub(const vcsn_test::Natural&, int v1, int v2)
  {
    return v1 - v2;
  }

  int op_mul(const vcsn_test::Natural&, int v1, int v2)
  {
    return v1 * v2;
  }

  int op_div(const vcsn_test::Natural&, int v1, int)
  {
    // To avoid "floating-point exception."
    return v1 / 1;
  }

  int op_mod(const vcsn_test::Natural&, int v1, int)
  {
    // To avoid "floating-point exception."
    return v1 % 1;
  }

  vcsn::Element<vcsn_test::Natural, int>
  op_neg(const vcsn_test::Natural& set, int v)
  {
    return Element<vcsn_test::Natural, int>(set, -v);
  }

} // vcsn

int main(int, char **)
{
  using namespace vcsn;
  using namespace vcsn_test;

  Natural n;

  test_design_pattern<Natural, int>(n);

  return EXIT_SUCCESS;
}

