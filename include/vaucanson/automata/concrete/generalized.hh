// generalized.hh
//
// $Id$
// VCSN_HEADER
#ifndef VAUCANSON_AUTOMATA_CONCRETE_GENERALIZED_HH
# define VAUCANSON_AUTOMATA_CONCRETE_GENERALIZED_HH

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concrete/manylinks.hh>
# include <vaucanson/automata/concept/copy.hh>

# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/concrete/series/generalized.hh>
# include <vaucanson/algebra/concrete/series/rat/exp.hh>
# include <vaucanson/algebra/concrete/series/krat.hh>

# include <map>

namespace vcsn {

    /*----------------------.
    | Generalized automaton |
    `----------------------*/
  template <class Auto_>
  struct generalized_traits
  {
    // FIXME : static check on the concept of automaton
    typedef typename Auto_::series_t		series_t;
    typedef typename Auto_::series_elt_t	series_elt_t;
    typedef typename series_elt_t::monoid_elt_t monoid_elt_t;
    typedef typename monoid_elt_t::value_t	monoid_value_t;
    typedef typename series_elt_t::weight_t     weight_t;
    typedef typename weight_t::value_t		weight_value_t;
    
    typedef vcsn::Element<vcsn::Automata,
      utility::ref<
      vcsn::AutomatonImpl
    <
      vcsn::labels_are_series,
      series_t,
      rat::exp<monoid_value_t, weight_value_t>,
      vcsn::ManyLinks
      <
      rat::exp<monoid_value_t, weight_value_t>,
      vcsn::NoTag,
      vcsn::NoTag 
      >,
      vcsn::NoTag,
      std::map 
    > > > automaton_t;
  };

  template <class Auto_>
  typename generalized_traits<Auto_>::automaton_t
  generalized(const Auto_& from);
  

} // vcsn

# include <vaucanson/automata/concrete/generalized.hxx>

#endif // VAUCANSON_AUTOMATA_GENERALIZED_HH
