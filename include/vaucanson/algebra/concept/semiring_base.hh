// semiring_base.hh
//
//
// $Id$
// VCSN_HEADER

#ifndef ALGEBRA_SEMIRING_BASE_HH
# define ALGEBRA_SEMIRING_BASE_HH

# include <vaucanson/algebra/concept/monoid_base.hh>
# include <cassert>

namespace vcsn {

  namespace algebra {

    /*-------------------.
    | SemiringBase<Self> |
    `-------------------*/
    //! SemiringBase is the base class for all structures that are semirings.
    template<class Self>
    struct SemiringBase : MonoidBase<Self>
    {
    protected:
      SemiringBase();
      SemiringBase(const SemiringBase& other);
    };

  } // algebra

    /*-----------------------------------.
    | MetaElement<SemiringBase<Self>, T> |
    `-----------------------------------*/

  template<typename Self, typename T>
  struct MetaElement<algebra::SemiringBase<Self>, T>
    : MetaElement<algebra::MonoidBase<Self>, T>
  {
    Element<Self, T>&   star();
    bool		stareable() const;

  protected:
    MetaElement();
    MetaElement(const MetaElement& other);
  };

  template<typename S, typename T>
  struct op_star_traits
  {
    typedef Element<S, T> ret_t;
  };
  
  template<typename S, typename T>
  typename op_star_traits<S, T>::ret_t
  star(const Element<S, T>& e);
  
  template<typename S, typename T>
  bool stareable(const Element<S, T>& elt);

  // default implementations:

  template<typename Self, typename T>
  bool op_stareable(const SemiringBase<Self>& s, const T& v);

  template<typename Self, typename T>
  void op_in_star(const SemiringBase<Self>& s, T& v);

  template<typename Self, typename T>
  T op_default(SELECTOR(SemiringBase<Self>), SELECTOR(T));

} // vcsn

# include <vaucanson/algebra/concept/semiring_base.hxx>

#endif // ALGEBRA_SEMIRING_BASE_HH



