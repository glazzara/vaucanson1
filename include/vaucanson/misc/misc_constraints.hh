/*******************************************************
 * <vaucanson/misc/misc_constraints.hh>: various minor *
 * constraint-checking classes                         *
 *******************************************************/
// $Id$

/* this file is part of the Vaucanson project. */
#ifndef UTILITY_MISC_CONSTRAINTS_HH
#define UTILITY_MISC_CONSTRAINTS_HH

#include <vaucanson/misc/constraints.hh>

namespace utility
{

  namespace concepts
  {

    /*-----------------------------------------------.
    | SameValue, SameType and DifferentType concepts |
    `-----------------------------------------------*/

#ifndef __KCC
    template <typename T, T A, T B>
    struct SameValue_chooser {};

    template <typename T, T A>
    struct SameValue_chooser<T, A, A> 
    { typedef void t; };
#endif
    template <typename T, T A, T B>
    struct SameValue 
    {
      void constraints() 
      {
#ifndef __KCC       
	typedef typename SameValue_chooser<T, A, B>::t required; 
#endif
      }
    };

    template <typename T, typename U>
    struct SameType_chooser { };
    template <typename T>
    struct SameType_chooser<T, T> { typedef void t; };

    template <typename T, typename U>
    struct SameType
    {
      void constraints() 
      {	typedef typename SameType_chooser<T, U>::t required; }
    };

    template <typename T, typename U>
    struct DifferentType_chooser { typedef int t; };
    template <typename T>
    struct DifferentType_chooser<T, T> { typedef void t; };

    template <typename T, typename U>
    struct DifferentType
    {
      void constraints() 
      {
	function_requires<
	  SameType<int, typename DifferentType_chooser<T, U>::t> >();
      }
    };


  }

}


#endif
