#define FAIL WITH_THROW

#include <vaucanson/xml/dynamic.hh>
#include <vaucanson/tools/usual.hh>
#include <iostream>

template <typename T>
int print_out(typename vcsn::xml::XmlOf<T>::ret x)
{
  using namespace vcsn;
  using namespace vcsn::tools;
  using namespace vcsn::xml;

  typedef typename AttachXmlInfos<T>::ret my_automaton_t;
  AUTOMATON_TYPES(my_automaton_t);

  automaton_t a;

  a = x;

  std::cout << "Letters:";
  for_each_letter(i, a.set().series().monoid().alphabet())
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

  return 0;
}

int main()
{
  using namespace vcsn;
  using namespace vcsn::tools;
  using namespace vcsn::xml;

  XML_BEGIN;

  xml_automaton_t x;

  try {
    std::cin >> x;
  }
  catch (const xml::LoaderException& e) {
    std::cerr << "error ?!?" << std::endl << e.get_msg() << std::endl;
    return -1;
  }

  if ((x.set().semiring_type() == XmlSet::NUMERICAL)
      && (x.set().semiring_set() == XmlSet::Z))
    return print_out<numerical_automaton_t>(x);

  if (x.set().semiring_set() == XmlSet::B)
    return print_out<usual_automaton_t>(x);

  std::cerr << "Automaton type not dealt" << std::endl;

  XML_END;

  return -1;
}
