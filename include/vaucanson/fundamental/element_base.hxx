/****************************************
 * <vaucanson/algebra/element_base.hxx> *
 ****************************************/
// $Id$

/* this file is part of the Vaucanson project. */
#ifndef ALGEBRA_ELEMENT_BASE_HXX
# define ALGEBRA_ELEMENT_BASE_HXX

# include <vaucanson/fundamental/element_base.hh>

namespace vcsn
{
  namespace algebra
  {

    template <typename S, typename T> 
    inline const S& 
    MetaElementBase<S, T>::set() const 
    { 
      return self().set(); 
    }

    template <typename S, typename T>
    inline T& 
    MetaElementBase<S, T>::value()
    { 
      return self().value(); 
    }
    
    template <typename S, typename T>
    inline const T& 
    MetaElementBase<S, T>::value() const
    { 
      return self().value(); 
    }
    
    // it can happen that we want different behaviours depending
    // on the set the value comes from. Hence the third argument.

#define ELEMENT_IN_OPERATOR(Op, HookName)				 \
      template <typename S, typename T>					 \
      template<typename OtherS, typename U>				 \
      inline Element<S, T>&						 \
      MetaElementBase<S, T>::Op (const Element<OtherS, U>& other)	 \
      {									 \
	op_in_ ## HookName (set(), other.set(), value(), other.value()); \
	return self();							 \
      }									 \
      template <typename S, typename T>					 \
      template<typename U>						 \
      inline Element<S, T>&						 \
      MetaElementBase<S, T>::Op (const U& other)			 \
      {									 \
	op_in_ ## HookName (set(), value(),				 \
			    op_convert(SELECT(T), SELECT(S), other));	 \
	return self();							 \
      }

    ELEMENT_IN_OPERATOR(operator +=, add);
    ELEMENT_IN_OPERATOR(operator -=, sub);
    ELEMENT_IN_OPERATOR(operator /=, div);
    ELEMENT_IN_OPERATOR(operator *=, mul);
    ELEMENT_IN_OPERATOR(operator %=, mod);
    
#undef ELEMENT_IN_OPERATOR

    template <typename S, typename T>
    inline Element<S, T>& 
    MetaElementBase<S, T>::operator++()
    { 
      op_in_inc(set(), value()); 
      return self(); 
    }
    
    template <typename S, typename T>
    inline Element<S, T> 
    MetaElementBase<S, T>::operator++(int)
    { 
      Element<S, T> ret(*this); 
      op_in_inc(set(), value()); 
      return ret; 
    }
    
    template <typename S, typename T>
    inline Element<S, T>& 
    MetaElementBase<S, T>::operator--()
    { 
      op_in_dec(set(), value()); 
      return self(); 
    }
    
    template <typename S, typename T>
    inline Element<S, T> 
    MetaElementBase<S, T>::operator--(int)
    { 
      Element<S, T> ret(*this); 
      op_in_dec(set(), value()); 
      return ret; 
    }
    
    template <typename S, typename T>
    template <typename U>
    inline Element<S, T>& 
    MetaElementBase<S, T>::swap(Element<S, U>& other)
    { 
      op_swap(SELECT(S), value(), other.value());
      return self(); 
    }
    
    template <typename S, typename T>
    template <typename OtherS, typename U>
    inline Element<S, T>&
    MetaElementBase<S, T>::swap(Element<OtherS, U>& other)
    { 
      op_swap(SELECT(S), SELECT(OtherS), value(), other.value());
      return self(); 
    }
    
    // static inheritance stuff. what's good is that we know
    // at this point the derived type.
    template <typename S, typename T>
    inline Element<S, T>&
    MetaElementBase<S, T>::self() 
    { 
      return static_cast<Element<S, T>&>(*this); 
    }
    
    template <typename S, typename T>
    inline const Element<S, T>& 
    MetaElementBase<S, T>::self() const
    { 
      return static_cast<const Element<S, T>&>(*this); 
    }
    
    template <typename S, typename T>
    inline MetaElementBase<S, T>::MetaElementBase() 
    {}
    
    template <typename S, typename T>
    inline MetaElementBase<S, T>::MetaElementBase(const MetaElementBase& other) 
    {} 

  } // algebra

} // vcsn

#endif // ALGEBRA_ELEMENT_BASE_HXX
