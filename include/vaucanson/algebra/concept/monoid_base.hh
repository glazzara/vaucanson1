// monoid_base.hh
//
// $Id$
// VCSN_HEADER

#ifndef ALGEBRA_MONOID_BASE_HH
# define ALGEBRA_MONOID_BASE_HH

# include <vaucanson/algebra/concept/semigroup_base.hh>

namespace vcsn {

  namespace algebra {

    /*-----------------.
    | MonoidBase<Self> |
    `-----------------*/
    //! MonoidBase is the base class of all structures that are monoids.
    /*! Monoid define identity for semigroups of mul_kind and zero for
      semigroup of add_kind.
    */

    template<class Self>
    struct MonoidBase : SemigroupBase<Self>
    {
      template<typename T>
      Element<Self, T> identity(SELECTOR(T)) const;

      template<typename T>
      Element<Self, T> zero(SELECTOR(T)) const;

    protected:
      MonoidBase();
      MonoidBase(const MonoidBase& other);
    };

  } // algebra

  using namespace algebra;

    /*---------------------------------.
    | MetaElement<MonoidBase<Self>, T> |
    `---------------------------------*/
    template<class Self, typename T>
    struct MetaElement<MonoidBase<Self>, T> 
      : MetaElement<SemigroupBase<Self>, T>
    { 
    protected:
      MetaElement();
      MetaElement(const MetaElement& other);
    };

    template<typename T, typename Self>
    T op_default(SELECTOR(MonoidBase<Self>), SELECTOR(T));

} // vcsn

# include <vaucanson/algebra/concept/monoid_base.hxx>

#endif // ALGEBRA_MONOID_BASE_HH
