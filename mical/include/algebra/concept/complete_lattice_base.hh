
#ifndef   COMPLETE_LATTICE_BASE_HH_
# define   COMPLETE_LATTICE_BASE_HH_

#include <concept/lattice_base.hh>

namespace vcsn {

  namespace algebra {

    template<class Self>
    struct CompleteLatticeBase 
      : LatticeBase<Self>
    {
    protected:
      
      //! Default constructor is protected since it is an abstract class.
      ComplementedLatticeBase();
      
      //! Copy constructor is protected since it is an abstract class.
      ComplementedLatticeBase(const ComplementedLatticeBase& other);
    };

  } // algebra
  
    template<class Self, typename T>
    struct MetaElement<CompleteLatticeBase<Self>, T> 
      : MetaElement<LatticeBase<Self>, T>
    { 
      typedef T completelattice_value_t;
      typedef Self completelattice_elt_t;
      
            
    protected:
      //! Default constructor is protected since it is an abstract class.
      MetaElement();
      
      //! Copy constructor is protected since it is an abstract class.
      MetaElement(const MetaElement& other);
    };

} // vcsn

#include <concept/complete_lattice_base.hxx>


#endif /* !COMPLETE_LATTICE_BASE_HH_ */
