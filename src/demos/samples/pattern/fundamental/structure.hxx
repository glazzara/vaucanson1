

 template <typename Self>
  template <typename T>
  bool 
  Structure<Self>::contains(const Element<Self, T>& elt) const
  { 
    return op_contains(self(), elt.value()); 
  }

  template <typename Self>
  template <typename S, typename T>
  bool 
  Structure<Self>::contains(const Element<S, T>& other) const
  { 
    return false; 
  }

  template <typename Self>
  Self&        
  Structure<Self>::self()
  { 
    return static_cast<self_t&>(*this); 
  }
    
  template <typename Self>
  const Self&  
  Structure<Self>::self() const 
  { 
    return static_cast<const self_t&>(*this); 
  }
    
  template <typename Self>
  Structure<Self>::Structure()
  {}

  template <typename Self>
  Structure<Self>::Structure(const Structure&)
  {}
