// krat_exp_partial_derivation_common.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_PARTIAL_DERIVATION_KRAT_EXP_PARTIAL_DERIVATION_COMMON_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_PARTIAL_DERIVATION_KRAT_EXP_PARTIAL_DERIVATION_COMMON_HH

# include <iostream>

template <typename T>
std::ostream& operator<<(std::ostream& o, const std::set<T>& s)
{
  typename std::set<T>::iterator i = s.begin();
  o << "{";
  if (i != s.end())
  {
    o << *i;
    for (++i; i != s.end(); ++i)
      o << "," << *i;
  }
  o << "}";
  return o;
}

#endif // ! VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_PARTIAL_DERIVATION_KRAT_EXP_PARTIAL_DERIVATION_COMMON_HH
