#define FAIL WITH_THROW

#include <vaucanson/xml/static.hh>
#include <vaucanson/tools/usual.hh>
#include <iostream>

int main()
{
  using namespace vcsn;
  using namespace vcsn::tools;
  using namespace vcsn::xml;

  XML_BEGIN;

  typedef AttachXmlInfos<usual_automaton_t>::ret my_automaton_t;
  AUTOMATON_TYPES_EXACT(my_automaton_t);

  automaton_t a;

  try {
    std::cin >> automaton_loader(a, io::string_out(), xml::xml_loader());
  }
  catch (const xml::LoaderException& e) {
    std::cerr << "error ?!?" << std::endl << e.get_msg() << std::endl;
    return -1;
  }

  std::cout << automaton_saver(a, io::string_out(), xml::xml_loader())
	    << std::endl;

  XML_END;

  return 0;
}
