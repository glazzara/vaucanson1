// krat_exp_verbalization.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_VERBALIZATION_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_VERBALIZATION_HXX

# include <vaucanson/algebra/implementation/series/krat_exp_support.hxx>

namespace vcsn {

  namespace algebra {

    template <class Series, class T>
    Element<Series, T>
    verbalize(const Element<Series, T>& exp)
    {
      Element<Series, T> ret(exp.structure());
      typedef SupportMatcher<Series, T, algebra::DispatchFunction<T> >
	matcher_t;
      matcher_t matcher(exp.structure());
      matcher.match(exp.value());
      typedef typename matcher_t::ext_support_t ext_support_t;
      ext_support_t supp = matcher.ext_get();
      for_each_const_(ext_support_t, m, supp)
	{
	  typename Element<Series, T>::monoid_elt_t
	    w (exp.structure().monoid(), m->second);
	  typename Element<Series, T>::semiring_elt_t
	    wg(exp.structure().semiring(), m->first);
	  Element<Series, T> me(exp.structure());
	  me = w;
	  ret += wg * me;
	}
      return ret;
    }


  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_VERBALIZATION_HXX
