// numerical_semiring.hh
//
//
// $Id$
// VCSN_HEADER

#ifndef ALGEBRA_CONCEPT_NUMERICAL_SEMIRING_HH
# define ALGEBRA_CONCEPT_NUMERICAL_SEMIRING_HH

namespace vcsn {

  namespace algebra {
    
    /*------------------.
    | NumericalSemiring |
    `------------------*/
    //! NumericalSemiring is the set of semirings implemented with 
    //! usual operations (+, *).
    struct NumericalSemiring
      : SemiringBase<NumericalSemiring>
    {};

  } // algebra

  template<>
  struct MetaSet<NumericalSemiring>
  {
    static const bool dynamic_set = false;
    typedef           mul_kind    semigroup_kind;
  };
  
  template<typename T>
  struct MetaElement<NumericalSemiring, T>
    : MetaElement<SemiringBase<NumericalSemiring>, T>
  {};

} // vcsn


#endif // ALGEBRA_CONCEPT_NUMERICAL_SEMIRING_HH
