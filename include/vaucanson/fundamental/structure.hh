/*********************************************************************
 * <vaucanson/algebra/algebraic_structure.hh>: companion to meta_set *
 *********************************************************************/
// $Id$

/* this file is part of the Vaucanson project. */
#ifndef FUNDAMENTAL_STRUCTURE_HH
# define FUNDAMENTAL_STRUCTURE_HH

# include <vaucanson/misc/selectors.hh>
# include <vaucanson/fundamental/predefs.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/internal/traits.hh>

namespace vcsn {

    /*----------------.
    | Structure<Self> |
    `----------------*/

    template<typename Self>
    struct Structure
    {
      typedef Self		self_t;

      template<typename T>
      bool 
      contains(const Element<Self, T>& elt) const;

      template<typename S, typename T>
      bool 
      contains(const Element<S, T>& other) const;

      template<typename T>
      bool 
      contains(const T& elt_value) const;

      template <class T>
      Element<Self, T> choose(SELECTOR(T)) const;

      // static inheritance stuff below
      self_t&        
      self();

      const self_t&  
      self() const;

    protected:
      Structure();
      Structure(const Structure& other);
    };

} // vcsn

/*--------------------.
| default comparisons |
`--------------------*/
template<typename S>
bool operator==(const vcsn::Structure<S>& a,
		const vcsn::Structure<S>& b);

template<typename S>
bool operator!=(const vcsn::Structure<S>& a,
		const vcsn::Structure<S>& b);

# include <vaucanson/fundamental/structure.hxx>

#endif // FUNDAMENTAL_STRUCTURE_HH
