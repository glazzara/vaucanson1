// history.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
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
//       for (typename state_events_t::const_iterator ev 
// 	     = states_events_[s].begin();
// 	   ev != states_events_[s].end();
// 	   ++ev)
// 	if (ev->second->get_event_kind() == e)
// 	  return false;
//       states_events_[s].push_front(new Event<hstate_t>(e));
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
	if ((*ev)->get_event_kind() == e)
	  return false;
      states_events_[s].push_front(new UnaryEvent<hstate_t>(e, first));
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
	if ((*ev)->get_event_kind() == e)
	  return false;
      states_events_[s].push_front(new BinaryEvent<hstate_t>
				   (e, first, second));
      return true;
    }
    
    template <class AutoType_>
    const Event<hstate_t> 
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
    const Event<hedge_t> 
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
    const Event<AutoType_> 
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
    std::ostream&
    operator<<(std::ostream& out, const Event<T>& e)
    {
      out << e.get_event_kind();
      return out;
    }


  } // history

} // vcsn

#endif // VCSN_AUTOMATA_CONCEPT_HISTORY_HXX
