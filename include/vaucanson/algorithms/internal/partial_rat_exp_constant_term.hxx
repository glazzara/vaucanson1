// partial_rat_exp_constant_term.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_CONSTANT_TERM_HXX
# define VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_CONSTANT_TERM_HXX

# include <utility>
# include <vaucanson/algorithms/internal/partial_rat_exp_constant_term.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>

namespace vcsn {

  template <class Series, class T>
  std::pair<typename Element<Series, T>::semiring_elt_t, bool>
  constant_term(const PartialExp<Series, T>& exp)
  {
    typedef
    typename PartialExp<Series, T>::const_iterator		const_iterator;
    typedef
    typename PartialExp<Series, T>::semiring_elt_t			semiring_elt_t;
    typedef
    typename PartialExp<Series, T>::series_impl_t		series_impl_t;
    typedef
    std::pair<typename Element<Series, T>::semiring_elt_t, bool>	result_t;
    
    semiring_elt_t 	res 	  = exp.exp_structure().semiring().identity(
			      SELECT(typename semiring_elt_t::value_t));;
    bool	undefined = false;
    
    for (const_iterator i = exp.begin(); i != exp.end() && !undefined; ++i)
    {
      result_t tmp = constant_term(Element<Series, T>(exp.exp_structure(),
						      series_impl_t(*i)));
      undefined = !tmp.second;
      res *= tmp.first;
    }
    return std::make_pair(exp.weight() * res, !undefined);
  }

} // vcsn

#endif // VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_CONSTANT_TERM_HXX
