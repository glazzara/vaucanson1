// fundamental/element_base.hh
//
// $Id$
// VCSN_HEADER
#ifndef FUNDAMENTAL_ELEMENT_BASE_HH
# define FUNDAMENTAL_ELEMENT_BASE_HH

# include <vaucanson/fundamental/predefs.hh>

namespace vcsn
{

    // Obviously we have a funny situation here:
    // at any time, for an element, we know both
    // its base class (MetaElementBase) and the most
    // derived class (Element). However the intermediary
    // structures depend on the algebraic structure we consider.

    // and remember: the key of the system is that members of templates
    // are instanciated only when used.

    /*----------------------.
    | MetaElementBase<S, T> |
    `----------------------*/

    template<typename S, typename T> 
    struct MetaElementBase
    {
      // should be redefined
      static const bool dynamic_values = true;

      const S&  set() const;
      T&	value();
      const T&  value() const;

      // Arithmetic operators
      // --
      // It could seem strange to see these methods here :
      // An element is not necessary able to provide such facilities.
      // However, these operators are here to permit a work around the
      // problem of ambiguities in case of some operators call.
      // 

      template<typename OtherS, typename U>				 
      Element<S, T>& operator+=(const Element<OtherS, U>& other);	 
      template<typename U>						 
      Element<S, T>& operator+=(const U& other);    

      template<typename OtherS, typename U>				 
      Element<S, T>& operator-=(const Element<OtherS, U>& other);	 
      template<typename U>						 
      Element<S, T>& operator-=(const U& other);    

      template<typename OtherS, typename U>				 
      Element<S, T>& operator/=(const Element<OtherS, U>& other);	 
      template<typename U>						 
      Element<S, T>& operator/=(const U& other);    

      template<typename OtherS, typename U>				 
      Element<S, T>& operator*=(const Element<OtherS, U>& other);	 
      template<typename U>						 
      Element<S, T>& operator*=(const U& other);    

      template<typename OtherS, typename U>				 
      Element<S, T>& operator%=(const Element<OtherS, U>& other);	 
      template<typename U>						 
      Element<S, T>& operator%=(const U& other);    

      Element<S, T>& operator++();
      Element<S, T> operator++(int);

      Element<S, T>& operator--();
      Element<S, T> operator--(int);

      template<typename U>
      Element<S, T>& swap(Element<S, U>& other);

      template<typename OtherS, typename U>
      Element<S, T>& swap(Element<OtherS, U>& other);

      // static inheritance stuff. what's good is that we know
      // at this point the derived type.
      Element<S, T>& self();
      const Element<S, T>& self() const;

    protected:
      // this is an abstract class
      MetaElementBase();
      MetaElementBase(const MetaElementBase& other);
    };

    /*------------------.
    | MetaElement<S, T> |
    `------------------*/
    // Empty class that has to be specialized for providing meta
    // information about each couple Element<S, T>.
    template<typename S, typename T>
    struct MetaElement
    {};


} // vcsn

# include <vaucanson/fundamental/element_base.hxx>

#endif // FUNDAMENTAL_ELEMENT_BASE_HH
