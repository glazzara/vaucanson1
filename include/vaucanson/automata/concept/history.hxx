// history.hxx
//
// $Id$
// VCSN_HEADER
#ifndef AUTOMATA_HISTORY_HXX
# define AUTOMATA_HISTORY_HXX

# include <list>
# include <map>

# include <vaucanson/automata/concept/history.hh>

namespace vcsn {

  namespace history {

    template <class T>
    inline
    Event<T>::Event(event_kind_t e) : kind_(e)
    {}

    template <class T>
    inline
    Event<T>::~Event() 
    {}

    template <class T>
    inline
    event_kind_t	
    Event<T>::get_event_kind() const
    {
      return kind_;
    }

    template <class T>
    inline
    BinaryEvent<T>::BinaryEvent(event_kind_t e, const T& first, 
				const T& second) :
      Event<T>(e),
      first_(first),
      second_(second)
    {}

    template <class T>
    inline
    const T&
    BinaryEvent<T>::get_first() const
    {
      return first_;
    }

    template <class T>
    inline
    const T&
    BinaryEvent<T>::get_second() const
    {
      return second_;
    }

    template <class T>
    UnaryEvent<T>::UnaryEvent(event_kind_t e, const T& first) :
      Event<T>(e),
      first_(first)
    {}

    template <class T>
    inline
    const T&
    UnaryEvent<T>::get_first() const
    {
      return first_;
    }

    // FIXME : use std::find_if with a good function object.
    template <class AutoType_>      
    inline
    bool 
    AutomatonHistory<AutoType_>::set_state_event_about(event_kind_t e, 
						       hstate_t s)
    {
      for (typename state_events_t::const_iterator ev 
	     = states_events_[s].begin();
	   ev != states_events_[s].end();
	   ++ev)
	if (ev->second->get_event_kind() == e)
	  return false;
      states_events_[s].push_front(new Event<hstate_t>(e));
      return true;
    }

    template <class AutoType_>
    inline
    bool 
    AutomatonHistory<AutoType_>::set_state_event_about(event_kind_t e, 
						       hstate_t s, 
						       hstate_t first)
    {
      for (typename state_events_t::const_iterator ev 
	     = states_events_[s].begin();
	   ev != states_events_[s].end();
	   ++ev)
	if ((*ev)->get_event_kind() == e)
	  return false;
      states_events_[s].push_front(new UnaryEvent<hstate_t>(e, first));
      return true;
    }
      
    template <class AutoType_>
    inline
    bool 
    AutomatonHistory<AutoType_>::set_state_event_about(event_kind_t e, 
						       hstate_t s, 
						       hstate_t first, 
						       hstate_t second)
    {
      for (typename state_events_t::const_iterator ev = 
	     states_events_[s].begin();
	   ev != states_events_[s].end();
	   ++ev)
	if ((*ev)->get_event_kind() == e)
	  return false;
      states_events_[s].push_front(new BinaryEvent<hstate_t>
				   (e, first, second));
      return true;
    }
    
    template <class AutoType_>
    inline
    const utility::ref<Event<hstate_t> >
    AutomatonHistory<AutoType_>::get_state_event_about(event_kind_t e, 
						       hstate_t     s) const
    {
      typename states_events_t::const_iterator se = states_events_.find(s);
      if (se == states_events_.end())
	return 0;
      for (typename state_events_t::const_iterator ev = se->second.begin();
	   ev != se->second.end();
	   ++ev)
	if ((*ev)->get_event_kind() == e)
	  return *ev;
      return 0;      
    }

    template <class AutoType_>
    inline
    bool 
    AutomatonHistory<AutoType_>::set_edge_event_about(event_kind_t e,
						      hedge_t edge)
    {
      for (typename edge_events_t::const_iterator ev 
	     = edges_events_[edge].begin();
	   ev != edges_events_[edge].end();
	   ++ev)
	if (ev->second->get_event_kind() == e)
	  return false;
      edges_events_[edge].push_front(new Event<hedge_t>(e));
      return true;
    }

    template <class AutoType_>
    inline
    bool 
    AutomatonHistory<AutoType_>::set_edge_event_about(event_kind_t e, 
						      hedge_t edge, 
						      hedge_t first)
    {
      for (typename edge_events_t::const_iterator ev 
	     = edges_events_[edge].begin();
	   ev != edges_events_[edge].end();
	   ++ev)
	if ((*ev)->get_event_kind() == e)
	  return false;
      edges_events_[edge].push_front(new UnaryEvent<hedge_t>(e, first));
      return true;
    }
    
    template <class AutoType_>
    inline
    bool 
    AutomatonHistory<AutoType_>::set_edge_event_about(event_kind_t e,
						      hedge_t edge, 
						      hedge_t first,
						      hedge_t second)
    {
      for (typename edge_events_t::const_iterator ev 
	     = edges_events_[edge].begin();
	   ev != edges_events_[edge].end();
	   ++ev)
	if ((*ev)->get_event_kind() == e)
	  return false;
      edges_events_[edge].push_front
	(new BinaryEvent<hedge_t>(e, first, second));
      return true;
    }
    
    template <class AutoType_>
    inline
    const utility::ref<Event<hedge_t> >
    AutomatonHistory<AutoType_>::get_edge_event_about(event_kind_t e,
						      hedge_t edge
						      ) const
    {
      typename edges_events_t::const_iterator ee = edges_events_.find(edge);
      if (ee == edges_events_.end())
	return 0;
      for (typename edge_events_t::const_iterator ev = ee->second.begin();
	   ev != ee->second.end();
	   ++ev)
	if ((*ev)->get_event_kind() == e)
	  return (*ev);
      return 0;
    }
    
    template <class AutoType_>
    inline
    bool 
    AutomatonHistory<AutoType_>::set_auto_event_about(event_kind_t e)
    {
      for (typename auto_events_t::const_iterator ev = auto_events_.begin();
	   ev != auto_events_.end();
	   ++ev)
	if (ev->second->get_event_kind() == e)
	  return false;
      auto_events_.push_front(new Event<AutoType_>(e));
      return true;
    }
    
    template <class AutoType_>
    inline
    bool 
    AutomatonHistory<AutoType_>::set_auto_event_about(event_kind_t e, 
						      AutoType_ first)
    {
      for (typename auto_events_t::const_iterator ev = auto_events_.begin();
	   ev != auto_events_.end();
	   ++ev)
	if (ev->second->get_event_kind() == e)
	  return false;
      auto_events_.push_front(new Event<AutoType_>(e, first));
      return true;
    }

    template <class AutoType_>
    inline
    bool 
    AutomatonHistory<AutoType_>::set_auto_event_about(event_kind_t e, 
						      AutoType_ first,
						      AutoType_ second)
    {
      for (typename auto_events_t::const_iterator ev = auto_events_.begin();
	   ev != auto_events_.end();
	   ++ev)
	if ((*ev)->get_event_kind() == e)
	  return false;
      auto_events_.push_front(new BinaryEvent<AutoType_>(e, first, second));
      return true;
    }
    
    template <class AutoType_>
    inline
    const utility::ref<Event<AutoType_> > 
    AutomatonHistory<AutoType_>::get_auto_event_about(event_kind_t e) const
    {
      for (typename auto_events_t::const_iterator ev = auto_events_.begin();
	   ev != auto_events_.end();
	   ++ev)
	if ((*ev)->get_event_kind() == e)
	  return (*ev);      
      return 0;
    }

    template <class T>
    inline
    std::ostream&
    operator<<(std::ostream& out, const Event<T>& e)
    {
      out << e.get_event_kind();
      return out;
    }


  } // history

} // vcsn

#endif // AUTOMATA_HISTORY_HXX
