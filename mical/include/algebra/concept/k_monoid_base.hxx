// freemonoid_base.hxx
//
// MICAL_HEADER

#ifndef K_MONOID_BASE_HXX
# define K_MONOID_BASE_HXX

# include <algebra/concept/k_monoid_base.hh>

namespace vcsn {

  namespace algebra {

    /*---------------------.
    | FreeMonoidBase<Self> |
    `---------------------*/
    template <class Self>
    typename KMonoidBase<Self>::alphabet_t& 
    KMonoidBase<Self>::alphabet() 
    { 
      return self().alphabet(); 
    }
    
    template <class Self>
    const typename KMonoidBase<Self>::alphabet_t& 
    KMonoidBase<Self>::alphabet() const
    { 
      return self().alphabet(); 
    }
    
    template <class Self>
    KMonoidBase<Self>::KMonoidBase() 
    {}
    
    template <class Self>
    KMonoidBase<Self>::KMonoidBase(const KMonoidBase& m) :
      MonoidBase<Self>(m)
    {}

  } // algebra 

  using namespace algebra;

  /*-------------------------------------.
  | MetaElement<KMonoidBase<Self>, T> |
  `-------------------------------------*/
  template <class Self, typename T>
  size_t 
  MetaElement<KMonoidBase<Self>, T>::length() const
  { 
    return op_size(this->set(), this->value()); 
  }

  template <class Self, typename T>
  typename MetaElement<KMonoidBase<Self>, T>::iterator 
  MetaElement<KMonoidBase<Self>, T>::begin() 
  { 
    return op_begin(this->set(), this->value()); 
  }
    
  template <class Self, typename T>
  typename MetaElement<KMonoidBase<Self>, T>::const_iterator 
  MetaElement<KMonoidBase<Self>, T>::begin() const
  { 
    return op_begin_const(this->set(), this->value()); 
  }
    
  template <class Self, typename T>
  typename MetaElement<KMonoidBase<Self>, T>::reverse_iterator 
  MetaElement<KMonoidBase<Self>, T>::rbegin()
  { 
    return op_rbegin(this->set(), this->value()); 
  }
    
  template <class Self, typename T>
  typename MetaElement<KMonoidBase<Self>, T>::const_reverse_iterator 
  MetaElement<KMonoidBase<Self>, T>::rbegin() const
  { 
    return op_rbegin(this->set(), this->value()); 
  }
    
  template <class Self, typename T>
  typename MetaElement<KMonoidBase<Self>, T>::iterator 
  MetaElement<KMonoidBase<Self>, T>::end() 
  { 
    return op_end(this->set(), this->value()); 
  }
    
  template <class Self, typename T>
  typename MetaElement<KMonoidBase<Self>, T>::const_iterator 
  MetaElement<KMonoidBase<Self>, T>::end() const
  { 
    return op_end(this->set(), this->value()); 
  }
    
  template <class Self, typename T>
  typename MetaElement<KMonoidBase<Self>, T>::reverse_iterator 
  MetaElement<KMonoidBase<Self>, T>::rend()
  { 
    return op_rend(this->set(), this->value()); 
  }
    
  template <class Self, typename T>
  typename MetaElement<KMonoidBase<Self>, T>::const_reverse_iterator 
  MetaElement<KMonoidBase<Self>, T>::rend() const
  { 
    return op_rend(this->set(), this->value()); 
  }

  template <class Self, typename T>
  void
  MetaElement<KMonoidBase<Self>, T>::
  insert(typename KMonoidBase<Self>::letter_t l)
  {
    op_insert(this->set(), this->value(), l, k_);
  }
  
  template <class Self, typename T>
  void
  MetaElement<KMonoidBase<Self>, T>::
  insert(Element<FreeMonoid<typename KMonoidBase<Self>::alphabet_t>, T> str)
  {
    typedef Element<FreeMonoid<typename KMonoidBase<Self>::alphabet_t>, T> Word;

    for (typename Word::iterator i = str.begin(); i != str.end(); i++)
      insert(*i);
  }

  template <class Self, typename T>
  void 
  MetaElement<KMonoidBase<Self>, T>::
  clear()
  {
    op_clear(this->set(), this->value());
  }

  template <class Self, typename T>
  MetaElement<KMonoidBase<Self>, T>::MetaElement() 
  {}
    
  template <class Self, typename T>
  MetaElement<KMonoidBase<Self>, T>::MetaElement(const MetaElement& o) :
    MetaElement<MonoidBase<Self>, T>()
  {}

  /*-------------------.
  | External functions |
  `-------------------*/


  template <typename Self, typename T>
  bool 
  op_contains(const KMonoidBase<Self>& s, const T& v)
  { 
    typedef typename op_begin_traits<Self, T>::const_ret_t const_iterator;

    for (const_iterator i = op_begin(s.self(), v);
	 i != op_end(s.self(), v);
	 ++i)
      if (! s.alphabet().contains(*i))
	return false;
    return true;
  }


} // vcsn

#endif // K_MONOID_BASE_HXX
