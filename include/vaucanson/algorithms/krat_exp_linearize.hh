// krat_exp_linearize.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_ALGORITHMS_KRAT_EXP_LINEARIZE_HH
# define VCSN_ALGORITHMS_KRAT_EXP_LINEARIZE_HH

# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/concrete/letter/couple_letter.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  //! The types of a linearized expression
  template <typename S, typename T>
  struct linearize_element
  {
    // Get types which are useful to build the new type 
    typedef typename T::weight_value_t		orig_weight_value_t;
    typedef typename S::weights_t		orig_semiring_t;
    typedef typename S::monoid_t		orig_monoid_t;
    typedef typename orig_monoid_t::letter_t	orig_letter_t;

    // Build it !
    typedef int							index_t;
    typedef std::pair<orig_letter_t, index_t>			letter_t;
    typedef AlphabetSet<letter_t>				alphabets_t;
    typedef std::set<letter_t>					alphabet_impl_t;
    typedef Element<alphabets_t, alphabet_impl_t>		alphabet_t;
    typedef FreeMonoid<alphabet_t>				monoid_t;
    typedef Series<orig_semiring_t, monoid_t>			series_t;
    typedef std::basic_string<letter_t>				monoid_value_t;
    typedef rat::exp<monoid_value_t, orig_weight_value_t>	serie_impl_t;
    // And the resulting type:
    typedef Element<series_t, serie_impl_t>			element_t;
  };

  //! The linearization of the krat expression
  template <class Series, class T>
  typename linearize_element<Series, T>::element_t
  linearize(const Element<Series, T>& exp);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/krat_exp_linearize.hxx>

#endif // VCSN_ALGORITHMS_KRAT_EXP_LINEARIZE_HH
