// series_base.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey 
// and Regis-Gianas.
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

#ifndef VCSN_ALGEBRA_CONCEPT_SERIES_BASE_HXX
# define VCSN_ALGEBRA_CONCEPT_SERIES_BASE_HXX

# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {

  namespace algebra {

    /*-----------------.
      | SeriesBase<Self> |
      `-----------------*/

    template<class Self>
    const typename SeriesBase<Self>::monoid_t& 
    SeriesBase<Self>::monoid() const
    { 
      return self().monoid(); 
    }
    
    template<class Self>
    const typename SeriesBase<Self>::weights_t& 
    SeriesBase<Self>::weights() const
    { 
      return self().weights(); 
    }

    template<class Self>
    typename SeriesBase<Self>::monoid_t& 
    SeriesBase<Self>::monoid() 
    { 
      return self().monoid(); 
    }

    template<class Self>     
    typename SeriesBase<Self>::weights_t& 
    SeriesBase<Self>::weights() 
    { 
      return self().weights(); 
    }

    template<class Self>     
    SeriesBase<Self>::SeriesBase() 
    {}

    template<class Self>     
    SeriesBase<Self>::SeriesBase(const SeriesBase& other) :
      SemiringBase<Self>(other)
    {}

  } // algebra


    /*---------------------------------.
      | MetaElement<SeriesBase<Self>, T> |
      `---------------------------------*/
    
  template<typename S, typename T>
  typename MetaElement<SeriesBase<S>, T>::weight_value_t 
  MetaElement<SeriesBase<S>, T>::value_get(const monoid_value_t& m) const
  { 
    // assert(set().monoid().contains(m));
    return op_series_get(set(), value(), m);
  }

  template<typename S, typename T>
  typename MetaElement<SeriesBase<S>, T>::weight_t 
  MetaElement<SeriesBase<S>, T>::get(const monoid_elt_t& m) const
  { 
    return weight_t(set().weights(), value_get(m.value())); 
  }

  template<typename S, typename T>
  void 
  MetaElement<SeriesBase<S>, T>::value_set(const monoid_value_t& m, 
					   const weight_value_t& w) 
  { 
    // assert(set().monoid().contains(m));
    // assert(set().weights().contains(w));
    return op_series_set(set(), value(), m, w);
  }

  template<typename S, typename T>
  void 
  MetaElement<SeriesBase<S>, T>::assoc(const monoid_elt_t& m, 
				       const weight_t& w) 
  { 
    value_set(m.value(), w.value()); 
  }

  template<typename S, typename T>
  bool 
  MetaElement<SeriesBase<S>, T>::is_finite_app() const
  { 
    return op_is_finite_app(set(), value()); 
  }

  template <typename S, typename T>
  typename MetaElement<SeriesBase<S>, T>::monoid_elt_t
  MetaElement<SeriesBase<S>, T>::choose_from_supp() const
  {
    return op_choose_from_supp(this->set(), value());
  }

  template <typename S, typename T>
  void
  MetaElement<SeriesBase<S>, T>::transpose()
  {
    op_in_transpose(this->set(), value());
  }

  template <typename S, typename T>
  typename MetaElement<SeriesBase<S>, T>::support_t
  MetaElement<SeriesBase<S>, T>::supp() const  
  {
    return op_support(this->set(), value());
  }

  template<typename S, typename T>
  MetaElement<SeriesBase<S>, T>::MetaElement() 
  {}
    
  template<typename S, typename T>
  MetaElement<SeriesBase<S>, T>::MetaElement(const MetaElement& other) :
    MetaElement<SemiringBase<S>, T>(other)
  {}
    
  template<typename S, typename T>
  bool op_is_finite_app(const SeriesBase<S>& s, const T& t)
  { 
    return false; 
  }
    
  template<typename S, typename T, typename M, typename W>
  void op_series_set(const SeriesBase<S>& s, const T& t, const W& w)
  {
    assert(! "defined.");
  }

  template <class S, class T>
  Element<S, T> op_series_choose(const SeriesBase<S>& s, SELECTOR(T)) 
  {
    assert(! "defined.");
  }

  template <class S, class T>
  inline
  typename series_traits<T>::support_t
  op_support(const SeriesBase<S>&, const T& v)
  {
    return v;
  }

  template <class S, class T>
  Element<S, T>
  transpose(const SeriesBase<S>& s, const T& t)
  {
    T	new_t(t);
    new_t.transpose();
    return new_t;
  }

  template <class S, class T>
  bool
  is_letter_support(const Element<S, T>& s)
  {
    typedef typename series_traits<T>::support_t support_t;
    for_each_const_(support_t, e, s.supp())
      if (op_size(s.set().monoid(), e->first ) != 1)
	return false;
    return true;
  }
  
} // vcsn

#endif // VCSN_ALGEBRA_CONCEPT_SERIES_BASE_HXX
