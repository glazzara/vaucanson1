// hash_label.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007, 2008 The Vaucanson Group.
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

#ifndef VCSN_MISC_HASH_HXX_
# define VCSN_MISC_HASH_HXX_

# include <utility>
# include <boost/functional/hash/hash.hpp>
# include <vaucanson/algebra/implementation/series/rat/hash_visitor.hh>

namespace vcsn
{
  namespace misc
  {

    inline
    std::size_t hash_label<char>::operator()(const char c) const
    {
      return c;
    };

    template <typename Word, typename Weight>
    std::size_t
    hash_label<algebra::polynom<Word, Weight> >::operator() (const algebra::polynom<Word, Weight>& l) const
    {
      std::size_t seed (0);

      for (typename algebra::polynom<Word, Weight>::const_iterator i = l.begin ();
	   i != l.end ();
	   ++i)
      {
	// FIXME: it might not be correct yet
	::boost::hash_combine (seed, i->first); // std::string
//	::boost::hash_combine (seed, i->second); It does not make sense to hash the weight
      }
      return seed;
    }

    template <typename Word, typename LetterT, typename WeightT>
    std::size_t
    hash_label<algebra::polynom<Word, rat::exp<LetterT, WeightT> > >::operator() (
	  const algebra::polynom<Word, rat::exp<LetterT, WeightT> >& l) const
    {
      std::size_t seed (0);
      hash_label hash;

      for (typename algebra::polynom<Word, rat::exp<LetterT,
	    WeightT> >::const_iterator i = l.begin ();
	   i != l.end ();
	   ++i)
      {
	::boost::hash_combine (seed, hash(i->first));
	::boost::hash_combine (seed, i->second);
      }
      return seed;
    }

    template <typename Word, typename WeightT>
    std::size_t
    hash_label<algebra::polynom<Word, rat::exp<std::string, WeightT> > >::operator() (
	const rat::exp<std::string, WeightT>& l) const
    {
      rat::HashVisitor<std::string, WeightT> visitor;
      l.accept(visitor);
      return visitor.hash_value();
    }


    template <typename Word, typename WeightT>
    std::size_t
    hash_label<algebra::polynom<Word, rat::exp<std::string, WeightT> > >::operator() (
	  const algebra::polynom<Word, rat::exp<std::string, WeightT> >& l) const
    {
      std::size_t seed (0);
      hash_label hash;

      for (typename algebra::polynom<Word, rat::exp<std::string,
	    WeightT> >::const_iterator i = l.begin ();
	   i != l.end ();
	   ++i)
      {
	::boost::hash_combine (seed, i->first);
	::boost::hash_combine (seed, hash(i->second));
      }
      return seed;
    }

    template <typename Weight, typename T, typename U>
    std::size_t
    hash_label<algebra::polynom<std::pair<T, U>, Weight> >::operator() (
	const algebra::polynom<std::pair<T, U>, Weight >& l) const
    {
      std::size_t seed (0);

      for (typename algebra::polynom<std::pair<T, U>, Weight>::const_iterator i = l.begin ();
	   i != l.end ();
	   ++i)
      {
	::boost::hash_combine (seed, i->first.first);
	::boost::hash_combine (seed, i->first.second);
	::boost::hash_combine (seed, i->second);
      }
      return seed;
    }

    template <typename Word, typename Weight>
    std::size_t
    hash_label<rat::exp<Word, Weight> >::operator() (const rat::exp<Word, Weight>& l) const
    {
      rat::HashVisitor<Word, Weight> visitor;
      l.accept(visitor);
      return visitor.hash_value();
    }

    template <typename Kind, typename Type>
    std::size_t
    hash_handler<handler<Kind, Type> >::operator() (const handler<Kind, Type>& h) const
    {
      return ::boost::hash_value (h.value());
    }

    inline
    std::size_t
    hash_handler<char>::operator() (const char c) const
    {
      return ::boost::hash_value (c);
    }

  }
}

#endif // ! VCSN_MISC_HASH_HXX_ //
