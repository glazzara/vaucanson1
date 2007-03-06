// set_alphabet.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_SET_ALPHABET_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_SET_ALPHABET_HH

# include <vaucanson/algebra/implementation/alphabets/alphabets.hh>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup alphabet *//** @{ */

    /*--------------------------------------------.
    | alphabet_traits<AlphabetSet<L>,std::set<L>> |
    `--------------------------------------------*/

    /// Meta information about the mixing of AlphabetSet with std::set.
    template<typename L>
    struct alphabet_traits<AlphabetSet<L>, std::set<L> >
    {
      /// The type of letters held by the alphabet.
      typedef L			letter_t;
    };

    /** @} */
    /** @} */

  } // algebra

  /** @addtogroup algebra *//** @{ */
  /** @addtogroup alphabet *//** @{ */

  /*-----------------------------------------.
  | MetaElement<AlphabetSet<L>, std::set<L>> |
  `-----------------------------------------*/

  /**
   * Services of every alphabet implemented with std::set.
   *
   * @see MetaElement<AlphabetSetBase<Self>, T>
   */
  template<typename L>
  struct MetaElement<algebra::AlphabetSet<L>, std::set<L> >
    : MetaElement<algebra::AlphabetSetBase<algebra::AlphabetSet<L> >, std::set<L> >
  {
    /// An alphabet implemented with std::set is a dynamic value.
    static const bool dynamic_value = true;
  };

  /** @} */
  /** @} */

  template <typename L>
  size_t op_max_size(const algebra::AlphabetSet<L>&, const std::set<L>&);

  template <typename L>
  bool op_contains(const algebra::AlphabetSet<L>& s, const std::set<L>& a);

  template <typename L>
  bool op_is_finite(const algebra::AlphabetSet<L>& s, const std::set<L>& a);

  template <typename L>
  bool op_contains_e(const algebra::AlphabetSet<L>& s, const std::set<L>& a,
		     const L& v);

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/alphabets/set_alphabet.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_SET_ALPHABET_HH
