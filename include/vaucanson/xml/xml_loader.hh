#ifndef VCSN_XML_XML_LOADER_HH
# define VCSN_XML_XML_LOADER_HH

# include <iostream>

/** @addtogroup xml XML tools for Vaucanson *//** @{ */
/**
 * @file xml_loader.hh
 * @brief Static load tools for @c automaton_loader .
 * @author Valentin David <valentin@lrde.epita.fr>
 */

namespace vcsn
{
  namespace xml
  {
    /// XML Loader.
    class xml_loader {
    public:
      template <typename Saver, typename Conv>
      void operator()(std::ostream& out, const Saver& s, const Conv& conv)
	const;
      template<typename Loader>
      void operator()(std::istream& in, Loader& l);
    };
  }
}

/** @} */

# include <vaucanson/xml/xml_loader.hxx>

#endif // VCSN_XML_XML_LOAD_HH
