// alphabets_base.hxx
//
// VCSN_HEADER

#ifndef ALGEBRA_ALPHABETS_BASE_HXX
# define ALGEBRA_ALPHABETS_BASE_HXX

# include <vaucanson/algebra/concept/alphabets_base.hh>
# include <vaucanson/misc/container_ops.hh>
# include <vaucanson/misc/random.hh>

namespace vcsn {

  namespace algebra {

    /*--------------------.
    | AlphabetsBase<Self> |
    `--------------------*/

    template<class Self>
    AlphabetsBase<Self>::AlphabetsBase()
    {}

    template<class Self>
    AlphabetsBase<Self>::AlphabetsBase(const AlphabetsBase& other) 
    {}

  } // algebra

  using namespace algebra;
  
    /*------------------------------------.
    | MetaElement<AlphabetsBase<Self>, T> |
    `------------------------------------*/
    // Meta-information about element formed from an AlphabetsBase
    // structuring element.
    
    template<class Self, typename T>
    size_t 
    MetaElement<AlphabetsBase<Self>, T>::size() const
    { 
      return op_size(set(), value()); 
    }
    
    template<class Self, typename T>
    bool 
    MetaElement<AlphabetsBase<Self>, T>::contains(const letter_t& l) const
    { 
      return op_contains_e(set(), value(), l); 
    }
    
    template<class Self, typename T>
    bool 
    MetaElement<AlphabetsBase<Self>, T>::is_finite() const
    { 
      return op_is_finite(set(), value()); 
    }
    
    template<class Self, typename T>
    MetaElement<AlphabetsBase<Self>, T>::iterator 
    MetaElement<AlphabetsBase<Self>, T>::begin() 
    { 
      return op_begin(set(), value()); 
    }
    
    template<class Self, typename T> 
    MetaElement<AlphabetsBase<Self>, T>::const_iterator 
    MetaElement<AlphabetsBase<Self>, T>::begin() const
    { 
      return op_begin(set(), value()); 
    }
    
    template<class Self, typename T>
    MetaElement<AlphabetsBase<Self>, T>::iterator 
    MetaElement<AlphabetsBase<Self>, T>::end() 
    { 
      return op_end(set(), value()); 
    }
    
    template<class Self, typename T>
    MetaElement<AlphabetsBase<Self>, T>::const_iterator 
    MetaElement<AlphabetsBase<Self>, T>::end() const
    { 
      return op_end(set(), value()); 
    }
    
    template<class Self, typename T>
    void 
    MetaElement<AlphabetsBase<Self>, T>::insert(const letter_t& l) 
    { 
      op_insert(set(), value(), l); 
    }
    
  template<class Self, typename T>
  typename alphabet_traits<Self, T>::letter_t
  MetaElement<AlphabetsBase<Self>, T>::choose() const
  { 
    assert (this->size() > 0);
    int  n = this->size() - 1;
    int  c = ((unsigned) trunc(((float) random() / (float) RAND_MAX) * n));

    iterator it = this->begin();

    for (int k = 0; k < c; ++k)
      ++it;

    return *it;
  }

  template <class Self, typename T>
  typename alphabet_traits<Self, T>::letter_t
  MetaElement<AlphabetsBase<Self>, T>::random_letter() const
  {
    return
      misc::RandomGenerator<typename alphabet_traits<Self, T>::letter_t>
      ::do_it();
  }


  template<class Self, typename T>
  MetaElement<AlphabetsBase<Self>, T>::MetaElement() 
  {}
    
    template<class Self, typename T>
    MetaElement<AlphabetsBase<Self>, T>::MetaElement(const MetaElement& other) :
      MetaElement<Structure<Self>, T>(other)
    {}
  
    template<typename Self, typename St, typename T>
    St& op_rout(const AlphabetsBase<Self>& s, St& st, const T& a)
    {
      st << "{ ";
      if (op_is_finite(s.self(), a))
	for (typename op_begin_traits<Self, T>::const_ret_t i = op_begin(s.self(), a);
	     i != op_end(s.self(), a);
	     ++i)
	  {
	    if (i != op_begin(s.self(), a))
	      st << ", ";
	    st << *i;
	  }
      else
	st << "<many letters>";
      st << " }";
      return st;
    }

} // vcsn

#endif // ALGEBRA_ALPHABETS_BASE_HXX
