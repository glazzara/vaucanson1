// manylinks.hh
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
#ifndef AUTOMATA_CONCRETE_MANYLINKS_HH
# define AUTOMATA_CONCRETE_MANYLINKS_HH

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concrete/manylinks_carriers.hh>

namespace vcsn {

  /*----------.
  | ManyLinks |
  `----------*/
  //! ManyLinks implements an automaton with every services in O(1). 
  /*! This is an implementation that uses a lot of pointers (its name
    come from this fact). 
  */ 
  template<typename Label, typename StateTag, typename EdgeTag>
  class ManyLinks
  {
  public:
    typedef ManyLinksStatesCarrier<StateTag, EdgeTag, Label>	states_t;
    typedef ManyLinksInitialCarrier<StateTag, EdgeTag, Label>	initial_t;
    typedef ManyLinksFinalCarrier<StateTag, EdgeTag, Label>	final_t;
    typedef ManyLinksState<StateTag, EdgeTag, Label>		state_t;
    typedef ManyLinksEdgesCarrier<state_t, EdgeTag, Label>	edges_t;
    typedef Label						label_t;

    ManyLinks();
      
    ManyLinks(const ManyLinks& other);

    states_t& states();

    const states_t& states() const;
    
    edges_t& edges(); 

    const edges_t& edges() const; 

    final_t& final();

    const final_t& final() const;

    initial_t& initial();

    const initial_t& initial() const;

  protected:
    final_t final_;
    edges_t edges_;
  };


  template<typename L, typename S, typename E>
  struct automaton_traits<ManyLinks<L, S, E> >
  {
    typedef const ManyLinksStatesCarrier<S, E, L>& states_ret_t;
    typedef const ManyLinksInitialCarrier<S, E, L>& initial_ret_t;
    typedef const ManyLinksFinalCarrier<S, E, L>& final_ret_t;
    typedef const ManyLinksEdgesCarrier<ManyLinksState<S, E, L>,
					E, L>& edges_ret_t;
    typedef L label_ret_t;
  };

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  const ManyLinksStatesCarrier<StateTag, EdgeTag, Label>&
  auto_op_states(const Structure<S>& series,
		 const ManyLinks<Label, StateTag, EdgeTag>& impl);

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  const ManyLinksEdgesCarrier<ManyLinksState<StateTag, EdgeTag, Label>, 
			      EdgeTag, Label>&
  auto_op_edges(const Structure<S>& series,
		const ManyLinks<Label, StateTag, EdgeTag>& impl);
		 
  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  const ManyLinksInitialCarrier<StateTag, EdgeTag, Label>&
  auto_op_initial(const Structure<S>& series,
		  const ManyLinks<Label, StateTag, EdgeTag>& impl);
  
  
  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  const ManyLinksFinalCarrier<StateTag, EdgeTag, Label>&
  auto_op_final(const Structure<S>& series,
		const ManyLinks<Label, StateTag, EdgeTag>& impl);


  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  unsigned auto_op_add_state(const Structure<S>& series,
			     ManyLinks<Label, StateTag, EdgeTag>& impl);

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  unsigned auto_op_new_edge(const Structure<S>& series,
			    ManyLinks<Label, StateTag, EdgeTag>& impl,
			    unsigned from, unsigned to,
			    const Label& l);
			     
  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  unsigned auto_op_add_edge(const Structure<S>& series,
			    ManyLinks<Label, StateTag, EdgeTag>& impl,
			    unsigned from, unsigned to,
			    const Label& l);

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  void auto_op_clear_initial(const Structure<S>& series,
			     ManyLinks<Label, StateTag, EdgeTag>& impl, 
			     unsigned s);

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  void auto_op_clear_final(const Structure<S>& series,
			   ManyLinks<Label, StateTag, EdgeTag>& impl, 
			   unsigned s);

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  void auto_op_set_initial(const Structure<S>& series,
			   ManyLinks<Label, StateTag, EdgeTag>& impl, 
			   unsigned s);

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  void auto_op_set_final(const Structure<S>& series,
			 ManyLinks<Label, StateTag, EdgeTag>& impl, 
			 unsigned s);

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  void auto_op_del_state(const Structure<S>& series,
			 ManyLinks<Label, StateTag, EdgeTag>& impl, 
			 unsigned s);

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  void auto_op_del_edge(const Structure<S>& series,
			ManyLinks<Label, StateTag, EdgeTag>& impl, 
			unsigned s);

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  void auto_op_safe_del_state(const Structure<S>& series,
			      ManyLinks<Label, StateTag, EdgeTag>& impl, 
			      unsigned s);

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  bool auto_op_has_state(const Structure<S>& series,
			 const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			 unsigned s);

  template<typename S, typename Label, typename StateTag, typename EdgeTag>
  bool auto_op_has_edge(const Structure<S>& series,
			const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			unsigned e);

  template<typename S, typename Label, typename StateTag, typename EdgeTag, 
	   typename Iter>
  void auto_op_delta_states(const Structure<S>& series,
			    const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			    Iter out,
			    unsigned s);

  template<typename S, typename Label, typename StateTag, typename EdgeTag, 
	   typename Iter>
  void auto_op_delta_edges(const Structure<S>& series,
			   const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			   Iter out,
			   unsigned s);

  template<typename S, typename Label, typename StateTag, typename EdgeTag,
	   typename Iter>
  void auto_op_rdelta_states(const Structure<S>& series,
			     const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			     Iter out,
			     unsigned s);

  template<typename S, typename Label, typename StateTag, typename EdgeTag, 
	   typename Iter>
  void auto_op_rdelta_edges(const Structure<S>& series,
			    const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			    Iter out,
			    unsigned s);

  template<typename S, typename Label, typename StateTag, typename EdgeTag, 
	   typename Iter, typename Q>
  void auto_op_delta_states(const Structure<S>& series,
			    const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			    Iter out,
			    unsigned s,
			    const Q& q);

  template<typename S, typename Label, typename StateTag, typename EdgeTag, 
	   typename Iter, typename Q>
  void auto_op_delta_edges(const Structure<S>& series,
			   const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			   Iter out,
			   unsigned s,
			   const Q& q);

  template<typename S, typename Label, typename StateTag, typename EdgeTag, 
	   typename Iter, typename Q>
  void auto_op_rdelta_states(const Structure<S>& series,
			     const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			     Iter out,
			     unsigned s,
			     const Q& q);

  template<typename S, typename Label, typename StateTag, typename EdgeTag, 
	   typename Iter, typename Q>
  void auto_op_rdelta_edges(const Structure<S>& series,
			    const ManyLinks<Label, StateTag, EdgeTag>& impl, 
			    Iter out,
			    unsigned s,
			    const Q& q);
  
} // vcsn

# include <vaucanson/automata/concrete/manylinks.hxx>

#endif // AUTOMATA_CONCRETE_MANYLINKS_HH
