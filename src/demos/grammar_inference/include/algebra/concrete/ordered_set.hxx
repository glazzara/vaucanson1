
#ifndef   ORDERSET_HXX_
# define   ORDERSET_HXX_

#include <vaucanson/algebra/concept/orderset_base.hh>

#include <iostream>

namespace vcsn {
  
  template <class T>
  bool op_contains(SELECTOR(OrderSet), T c)
  {
    std::cout << "op_contains" << std::endl;
    return true;
  }

  template <class T>
  bool op_llt(SELECTOR(OrderSet), T lhs, T rhs)
  {
    std::cout << "op_llt" << std::endl;
    return lhs < rhs;
  }

  template <class T>
  bool op_rlt(SELECTOR(OrderSet), T lhs, T rhs)
  {
    std::cout << "op_rlt" << std::endl;
    return lhs > rhs;
  }


} // vcsn


#endif /* !ORDERSET_HXX_ */
