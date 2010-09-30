#ifndef VCSN_BOOST_SPIRIT_COMPATIBILITY_HH
# define VCSN_BOOST_SPIRIT_COMPATIBILITY_HH

# include <boost/version.hpp>

# if BOOST_VERSION >= 104300
#  define VCSN_SPIRIT_CLASSIC spirit::classic
# else
#  define VCSN_SPIRIT_CLASSIC spirit
# endif

#endif /* !VCSN_BOOST_SPIRIT_COMPATIBILITY_HH */
