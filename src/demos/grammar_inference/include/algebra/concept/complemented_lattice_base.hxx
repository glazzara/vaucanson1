
#ifndef   COMPLEMENTEDLATTICE_BASE_HXX_
# define   COMPLEMENTEDLATTICE_BASE_HXX_

#include <concept/complemented_lattice_base.hh>

namespace vcsn {

  namespace algebra {


    // in order to get THE null element of lattice
    template<class Self, typename T>
    Element<Self, T>
    ComplementedLatticeBase<Self>::null(SELECTOR(T)) const
    {
      return Element<Self,T>(self(), op_null_value(SELECT(Self), SELECT(T)));
    }
      
    // in order to get THE universal element of lattice
    template<class Self, typename T>
    Element<Self, T> 
    ComplementedLatticeBase<Self>::universal(SELECTOR(T)) const
    {
      return Element<Self,T>(self(), op_universal_value(SELECT(Self), SELECT(T)));
    }
      
    //! Default constructor is protected since it is an abstract
    //class.
    template<class Self>
    ComplementedLatticeBase<Self>::ComplementedLatticeBase()
    {}
      
    //! Copy constructor is protected since it is an abstract class.
    template<class Self>
    ComplementedLatticeBase<Self>::
    ComplementedLatticeBase(const ComplementedLatticeBase& other)
    {}


  } // algebra      
      
  // in order to get complemented element
  template<class Self, typename T>
  Element<Self,T>
  MetaElement<ComplementedLatticeBase<Self>, T>::get_complemented() const
  {
    return Element<Self, T>(self(), op_get_complemented_value(SELECT(Self), value()));
  }
      
  template<class Self, typename T>
  T
  MetaElement<ComplementedLatticeBase<Self>, T>::get_complemented_value() const
  {
    return op_get_complemented_value(SELECT(Self), value());
  }
      
      
  //! Default constructor is protected since it is an abstract
  //class.
  template<class Self, typename T>
  MetaElement<ComplementedLatticeBase<Self>, T>::MetaElement()
  {}
      
  //! Copy constructor is protected since it is an abstract class.
  template<class Self, typename T>
  MetaElement<ComplementedLatticeBase<Self>, T>::
  MetaElement(const MetaElement& other)
  {}


} // vcsn

#endif /* !COMPLEMENTEDLATTICE_BASE_HXX_ */
