// series_base.hh
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
      typedef typename virtual_types<Self>::monoid_t  monoid_t;

      //! The type of the semiring K.
      typedef typename virtual_types<Self>::weights_t weights_t;

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
    template<typename T>
    struct series_traits
    {
      typedef undefined_type	monoid_value_t;
      typedef undefined_type	weight_value_t;
    };

    template <typename T, typename W, typename M>
    struct mute_serie_impl
    {
      typedef undefined_type	ret;
    };

    template <typename T, typename W, typename M>
    struct mute_series_traits
    {
      typedef undefined_type    ret;
    };

    /*! @} @} */

  } // algebra

  /*! \addtogroup algebra */  /* @{ */
  /*! \addtogroup series */ /* @{ */

  /*----------------------------------.
  | dynamic_traits<SeriesBase<Self> > |
  `----------------------------------*/
  template<typename Self>
  struct dynamic_traits<algebra::SeriesBase<Self> >
    : dynamic_traits<algebra::SemiringBase<Self> >
  {};

  template<typename S>
  struct virtual_types<algebra::SeriesBase<S> >
    : virtual_types<algebra::SemiringBase<S> >
  {
    typedef undefined_type monoid_t;
    typedef undefined_type weights_t;
  };
  
  /*---------------------------------.
  | MetaElement<SeriesBase<Self>, T> |
  `---------------------------------*/
  //! Services of every serie.
  template<class Self, typename T>
  class MetaElement<algebra::SeriesBase<Self>, T> 
    : public MetaElement<algebra::SemiringBase<Self>, T>
  {
  public:
    //! type of the implementation of weight (element of semiring).
    typedef typename algebra::series_traits<T>::weight_value_t   weight_value_t;

    //! type of the implementation of free monoid element.
    typedef typename algebra::series_traits<T>::monoid_value_t    monoid_value_t;

    //! type of the element of the semiring element.
    typedef Element<typename Self::weights_t, weight_value_t> weight_t;

    //! type of the element of the monoid.
    typedef Element<typename Self::monoid_t, monoid_value_t>	 monoid_elt_t;

    //! type of the serie.
    typedef Element<Self, T>				 element_t;

    //! type of the iterator over the series when finite.
    typedef typename algebra::series_traits<T>::support_t	support_t;

    //! returns the weight associated to a word. 
    weight_value_t	value_get(const monoid_value_t& m) const;

    //! returns the weight associated to a word. 
    weight_t		get(const monoid_elt_t& m) const;

    //! associates a weight to a word. 
    void		value_set(const monoid_value_t& m, 
				  const weight_value_t& w);

    //! associates a weight to a word. 
    void		assoc(const monoid_elt_t& m, const weight_t& w);

    //! returns true if the serie support is finite.
    bool		is_finite_app() const;

    //! returns a word that is in the support of the serie.
    monoid_elt_t	choose_from_supp() const;

    //! in-place transpose transformation of the serie.
    void       	        transpose();

    //! returns a container which is the support of the serie.
    //! The container elements are couples (m, k) where m is in
    //! the support and k is the image of m by the serie.
    //! The support is accessible only if is_finite_app is true.
    support_t		supp() const;

  protected:
    //! Default constructor is protected since it is an abstract class.
    MetaElement();

    //! Copy constructor is protected since it is an abstract class.
    MetaElement(const MetaElement& other);
  };

  //! returns a fresh serie that is the transposed of the argument.
  template <typename S, typename T>
  Element<S, T>
  transpose(const algebra::SeriesBase<S>& s, const T& t);

  //! returns true if the support of the serie is only composed of
  //! letters.
  template <typename S, typename T>
  bool
  is_letter_support(const Element<S, T>& s);

  //! make the first serie be the support of the second. 
  template <typename S1, typename S2, typename T1, typename T2>
  void
  extract_support(Element<S1, T1>&, Element<S2, T2>&);

  //! return the hadamard product of lhs and rhs.
  template <class S, class T>
  Element<S, T> hadamard(const Element<S, T>& lhs,
			 const Element<S, T>& rhs);
  
  /*! @} @} */

  template <typename S, typename T>
  bool	
  op_is_finite_app(const algebra::SeriesBase<S>& s, const T& t);

  template <typename S, typename T>
  typename MetaElement<algebra::SeriesBase<S>, T>::monoid_elt_t 

  op_choose_from_supp(const algebra::SeriesBase<S>& s, const T& t);

  template <class S, class T>
  Element<S, T> op_series_choose(const algebra::SeriesBase<S>& s, SELECTOR(T));
  
  template <typename S, typename T, typename M, typename W>
  void	
  op_series_set(const algebra::SeriesBase<S>& s, const T& t, const W& w);

  template <class S, class T>
  typename algebra::series_traits<T>::support_t
  op_support(const algebra::SeriesBase<S>&, const T& v);

} // vcsn

# include <vaucanson/algebra/concept/series_base.hxx>

#endif // VCSN_ALGEBRA_SERIES_BASE_HH
