// history.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_HISTORY_HH
# define VCSN_AUTOMATA_CONCEPT_HISTORY_HH

# include <list>
# include <map>
# include <string>

# include <vaucanson/automata/concept/handlers.hh>
// # include <vaucanson/misc/ref.hh>

namespace vcsn {

  namespace history {

    typedef std::string event_kind_t;

    template <class T>
    class Event
    {
      public:
	Event(event_kind_t e);

	virtual
	event_kind_t
	get_event_kind() const;

	virtual ~Event();
      protected :
	event_kind_t	kind_;
    };

    template <class T>
    class BinaryEvent : public Event<T>
    {
      public:
	BinaryEvent(event_kind_t e, const T& first, const T& second);

	const T&
	get_first() const;

	const T&
	get_second() const;

      protected :
	T		first_, second_;
    };

    template <class T>
    class UnaryEvent : public Event<T>
    {
      public:
	UnaryEvent(event_kind_t e, const T& first);

	const T&
	get_first() const;

      protected :
	T		first_;
    };

    template <class T>
    std::ostream&
    operator<<(std::ostream& out, const Event<T>& e);

    template <class AutoType_>
    class AutomatonHistory
    {
      public :
	typedef std::list<Event<AutoType_> >		     auto_events_t;
	typedef std::list<Event<hstate_t> >		     state_events_t;
	typedef std::list<Event<htransition_t> >	     transition_events_t;
	typedef std::map<hstate_t, state_events_t>	     states_events_t;
	typedef std::map<htransition_t, transition_events_t> transitions_events_t;

	bool
	set_state_event_about(event_kind_t, hstate_t);
	bool
	set_state_event_about(event_kind_t, hstate_t, hstate_t);
	bool
	set_state_event_about(event_kind_t, hstate_t, hstate_t, hstate_t);
	const Event<hstate_t>
	get_state_event_about(event_kind_t, hstate_t) const;

	bool
	set_transition_event_about(event_kind_t, htransition_t);
	bool
	set_transition_event_about(event_kind_t, htransition_t, htransition_t);
	bool
	set_transition_event_about(event_kind_t, htransition_t, htransition_t,
				   htransition_t);
	const Event<htransition_t>
	get_transition_event_about(event_kind_t, htransition_t) const;

	bool
	set_auto_event_about(event_kind_t);
	bool
	set_auto_event_about(event_kind_t, AutoType_);
	bool
	set_auto_event_about(event_kind_t, AutoType_, AutoType_);
	const Event<AutoType_>
	get_auto_event_about(event_kind_t) const;

      protected :
	states_events_t		states_events_;
	transitions_events_t		transitions_events_;
	auto_events_t			auto_events_;
    };

  } // history

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
# include <vaucanson/automata/concept/history.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_CONCEPT_HISTORY_HH
