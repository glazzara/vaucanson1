#ifndef VCSN_XML_CALLBACK_HH
# define VCSN_XML_CALLBACK_HH

# include <vaucanson/xml/dynamic.hh>
# include <iostream>

/** @addtogroup xml XML tools for Vaucanson *//** @{ */
/**
 * @file callback.hh
 * @brief Tools for XML generic loading.
 * @author Valentin David <valentin@lrde.epita.fr>
 */
namespace vcsn
{
  namespace xml
  {
    /**
     * @brief 
     * @param in Standard istream where automaton is defined in XML.
     * @param user User data to pass to the callback.
     * @param Callback The callback class with a operator()(Auto,User&) defined.
     */
    template <template <typename I> class Callback,
	      typename User>
    int
    apply(std::istream& in, User& user);
  }
}

/** @} */

# include <vaucanson/xml/callback.hxx>

#endif // VCSN_XML_CALLBACK_HH
