#define FAIL WITH_THROW

#include <vaucanson/xml/session.hh>
#include <vaucanson/tools/usual.hh>
#include <iostream>

int main(int argc, char *argv[])
{
  using namespace vcsn;
  using namespace vcsn::tools;
  using namespace vcsn::xml;

  XML_BEGIN;

  typedef AttachXmlInfos<usual_automaton_t>::ret my_automaton_t;
  typedef XmlOf<my_automaton_t>::ret my_xml_automaton_t;
  AUTOMATON_TYPES_EXACT(my_automaton_t);

  my_xml_automaton_t x;
  xml_automaton_t dyn;
  automaton_t a;
  XmlSession session;

  try {
    std::cin >> dyn;
    x = dyn;
    a = x;
    x = a;
    session << x;
    for (int i = 1; i < argc; i++) {
      std::ifstream f(argv[i]);
      f >> dyn;
      x = dyn;
      a = x;
      x = a;
      session << x;
    }
  }
  catch (const xml::LoaderException& e) {
    std::cerr << "error ?!?" << std::endl << e.get_msg() << std::endl;
    return -1;
  }

  std::cout << session;

  XML_END;

  return 0;
}
