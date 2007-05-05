// hash_label.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_MISC_HASH_HXX_
# define VCSN_MISC_HASH_HXX_

# include <boost/functional/hash/hash.hpp>

namespace vcsn
{
  namespace misc
  {
    template <typename Word, typename Weight>
    std::size_t
    hash_label<algebra::polynom<Word, Weight> >::operator() (const algebra::polynom<Word, Weight>& l) const
    {
      std::size_t seed (0);

      for (typename algebra::polynom<Word, Weight>::const_iterator i = l.begin ();
	   i != l.end ();
	   i++)
      {
	::boost::hash_range (seed, i->first.begin(), i->first.end()); // std::string
	::boost::hash_combine (seed, i->second);
      }
      return seed;
    }

    template <typename Kind, typename Type>
    std::size_t
    hash_handler<handler<Kind, Type> >::operator() (const handler<Kind, Type>& h) const
    {
      return ::boost::hash_value (h.value());
    }
  }
}

#endif // ! VCSN_MISC_HASH_HXX_ //
