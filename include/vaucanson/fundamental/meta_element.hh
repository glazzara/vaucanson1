// meta_element.hh
//
//
// $Id$
// VCSN_HEADER

#ifndef FUNDAMENTAL_META_ELEMENT_HH
# define FUNDAMENTAL_META_ELEMENT_HH

# include <vaucanson/fundamental/structure.hh>
# include <vaucanson/fundamental/element_base.hh>

namespace vcsn {
  /*--------------------------------.
  | MetaElement<Structure<Self>, T> |
  `--------------------------------*/
  //! MetaElement is the way of defining interactions between a set and an implementation.
  
  /*! MetaElement<Structure<Self>, T> is the specialization that is at
    the top of all the hierarchy of Vaucanson.
  */

  template<class Self, typename T>
  struct MetaElement<Structure<Self>, T>
    : SyntacticDecorator<Self, T>
  {
  public:

      static const bool dynamic_values = true;

  protected:
    MetaElement();
    MetaElement(const MetaElement& other);
  };

} // vcsn

# include <vaucanson/fundamental/meta_element.hxx>

#endif //  FUNDAMENTAL_META_ELEMENT_HH
