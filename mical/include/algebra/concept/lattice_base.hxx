// lattice_base.hxx

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

  
  // constructors
  
  template<class Self, typename T>
  MetaElement<LatticeBase<Self>, T>::MetaElement()
  {}
  
  template<class Self, typename T>
  MetaElement<LatticeBase<Self>, T>::MetaElement(const MetaElement& other)
  {}



  // return the set of tallest minorants
  template <typename S, typename T>
  std::set<T> get_mins(const Element<S,T>& lhs, 
		       const Element<S,T>& rhs)
  {
    std::cout << "get_mins" << std::endl;
    return op_get_mins(lhs.set(), lhs.value(), rhs.value());
  }
  
  // return the set of tallest majorants
  template <typename S, typename T>
  Element<S,T> get_maxs(const Element<S,T>& lhs, 
		       const Element<S,T>& rhs)
  {
    std::cout << "get_maxs" << std::endl;
    return Element<S,T>(op_get_maxs(lhs.set(), 
				    lhs.value(), rhs.value()));
  }



} // vcsn


#endif  LATTICE_BASE_HXX_
