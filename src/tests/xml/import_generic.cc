#define FAIL WITH_THROW
#define VCSN_XML_GENRERIC_WEIGHTED 1

#include <vaucanson/xml/generic.hh>
#include <vaucanson/tools/usual.hh>
#include <iostream>

struct MyData
{
  int argc;
  char **argv;
  MyData(int c, char** v) : argc(c), argv(v) { }
};

template <typename Auto>
struct MyCallBack
{
  int operator()(Auto& a, MyData&)
  {
    using namespace vcsn;
    using namespace vcsn::tools;
    using namespace vcsn::xml;

    AUTOMATON_TYPES(Auto);

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
};

int main(int argc, char *argv[])
{
  using namespace vcsn;
  using namespace vcsn::xml;

  XML_BEGIN;

  try {
    MyData data(argc, argv);
    return apply<MyCallBack, MyData>(std::cin, data);
  }
  catch (const xml::LoaderException& e) {
    std::cerr << "error ?!?" << std::endl << e.get_msg() << std::endl;
    return -1;
  }
}
