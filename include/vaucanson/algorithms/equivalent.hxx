// equivalent.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_EQUIVALENT_HXX
# define VCSN_ALGORITHMS_EQUIVALENT_HXX

# include <vaucanson/algorithms/equivalent.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/is_deterministic.hh>
# include <vaucanson/algorithms/complement.hh>
# include <vaucanson/algorithms/complete.hh>
# include <vaucanson/algorithms/trim.hh>
# include <vaucanson/algorithms/product.hh>

# include <vaucanson/algebra/implementation/series/rat/exp.hh>
# include <vaucanson/misc/usual_macros.hh>


namespace vcsn
{

  template<typename SA, typename A,
	   typename SB, typename B>
  bool
  do_are_equivalent(const AutomataBase<SA>&, const A& a,
		    const AutomataBase<SB>&, const B& b)
  {
    A pos_a(a);
    B pos_b(b);

    if (not is_realtime(pos_a))
      realtime_here(pos_a);
    if (not is_realtime(pos_b))
      realtime_here(pos_b);

    // L(a) = L(b) \iff (L(b) \subset L(a) \land L(a) \subset L(b))

    // L(b) \subset L(a)  \iff   \overline{L(a)}\cap L(b)=\emptyset
    // We compute the latter with complement and product.
    A neg_a(pos_a);
    if (not is_deterministic(neg_a))
      neg_a = determinize(neg_a);
    else if (not is_complete(neg_a))
      complete_here(neg_a);
    complement_here(neg_a);
    if (trim(product(neg_a, pos_b)).states().size() != 0)
      return false;

    // L(a) \subset L(b)  \iff   L(a)\cap\overline{L(b)}=\emptyset
    A neg_b(pos_b);
    if (not is_deterministic(neg_b))
      neg_b = determinize(neg_b);
    else if(not is_complete(neg_b))
      complete_here(neg_b);
    complement_here(neg_b);
    return (trim(product(pos_a, neg_b)).states().size() == 0);
  }


  template<typename S, typename A, typename B>
  bool
  are_equivalent(const Element<S, A>& a, const Element<S, B>& b)
  {
    return do_are_equivalent(a.structure(), a,
			     b.structure(), b);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_EQUIVALENT_HXX
