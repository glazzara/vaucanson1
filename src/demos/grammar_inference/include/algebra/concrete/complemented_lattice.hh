
#ifndef   COMPLEMENTED_LATTICE_HH_
# define   COMPLEMENTED_LATTICE_HH_

#include <concept/complemented_lattice_base.hh>

using namespace vcsn {

  using namespace algebra {
    
    struct ComplementedLattice
      : ComplementedLatticeBase<ComplementedLattice>
    {};
    
    
    int
    op_null_value(SELECTOR(ComplementedLattice), int);

    int
    op_universal_value(SELECTOR(ComplementedLattice), int);

  } // algebra 
  
  using namespace algebra;

  template<typename T>
  struct MetaElement<ComplementedLattice, T>
    : MetaElement<ComplementedLatticeBase<ComplementedLattice>, T>
  {
    static const bool dynamic_set = false;
  };
  
  int 
  op_get_complemented_value(SELECTOR(Self), int elt);


} // vcsn

#include <concrete/complemented_lattice.hxx>


#endif /* !COMPLEMENTED_LATTICE_HH_ */
