// monoid_rep_base.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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

#ifndef VCSN_ALGEBRA_IMPLEMENTATION_MONOID_MONOID_REP_BASE_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_MONOID_MONOID_REP_BASE_HXX

# include <vaucanson/algebra/implementation/monoid/monoid_rep_base.hh>

namespace vcsn
{
  namespace algebra
  {
    template <template <typename> class S, typename T>
    MonoidRepBase<S, T>::MonoidRepBase()
    {
      self_t* self = static_cast<self_t*>(this);

      // Sane defaults.
      self->maybe_epsilon.push_back("1");
      self->maybe_epsilon.push_back("e");

      // Trying with more than one char.
      self->maybe_epsilon.push_back("_e");
      self->maybe_epsilon.push_back("eps");

      self->empty = *(self->maybe_epsilon.begin());
      self->concat = "";
    }

    template <template <typename> class S, typename T>
    void
    MonoidRepBase<S, T>::disambiguate(const monoid_t& monoid, pointer_t& orig)
    {
      // Type helpers.
      typedef typename monoid_t::alphabet_t	alphabet_t;
      typedef typename alphabet_t::letter_t	letter_t;

      self_t* self = static_cast<self_t*>(this);

      // Type helpers.
      typedef std::vector<std::string>::const_iterator iterator_t;

      self_t new_rep = *self;

      for (iterator_t empty_it = new_rep.maybe_epsilon.begin();
	   empty_it != new_rep.maybe_epsilon.end();
	   ++empty_it)
      {
	bool found = true;

	for_all_const_(alphabet_t, i, monoid.alphabet())
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
	  // Copy on write.
	  if (new_rep.empty != *empty_it)
	  {
	    new_rep.empty = *empty_it;
	    orig = pointer_t(new self_t(new_rep));
	  }
	  break;
	}
      }
    }

    template <template <typename> class S, typename T>
    bool
    operator==(boost::shared_ptr<MonoidRepBase<S, T> > lhs,
	       boost::shared_ptr<MonoidRepBase<S, T> > rhs)
    {
      return (lhs->empty == rhs->empty &&
	      lhs->concat == rhs->concat &&
	      lhs->maybe_epsilon == rhs->maybe_epsilon);
    }

  } // ! algebra

} // ! vcsn

#endif // !VCSN_ALGEBRA_IMPLEMENTATION_MONOID_MONOID_REP_BASE_HXX
