/************************************
 * <vaucanson/automata/concepts.hh> *
 ************************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef AUTOMATA_CONCEPTS_HH
#define AUTOMATA_CONCEPTS_HH

#include <vaucanson/algebra/concept/concepts.hh>
#include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn
{
  
  template<typename S, typename T>
  struct AutomataConcept
  {
    S s;
    typedef Element<S, T> auto_t;
    auto_t a;

    typedef typename auto_t::label_t label_t;
    typedef typename auto_t::series_t series_t;
    typedef typename auto_t::series_value_t series_value_t;
    typedef typename auto_t::monoid_t monoid_t;
    typedef typename auto_t::weights_t weights_t;

    void constraints();

    AutomataBase<S>&			check_inheritance();
    MetaElement<AutomataBase<S>, T>&	check_elt_inheritance();


    hstate_t check_add_state();

    bool check_ref_ops(const auto_t& ac);

    Element<series_t, series_value_t> check_get_initial(const auto_t& a);

    Element<series_t, series_value_t> check_get_final(const auto_t& a);

    bool check_has(const auto_t& a);

    typename auto_t::series_t& check_series();

    const typename auto_t::series_t& check_const_series(const auto_t& a);

  };
    
}

# include <vaucanson/automata/concept/concepts.hxx>

#endif

