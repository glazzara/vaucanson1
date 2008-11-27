// free_monoid.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_HXX

# include <vaucanson/algebra/implementation/monoid/free_monoid.hh>

namespace vcsn
{
  namespace algebra
  {
    inline
    monoid_rep<FreeMonoid<Element<AlphabetSet<int>, std::set<int> > > >::monoid_rep()
    {
      maybe_epsilon.clear();

      // Sane defaults.
      maybe_epsilon.push_back("e");
      maybe_epsilon.push_back("1");

      // Trying with more than one char.
      maybe_epsilon.push_back("_e");
      maybe_epsilon.push_back("eps");

      empty = *(maybe_epsilon.begin());
      concat = "#";
    }

    /*--------------.
    | FreeMonoid<A> |
    `--------------*/

    template <class A>
    FreeMonoid<A>::FreeMonoid(const A& a) :
      rep_(monoid_rep_default<FreeMonoid<A> >::get_instance()),
      alph_(a)
    {
      // Type helpers.
      typedef typename A::letter_t letter_t;
      typedef std::vector<std::string>::const_iterator iterator_t;
      typedef monoid_rep<FreeMonoid<A> > monoid_rep_t;

      monoid_rep_t rep;

      for (iterator_t empty_it = rep.maybe_epsilon.begin();
	   empty_it != rep.maybe_epsilon.end();
	   ++empty_it)
      {
	bool found = true;

	for_all_const_(A, i, a)
	{
	  if (letter_traits<letter_t>::letter_to_literal(*i) == *empty_it)
	  {
	    found = false;
	    break;
	  }
	}

	// Best match.
	if (found)
	{
	  rep.empty = *empty_it;
	  break;
	}
      }

      set_representation(rep);
    }

    template <class A>
    FreeMonoid<A>::FreeMonoid(const A& a,
			      monoid_rep<FreeMonoid<A> > mr) :
      rep_(boost::shared_ptr<monoid_rep<FreeMonoid<A> > >(
	new monoid_rep<FreeMonoid<A> > (mr))),
      alph_(a)
    {
    }

    template <class A>
    FreeMonoid<A>::FreeMonoid(const FreeMonoid& w) :
      FreeMonoidBase<FreeMonoid<A> >(w),
      rep_(w.rep_),
      alph_(w.alph_)
    {
    }

    template <class A>
    const boost::shared_ptr<monoid_rep<FreeMonoid<A> > >
    FreeMonoid<A>::representation() const
    {
      return rep_;
    }

    template <class A>
    void
    FreeMonoid<A>::set_representation(monoid_rep<FreeMonoid<A> > mr)
    {
      rep_ = boost::shared_ptr<monoid_rep<FreeMonoid<A> > >(new monoid_rep<FreeMonoid<A> > (mr));
    }

    template <class A>
    A& FreeMonoid<A>::alphabet()
    {
      return alph_;
    }

    template <class A>
    const A& FreeMonoid<A>::alphabet() const
    {
      return alph_;
    }

    template<typename A>
    bool operator==(const FreeMonoid<A>& a,
		    const FreeMonoid<A>& b)
    {
      return (a.alphabet() == b.alphabet()) &&
	     (a.representation() == b.representation());
    }

  } // ! algebra

} // ! vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_HXX
