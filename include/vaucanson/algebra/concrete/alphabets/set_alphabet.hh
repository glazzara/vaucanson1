// set_alphabet.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_CONCRETE_ALPHABETS_SET_ALPHABET_HH
# define VCSN_ALGEBRA_CONCRETE_ALPHABETS_SET_ALPHABET_HH

# include <vaucanson/algebra/concrete/alphabets/alphabets.hh>

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
      /// The type of letter hold by the alphabet.
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
   *  Services of every alphabet implemented with std::set.
   *
   * @see MetaElement<AlphabetSetBase<Self>, T>
   */
  template<typename L>
  struct MetaElement<algebra::AlphabetSet<L>, std::set<L> >
    : MetaElement<algebra::AlphabetSetBase<algebra::AlphabetSet<L> >, std::set<L> >
  {
    /// An alphabet implemented with std::set is a dynamic value.
    static const bool dynamic_values = true;
  };

  /** @} */
  /** @} */

  template <typename L>
  size_t
  op_max_size(const algebra::AlphabetSet<L>&, const std::set<L>&);

  template <typename L>
  bool op_contains(const algebra::AlphabetSet<L>& s, const std::set<L>& a);

  template <typename L>
  bool op_is_finite(const algebra::AlphabetSet<L>& s, const std::set<L>& a);

  template <typename L>
  bool op_contains_e(const algebra::AlphabetSet<L>& s, const std::set<L>& a,
		     const L& v);

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/concrete/alphabets/set_alphabet.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGEBRA_CONCRETE_ALPHABETS_SET_ALPHABET_HH
