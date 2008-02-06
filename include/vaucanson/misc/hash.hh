// hash_label.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007 The Vaucanson Group.
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

#ifndef VCSN_MISC_HASH_HH_
# define VCSN_MISC_HASH_HH_

# include <cstddef>
# include <vaucanson/algebra/implementation/series/polynoms.hh>
# include <vaucanson/algebra/implementation/series/rat/exp.hh>
# include <vaucanson/automata/concept/handlers.hh>
# include <boost/functional/hash/hash.hpp>
# include <boost/shared_ptr.hpp>

namespace vcsn
{
  namespace misc
  {
    template <typename T>
    struct hash_label;

    template <>
    struct hash_label<char>
    {
      std::size_t operator() (const char) const;
    };

    template <typename Word, typename Weight>
    struct hash_label<algebra::polynom<Word, Weight> >
    {
      std::size_t operator() (const algebra::polynom<Word, Weight>& l) const;
    };

    template <typename Weight, typename T, typename U>
    struct hash_label<algebra::polynom<std::pair<T, U>, Weight> >
    {
      std::size_t operator() (const algebra::polynom<std::pair<T, U>, Weight>& l) const;
    };

    template <typename Word, typename WeightT>
    struct hash_label<algebra::polynom<Word, rat::exp<std::string, WeightT> > >
    {
      std::size_t operator() (const algebra::polynom<Word, rat::exp<std::string, WeightT> >& l) const;
      std::size_t operator() (const rat::exp<std::string, WeightT>& l) const;

    };

    template <typename Word, typename LetterT, typename WeightT>
    struct hash_label<algebra::polynom<Word, rat::exp<LetterT, WeightT> > >
    {
      std::size_t operator() (const algebra::polynom<Word, rat::exp<LetterT, WeightT> >& l) const;
    };


/*    template <typename Word, typename LetterT, typename WeightT>
    struct hash_label<algebra::polynom<Word, rat::exp<std::string, rat::exp<LetterT, WeightT> > > >
    {
      std::size_t operator() (const algebra::polynom<Word, rat::exp<std::string, rat::exp<LetterT, WeightT > > >& l) const;
    };
*/
    template <typename Word, typename Weight>
    struct hash_label<rat::exp<Word, Weight> >
    {
      std::size_t operator() (const rat::exp<Word, Weight>& l) const;
    };

    template <typename T>
    struct hash_handler;

    template <typename Kind, typename Type>
    struct hash_handler<handler<Kind, Type> >
    {
      std::size_t operator() (const handler<Kind, Type>& h) const;
    };

    template<>
    struct hash_handler<char>
    {
      std::size_t operator() (const char h) const;
    };

    struct hash_state_handler
    {
      inline std::size_t operator() (const handler<state_h, std::size_t*>& h) const
      {
	return ::boost::hash_value (reinterpret_cast<std::size_t>(h.value()));
      }

      inline std::size_t operator() (const boost::shared_ptr<std::size_t>& h) const
      {
	return ::boost::hash_value (reinterpret_cast<std::size_t>(h.get()));
      }

      inline std::size_t operator() (const std::size_t* h) const
      {
	return ::boost::hash_value (reinterpret_cast<std::size_t>(h));
      }
    };

  }
} // End of namespace vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/misc/hash.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY || VCSN_USE_LIB

#endif // ! VCSN_MISC_HASH_HH_ //
