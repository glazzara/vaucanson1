
#ifndef   LATTICE_HXX_
# define   LATTICE_HXX_

#include <vaucanson/algebra/concrete/order/lattice.hh>

#include <set>

namespace vcsn {

  template<typename T>
  std::set<T>
  op_get_mins(const algebra::Lattice& Lat, T lhs, T rhs)
  {
    std::cout << "op_get_mins" << std::endl;
    return op_get_prevs(Lat, op_min(lhs, rhs));
  }

  std::set<unsigned>
  op_get_prevs(const algebra::Lattice& Lat, unsigned elt)
  {
    std::set<unsigned> res;

    std::cout << "op_get_prevs" << std::endl;

    if (elt)
      res.insert(elt - 1);
    else
      res.insert(elt);
    
    return res;
  }
    
  unsigned op_min(unsigned lhs, unsigned rhs)
  {
    if (lhs < rhs)
      return lhs;
    return rhs;
  }
  


} // vcsn


#endif /* !LATTICE_HXX_ */
