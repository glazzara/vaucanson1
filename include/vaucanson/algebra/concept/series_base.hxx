// series_base.hxx
//
// $Id$
// VCSN_HEADER

#ifndef ALGEBRA_SERIES_BASE_HXX
# define ALGEBRA_SERIES_BASE_HXX

# include <vaucanson/algebra/concept/series_base.hh>

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

    /*--------------------.
    | DefaultTransposeFun |
    `--------------------*/


    /*---------------------------------.
    | MetaElement<SeriesBase<Self>, T> |
    `---------------------------------*/
    
    template<typename S, typename T>
    typename MetaElement<SeriesBase<S>, T>::weights_value_t 
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
						const weights_value_t& w) 
    { 
      // assert(set().monoid().contains(m));
      // assert(set().weights().contains(w));
      return op_series_set(set(), value(), m, w);
    }

    // without this definition, the one following gives an ambiguity
    template<typename S, typename T>
    const S& 
    MetaElement<SeriesBase<S>, T>::set() const
    { 
      return self().set(); 
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

    template<typename S, typename T>
    T& 
    MetaElement<SeriesBase<S>, T>::supp() 
    { 
      return value(); 
    }

    template<typename S, typename T>
    const T& 
    MetaElement<SeriesBase<S>, T>::supp() const 
    { 
      return value(); 
    }

    template <typename S, typename T>
    typename MetaElement<SeriesBase<S>, T>::monoid_elt_t
    MetaElement<SeriesBase<S>, T>::choose_from_supp() const
    {
      return op_choose_from_supp(set(), value());
    }

    template <typename S, typename T>
    Element<S, T>&       	
    MetaElement<SeriesBase<S>, T>::transpose()
    {
      op_in_transpose(set(), value());
    }

    template<typename S, typename T>
    MetaElement<SeriesBase<S>, T>::MetaElement() 
    {}
    
    template<typename S, typename T>
    MetaElement<SeriesBase<S>, T>::MetaElement(const MetaElement& other) :
      MetaElement<SemiringBase<S>, T>(other)
    {}
    
    template<typename S, typename T>
    T& supp(Element<S, T>& e)
    { 
      return e.supp(); 
    }
    
    template<typename S, typename T>
    const T& supp(const Element<S, T>& e)
    { 
      return e.supp(); 
    }
    
    template<typename S, typename T>
    bool op_is_finite_app(const SeriesBase<S>& s, const T& t)
    { 
      return false; 
    }
    
    template<typename S, typename T, typename M, typename W>
    void op_series_set(const SeriesBase<S>& s, const T& t, const W& w)
    {
      assert(! "defined");
    }

    template <typename S, typename T>
    Element<S, T>
    transpose(const SeriesBase<S>& s, const T& t)
    {
      T	new_t(t);
      new_t.transpose();
      return new_t;
    }

  } // algebra
  
} // vcsn

#endif // ALGEBRA_SERIES_BASE_HXX
