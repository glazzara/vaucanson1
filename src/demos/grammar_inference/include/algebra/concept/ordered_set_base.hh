
#ifndef   ORDERSET_BASE_HH_
# define   ORDERSET_BASE_HH_

# include <vaucanson/fundamental/fundamental.hh>

namespace vcsn {

  namespace algebra {

    template<class Self>
    struct OrderSetBase 
      : Structure<Self>
    {
    protected:
      
      //! Default constructor is protected since it is an abstract class.
      OrderSetBase();
      
      //! Copy constructor is protected since it is an abstract class.
      OrderSetBase(const OrderSetBase& other);
    };
    
  } // algebra
  
  using namespace algebra;

  template<class Self, typename T>
  struct MetaElement<OrderSetBase<Self>, T> 
    : MetaElement<Structure<Self>, T>
  { 
  protected:
    //! Default constructor is protected since it is an abstract class.
    MetaElement();
      
    //! Copy constructor is protected since it is an abstract class.
    MetaElement(const MetaElement& other);
  };

#include <vaucanson/algebra/concept/orderset_base.hxx>


} // vcsn

#endif /* !ORDERSET_BASE_HH_ */
