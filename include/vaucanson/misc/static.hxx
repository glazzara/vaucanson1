// misc/static.hxx
//
// $Id$
// VCSN_HEADER
#ifndef MISC_STATIC_HXX
# define MISC_STATIC_HXX

# include <cstddef>

# include <vaucanson/misc/static.hh>

namespace utility {

  template<bool b, typename T, typename U>
  static typename remove_reference<T>::t& 
  static_if<b, T, U>::choose(typename remove_reference<T>::t& p1, 
			     typename remove_reference<U>::t& p2)
  { 
    return p1; 
  }
  
  template<typename T, typename U>
  static typename remove_reference<U>::t& 
  static_if<false, T, U>::choose(typename remove_reference<T>::t& p1, 
				 typename remove_reference<U>::t& p2)
  { 
    return p2; 
  }

} // utility

#endif // MISC_STATIC_HXX
