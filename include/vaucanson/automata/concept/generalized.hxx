/***************************************
 * <vaucanson/automata/generalized_hxx> *
 **************************************/

/* this file is part of the Vaucanson project */
#ifndef VAUCANSON_AUTOMATA_GENERALIZED_HXX
# define VAUCANSON_AUTOMATA_GENERALIZED_HXX

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concrete/manylinks.hh>
# include <vaucanson/automata/concept/copy.hh>

# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/generalized.hh>
# include <vaucanson/rat/exp.hh>
# include <vaucanson/algebra/concrete/series/krat.hh>

namespace vcsn {

  template <class Auto_>
  typename generalized_traits<Auto_>::automaton_t
  generalized(const Auto_& from)
  {
    typename generalized_traits<Auto_>::automaton_t to;
    auto_copy(to, from);
    return to;
  }
  

} // vcsn

#endif // VAUCANSON_AUTOMATA_GENERALIZED_HXX
