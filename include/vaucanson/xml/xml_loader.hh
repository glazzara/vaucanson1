#ifndef VCSN_XML_XML_LOADER_HH
# define VCSN_XML_XML_LOADER_HH

# include <iostream>

namespace vcsn
{
  namespace xml
  {
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

# include <vaucanson/xml/xml_loader.hxx>

#endif // VCSN_XML_XML_LOAD_HH
