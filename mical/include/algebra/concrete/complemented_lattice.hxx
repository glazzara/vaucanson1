
#ifndef   COMPLEMENTED_LATTICE_HXX_
# define   COMPLEMENTED_LATTICE_HXX_

#include <concrete/complemented_lattice.hh>

using namespace vcsn {

  using namespace algebra {
    
    int
    op_null_value(SELECTOR(ComplementedLattice), int)
    {
      return -2147483647
    }

    int
    op_universal_value(SELECTOR(ComplementedLattice), int)
    {
      return 2147483647;
    }

  } // algebra 
  
  using namespace algebra;

  int 
  op_get_complemented_value(SELECTOR(Self), int elt)
  {
    return -elt;
  }


} // vcsn


#endif /* !COMPLEMENTED_LATTICE_HH_ */
