#include <iostream>

#include <vaucanson/boolean_automaton.hh>

#define FAIL WITH_THROW
#include <vaucanson/xml/static.hh>


int
main()
{
  using namespace vcsn::io;
  using namespace vcsn::xml;

  typedef ATTACH_XML_INFOS(vcsn::boolean_automaton::automaton_t) automaton_t;
  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t		at;
  monoid_t		md (at);
  semiring_t		sg;
  series_set_t		ss (sg, md);
  automata_set_t	aa (ss);

  automaton_t a (aa);

  XML_BEGIN;
  try
    {
      std::cin >> automaton_loader(a, string_out (), xml_loader ());
    }
  catch (const LoaderException& e)
    {
      std::cerr << "error ?!?" << std::endl << e.get_msg() << std::endl;
      return 1;
    }
  XML_END;

  std::cout << "Letters:";
  for_each_letter(i, a.structure().series().monoid().alphabet())
    std::cout << " " << *i;
  std::cout << std::endl;

  std::cout << "States:" << std::endl;
  for_each_state(i, a)
    {
      std::cout << *i << " ";
      std::cout << a.tag().get_states().get_name()[*i] << std::endl;
    }

  std::cout << "Edges:" << std::endl;
  for_each_edge(i, a)
    {
      std::cout << *i << " ";
      std::cout << a.aim_of(*i) << " ";
      std::cout << a.origin_of(*i) << " ";
      std::cout << a.label_of(*i) << std::endl;
    }

  std::cout << "Initials:" << std::endl;
  for_each_initial_state(i, a)
    {
      std::cout << *i << " ";
      std::cout << a.get_initial(*i) << std::endl;
    }

  std::cout << "Finals:" << std::endl;
  for_each_final_state(i, a)
    {
      std::cout << *i << " ";
      std::cout << a.get_final(*i) << std::endl;
    }
}
