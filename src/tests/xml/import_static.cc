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

  std::cout << "Letters:";
  for_each_letter(i, a.structure().series().monoid().alphabet())
    std::cout << " " << *i;
  std::cout << std::endl;

  std::cout << "States:" << std::endl;
  for_each_state(i, a) {
    std::cout << *i << " ";
    std::cout << a.tag().get_states().get_name()[*i] << std::endl;
  }

  std::cout << "Edges:" << std::endl;
  for_each_edge(i, a) {
    std::cout << *i << " ";
    std::cout << a.aim_of(*i) << " ";
    std::cout << a.origin_of(*i) << " ";
    std::cout << a.label_of(*i) << std::endl;
  }

  std::cout << "Initials:" << std::endl;
  for_each_initial_state(i, a) {
    std::cout << *i << " ";
    std::cout << a.get_initial(*i) << std::endl;
  }

  std::cout << "Finals:" << std::endl;
  for_each_final_state(i, a) {
    std::cout << *i << " ";
    std::cout << a.get_final(*i) << std::endl;
  }

  XML_END;

  return 0;
}
