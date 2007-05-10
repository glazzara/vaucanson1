// history.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_AUTOMATA_CONCEPT_HISTORY_HXX
# define VCSN_AUTOMATA_CONCEPT_HISTORY_HXX

# include <list>
# include <map>

# include <vaucanson/automata/concept/history.hh>

namespace vcsn {

  namespace history {

    template <class T>
    Event<T>::Event(event_kind_t e) : kind_(e)
    {}

    template <class T>
    Event<T>::~Event()
    {}

    template <class T>
    event_kind_t
    Event<T>::get_event_kind() const
    {
      return kind_;
    }

    template <class T>
    BinaryEvent<T>::BinaryEvent(event_kind_t e, const T& first,
				const T& second) :
      Event<T>(e),
      first_(first),
      second_(second)
    {}

    template <class T>
    const T&
    BinaryEvent<T>::get_first() const
    {
      return first_;
    }

    template <class T>
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
    const T&
    UnaryEvent<T>::get_first() const
    {
      return first_;
    }

    // FIXME : use std::find_if with a good function object.
    template <class AutoType_>
    bool
    AutomatonHistory<AutoType_>::set_state_event_about(event_kind_t e,
						       hstate_t s)
    {
      // FIXME: fix this code.
//	 for (typename state_events_t::const_iterator ev
//	     = states_events_[s].begin();
//	   ev != states_events_[s].end();
//	   ++ev)
//	if (ev->second->get_event_kind() == e)
//	  return false;
//	 states_events_[s].push_front(new Event<hstate_t>(e));
      return true;
    }

    template <class AutoType_>
    bool
    AutomatonHistory<AutoType_>::set_state_event_about(event_kind_t e,
						       hstate_t s,
						       hstate_t first)
    {
      for (typename state_events_t::const_iterator ev
	     = states_events_[s].begin();
	   ev != states_events_[s].end();
	   ++ev)
	if (ev->get_event_kind() == e)
	  return false;
      states_events_[s].push_front(UnaryEvent<hstate_t>(e, first));
      return true;
    }

    template <class AutoType_>
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
	if (ev->get_event_kind() == e)
	  return false;
      states_events_[s].push_front(BinaryEvent<hstate_t>
				   (e, first, second));
      return true;
    }

    template <class AutoType_>
    const Event<typename AutoType_::hstate_t>
    AutomatonHistory<AutoType_>::get_state_event_about(event_kind_t e,
						       hstate_t	    s) const
    {
      typename states_events_t::const_iterator se = states_events_.find(s);
      if (se == states_events_.end())
	return 0;
      for (typename state_events_t::const_iterator ev = se->second.begin();
	   ev != se->second.end();
	   ++ev)
	if (ev->get_event_kind() == e)
	  return *ev;
      return 0;
    }

    template <class AutoType_>
    bool
    AutomatonHistory<AutoType_>::set_transition_event_about(event_kind_t e,
							    htransition_t transition)
    {
      for (typename transition_events_t::const_iterator ev
	     = transitions_events_[transition].begin();
	   ev != transitions_events_[transition].end();
	   ++ev)
	if (ev->get_event_kind() == e)
	  return false;
      transitions_events_[transition].push_front(Event<htransition_t>(e));
      return true;
    }

    template <class AutoType_>
    bool
    AutomatonHistory<AutoType_>::set_transition_event_about(event_kind_t e,
							    htransition_t transition,
							    htransition_t first)
    {
      for (typename transition_events_t::const_iterator ev
	     = transitions_events_[transition].begin();
	   ev != transitions_events_[transition].end();
	   ++ev)
	if (ev->get_event_kind() == e)
	  return false;
      transitions_events_[transition].push_front(UnaryEvent<htransition_t>(e, first));
      return true;
    }

    template <class AutoType_>
    bool
    AutomatonHistory<AutoType_>::set_transition_event_about(event_kind_t e,
							    htransition_t transition,
							    htransition_t first,
							    htransition_t second)
    {
      for (typename transition_events_t::const_iterator ev
	     = transitions_events_[transition].begin();
	   ev != transitions_events_[transition].end();
	   ++ev)
	if (ev->get_event_kind() == e)
	  return false;
      transitions_events_[transition].push_front
	(BinaryEvent<htransition_t>(e, first, second));
      return true;
    }

    template <class AutoType_>
    const Event<typename AutoType_::htransition_t>
    AutomatonHistory<AutoType_>::get_transition_event_about(event_kind_t e,
							    htransition_t transition
      ) const
    {
      typename transitions_events_t::const_iterator ee =
	transitions_events_.find(transition);
      if (ee == transitions_events_.end())
	return 0;
      for (typename transition_events_t::const_iterator ev = ee->second.begin();
	   ev != ee->second.end();
	   ++ev)
	if (ev->get_event_kind() == e)
	  return (*ev);
      return 0;
    }

    template <class AutoType_>
    bool
    AutomatonHistory<AutoType_>::set_auto_event_about(event_kind_t e)
    {
      for (typename auto_events_t::const_iterator ev = auto_events_.begin();
	   ev != auto_events_.end();
	   ++ev)
	if (ev->second->get_event_kind() == e)
	  return false;
      auto_events_.push_front(Event<AutoType_>(e));
      return true;
    }

    template <class AutoType_>
    bool
    AutomatonHistory<AutoType_>::set_auto_event_about(event_kind_t e,
						      AutoType_ first)
    {
      for (typename auto_events_t::const_iterator ev = auto_events_.begin();
	   ev != auto_events_.end();
	   ++ev)
	if (ev->second->get_event_kind() == e)
	  return false;
      auto_events_.push_front(Event<AutoType_>(e, first));
      return true;
    }

    template <class AutoType_>
    bool
    AutomatonHistory<AutoType_>::set_auto_event_about(event_kind_t e,
						      AutoType_ first,
						      AutoType_ second)
    {
      for (typename auto_events_t::const_iterator ev = auto_events_.begin();
	   ev != auto_events_.end();
	   ++ev)
	if (ev->get_event_kind() == e)
	  return false;
      auto_events_.push_front(BinaryEvent<AutoType_>(e, first, second));
      return true;
    }

    template <class AutoType_>
    const Event<AutoType_>
    AutomatonHistory<AutoType_>::get_auto_event_about(event_kind_t e) const
    {
      for (typename auto_events_t::const_iterator ev = auto_events_.begin();
	   ev != auto_events_.end();
	   ++ev)
	if (ev->get_event_kind() == e)
	  return (*ev);
      return 0;
    }

    template <class T>
    std::ostream&
    operator<<(std::ostream& out, const Event<T>& e)
    {
      out << e.get_event_kind();
      return out;
    }


  } // history

} // vcsn

#endif // ! VCSN_AUTOMATA_CONCEPT_HISTORY_HXX
