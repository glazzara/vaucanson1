// alphabet_set.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2007, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_ALPHABET_SET_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_ALPHABET_SET_HH

# include <vaucanson/algebra/implementation/alphabets/alphabets.hh>
# include <vaucanson/misc/usual_macros.hh>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup alphabet *//** @{ */

    /*--------------------------------------------.
    | alphabet_traits<AlphabetSet<L>,std::set<L>> |
    `--------------------------------------------*/

    /// Meta information about the mixing of AlphabetSet with std::set.
    template <typename L>
    struct alphabet_traits<AlphabetSet<L>, std::set<L> >
    {
      /// The type of the alphabet.
      typedef Element<AlphabetSet<L>, std::set<L> > alphabet_t;

      /// The type of letters held by the alphabet.
      typedef L letter_t;

      /// The type of letters held by the first projection.
      typedef typename letter_traits<letter_t>::first_projection_t
      first_projection_letter_t;

      /// The type of letters held by the second projection.
      typedef typename letter_traits<letter_t>::second_projection_t
      second_projection_letter_t;

      /// The type of the first projection alphabet.
      typedef Element<AlphabetSet<first_projection_letter_t>,
	      std::set<first_projection_letter_t> > first_projection_t;

      /// The type of the second projection alphabet.
      typedef Element<AlphabetSet<second_projection_letter_t>,
	      std::set<second_projection_letter_t> > second_projection_t;

      /// The first projection alphabet maker.
      static first_projection_t first_projection(const alphabet_t&);

      /// The second projection alphabet maker.
      static second_projection_t second_projection(const alphabet_t&);
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

  namespace algebra {

    template <typename L>
    std::pair<bool, L> op_parse(const AlphabetSet<L>&,
				const std::set<L>&,
				const std::string&,
				size_t&);

    template <typename L>
    size_t op_max_size(const algebra::AlphabetSet<L>&, const std::set<L>&);

    template <typename L>
    bool op_contains(const algebra::AlphabetSet<L>& s, const std::set<L>& a);

    template <typename L>
    bool op_is_finite(const algebra::AlphabetSet<L>& s, const std::set<L>& a);

    template <typename L>
    bool op_contains_e(const algebra::AlphabetSet<L>& s, const std::set<L>& a,
		       const L& v);
  }

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/alphabets/alphabet_set.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_ALPHABET_SET_HH
