// series_base.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef VCSN_ALGEBRA_SERIES_BASE_HH
# define VCSN_ALGEBRA_SERIES_BASE_HH

# include <vaucanson/algebra/concept/semiring_base.hh>

namespace vcsn {

  namespace algebra {

    /*! \addtogroup algebra */  /* @{ */
    /*! \addtogroup series */ /* @{ */

    /*-----------------.
    | SeriesBase<Self> |
    `-----------------*/
    //! Structural element of series K<A*> from a free monoid A* to a
    //! semiring K.
    template<class Self>
    struct SeriesBase 
      : SemiringBase<Self>
    {
      //! The type of the free monoid A*.
      typedef typename traits::virtual_types<Self>::monoid_t  monoid_t;

      //! The type of the semiring K.
      typedef typename traits::virtual_types<Self>::weights_t weights_t;

      //! Accessor to the monoid (const version).
      const monoid_t&	monoid() const;      

      //! Accessor to the semiring (const version).
      const weights_t&  weights() const;

      //! Accessor to the monoid.
      monoid_t&		monoid();

      //! Accessor to the semiring.      
      weights_t&	weights(); 

    protected:
      //! Default constructor is protected since it is an abstract class.
      SeriesBase();

      //! Copy constructor is protected since it is an abstract class.
      SeriesBase(const SeriesBase& other);
    };

    //! Meta information about series.
    template<typename S, typename T>
    struct series_traits
    {};

    /*! @} @} */

  } // algebra

  /*! \addtogroup algebra */  /* @{ */
  /*! \addtogroup series */ /* @{ */

  /*---------------------------------.
  | MetaElement<SeriesBase<Self>, T> |
  `---------------------------------*/
  //! Services of every serie.
  template<class Self, typename T>
  class MetaElement<SeriesBase<Self>, T> 
    : public MetaElement<SemiringBase<Self>, T>
  {
  public:
    //! type of the implementation of weight (element of semiring).
    typedef typename series_traits<Self, T>::weights_value_t   weights_value_t;

    //! type of the implementation of free monoid element.
    typedef typename series_traits<Self, T>::monoid_value_t    monoid_value_t;

    //! type of the element of the semiring (element).
    typedef Element<typename Self::weights_t, weights_value_t> weight_t;

    //! type of the element of the monoid.
    typedef Element<typename Self::monoid_t, monoid_value_t>	 monoid_elt_t;

    //! type of the serie.
    typedef Element<Self, T>					 element_t;

    //! returns the weight associated to a word. 
    weights_value_t	value_get(const monoid_value_t& m) const;

    //! returns the weight associated to a word. 
    weight_t		get(const monoid_elt_t& m) const;

    //! associates a weight to a word. 
    void		value_set(const monoid_value_t& m, 
				  const weights_value_t& w);

    //! associates a weight to a word. 
    void		assoc(const monoid_elt_t& m, const weight_t& w);

    //! returns true if the serie support is finite.
    bool		is_finite_app() const;

    //! returns a word that is in the support of the serie.
    monoid_elt_t	choose_from_supp() const;

    //! in-place transpose transformation of the serie.
    void       	transpose();

    // undocumented.
    const Self&	set() const;

    // undocumented.
    T&		supp();

    // undocumented.
    const T&		supp() const;
      
  protected:
    //! Default constructor is protected since it is an abstract class.
    MetaElement();

    //! Copy constructor is protected since it is an abstract class.
    MetaElement(const MetaElement& other);
  };

  //! returns a fresh serie that is the transposed of the argument.
  template <typename S, typename T>
  Element<S, T>
  transpose(const SeriesBase<S>& s, const T& t);

  /*! @} @} */

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
    
 //  template <typename S, typename T>
//   void	
//   op_in_transpose(const SeriesBase<S>& s, T& t);

} // vcsn

# include <vaucanson/algebra/concept/series_base.hxx>

#endif // VCSN_ALGEBRA_SERIES_BASE_HH
