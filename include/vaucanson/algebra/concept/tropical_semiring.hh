// tropical_semiring.hh
//
//
//
// $Id$
// VCSN_HEADER

#ifndef ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HH
# define ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HH

# include <vaucanson/algebra/concept/semiring_base.hh>

namespace vcsn {

  namespace algebra {

    // Forward declaration.
    template <class TropicalKind>
    struct TropicalSemiring;

  } // algebra


    /*----------------------------------------------------.
    | MetaSet : traits about the set of tropical semiring |
    `----------------------------------------------------*/
    template<class TropicalKind>
    struct MetaSet<TropicalSemiring<TropicalKind> >
    {
      static const bool dynamic_set = false;
      typedef mul_kind	semigroup_kind;
    };

  namespace algebra {

    /*-----------------.
    | Kind of tropical |
    `-----------------*/
    struct TropicalMin
    {};

    struct TropicalMax
    {};

    /*-----------------.
    | TropicalSemiring |
    `-----------------*/
    template <class TropicalKind>
    struct TropicalSemiring
      : SemiringBase<TropicalSemiring<TropicalKind> >
    {};

  } // algebra

    /*------------.
    | MetaElement |
    `------------*/
    template<class TropicalKind, typename T>
    struct MetaElement<TropicalSemiring<TropicalKind> , T>
      : MetaElement<SemiringBase<TropicalSemiring<TropicalKind> >, T>
    {};

} // vcsn


#endif // ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HH
