// lattice.hh

#ifndef   LATTICE_HH_
# define   LATTICE_HH_

#include <vaucanson/algebra/concept/lattice_base.hh>

#include <set>

namespace vcsn {

  namespace algebra {

    struct Lattice
      : LatticeBase<Lattice>
    {};

  } // algebra
  
  using namespace algebra;


  template<typename T>
  struct MetaElement<Lattice, T>
    : MetaElement<LatticeBase<Lattice>, T>
  {
    static const bool dynamic_set = false;
  };
  
  // trivial code -> more intelligent structure 
  // is needed than std::set for operators return 
  // (non-explicit presence of elts in the set for case of 
  // important number of minorants / majorants)

  // operators for minorants 

  template<typename T>
  std::set<T> 
  op_get_mins(const Lattice& Lat, T lhs, T rhs);
  
  std::set<unsigned>
  op_get_prevs(const Lattice& Lat, unsigned elt);
  
  template<typename T>
  T op_min(T lhs, T rhs);


  // operators for majorants

  template<typename T>
  std::set<T> 
  op_get_maxs(const Lattice& Lat, T lhs, T rhs);
  
  std::set<unsigned>
  op_get_nexts(const Lattice& Lat, unsigned elt);
  
  template<typename T>
  T op_max(T lhs, T rhs);

} // vcsn


#include <vaucanson/algebra/concrete/order/lattice.hxx>

#endif /* !LATTICE_HH_ */
