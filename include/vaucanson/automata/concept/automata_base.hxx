// automata_base.hxx
//
// $Id$
// VCSN_HEADER
#ifndef AUTOMATA_AUTOMATA_BASE_HXX
# define AUTOMATA_AUTOMATA_BASE_HXX

# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/history.hh>
# include <iterator>

namespace vcsn
{
 
  template<typename Self> 
  AutomataBase<Self>::AutomataBase() 
  {}
  
  template<typename Self> 
  AutomataBase<Self>::AutomataBase(const AutomataBase& other) 
  {}


  /*-----------------------------------.
  | MetaElement<AutomataBase<Self>, T> |
  `-----------------------------------*/

   

  template<typename Self, typename T>
  void MetaElement<AutomataBase<Self>, T>::create()
  { 
    if (! value().get())
      value().reset(new typename T::element_type());
  }

  template<typename Self, typename T>
  void MetaElement<AutomataBase<Self>, T>::emancipate()
  { 
    if (! value().unique()) 
      value().reset(new typename T::element_type(*value().get()));
  }

  template<typename Self, typename T>
  const history::AutomatonHistory<MetaElement<AutomataBase<Self>, T> >&
  MetaElement<AutomataBase<Self>, T>::history() const 
  {
    return history_;
  }

  template<typename Self, typename T>
  history::AutomatonHistory<MetaElement<AutomataBase<Self>, T> >&
  MetaElement<AutomataBase<Self>, T>::history() 
  {
    return history_;
  }

  template<typename Self, typename T>
  bool MetaElement<AutomataBase<Self>, T>::exists() const
  { 
    return value()->get(); 
  }
  
  template<typename Self, typename T>
  typename automaton_traits<T>::states_ret_t
  MetaElement<AutomataBase<Self>, T>::states() const
  { 
    return value()->states(); 
  }
  // before value->states() ??


  template<typename Self, typename T>
  typename automaton_traits<T>::edges_ret_t
  MetaElement<AutomataBase<Self>, T>::edges() const
  { return value()->edges(); }

  template<typename Self, typename T>
  typename automaton_traits<T>::initial_ret_t
  MetaElement<AutomataBase<Self>, T>::initial() const
  { return value()->initial(); }

  template<typename Self, typename T>
  typename automaton_traits<T>::final_ret_t
  MetaElement<AutomataBase<Self>, T>::final() const
  { return value()->final(); }

  template<typename Self, typename T>
  bool MetaElement<AutomataBase<Self>, T>::is_initial(hstate_t what) const
  { return value()->is_initial(what.value()); }

  template<typename Self, typename T>
  bool MetaElement<AutomataBase<Self>, T>::is_final(hstate_t what) const
  { return value()->is_final(what.value()); }

  template<typename Self, typename T>
  void MetaElement<AutomataBase<Self>, T>::set_initial(hstate_t what)
  { value()->set_initial(what.value()); }

  template<typename Self, typename T> template <typename U>
  void MetaElement<AutomataBase<Self>, T>::set_initial(hstate_t what, const U& t)
  { value()->set_initial(what.value(), t); }

  template<typename Self, typename T>
  void MetaElement<AutomataBase<Self>, T>::set_final(hstate_t what)
  { value()->set_final(what.value()); }
  
  template<typename Self, typename T> template <typename U> 
  void MetaElement<AutomataBase<Self>, T>::set_final(hstate_t what, const U& t)
  { value()->set_final(what.value(), t); }

  template<typename Self, typename T>
  void MetaElement<AutomataBase<Self>, T>::unset_initial(hstate_t what)
  { value()->unset_initial(what.value()); }

  template<typename Self, typename T>
  void MetaElement<AutomataBase<Self>, T>::unset_final(hstate_t what)
  { value()->unset_final(what.value()); }
  
  // FIXME : make this a method of all
  template<typename Self, typename T>
  void MetaElement<AutomataBase<Self>, T>::clear_initial()
  {
    value()->clear_initial();
  }
  
  template<typename Self, typename T>
  void MetaElement<AutomataBase<Self>, T>::clear_final()
  {
    value()->clear_final();
  }

  template<typename Self, typename T>
  Element<typename automaton_traits<T>::series_t, typename automaton_traits<T>::series_value_t>
  MetaElement<AutomataBase<Self>, T>::get_initial(hstate_t what) const
  { return value()->get_initial(what.value()); }
  
  template<typename Self, typename T>
  Element<typename automaton_traits<T>::series_t, typename automaton_traits<T>::series_value_t>
  MetaElement<AutomataBase<Self>, T>::get_final(hstate_t what) const
  { return value()->get_final(what.value()); }

  template<typename Self, typename T>
  hstate_t MetaElement<AutomataBase<Self>, T>::add_state()
  {	return value()->add_state(); }
  
  template<typename Self, typename T>
  hstate_t MetaElement<AutomataBase<Self>, T>::select_state(unsigned n)
  {	
    state_iterator h = states().begin();
    
    for (unsigned i = 0; i < n; i++)
      h = ++h;
    
    return *h;
  }

  template<typename Self, typename T>
  hedge_t MetaElement<AutomataBase<Self>, T>::add_edge(hstate_t from, hstate_t to, const label_t& label)
  { return value()->add_edge(from.value(), to.value(), label); }

  template<typename Self, typename T>
  void MetaElement<AutomataBase<Self>, T>::del_state(hstate_t s)
  { value()->del_state(s.value()); }

  template<typename Self, typename T>
  void MetaElement<AutomataBase<Self>, T>::del_edge(hedge_t e)
  { value()->del_edge(e.value()); }

  template<typename Self, typename T>
  void MetaElement<AutomataBase<Self>, T>::safe_del_state(hstate_t s)
  {	value()->safe_del_state(s.value()); }

  template<typename Self, typename T>
  bool MetaElement<AutomataBase<Self>, T>::has_state(hstate_t s) const
  { return value()->has_state(s.value()); }
  
  template<typename Self, typename T>
  bool MetaElement<AutomataBase<Self>, T>::has_edge(hedge_t e) const
  { return value()->has_edge(e.value()); }

  template<typename Self, typename T>
  hstate_t MetaElement<AutomataBase<Self>, T>::origin_of(hedge_t e) const
  { return value()->origin_of(e.value()); }

  template<typename Self, typename T>
  hstate_t MetaElement<AutomataBase<Self>, T>::aim_of(hedge_t e) const
  { return value()->aim_of(e.value()); }
  
  template<typename Self, typename T>
  typename automaton_traits<T>::label_ret_t
  MetaElement<AutomataBase<Self>, T>::label_of(hedge_t e) const
  { return value()->label_of(e.value()); }
  
#define DELTA_IMPL(Name, Type, Kind_type)						\
      template<typename Self, typename T> template<typename OutputIterator>							\
      void MetaElement<AutomataBase<Self>, T>::Name (OutputIterator res, hstate_t from,					\
		 Kind_type k) const						\
      { value()-> Name ## _ ## Type (res, from); }					\
											\
      template<typename Self, typename T> template<typename OutputIterator, typename L>					\
      void MetaElement<AutomataBase<Self>, T>::Name (OutputIterator res, hstate_t from, const L& query,			\
		 Kind_type k) const						\
      { value()-> Name ## _ ## Type (res, from, query); }				\
											\
      template<typename Self, typename T> template<typename Container>							\
      void MetaElement<AutomataBase<Self>, T>::Name ## c (Container& dst, hstate_t from,					\
		      Kind_type k) const						\
      {											\
	std::insert_iterator<Container> i(dst, dst.begin());				\
	value()-> Name ## _ ## Type (i, from);						\
      }											\
											\
      template<typename Self, typename T> template<typename Container, typename L>						\
      void MetaElement<AutomataBase<Self>, T>::Name ## c (Container& dst, hstate_t from, const L& query,			\
		      Kind_type k) const						\
      {											\
	std::insert_iterator<Container> i(dst, dst.begin());				\
	value()-> Name ## _ ## Type (i, from, query);					\
      }

    DELTA_IMPL(delta, edges, delta_kind::edges);
    DELTA_IMPL(rdelta, edges, delta_kind::edges);

    DELTA_IMPL(delta, states, delta_kind::states);
    DELTA_IMPL(rdelta, states, delta_kind::states);

#undef DELTA_IMPL

  template<typename Self, typename T>
  typename automaton_traits<T>::series_t& 
  MetaElement<AutomataBase<Self>, T>::series() 
  { return value()->series(); }

  template<typename Self, typename T>
  const typename automaton_traits<T>::series_t& 
  MetaElement<AutomataBase<Self>, T>::series()  const
  { return value()->series(); }

  template<typename Self, typename T>
  typename automaton_traits<T>::tag_t& 
  MetaElement<AutomataBase<Self>, T>::tag() 
  { return value()->tag(); }

  template<typename Self, typename T>
  const typename automaton_traits<T>::tag_t& 
  MetaElement<AutomataBase<Self>, T>::tag() const
  { return value()->tag(); }

  template<typename Self, typename T>
  MetaElement<AutomataBase<Self>, T>::MetaElement() 
  {}

  template<typename Self, typename T>
  MetaElement<AutomataBase<Self>, T>::MetaElement(const MetaElement& other) :
    MetaElement<Structure<Self>, T>(other), 
    AutoKind<typename automaton_traits<T>::adapter_kind_t,
	     Element<Self, T>,
	     typename automaton_traits<T>::series_t,
	     typename automaton_traits<T>::series_value_t,
	     typename automaton_traits<T>::label_t>(other)	
  {}




  template<typename S, typename St, typename T>
  St& op_rout(const AutomataBase<S>& s, St& st, const T& r)
  { 
    (void)(&s);
    if (! r.get())
      st << "NULL";
    else
      {
	st << "{ " 
	   << r.get()->states().size() << " states, "
	   << r.get()->edges().size() << " edges, "
	   << "#I = " << r.get()->initial().size() << ", "
	   << "#T = " << r.get()->final().size()
	   << " }";
      }
    return st;
  }
      
}


#endif
