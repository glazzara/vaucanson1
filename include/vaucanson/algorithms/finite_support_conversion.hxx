// finite_support_conversion.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_FINITE_SUPPORT_CONVERSION_HXX
# define VCSN_ALGORITHMS_FINITE_SUPPORT_CONVERSION_HXX

# include <vaucanson/algorithms/finite_support_conversion.hh>
# include <vaucanson/algebra/concept/monoid_base.hh> // For zero_as.

# include <vaucanson/misc/contract.hh>

namespace vcsn
{

  template<typename S, typename T, typename Ss, typename Ts>
  void finite_support_convert(Element<S, T>& dst, const Element<Ss, Ts>& org)
  {
    precondition(org.is_finite_app());

    typedef typename Element<S, T>::monoid_elt_t me_t;
    typedef typename Element<S, T>::semiring_elt_t se_t;
    typedef typename Element<Ss, Ts>::monoid_elt_t sme_t;
    typedef typename Element<Ss, Ts>::semiring_elt_t sse_t;

    typedef typename Element<Ss, Ts>::support_t support_t;

    dst = algebra::zero_as<T>::of(dst.structure());

    const support_t& org_supp = org.supp();
    for (typename support_t::const_iterator i = org_supp.begin();
	 i != org_supp.end();
	 ++i)
      {
	const sme_t &sm = sme_t(org.structure().monoid(), *i);

	const me_t &m = me_t(dst.structure().monoid(), sm);
	const se_t &w = se_t(dst.structure().semiring(), org.get(sm));

	dst += w * Element<S, T>(dst.structure(), m);
      }

    postcondition(dst.is_finite_app());
  }

}

#endif // VCSN_ALGORITHMS_FINITE_SUPPORT_CONVERSION_HXX
