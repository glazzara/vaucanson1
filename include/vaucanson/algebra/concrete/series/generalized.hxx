// generalized.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_GENERALIZED_HXX
# define VCSN_ALGEBRA_CONCRETE_SERIES_GENERALIZED_HXX

# include <vaucanson/misc/selectors.hh>
# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/concrete/series/polynoms.hh>
# include <vaucanson/algebra/concrete/series/krat.hh>

namespace vcsn {

  namespace algebra {
    
    /*----------------------.
    | Generalized converter |
    `----------------------*/
    template<typename Tm, typename Tw, typename W, typename M>
    rat::exp<Tm, Tw> op_convert(SELECTOR2(rat::exp<Tm, Tw>),
				SELECTOR2(Series<W, M>),
				const polynom<Tm, Tw>& p_value)
    {
      typedef rat::exp<Tm, Tw> kexp_t;
      kexp_t	exp;

      if (p_value == identity_value(SELECT2(Series<W, M>), 
				    SELECT2(polynom<Tm, Tw>)))
	return kexp_t::one();
      
      if (p_value == zero_value(SELECT2(Series<W, M>), 
				SELECT2(polynom<Tm, Tw>)))
	return kexp_t::zero();

      for (typename polynom<Tm, Tw>::const_iterator p = p_value.begin();
	   p != p_value.end();
	   ++p)
	if (exp == kexp_t::zero())
	  exp = (*p).second *  kexp_t::constant((*p).first);
	else
	  exp += (*p).second *  kexp_t::constant((*p).first);
      return exp;
    }

  } // algebra

} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_SERIES_GENERALIZED_HXX
