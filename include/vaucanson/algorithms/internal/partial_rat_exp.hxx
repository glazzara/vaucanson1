// partial_rat_exp.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_HXX
# define VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_HXX

# include <vaucanson/algorithms/internal/partial_rat_exp.hh>

namespace vcsn
{
  /*-----------------.
  | PartialExp class |
  `-----------------*/

  template <typename Series, typename T>
  PartialExp<Series, T>::PartialExp(const exp_t &e):
    rat_exp_(&e),
    weight_(rat_exp_->set().semiring().identity(
      SELECT(typename semiring_elt_t::value_t))),
    ptr_list_()
  { }

  template <typename Series, typename T>
  PartialExp<Series, T>::PartialExp(const PartialExp &other):
    rat_exp_(other.rat_exp_),
    weight_(other.weight_),
    ptr_list_(other.ptr_list_)
  { }
    
  template <typename Series, typename T>
  PartialExp<Series, T>& PartialExp<Series, T>::operator^=(semiring_elt_t w)
  {
    weight_ = w * weight_;
    return *this;
  }
    
  template <typename Series, typename T>
  PartialExp<Series, T>&
  PartialExp<Series, T>::insert(const value_t *v)
  {
    ptr_list_.push_back(v);
    return *this;
  }

  template <typename Series, typename T>
  typename PartialExp<Series, T>::semiring_elt_t&
  PartialExp<Series, T>::weight()
  {
    return weight_;
  }

  template <typename Series, typename T>
  const typename PartialExp<Series, T>::semiring_elt_t&
  PartialExp<Series, T>::weight() const
  {
    return weight_;
  }

  template <typename Series, typename T>
  const typename PartialExp<Series, T>::ptr_list_t&
  PartialExp<Series, T>::ptr_list() const
  {
    return ptr_list_;
  }

  template <typename Series, typename T>
  typename PartialExp<Series, T>::ptr_list_t&
  PartialExp<Series, T>::ptr_list()
  {
    return ptr_list_;
  }
  
  template <typename Series, typename T>
  const Series&
  PartialExp<Series, T>::exp_set() const
  {
    return rat_exp_->set();
  }
  
  template <typename Series, typename T>
  const T&
  PartialExp<Series, T>::exp_value() const
  {
    return rat_exp_->value();
  }

  template <typename Series, typename T>
  const typename PartialExp<Series, T>::exp_t&
  PartialExp<Series, T>::exp() const
  {
    return *rat_exp_;
  }
  
  template <typename Series, typename T>
  typename PartialExp<Series, T>::iterator
  PartialExp<Series, T>::begin()
  {
    return ptr_list_.begin();
  }

  template <typename Series, typename T>
  typename PartialExp<Series, T>::iterator
  PartialExp<Series, T>::end()
  {
    return ptr_list_.end();
  }

  template <typename Series, typename T>
  typename PartialExp<Series, T>::const_iterator
  PartialExp<Series, T>::begin() const
  {
    return ptr_list_.begin();
  }

  template <typename Series, typename T>
  typename PartialExp<Series, T>::const_iterator
  PartialExp<Series, T>::end() const
  {
    return ptr_list_.end();
  }
 
  /*---------------------.
  | PartialExp functions |
  `---------------------*/

  template <typename S, typename T>
  std::ostream& operator<< (std::ostream& o, PartialExp<S, T> e)
  {
    typename PartialExp<S, T>::const_iterator i;

    o << "[" << e.weight() << ",{";
    i = e.begin();
    if (i != e.end())
    {
      o << PartialExp<S, T>::series_impl_t(*i);
      for (++i; i != e.end(); ++i)
	o << "," << PartialExp<S, T>::series_impl_t(*i);
    }
    return o << "}]";
  }

  template <typename S, typename T>
  PartialExp<S, T> prat_exp_convert(const Element<S, T>& exp)
  {
    PartialExp<S, T>	res(exp);
    res.insert(exp.value().base());
    return res;
  }

  template <typename S, typename T>
  bool operator< (const PartialExp<S, T>& e1, const PartialExp<S, T>& e2)
  {
    typedef typename PartialExp<S, T>::const_iterator	const_iterator;
    typedef typename PartialExp<S, T>::series_impl_t	series_impl_t;
    
    if (e1.weight() != e2.weight())
      return e1.weight() < e2.weight();

    const_iterator i1 = e1.begin();
    const_iterator i2 = e2.begin();
    while (i1 != e1.end() && i2 != e2.end()
	   && series_impl_t(*i1) == series_impl_t(*i2))
    {
      ++i1;
      ++i2;
    }

    if (i1 == e1.end() || i2 == e2.end())
      return (i1 == e1.end() && i2 != e2.end());
    else
      return series_impl_t(*i1) < series_impl_t(*i2);
  }

  template <typename S, typename T>
  bool operator== (const PartialExp<S, T>& e1, const PartialExp<S, T>& e2)
  {
    typedef typename PartialExp<S, T>::const_iterator	const_iterator;
    typedef typename PartialExp<S, T>::series_impl_t	series_impl_t;
    
    if (e1.weight() != e2.weight())
      return false;
 
    const_iterator i1 = e1.begin();
    const_iterator i2 = e2.begin();
    while (i1 != e1.end() && i2 != e2.end()
	   && series_impl_t(*i1) == series_impl_t(*i2))
    {
      ++i1;
      ++i2;
    }

    return (i1 == e1.end() && i2 == e2.end());
  }
  
} // vcsn

#endif // VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_HXX
