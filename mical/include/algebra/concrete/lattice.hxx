// lattice.hxx

#ifndef   LATTICE_HXX_
# define   LATTICE_HXX_

#include <vaucanson/algebra/concrete/order/lattice.hh>

#include <set>

namespace vcsn {

  // operators for minorants

  template<typename T>
  std::set<T>
  op_get_mins(const algebra::Lattice& Lat, T lhs, T rhs)
  {
    return op_get_prevs(Lat, op_min(lhs, rhs));
  }

  std::set<unsigned>
  op_get_prevs(const algebra::Lattice& Lat, unsigned elt)
  {
    std::set<unsigned> res;

    if (elt)
      res.insert(elt - 1);
    else
      res.insert(elt);
    
    return res;
  }
    
  template<typename T>
  T op_min(T lhs, T rhs)
  {
    if (lhs < rhs)
      return lhs;
    return rhs;
  }
  

  // operators for majorants
  
  template<typename T>
  std::set<T>
  op_get_maxs(const algebra::Lattice& Lat, T lhs, T rhs)
  {
    return op_get_nexts(Lat, op_max(lhs, rhs));
  }

  std::set<unsigned>
  op_get_nexts(const algebra::Lattice& Lat, unsigned elt)
  {
    std::set<unsigned> res;
    
    res.insert(elt + 1);
    
    return res;
  }
  
  template<typename T>
  T op_max(T lhs, T rhs)
  {
    if (lhs > rhs)
      return lhs;
    return rhs;
  }
  
} // vcsn


#endif /* !LATTICE_HXX_ */
