
#ifndef   ORDERSET_BASE_HXX_
# define   ORDERSET_BASE_HXX_

#include <vaucanson/algebra/concept/orderset_base.hh>

namespace vcsn {

  namespace algebra {

    template<class Self>
    OrderSetBase<Self>::OrderSetBase()
    {}
    
    template<class Self>
    OrderSetBase<Self>::OrderSetBase(const OrderSetBase& other) 
    {}

  } // algebra

  using namespace algebra;
  
  template<class Self, typename T>
  MetaElement<OrderSetBase<Self>, T>::MetaElement()
  {}
  

  template<class Self, typename T>
  MetaElement<OrderSetBase<Self>, T>::MetaElement(const MetaElement& other)
  {}
  
} // vcsn




#endif /* !ORDERSET_BASE_HXX_ */
