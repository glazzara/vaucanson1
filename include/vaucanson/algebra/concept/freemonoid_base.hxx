/******************************************
 * <vaucanson/algebra/freemonoid_base.hxx> *
 ******************************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef ALGEBRA_FREEMONOID_BASE_HXX
# define ALGEBRA_FREEMONOID_BASE_HXX

# include <vaucanson/algebra/concept/freemonoid_base.hh>

namespace vcsn {

  namespace algebra {

    /*---------------------.
    | FreeMonoidBase<Self> |
    `---------------------*/
    template<class Self>
    typename FreeMonoidBase<Self>::alphabet_t& 
    FreeMonoidBase<Self>::alphabet() 
    { 
      return self().alphabet(); 
    }
    
    template<class Self>
    const typename FreeMonoidBase<Self>::alphabet_t& 
    FreeMonoidBase<Self>::alphabet() const
    { 
      return self().alphabet(); 
    }
    
    template<class Self>
    FreeMonoidBase<Self>::FreeMonoidBase() 
    {}
    
    template<class Self>
    FreeMonoidBase<Self>::FreeMonoidBase(const FreeMonoidBase& m) :
      MonoidBase<Self>(m)
    {}

  } // algebra 

  using namespace algebra;

    /*-------------------------------------.
    | MetaElement<FreeMonoidBase<Self>, T> |
    `-------------------------------------*/
    template<class Self, typename T>
    size_t 
    MetaElement<FreeMonoidBase<Self>, T>::length() const
    { 
      return op_size(set(), value()); 
    }

    template<class Self, typename T>
    Element<Self, T>&
    MetaElement<FreeMonoidBase<Self>, T>::mirror()
    {
      op_in_mirror(set(), value());
      return self();
    }

    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::iterator 
    MetaElement<FreeMonoidBase<Self>, T>::begin() 
    { 
      return op_begin(set(), value()); 
    }
    
    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::const_iterator 
    MetaElement<FreeMonoidBase<Self>, T>::begin() const
    { 
      return op_begin(set(), value()); 
    }
    
    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::reverse_iterator 
    MetaElement<FreeMonoidBase<Self>, T>::rbegin()
    { 
      return op_rbegin(set(), value()); 
    }
    
    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::const_reverse_iterator 
    MetaElement<FreeMonoidBase<Self>, T>::rbegin() const
    { 
      return op_rbegin(set(), value()); 
    }
    
    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::iterator 
    MetaElement<FreeMonoidBase<Self>, T>::end() 
    { 
      return op_end(set(), value()); 
    }
    
    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::const_iterator 
    MetaElement<FreeMonoidBase<Self>, T>::end() const
    { 
      return op_end(set(), value()); 
    }
    
    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::reverse_iterator 
    MetaElement<FreeMonoidBase<Self>, T>::rend()
    { 
      return op_rend(set(), value()); 
    }
    
    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::const_reverse_iterator 
    MetaElement<FreeMonoidBase<Self>, T>::rend() const
    { 
      return op_rend(set(), value()); 
    }

    template<class Self, typename T>
    MetaElement<FreeMonoidBase<Self>, T>::MetaElement() 
    {}
    
    template<class Self, typename T>
    MetaElement<FreeMonoidBase<Self>, T>::MetaElement(const MetaElement& o) :
      MetaElement<MonoidBase<Self>, T>(o)
    {}

    /*-------------------.
    | External functions |
    `-------------------*/

    template<typename S, typename T>
    Element<S, T>
    mirror(const Element<S, T>& e)
    {
      Element<S, T>	ret(e);
      return ret.mirror();
    }
    
    template<typename Self, typename T>
    void 
    op_in_mirror(const FreeMonoidBase<Self>& s, T& v)
    {
      const T		new_v(v);
      typename MetaElement<FreeMonoidBase<Self>, T>::iterator  it 
	= op_begin(s.self(), v);

      for (typename MetaElement<FreeMonoidBase<Self>, T>::
	     const_reverse_iterator i = op_rbegin(s.self(), new_v);
	   i != op_rend(s.self(), new_v);
	   ++i)
	*it++ = *i;
    }

    template<typename Self, typename T>
    bool 
    op_contains(const FreeMonoidBase<Self>& s, const T& v)
    { 
      typedef typename op_begin_traits<Self, T>::const_ret_t const_iterator;

      for (const_iterator i = op_begin(s.self(), v);
	   i != op_end(s.self(), v);
	   ++i)
	if (! s.alphabet().contains(*i))
	  return false;
      return true;
    }

    template<typename Self, typename St, typename T>
    St& 
    op_rout(const FreeMonoidBase<Self>& s,
	    St& st, 
	    const T& v)
    {
      typedef typename op_begin_traits<Self, T>::const_ret_t const_iterator;
      
      for (const_iterator i = op_begin(s.self(), v);
	   i != op_end(s.self(), v);
	   ++i)
	st << *i;
      return st;
    }

} // vcsn

#endif // ALGEBRA_FREEMONOID_BASE_HXX
