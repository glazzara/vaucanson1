// krat_exp_transpose.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_TRANSPOSE_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_TRANSPOSE_HXX

# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>


namespace vcsn {

  namespace algebra {

    template <class Series, class T, class Dispatch>
    struct KRatExpTranspose : algebra::KRatExpIdentity<
      KRatExpTranspose<Series, T, Dispatch>,
      Series,
      T,
      Dispatch
      >
    {
      typedef KRatExpTranspose<Series, T, Dispatch>	self_t;
      typedef Element<Series, T>			return_type;
      typedef typename Element<Series, T>::semiring_elt_t semiring_elt_t;
      typedef typename semiring_elt_t::value_t		semiring_elt_value_t;
      typedef typename Element<Series, T>::monoid_elt_t	monoid_elt_t;
      typedef typename monoid_elt_t::value_t		monoid_elt_value_t;
      typedef typename monoid_elt_t::set_t		monoid_t;
      typedef typename monoid_t::alphabet_t		alphabet_t;
      typedef typename alphabet_t::letter_t		letter_t;
      INHERIT_CONSTRUCTORS(self_t, T, semiring_elt_t, Dispatch);

      KRatExpTranspose(const Element<Series, T>& exp) :
	KRatExpIdentity<KRatExpTranspose<Series, T, Dispatch>,
      			Series,
      			T,
      			Dispatch
      			>(exp)
      {}

      MATCH__(Product, lhs, rhs)
      {
	return match(rhs) * match(lhs);
      }
      END

      MATCH_(Constant, m)
      {
	monoid_elt_t melt (this->exp_.structure().monoid(), m);
	melt.mirror();
	return Element<Series, T> (this->exp_.structure(), melt);
      }
      END

    };


  } // algebra

}

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_TRANSPOSE_HXX
