/*------------------------------.
| <vaucanson/algebra/slots.hxx> |
`------------------------------*/
// $id$

/* this file is part of the Vaucanson project */
#ifndef FUNDAMENTAL_SLOTS_HXX
# define FUNDAMENTAL_SLOTS_HXX

# include <cstdlib>

# include <vaucanson/fundamental/struct_decl.hh>

namespace vcsn {

  /*-----------------------------------.
    | Base class for SetSlot class below |
    `-----------------------------------*/
  template<typename S, bool dynamic /* default: false */>
  SetSlotAttribute<S, dynamic>::SetSlotAttribute() 
  {}

  template<typename S, bool dynamic /* default: false */>  
  SetSlotAttribute<S, dynamic>::SetSlotAttribute(const SetSlotAttribute& other) 
  {}

  template<typename S, bool dynamic /* default: false */>  
  SetSlotAttribute<S, dynamic>::SetSlotAttribute(const S& other) 
  {}

  template<typename S, bool dynamic /* default: false */>   
  const S& SetSlotAttribute<S, dynamic>::get() const
  {	
    return *static_cast<const S*>(NULL); 
  }

  template<typename S, bool dynamic /* default: false */>   
  S& SetSlotAttribute<S, dynamic>::get()
  { 
      return *static_cast<S*>(NULL); 
  }

  template<typename S, bool dynamic /* default: false */>    
  void SetSlotAttribute<S, dynamic>::assign(const SetSlotAttribute& other)
  {}

  template<typename S, bool dynamic /* default: false */>
  void SetSlotAttribute<S, dynamic>::attach(const S& other)
  {}

  template<typename S, bool dynamic /* default: false */>
  bool SetSlotAttribute<S, dynamic>::bound() const
  { 
    return true; 
  }

  // Specialization when structural element is dynamic

  template <class S>
  SetSlotAttribute<S, true>::SetSlotAttribute() 
    : s_(NULL) 
  {}

  template <class S>  
  SetSlotAttribute<S, true>::SetSlotAttribute(const SetSlotAttribute& other) 
    : s_(other.s_)
  {}

  template <class S>  
  SetSlotAttribute<S, true>::SetSlotAttribute(const S& other) 
    : s_(&other) 
  {}

  template <class S> 
  const S& SetSlotAttribute<S, true>::get() const
  { 
    return *s_; 
  }

  template <class S>
  S& SetSlotAttribute<S, true>::get()
  { 
    return *s_; 
  }

  template <class S>
  void SetSlotAttribute<S, true>::assign(const SetSlotAttribute& other)
  { 
    s_ = other.s_; 
  }

  template <class S>
  void SetSlotAttribute<S, true>::attach(const S& s)
  { 
    s_ = &s; 
  }

  template <class S>
  bool SetSlotAttribute<S, true>::bound() const
  { 
    return s_; 
  }


  /*------------------------------------.
  | Set attribute for the Element class |
  `------------------------------------*/

  template <class S>
  SetSlot<S>::SetSlot()
  {}
  
  template <class S>
  SetSlot<S>::SetSlot(const SetSlot& other)
    : SetSlotAttribute<S, MetaSet<S>::dynamic_set>(other)
  {}

  template <class S>
  SetSlot<S>::SetSlot(const S& other)
    : SetSlotAttribute<S, MetaSet<S>::dynamic_set>(other)
  {}

  /*-------------------------------------.
  | Base class for ValueSlot class below |
  `-------------------------------------*/

  template<typename T, bool dynamic>
  ValueSlotAttribute<T, dynamic>::ValueSlotAttribute() 
  {}
  
  template<typename T, bool dynamic>
  ValueSlotAttribute<T, dynamic>::ValueSlotAttribute(const T& data) 
  {}
  
  template<typename T, bool dynamic>
  ValueSlotAttribute<T, dynamic>::ValueSlotAttribute(const ValueSlotAttribute& other) 
  {}
  
  template<typename T, bool dynamic>
  const T& ValueSlotAttribute<T, dynamic>::get() const
  { 
    return *static_cast<const T*>(NULL); 
  }
  
  template<typename T, bool dynamic>
  T& ValueSlotAttribute<T, dynamic>::get()
  { 
    return *static_cast<T*>(NULL); 
  }

  template<typename T, bool dynamic>
  void ValueSlotAttribute<T, dynamic>::assign(const ValueSlotAttribute& other)
  {}

  template<typename T>
  ValueSlotAttribute<T, true>::ValueSlotAttribute() 
  {}

  template<typename T>
  ValueSlotAttribute<T, true>::ValueSlotAttribute(const T& data) 
    : data_(data) 
  {}

  template<typename T>
  ValueSlotAttribute<T, true>::ValueSlotAttribute(const ValueSlotAttribute& other)
    : data_(other.data_) 
  {}

  template<typename T>
  T& ValueSlotAttribute<T, true>::get()		   
  { 
    return data_; 
  }

  template<typename T>
  const T& ValueSlotAttribute<T, true>::get() const 
  { 
    return data_; 
  }

  template<typename T>
  void ValueSlotAttribute<T, true>::assign(const ValueSlotAttribute& other)
  { 
    data_ = other.data_; 
  }

  /*--------------------------------------.
  | Value attribute for the Element class |
  `--------------------------------------*/

  template <typename S, typename T>
  ValueSlot<S, T>::ValueSlot()
  {}

  template <typename S, typename T>  
  ValueSlot<S, T>::ValueSlot(const ValueSlot& other)
    : ValueSlotAttribute<T, MetaElement<S, T>::dynamic_values>(other)
  {}

  template <typename S, typename T>  
  ValueSlot<S, T>::ValueSlot(const T& other)
    : ValueSlotAttribute<T, MetaElement<S, T>::dynamic_values>(other)
  {}

  template <typename S, typename T>
  ValueSlot<S, T>::operator const T& () const 
  { 
    return get(); 
  }

} // vcsn

/*----------------------------.
| comparison between SetSlots |
`----------------------------*/
template<typename S>
static inline
bool operator==(const vcsn::SetSlotAttribute<S, true>& a,
		const vcsn::SetSlotAttribute<S, true>& b)
{ 
  return a.get() == b.get(); 
}

template<typename S>
static inline
bool operator==(const vcsn::SetSlotAttribute<S, false>& a,
		const vcsn::SetSlotAttribute<S, false>& b)
{ 
  return true; 
}

template<typename S>
static inline
bool operator!=(const vcsn::SetSlotAttribute<S, true>& a,
		const vcsn::SetSlotAttribute<S, true>& b)
{ 
  return !(a.get() == b.get()); 
}

template<typename S>
static inline
bool operator!=(const vcsn::SetSlotAttribute<S, false>& a,
		const vcsn::SetSlotAttribute<S, false>& b)
{ 
  return false; 
}

#endif // ALGEBRA_SLOTS_HXX
