#define FAIL WITH_THROW

#include <vaucanson/xml/dynamic.hh>
#include <vaucanson/tools/usual.hh>
#include <iostream>

int main()
{
  using namespace vcsn;
  using namespace vcsn::tools;
  using namespace vcsn::xml;

  XML_BEGIN;

  typedef AttachXmlInfos<usual_automaton_t>::ret my_automaton_t;
  typedef XmlOf<my_automaton_t>::ret my_xml_automaton_t;
  AUTOMATON_TYPES_EXACT(my_automaton_t);

  automaton_t a;

  try {
    xml_automaton_t dyn;
    my_xml_automaton_t x;
    std::cin >> dyn;
    x = dyn;
    a = x;
  }
  catch (const xml::LoaderException& e) {
    std::cerr << "error ?!?" << std::endl << e.get_msg() << std::endl;
    return -1;
  }

  my_xml_automaton_t x;
  x = a;

  std::cout << x << std::endl;
  XML_END;
  return 0;
}
