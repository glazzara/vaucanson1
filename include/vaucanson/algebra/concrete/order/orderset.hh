

#ifndef   ORDERSET_HH_
# define   ORDERSET_HH_

#include <vaucanson/algebra/concept/orderset_base.hh>

namespace vcsn {
  
  namespace algebra {

  struct OrderSet
    : OrderSetBase<OrderSet>
  {};
      
  } // algebra

  template<typename T>
  struct MetaElement<OrderSet, T>
    : MetaElement<OrderSetBase<OrderSet>, T>
  {
    static const bool dynamic_set = false;
  };


  template <class T>
  bool op_contains(SELECTOR(OrderSet), T c);

  template <class T>
  bool op_llt(SELECTOR(OrderSet), T lhs, T rhs);

  template <class T>
  bool op_rlt(SELECTOR(OrderSet), T lhs, T rhs);



} // vcsn

#include <vaucanson/algebra/concrete/order/orderset.hxx>

#endif /* !ORDERSET_HH_ */
