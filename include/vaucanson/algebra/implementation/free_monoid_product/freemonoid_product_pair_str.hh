// freemonoid_product_pair_str.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_PRODUCT_FREEMONOID_PRODUCT_PAIR_STR_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_PRODUCT_FREEMONOID_PRODUCT_PAIR_STR_HH

# include <vaucanson/algebra/concept/freemonoid_product.hh>

# include <utility>
# include <string>

namespace vcsn {

  /*----------------------------------------------------------.
  | Implementation of freemonoid_product with pair of strings |
  `----------------------------------------------------------*/

  template <class F, class S>
  void
  op_in_mul(const algebra::FreeMonoidProduct<F, S>& s,
	    std::pair<std::basic_string<typename F::letter_t>,
		      std::basic_string<typename S::letter_t> >& dst,
	    const std::pair<std::basic_string<typename F::letter_t>,
			    std::basic_string<typename S::letter_t> >& src);

  template<class F, class S>
  std::pair<std::basic_string<typename F::letter_t>,
	    std::basic_string<typename S::letter_t> >
  op_mul(const algebra::FreeMonoidProduct<F, S>& s,
	 const std::pair<std::basic_string<typename F::letter_t>,
			 std::basic_string<typename S::letter_t> >& a,
	 const std::pair<std::basic_string<typename F::letter_t>,
			 std::basic_string<typename S::letter_t> >& b);

  template<class F, class S>
  const std::pair<std::basic_string<typename F::letter_t>,
		  std::basic_string<typename S::letter_t> >
  identity_value(SELECTOR2(algebra::FreeMonoidProduct<F, S>),
		 SELECTOR2(std::pair<std::basic_string<typename F::letter_t>,
				    std::basic_string<typename S::letter_t> >));

  template<class F, class S>
  Element<algebra::FreeMonoidProduct<F, S>,
	  std::pair<std::basic_string<typename F::letter_t>,
		    std::basic_string<typename S::letter_t> > >
  op_choose(const algebra::FreeMonoidProduct<F, S>& s,
	    SELECTOR2(std::pair<std::basic_string<typename F::letter_t>,
			       std::basic_string<typename S::letter_t> >));

  template<typename Self, typename T>
  void op_in_mirror (const algebra::FreeMonoidProductBase<Self>& s, T& v);

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/implementation/free_monoid_product/freemonoid_product_pair_str.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_PRODUCT_FREEMONOID_PRODUCT_PAIR_STR_HH
