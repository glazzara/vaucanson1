// fundamental/element_base.hh
//
// $Id$
// VCSN_HEADER
#ifndef FUNDAMENTAL_ELEMENT_BASE_HH
# define FUNDAMENTAL_ELEMENT_BASE_HH

# include <vaucanson/fundamental/predefs.hh>

namespace vcsn
{

  // general remark : this file should be called syntactic_decorator.hh

    /*-------------------.
    | SyntacticDecorator |
    `-------------------*/
    //! SyntacticDecorator provides the standard operator to Element.
    //

    /*! SyntacticDecorator defines all the self-application operators
      of C++. In fact, this decorator is essential because it is
      the wrapper of standard operators to Vaucanson op_*. 

    */

    template<typename S, typename T> 
    struct SyntacticDecorator
    {
    
      const S&  set() const;
      T&	value();
      const T&  value() const;

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
      SyntacticDecorator();
      SyntacticDecorator(const SyntacticDecorator& other);
    };

} // vcsn

# include <vaucanson/fundamental/element_base.hxx>

#endif // FUNDAMENTAL_ELEMENT_BASE_HH
