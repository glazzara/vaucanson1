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
      float f = float(random()) / float(RAND_MAX);
      unsigned offs = unsigned((26 * f));
      return ('a' + offs);
    }

  } // misc

} // vcsn

#endif // MISC_RANDOM_HH
