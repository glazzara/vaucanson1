
#ifndef   COMPLEMENTEDLATTICE_BASE_HH_
# define   COMPLEMENTEDLATTICE_BASE_HH_

#include <algebra/concept/lattice_base.hh>

namespace vcsn {

  namespace algebra {

    template<class Self>
    struct ComplementedLatticeBase 
      : LatticeBase<Self>
    {
      // in order to get THE null element of lattice
      template<typename T>
      Element<Self, T> null(SELECTOR(T)) const;
      
      // in order to get THE universal element of lattice
      template<typename T>
      Element<Self, T> universal(SELECTOR(T)) const;
      
    protected:
      
      //! Default constructor is protected since it is an abstract class.
      ComplementedLatticeBase();
      
      //! Copy constructor is protected since it is an abstract class.
      ComplementedLatticeBase(const ComplementedLatticeBase& other);
    };

  } // algebra
  
    template<class Self, typename T>
    struct MetaElement<ComplementedLatticeBase<Self>, T> 
      : MetaElement<LatticeBase<Self>, T>
    { 
      
      typedef T complementedlattice_value_t;
      typedef Self complementedlattice_elt_t;
      
      
      // in order to get complemented element
      complementedlattice_elt_t 
      get_complemented() const;
      
      complementedlattice_value_t 
      get_complemented_value() const;
      
      
    protected:
      //! Default constructor is protected since it is an abstract class.
      MetaElement();
      
      //! Copy constructor is protected since it is an abstract class.
      MetaElement(const MetaElement& other);
    };

} // vcsn

#include <algebra/concept/complemented_lattice_base.hxx>


#endif /* !COMPLEMENTEDLATTICE_BASE_HH_ */
