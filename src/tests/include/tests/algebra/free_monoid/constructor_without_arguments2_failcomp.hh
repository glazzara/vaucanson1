// constructor_without_arguments2_failcomp.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TESTS_ALGEBRA_FREE_MONOID_CONSTRUCTOR_WITHOUT_ARGUMENTS__FAILCOMP_HH
# define VCSN_TESTS_ALGEBRA_FREE_MONOID_CONSTRUCTOR_WITHOUT_ARGUMENTS__FAILCOMP_HH

# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/algebra/concept/freemonoid_base.hh>
# include <tests/design_pattern/design_pattern-test.hh>

template <typename S, typename T>
bool constructor_without_arguments2_failcomp(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef Element<S, T> element_t;

  // This code *should not* compile since building a free monoid without
  // an alphabet has no sense.
  element_t a;

  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_FREE_MONOID_CONSTRUCTOR_WITHOUT_ARGUMENTS__FAILCOMP_HH
