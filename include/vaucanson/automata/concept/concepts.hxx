// concepts.hxx
//
// $Id$
// VCSN_HEADER
#ifndef AUTOMATA_CONCEPTS_HXX
# define AUTOMATA_CONCEPTS_HXX

#include <vaucanson/algebra/concept/concepts.hh>
#include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn
{
  
    template<typename S, typename T>
    void AutomataConcept<S, T>::constraints()
    {
      using namespace utility::concepts;

      (void)check_inheritance();
      (void)check_elt_inheritance();

      // FIXME : why this concept does not work ?
      //      function_requires<algebra::AlgebraicStructureConcept<S, T> >();
      function_requires<algebra::SeriesConcept<series_t, series_value_t> >();

      (void)check_ref_ops(a);
      
      a.del_state(hstate_t());
      a.del_edge(hedge_t());
      a.safe_del_state(hstate_t());
      (void)check_add_state();
      // cannot check add_edge nor new_edge here, because we don't know
      // the label type and how to get it

      (void)check_has(a);

      typedef typename auto_t::tag_t required;
      required& t1 UnusedConceptVar = a.tag();
      const required& t2 UnusedConceptVar = const_cast<const auto_t&>(a).tag();
      // FIXME: add checks for tags here

      typedef typename auto_t::states_t required_states;
      typedef typename auto_t::state_iterator required_state_iterator;
      typedef typename auto_t::edges_t required_edges;
      typedef typename auto_t::edge_iterator required_edge_iterator;

      typedef typename auto_t::initial_t required_initial;
      typedef typename auto_t::initial_iterator required_initial_iterator;
      typedef typename auto_t::final_t required_final;
      typedef typename auto_t::final_iterator required_final_iterator;

      const required_states& r1 UnusedConceptVar = const_cast<const auto_t&>(a).states();
      const required_edges& r2 UnusedConceptVar = const_cast<const auto_t&>(a).edges();
      const required_initial& r3 UnusedConceptVar = const_cast<const auto_t&>(a).initial();
      const required_final& r4 UnusedConceptVar = const_cast<const auto_t&>(a).final();

      required_state_iterator i UnusedConceptVar = r1.begin();
      i = r1.end();
      required_edge_iterator j UnusedConceptVar = r2.begin();
      j = r2.end();
      required_initial_iterator k UnusedConceptVar = r3.begin();
      k = r3.find(hstate_t());
      k = r3.end();
      required_final_iterator l UnusedConceptVar = r4.begin();
      l = r4.find(hstate_t());
      l = r4.end();
      // FIXME: add checks for iterators here
      

      size_t s1 UnusedConceptVar = r1.size();
      size_t s2 UnusedConceptVar = r2.size();
      size_t s3 UnusedConceptVar = r3.size();
      size_t s4 UnusedConceptVar = r4.size();


      (void)check_series();
      (void)check_const_series(a);


      a.set_initial(hstate_t());
      a.set_final(hstate_t());
      a.set_initial(hstate_t(), Element<series_t, series_value_t>());
      a.set_final(hstate_t(), Element<series_t, series_value_t>());
      (void)check_get_initial(a);
      (void)check_get_final(a);

    }

    template<typename S, typename T>
    AutomataBase<S>& 
    AutomataConcept<S, T>::check_inheritance()     
    { return s; }

    template<typename S, typename T>
    MetaElement<AutomataBase<S>, T>&	
    AutomataConcept<S, T>::check_elt_inheritance()
    { return a; }
    
    template<typename S, typename T>
    hstate_t AutomataConcept<S, T>::check_add_state()
    { return a.add_state(); }

    template<typename S, typename T>
    bool AutomataConcept<S, T>::check_ref_ops(const auto_t& ac)
    {
      a.create();
      a.emancipate();
      return ac.exists();
    }

    template<typename S, typename T>
    Element<typename Element<S, T>::series_t, typename Element<S, T>::series_value_t> 
    AutomataConcept<S, T>::check_get_initial(const auto_t& a)
    { return a.get_initial(hstate_t()); }

    template<typename S, typename T>
    Element<typename Element<S, T>::series_t, typename Element<S, T>::series_value_t> 
    AutomataConcept<S, T>::check_get_final(const auto_t& a)
    { return a.get_final(hstate_t()); }

    template<typename S, typename T>
    bool AutomataConcept<S, T>::check_has(const auto_t& a)
    { return a.has_state(hstate_t()) || a.has_edge(hedge_t()); }

    template<typename S, typename T>
    typename Element<S, T>::series_t& 
    AutomataConcept<S, T>::check_series()
    { return a.series(); }

    template<typename S, typename T>
    const typename Element<S, T>::series_t& 
    AutomataConcept<S, T>::check_const_series(const auto_t& a)
    { return a.series(); }

    
}


#endif
