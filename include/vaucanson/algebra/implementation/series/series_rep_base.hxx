// series_rep_base.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_REP_BASE_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_REP_BASE_HXX

# include <vaucanson/algebra/implementation/series/series_rep_base.hh>

namespace vcsn
{
  namespace algebra
  {
    template <template <typename, typename> class B, typename S, typename M>
    SeriesRepBase<B, S, M>::SeriesRepBase()
    {
      self_t* self = static_cast<self_t*>(this);

      // Sane defaults.
      self->maybe_zero.push_back("0");
      self->maybe_zero.push_back("z");

      // Trying with more than one char.
      self->maybe_zero.push_back("_z");
      self->maybe_zero.push_back("zero");

      self->zero = *(self->maybe_zero.begin());
      self->open_par = "(";
      self->close_par = ")";
      self->plus = "+";
      self->times = ".";
      self->star = "*";
      self->open_weight = "{";
      self->close_weight = "}";
      self->spaces.push_back(" ");
    }

    // FIXME: maybe we can factor even more code with MonoidRepBase
    // (maybe some sort of RepresentationBase?)
    template <template <typename, typename> class B, typename S, typename M>
    void
    SeriesRepBase<B, S, M>::disambiguate(const monoid_t& monoid,
					 pointer_t& orig)
    {
      // Type helpers.
      typedef typename monoid_t::alphabet_t	alphabet_t;
      typedef typename alphabet_t::letter_t	letter_t;

      self_t* self = static_cast<self_t*>(this);

      // Type helpers.
      typedef std::vector<std::string>::const_iterator iterator_t;

      self_t new_rep = *self;

      for (iterator_t zero_it = new_rep.maybe_zero.begin();
	   zero_it != new_rep.maybe_zero.end();
	   ++zero_it)
      {
	bool found = true;

	for_all_const_(alphabet_t, i, monoid.alphabet())
	{
	  if (letter_traits<letter_t>::letter_to_literal(*i) == *zero_it)
	  {
	    found = false;
	    break;
	  }
	}

	// Best match.
	if (found)
	{
	  // Copy on write.
	  if (new_rep.zero != *zero_it)
	  {
	    new_rep.zero = *zero_it;
	    orig = pointer_t(new self_t(new_rep));
	  }
	  break;
	}
      }
    }

    template <template <typename, typename> class B, typename S, typename M>
    bool
    operator==(boost::shared_ptr<SeriesRepBase<B, S, M> > lhs,
	       boost::shared_ptr<SeriesRepBase<B, S, M> > rhs)
    {
      return (lhs->open_par == rhs->open_par &&
	      lhs->close_par == rhs->close_par &&
	      lhs->plus == rhs->plus &&
	      lhs->times == rhs->times &&
	      lhs->star == rhs->star &&
	      lhs->zero == rhs->zero &&
	      lhs->open_weight == rhs->open_weight &&
	      lhs->close_weight == rhs->close_weight &&
	      lhs->spaces == rhs->spaces &&
	      lhs->maybe_zero == rhs->maybe_zero);
    }

  } // ! algebra

} // ! vcsn

#endif // !VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_REP_BASE_HXX
