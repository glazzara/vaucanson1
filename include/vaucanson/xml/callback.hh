#ifndef VCSN_XML_CALLBACK_HH
# define VCSN_XML_CALLBACK_HH

# include <vaucanson/xml/dynamic.hh>
# include <iostream>

/** @addtogroup xml *//** @{ */
/**
 * @file callback.hh
 *
 * Tools for XML generic loading.
 *
 * @author Valentin David <valentin@lrde.epita.fr>
 */
/** @} */

namespace vcsn
{

  namespace xml
  {

    /** @addtogroup xml *//** @{ */

    /**
     * @brief FIXME: Why is there no brief documentation here?
     *
     * The  template parameter  Callback is  the callback  class which
     * should provide:
     *
     * @code
     * operator()(Auto, User&)
     * @endcode
     *
     * @param in Standard istream where automaton is defined in XML.
     * @param user User data to pass to the callback.
     */
    template <template <typename I> class Callback, typename User>
    int
    apply(std::istream& in, User& user);

    /** @} */

  } // End of namespace xml.

} // End of namespace vcsn.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/callback.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_XML_CALLBACK_HH
