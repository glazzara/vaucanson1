// series_base.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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


#ifndef ALGEBRA_SERIES_BASE_HH
# define ALGEBRA_SERIES_BASE_HH

# include <vaucanson/algebra/concept/semiring_base.hh>

namespace vcsn {

  namespace algebra {

    /*-----------------.
    | SeriesBase<Self> |
    `-----------------*/
    template<class Self>
    struct SeriesBase 
      : SemiringBase<Self>
    {
      typedef typename traits::virtual_types<Self>::monoid_t  monoid_t;
      typedef typename traits::virtual_types<Self>::weights_t weights_t;

      // virtual methods :
      const monoid_t&	monoid() const;      
      const weights_t&  weights() const;

      monoid_t&		monoid();      
      weights_t&	weights(); 

    protected:
      SeriesBase();
      SeriesBase(const SeriesBase& other);
    };

    template<typename S, typename T>
    struct series_traits
    {};

  } // algebra

  /*---------------------------------.
  | MetaElement<SeriesBase<Self>, T> |
  `---------------------------------*/
  template<class Self, typename T>
  struct MetaElement<SeriesBase<Self>, T> 
    : MetaElement<SemiringBase<Self>, T>
  {
    typedef typename series_traits<Self, T>::weights_value_t   weights_value_t;
    typedef typename series_traits<Self, T>::monoid_value_t    monoid_value_t;
    typedef Element<typename Self::weights_t, weights_value_t> weight_t;
    typedef Element<typename Self::monoid_t, monoid_value_t>	 monoid_elt_t;
    typedef Element<Self, T>					 element_t;

    weights_value_t	value_get(const monoid_value_t& m) const;
    weight_t		get(const monoid_elt_t& m) const;
    void		value_set(const monoid_value_t& m, 
				  const weights_value_t& w);
    const Self&	set() const;
    void		assoc(const monoid_elt_t& m, const weight_t& w);
    bool		is_finite_app() const;
    T&		supp();
    const T&		supp() const;
    monoid_elt_t	choose_from_supp() const;

    element_t&       	transpose();
      
  protected:
    MetaElement();
    MetaElement(const MetaElement& other);
  };

  template <typename S, typename T>
  T&		
  supp(Element<S, T>& e);

  template <typename S, typename T>
  const T&	
  supp(const Element<S, T>& e);

  template <typename S, typename T>
  bool	
  op_is_finite_app(const SeriesBase<S>& s, const T& t);

  template <typename S, typename T>
  typename MetaElement<SeriesBase<S>, T>::monoid_elt_t 

  op_choose_from_supp(const SeriesBase<S>& s, const T& t);

  template <class S, class T>
  Element<S, T> op_series_choose(const SeriesBase<S>& s, SELECTOR(T));
  
  template <typename S, typename T, typename M, typename W>
  void	
  op_series_set(const SeriesBase<S>& s, const T& t, const W& w);
    
  template <typename S, typename T>
  void	
  op_in_transpose(SeriesBase<S>& s, T& t);

  template <typename S, typename T>
  Element<S, T>
  transpose(const SeriesBase<S>& s, const T& t);

} // vcsn

# include <vaucanson/algebra/concept/series_base.hxx>

#endif // ALGEBRA_SERIES_BASE_HH
