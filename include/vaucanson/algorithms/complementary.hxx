// complementary.hxx
//
// $Id$
// VCSN_HEADER

# include <vaucanson/automata/concept/automata_base.hh>

# include <vaucanson/tools/usual.hh>

namespace vcsn {

  template <typename A, typename T>
  void
  auto_in_complementary(Element<A, T>& e)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    for (state_iterator i = e.states().begin(); i != e.states().end(); i++)
      if (e.is_final(*i))
	e.unset_final(*i);
      else if (!e.is_initial(*i))
	e.set_final(*i);
  }

  template <typename A, typename T>
  Element<A, T>
  auto_complementary(const Element<A, T>& e)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);
  
    automaton_t work(e);
    work.emancipate();
    auto_in_complementary(work);
    return work;
  }

} // vcsn
