
#ifndef   COMPLETELATTICE_BASE_HXX_
# define   COMPLETELATTICE_BASE_HXX_

#include <concept/complete_lattice_base.hh>

namespace vcsn {

  namespace algebra {

    //! Default constructor is protected since it is an abstract
    //class.
    template<class Self>
    CompleteLatticeBase<Self>::CompleteLatticeBase()
    {}
      
    //! Copy constructor is protected since it is an abstract class.
    template<class Self>
    CompleteLatticeBase<Self>::
    CompleteLatticeBase(const CompleteLatticeBase& other)
    {}


  } // algebra      


  //! Default constructor is protected since it is an abstract
  //class.
  template<class Self, typename T>
  MetaElement<CompleteLatticeBase<Self>, T>::MetaElement()
  {}
      
  //! Copy constructor is protected since it is an abstract class.
  template<class Self, typename T>
  MetaElement<CompleteLatticeBase<Self>, T>::
  MetaElement(const MetaElement& other)
  {}


} // vcsn

#endif /* !COMPLETELATTICE_BASE_HXX_ */
