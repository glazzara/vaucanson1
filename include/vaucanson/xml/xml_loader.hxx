#ifndef VCSN_XML_XML_LOADER_HXX
# define VCSN_XML_XML_LOADER_HXX

# include <vaucanson/xml/xml_loader.hh>

# include <vaucanson/xml/types.hh>

# include <vaucanson/tools/usual.hh>
# include <vaucanson/tools/usual_macros.hh>

# include <iostream>

namespace vcsn
{
  namespace xml
  {
    template <typename Saver, typename Conv>
    inline
    void
    xml_loader::operator()(std::ostream& out,
			   const Saver& s,
			   const Conv&) const
    {
      typedef typename Saver::automaton_t auto_t;
      typedef typename XmlOf<auto_t>::ret xml_auto_t;
      AUTOMATON_TYPES(auto_t);

      const automaton_t& a = s.automaton();

      xml_auto_t xml_a;

      xml_a = a;

      out << xml_a;
    }

    template <typename Loader>
    inline
    void
    xml_loader::operator()(std::istream& in, Loader& l)
    {
      typedef typename Loader::automaton_t auto_t;
      typedef typename XmlOf<auto_t>::ret xml_auto_t;
      AUTOMATON_TYPES(auto_t);

      xml_automaton_t dyn_xml_a;
      xml_auto_t xml_a;

      automaton_t& a = l.automaton();

      in >> dyn_xml_a;

      xml_a = dyn_xml_a;

      a = xml_a;
    }
  }
}

#endif // VCSN_XML_XML_LOAD_HXX
