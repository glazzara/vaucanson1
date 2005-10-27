// partial_rat_exp_constant_term.hxx: this file is part of the Vaucanson project.
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
// `COPYING' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_CONSTANT_TERM_HXX
# define VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_CONSTANT_TERM_HXX

# include <utility>
# include <vaucanson/algorithms/internal/partial_rat_exp_constant_term.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>

namespace vcsn {

  template <class Series, class T>
  std::pair<typename Element<Series, T>::semiring_elt_t, bool>
  constant_term(const PartialExp<Series, T>& exp)
  {
    typedef typename PartialExp<Series, T>::const_iterator	const_iterator;
    typedef typename PartialExp<Series, T>::semiring_elt_t	semiring_elt_t;
    typedef typename PartialExp<Series, T>::series_set_elt_value_t
      series_set_elt_value_t;
    typedef std::pair<typename Element<Series, T>::semiring_elt_t, bool>
      result_t;
    
    const_iterator	i = exp.begin();
    semiring_elt_t 	res = i.semiring_elt();
    bool		defined = true;

    for (i++; i != exp.end() && defined; ++i)
    {
      if (i.on_node())
      {
        result_t tmp = constant_term(
	  Element<Series, T>(exp.exp_structure(),
	   		     series_set_elt_value_t (i.node())));
	defined = tmp.second;
	res *= tmp.first;
      }
      else
	res *= i.semiring_elt();
    }
    return std::make_pair(res, defined);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_CONSTANT_TERM_HXX
