// numerical_constraints.hh
//
//
// $Id$
// VCSN_HEADER

#ifndef UTILITY_NUMERICAL_CONSTRAINTS_HH
# define UTILITY_NUMERICAL_CONSTRAINTS_HH

# include <limits>
# include <vaucanson/misc/misc_constraints.hh>

namespace utility {

  namespace concepts {

    /*----------------------.
    | number types concepts |
    `----------------------*/

    template <typename T>
    struct HasLimits
    {
      void constraints() 
      {
	function_requires<SameValue<bool, 
	  std::numeric_limits<T>::is_specialized,
	  true > >();
      }
    };

    template <typename T>
    struct IntegerType
    {
      void constraints()
      {
	function_requires<HasLimits<T> >();
	function_requires<SameValue<bool,
	  std::numeric_limits<T>::is_integer, true> >();
      }
    };

    template <typename T>
    struct UnsignedType
    {
      void constraints()
      {
	function_requires<IntegerType<T> >();
	function_requires<SameValue<bool,
	  std::numeric_limits<T>::is_signed, false> >();
      }
    };
	

    template <typename T>
    struct HasInfinity
    {
      void constraints() 
      {
	function_requires<HasLimits<T> >();
	function_requires<SameValue<bool,
	  std::numeric_limits<T>::has_infinity,
	  true > >();
      }
    };

    template <typename T>
    struct BoundedType
    {
      void constraints() 
      {
	function_requires<HasLimits<T> >();
	function_requires<SameValue<bool,
	  std::numeric_limits<T>::is_bounded,
	  true > >();
      }
    };

    template <typename T>
    struct IsSigned
    {
      void constraints() 
      {
	function_requires<HasLimits<T> >();
	function_requires<SameValue<bool,
	  std::numeric_limits<T>::is_signed,
	  true > >();
      }
    };

  } // concepts

} // utility

#endif // UTILITY_NUMERICAL_CONSTRAINTS_HH
