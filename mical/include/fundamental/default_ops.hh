// default_ops.hh
// 
// MICAL_HEADER

#ifndef   DEFAULT_OPS_HH_
# define   DEFAULT_OPS_HH_

#include <vaucanson/fundamental/default_ops.hh>

namespace mical {

  using namespace vcsn;
  
  template<typename S, typename T>
  bool op_clear(const Structure<S>& set, const T& value)
  {
    value.clear();
  }



} // mical


#endif /* !DEFAULT_OPS_HH_ */
