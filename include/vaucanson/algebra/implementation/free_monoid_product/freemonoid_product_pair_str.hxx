// freemonoid_product_pair_str.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004, 2005 The Vaucanson Group.
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

#ifndef VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_PRODUCT_FREEMONOID_PRODUCT_PAIR_STR_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_PRODUCT_FREEMONOID_PRODUCT_PAIR_STR_HXX

# include <vaucanson/algebra/implementation/free_monoid_product/freemonoid_product_pair_str.hxx>

namespace vcsn {

  template <class Self, typename T>
  typename
  MetaElement<algebra::FreeMonoidProductBase<Self>, T>::first_monoid_elt_t&
  op_first(const algebra::FreeMonoidProductBase<Self>& s, T& v)
  {
    return Element<typename virtual_types<Self>::first_monoid_t,
		   typename T::first_type> (s.first_monoid(), v.first);
  }

  template <class Self, typename T>
  typename
  MetaElement<algebra::FreeMonoidProductBase<Self>, T>::second_monoid_elt_t&
  op_second(const algebra::FreeMonoidProductBase<Self>& s, T& v)
  {
    return Element<typename virtual_types<Self>::second_monoid_t,
		   typename T::second_type> (s.second_monoid(), v.second);
  }

  template <class F, class S>
  void
  op_in_mul(const algebra::FreeMonoidProduct<F, S>& s,
	    std::pair<std::basic_string<typename F::letter_t>,
		      std::basic_string<typename S::letter_t> >& dst,
	    const std::pair<std::basic_string<typename F::letter_t>,
			    std::basic_string<typename S::letter_t> >& src)
  {
    dst.first += src.first;
    dst.second += src.second;
  }

  template<class F, class S>
  std::pair<std::basic_string<typename F::letter_t>,
	    std::basic_string<typename S::letter_t> >
  op_mul(const algebra::FreeMonoidProduct<F, S>&,
	 const std::pair<std::basic_string<typename F::letter_t>,
			 std::basic_string<typename S::letter_t> >& a,
	 const std::pair<std::basic_string<typename F::letter_t>,
			 std::basic_string<typename S::letter_t> >& b)
  {
    return std::pair< std::basic_string<typename F::letter_t>,
		      std::basic_string<typename S::letter_t> >
			      (a.first + b.first, a.second + b.second);
  }

  template<class F, class S>
  const std::pair<std::basic_string<typename F::letter_t>,
		  std::basic_string<typename S::letter_t> >
  identity_value(SELECTOR2(algebra::FreeMonoidProduct<F, S>),
		 SELECTOR2(std::pair<std::basic_string<typename F::letter_t>,
			  std::basic_string<typename S::letter_t> >))
  {
    static const std::pair<std::basic_string<typename F::letter_t>,
			   std::basic_string<typename S::letter_t> > instance;
    return instance;
  }

  template <class F, class S>
  Element<algebra::FreeMonoidProduct<F, S>,
	  std::pair<std::basic_string<typename F::letter_t>,
		    std::basic_string<typename S::letter_t> > >
  op_choose(const algebra::FreeMonoidProduct<F, S>& s,
	    SELECTOR2(std::pair<std::basic_string<typename F::letter_t>,
			       std::basic_string<typename S::letter_t> >))
  {
    typedef std::basic_string<typename F::letter_t> T1;
    typedef std::basic_string<typename S::letter_t> T2;

    std::pair< T1, T2 >	   res(s.first_monoid().choose(SELECT(T1)).value(),
			       s.second_monoid().choose(SELECT(T2)).value());

    return Element<algebra::FreeMonoidProduct<F, S>,
		   std::pair< T1, T2 > >		(s, res);
  }

  template<typename Self, typename T>
  void
  op_in_mirror(const algebra::FreeMonoidProductBase<Self>& s, T& v)
  {
    op_in_mirror(s.first_monoid(), v.first);
    op_in_mirror(s.second_monoid(), v.second);
  }

  template<typename Self, typename T, typename Ftor>
  typename Ftor::result_type
  op_length(const algebra::FreeMonoidProductBase<Self>&, const T& v, Ftor f)
  {
    return f(v.first.length(), v.second.length());
  }

  template <typename Self, typename St, typename T>
  St&
  op_rout(const algebra::FreeMonoidProductBase<Self>& s,
	  St& st,
	  const T& v)
  {
    st << "(";
    op_rout(s.first_monoid(), st, v.first);
    st << ",";
    op_rout(s.second_monoid(), st, v.second);  
    st << ")";
    return st;
  }
} // vcsn

#endif // VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_PRODUCT_FREEMONOID_PRODUCT_PAIR_STR_HXX
