
#ifndef   COMPLETE_LATTICE_HH_
# define   COMPLETE_LATTICE_HH_

#include <algebra/concept/complete_lattice_base.hh>
#include <algebra/concept/complemented_lattice_base.hh>
#include <fundamental/mix.hh>


using namespace vcsn {

  using namespace algebra {
    
    struct CompleteLattice
      : CompleteLatticeBase<CompleteLattice>
    {};
    
  } // algebra 
  
  using namespace algebra;
  
  template <>
  struct mix<CompleteLattice, ComplementedLattice>
  {
    typedef CompleteLattice     first_t;
    typedef ComplementedLattice second_t;

    static const bool val = true;
  };
  
  template <>
  mix_traits<Lattice, ComplementedLattice, false>
  {
    typedef Lattice child_t;
  }

  template<typename T>
  struct MetaElement<CompleteLattice, T>
    : MetaElement<
    mix_traits<
    Lattice, ComplementedLattice, 
    mix<CompleteLattice, ComplementedLattice>::val
  >::child_t, T>
  {
    static const bool dynamic_set = false;
  };
  
  
  
  
} // vcsn

#include <concrete/complete_lattice.hxx>


#endif /* !COMPLETE_LATTICE_HH_ */
