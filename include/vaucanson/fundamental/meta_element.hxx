// meta_element.hxx
//
// VCSN_HEADER

#ifndef FUNDAMENTAL_META_ELEMENT_HXX
# define FUNDAMENTAL_META_ELEMENT_HXX

# include <vaucanson/fundamental/structure.hh>
# include <vaucanson/fundamental/element_base.hh>
# include <vaucanson/fundamental/meta_element.hh>

namespace vcsn {

 template <class Self, class T>
    MetaElement<Structure<Self>, T>::MetaElement()
    {}

    template <class Self, class T>
    MetaElement<Structure<Self>, T>::MetaElement(const MetaElement& o) :
      SyntacticDecorator<Self, T>(o)
    {}

} // vcsn

#endif //  FUNDAMENTAL_META_ELEMENT_HXX
