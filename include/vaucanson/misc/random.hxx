// random.hxx
//
// $Id$
// VCSN_HEADER
#ifndef MISC_RANDOM_HXX
# define MISC_RANDOM_HXX

# include <cstdlib>

namespace vcsn {

  namespace misc {
    
    template <class T>
    T 
    RandomGenerator<T>::do_it()
    {
      assert(!"No random generator for this type :"+(typeid(T)));
    }

    char 
    RandomGenerator<char>::do_it()
    {
      return (char)((random() * 255 / RAND_MAX));
    }

  } // misc

} // vcsn

#endif // MISC_RANDOM_HH
