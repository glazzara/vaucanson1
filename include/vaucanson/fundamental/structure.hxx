/*------------------------------------------------------------.
| <vaucanson/fundamental/structure.hh>: companion to meta_set |
`------------------------------------------------------------*/
// $Id$

/* this file is part of the Vaucanson project. */
#ifndef FUNDAMENTAL_STRUCTURE_HXX
# define FUNDAMENTAL_STRUCTURE_HXX

# include <vaucanson/fundamental/structure.hh>

# include <vaucanson/internal/traits.hh>

namespace vcsn {
    
    /*----------.
    | Structure |
    `----------*/

    template <typename Self>
    template <typename T>
    bool 
    Structure<Self>::contains(const Element<Self, T>& elt) const
    { 
      return op_contains(self(), elt.value()); 
    }

    template <typename Self>
    template <typename T>
    bool 
    Structure<Self>::contains(const T& elt_value) const
    { 
      return op_contains(self(), elt_value); 
    }
    
    template <typename Self>
    template <typename S, typename T>
    bool 
    Structure<Self>::contains(const Element<S, T>& other) const
    { 
      return false; 
    }
    
    // static inheritance stuff below
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


} // vcsn


/*--------------------.
| default comparisons |
`--------------------*/
template<typename S>
bool operator==(const vcsn::Structure<S>& a,
		const vcsn::Structure<S>& b)
{ 
  return true; 
}

template<typename S>
bool operator!=(const vcsn::Structure<S>& a,
		const vcsn::Structure<S>& b)
{ 
  return !(a == b); 
}

#endif // FUNDAMENTAL_STRUCTURE_HXX
