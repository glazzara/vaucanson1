
#ifndef   LATTICE_BASE_HXX_
# define   LATTICE_BASE_HXX_

# include <vaucanson/algebra/concept/lattice_base.hh>

#include <set>

namespace vcsn {

  namespace algebra {

    template<class Self>
    LatticeBase<Self>::LatticeBase()
    {}

    template<class Self>
    LatticeBase<Self>::LatticeBase(const LatticeBase& other)
    {}
    
  } // algebra
  
  template<class Self, typename T>
  MetaElement<LatticeBase<Self>, T>::MetaElement()
  {}
  
  template<class Self, typename T>
  MetaElement<LatticeBase<Self>, T>::MetaElement(const MetaElement& other)
  {}

  template <typename S, typename T>
  std::set<T> get_mins(const Element<S,T>& lhs, 
		       const Element<S,T>& rhs)
  {
    std::cout << "get_min" << std::endl;
    return op_get_mins(lhs.set(), lhs.value(), rhs.value());
  }
  
  template <typename S, typename T>
  Element<S,T> get_max(const Element<S,T>& lhs, 
		       const Element<S,T>& rhs)
  {
    return Element<S,T>(op_get_max(lhs.set(), 
				   lhs.value(), rhs.value()));
  }



} // vcsn


#endif  LATTICE_BASE_HXX_
