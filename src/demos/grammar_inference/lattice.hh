
#ifndef   LATTICE_HH_
# define   LATTICE_HH_

# include <vaucanson/algebra/concept/lattice_base.hh>

# include <set>

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
  
  
  template<typename T>
  std::set<T> 
  op_get_mins(const Lattice& Lat, T lhs, T rhs);
  
  std::set<unsigned>
  op_get_prevs(const Lattice& Lat, unsigned elt);
  
  unsigned op_min(unsigned lhs, unsigned rhs);

} // vcsn


#include <vaucanson/algebra/concrete/order/lattice.hxx>

#endif /* !LATTICE_HH_ */
