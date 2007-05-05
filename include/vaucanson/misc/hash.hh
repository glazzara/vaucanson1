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

namespace vcsn
{
  namespace misc
  {
    template <typename T>
    struct hash_label;

    template <typename Word, typename Weight>
    struct hash_label<algebra::polynom<Word, Weight> >
    {
      std::size_t operator() (const algebra::polynom<Word, Weight>& l) const;
    };

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
  }
} // End of namespace vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/misc/hash.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY || VCSN_USE_LIB

#endif // ! VCSN_MISC_HASH_HH_ //
