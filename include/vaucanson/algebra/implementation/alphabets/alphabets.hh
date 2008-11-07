// alphabets.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_ALPHABETS_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_ALPHABETS_HH

# include <set>
# include <utility>

# include <vaucanson/algebra/concept/alphabets_base.hh>

namespace vcsn
{
  namespace algebra
  {
    /** @addtogroup algebra *//** @{ */
    /** @addtogroup alphabet *//** @{ */

    /*---------------.
    | AlphabetSet<L> |
    `---------------*/

    /// Static implementation of alphabet structural element.
    template <typename L>
    struct AlphabetSet
      : AlphabetSetBase<AlphabetSet<L> >
    {
      /// The type of letters held by the alphabet.
      typedef L		letter_t;
    };

    /** @} */
    /** @} */

  } // algebra

  /** @addtogroup algebra *//** @{ */
  /** @addtogroup alphabet *//** @{ */

  /*------------------------------.
  | dynamic_traits<AlphabetSet<L> |
  `------------------------------*/

  /// Meta information about AlphabetSet.
  template<typename L>
  struct dynamic_traits<algebra::AlphabetSet<L> >
    : dynamic_traits<algebra::AlphabetSetBase<L> >
  { };

  /** @} */
  /** @} */

} // ! vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_ALPHABETS_HH
