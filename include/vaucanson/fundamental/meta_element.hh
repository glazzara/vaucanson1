// meta_element.hh
//
// VCSN_HEADER


#ifndef FUNDAMENTAL_META_ELEMENT_HH
# define FUNDAMENTAL_META_ELEMENT_HH

# include <vaucanson/fundamental/structure.hh>
# include <vaucanson/fundamental/element_base.hh>

namespace vcsn {
  /*--------------------------------.
    | MetaElement<Structure<Self>, T> |
    `--------------------------------*/

  template<class Self, typename T>
  struct MetaElement<Structure<Self>, T>
    : MetaElementBase<Self, T>
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
