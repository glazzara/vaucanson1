// semigroup_base.hh
//
// 
// $Id$
// VCSN_HEADER

#ifndef ALGEBRA_SEMIGROUP_BASE_HH
# define ALGEBRA_SEMIGROUP_BASE_HH

# include <vaucanson/algebra/concept/algebra_base.hh>
# include <vaucanson/fundamental/fundamental.hh>

namespace vcsn {

  namespace algebra {

    struct mul_kind 
    {};

    struct add_kind 
    {};

    //! SemigroupBase is the base class of all structures that are semigroups.
    /*! All derived classes must define type MetaSet<S>::semigroup_kind.
     */
    template<class Self>
    struct SemigroupBase : Structure<Self>
    {
      
    protected:
      SemigroupBase();
      SemigroupBase(const SemigroupBase& other);
    };

  } // algebra

  template<class Self, typename T>
  struct MetaElement<algebra::SemigroupBase<Self>, T>
    : MetaElement<Structure<Self>, T>
  {
  protected:
    MetaElement();
    MetaElement(const MetaElement& other);
  };
  
} // vcsn

# include <vaucanson/algebra/concept/semigroup_base.hxx>

#endif // ALGEBRA_SEMIGROUP_BASE_HH
