// history.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef AUTOMATA_HISTORY_HH
# define AUTOMATA_HISTORY_HH

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
      typedef std::list<Event<AutoType_>  >		       auto_events_t;
      typedef std::list<Event<hstate_t>  >		       state_events_t;
      typedef std::list<Event<hedge_t>  >		       edge_events_t;
      typedef std::map<hstate_t, state_events_t>	       states_events_t;
      typedef std::map<hedge_t, edge_events_t>		       edges_events_t;
      
      bool 
      set_state_event_about(event_kind_t, hstate_t);
      bool 
      set_state_event_about(event_kind_t, hstate_t, hstate_t);
      bool 
      set_state_event_about(event_kind_t, hstate_t, hstate_t, hstate_t);
      const Event<hstate_t> 
      get_state_event_about(event_kind_t, hstate_t) const;
							 
      bool 
      set_edge_event_about(event_kind_t, hedge_t);
      bool 
      set_edge_event_about(event_kind_t, hedge_t, hedge_t);
      bool 
      set_edge_event_about(event_kind_t, hedge_t, hedge_t, hedge_t);
      const Event<hedge_t> 
      get_edge_event_about(event_kind_t, hedge_t) const;
 
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
      edges_events_t	        edges_events_;
      auto_events_t    		auto_events_;
    };

  } // history

} // vcsn

# include <vaucanson/automata/concept/history.hxx>

#endif // AUTOMATA_HISTORY_HH
