
#ifndef   LATTICE_BASE_HH_
# define   LATTICE_BASE_HH_

# include <vaucanson/algebra/concept/orderset_base.hh>

#include <set>

namespace vcsn {

  namespace algebra {

    template<class Self>
    struct LatticeBase 
      : OrderSetBase<Self>
    {
    protected:
      
      //! Default constructor is protected since it is an abstract class.
      LatticeBase();
      
      //! Copy constructor is protected since it is an abstract class.
      LatticeBase(const LatticeBase& other);
    };
    
  } // algebra
  
  using namespace algebra;

    template<class Self, typename T>
    struct MetaElement<LatticeBase<Self>, T> 
      : MetaElement<OrderSetBase<Self>, T>
    { 
      
      typedef T lattice_value_t;
      typedef Self lattice_elt_t;
      
     protected:
      //! Default constructor is protected since it is an abstract class.
      MetaElement();
      
      //! Copy constructor is protected since it is an abstract class.
      MetaElement(const MetaElement& other);
    };

  template <typename S, typename T>
  std::set<T> get_mins(const Element<S,T>& lhs, 
		       const Element<S,T>& rhs);
  
  template <typename S, typename T>
  Element<S,T> get_max(const Element<S,T>& lhs, 
		       const Element<S,T>& rhs);
  

} // vcsn

#include <vaucanson/algebra/concept/lattice_base.hxx>

#endif /* !LATTICE_BASE_HH_ */
