// random.hh
//
// $Id$
// VCSN_HEADER
#ifndef MISC_RANDOM_HH
# define MISC_RANDOM_HH

# include <typeinfo>

namespace vcsn {

  namespace misc {

    template <class T>
    struct RandomGenerator
    {
      static T do_it();
    };

    template <>
    struct RandomGenerator<char>
    {
      static char do_it();
    };

    template <>
    struct RandomGenerator<bool>
    {
      static bool do_it();
    };

  } // misc

} // vcsn

# include <vaucanson/misc/random.hxx>

#endif // MISC_RANDOM_HH
