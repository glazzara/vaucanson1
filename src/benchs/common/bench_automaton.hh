#ifndef BENCH_AUTOMATON_HH
# define BENCH_AUTOMATON_HH

#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/algebra/implementation/predefs.hh>

namespace vcsn {

  namespace bench_automaton {

    using namespace vcsn;
    using namespace vcsn::algebra;
    using namespace vcsn::algebra::small_alpha_letter;

    typedef polynom<WordValue, bool> series_set_elt_value_t;

    typedef Series<NumericalSemiring, Words> series_set_t;

    typedef Graph
    <
      labels_are_letters,
      WordValue,
      bool,
      series_set_elt_value_t,
      char,
      NoTag>
    automaton_impl_t;

    typedef Element<Automata<series_set_t>, automaton_impl_t>
    automaton_t;

    AUTOMATON_TYPES_EXACT(automaton_t);
    AUTOMATON_FREEMONOID_TYPES_EXACT(automaton_t);

    template <class T>
    automaton_t new_automaton(const T& alphabet);

    template <class InputIterator>
    automaton_t new_automaton(InputIterator begin,
			      InputIterator end);

    template <class InputIterator>
    automata_set_t new_automata_set(InputIterator begin,
				    InputIterator end)
    {
      alphabet_t		alpha;
      for (InputIterator e = begin; e != end; ++e)
	alpha.insert(*e);
      semiring_t		semiring;
      monoid_t		freemonoid (alpha);
      series_set_t		series (semiring, freemonoid);
      return automata_set_t	(series);
    }

    template <class InputIterator>
    automaton_t new_automaton(InputIterator begin,
			      InputIterator end)
    {
      return automaton_t (new_automata_set(begin, end));
    }

    template <class T>
    automaton_t new_automaton(const T& alphabet)
    {
      return new_automaton(alphabet.begin(), alphabet.end());
    }



  } // bench_automaton

} // vcsn

#endif
