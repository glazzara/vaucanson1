// usual_macros.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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
#ifndef TOOLS_USUAL_MACROS_HH
# define TOOLS_USUAL_MACROS_HH

#define AUTOMATON_TYPES_(AutoType,Prefix)				      \
 typedef AutoType			Prefix##automaton_t;		      \
 typedef typename AutoType::states_t	Prefix##states_t;		      \
 typedef typename AutoType::state_iterator  Prefix##state_iterator;	      \
 typedef typename AutoType::edges_t	    Prefix##edges_t;		      \
 typedef typename AutoType::edge_iterator   Prefix##edge_iterator;	      \
 typedef typename AutoType::initial_t	    Prefix##initial_t;		      \
 typedef typename AutoType::final_t	    Prefix##final_t;		      \
 typedef typename AutoType::initial_iterator Prefix##initial_iterator;	      \
 typedef typename AutoType::final_iterator   Prefix##final_iterator;	      \
 typedef typename AutoType::monoid_t	     Prefix##monoid_t;		      \
 typedef typename AutoType::monoid_elt_t     Prefix##monoid_elt_t;	      \
 typedef typename Prefix##monoid_elt_t::value_t	Prefix##monoid_elt_value_t;   \
 typedef typename Prefix##monoid_t::alphabets_elt_t  Prefix##alphabets_elt_t; \
 typedef typename Prefix##monoid_t::alphabet_t       Prefix##alphabet_t;      \
 typedef typename Prefix##alphabet_t::iterator   Prefix##alphabet_iterator;   \
 typedef typename Prefix##alphabet_t::letter_t       Prefix##letter_t;	      \
 typedef typename AutoType::weights_t                Prefix##weights_t;	      \
 typedef typename AutoType::series_t                 Prefix##series_t;	      \
 typedef typename AutoType::series_elt_t             Prefix##series_elt_t;    \
 typedef typename Prefix##series_elt_t::weight_t     Prefix##weight_t;	      \
 typedef typename Prefix##weight_t::value_t          Prefix##weight_value_t;  \
 typedef typename AutoType::label_t			Prefix##label_t;      \
 typedef typename AutoType::tag_t			Prefix##tag_t;

#define AUTOMATON_TYPES_EXACT_(AutoType,Prefix)				  \
 typedef AutoType				Prefix##automaton_t;	  \
 typedef AutoType::states_t			Prefix##states_t;	  \
 typedef AutoType::state_iterator		Prefix##state_iterator;	  \
 typedef AutoType::edges_t			Prefix##edges_t;	  \
 typedef AutoType::edge_iterator		Prefix##edge_iterator;	  \
 typedef AutoType::initial_t			Prefix##initial_t;	  \
 typedef AutoType::final_t			Prefix##final_t;	  \
 typedef AutoType::initial_iterator		Prefix##initial_iterator; \
 typedef AutoType::final_iterator		Prefix##final_iterator;	  \
 typedef AutoType::monoid_t			Prefix##monoid_t;	  \
 typedef AutoType::monoid_elt_t	        Prefix##monoid_elt_t;		  \
 typedef Prefix##monoid_elt_t::value_t	Prefix##monoid_elt_value_t;	  \
 typedef Prefix##monoid_t::alphabets_elt_t	Prefix##alphabets_elt_t;  \
 typedef Prefix##monoid_t::alphabet_t	Prefix##alphabet_t;		  \
 typedef Prefix##alphabet_t::iterator	Prefix##alphabet_iterator;	  \
 typedef Prefix##alphabet_t::letter_t	Prefix##letter_t;		  \
 typedef AutoType::weights_t			Prefix##weights_t;	  \
 typedef AutoType::series_t			Prefix##series_t;	  \
 typedef AutoType::series_elt_t		Prefix##series_elt_t;		  \
 typedef Prefix##series_elt_t::weight_t	Prefix##weight_t;		  \
 typedef Prefix##weight_t::value_t		Prefix##weight_value_t;	  \
 typedef AutoType::label_t			Prefix##label_t;	  \
 typedef AutoType::tag_t			Prefix##tag_t;

#define AUTOMATON_TYPES(AutoType)           AUTOMATON_TYPES_(AutoType,)	      
#define AUTOMATON_TYPES_EXACT(AutoType)     AUTOMATON_TYPES_EXACT_(AutoType,)

// the following macros assume you have used a macro AUTOMATON_TYPES*
// previously.

#define for_each_letter(E, A) \
    for (alphabet_iterator E = A.begin(); E != A.end(); ++E)

#define for_each_state(S, A) \
    for (state_iterator S = A.states().begin(); 	\
	 S != A.states().end(); 			\
	 ++S)

#define for_each_edge(E, A) \
    for (edge_iterator E = A.edges().begin(); 	\
	 E != A.edges().end(); 			\
	 ++E)

#define for_each_final_state(S, A) \
    for (final_iterator S = A.final().begin(); 	\
	 S != A.final().end(); 			\
	 ++S)

#define for_each_initial_state(S, A) \
    for (initial_iterator S = A.initial().begin(); 	\
	 S != A.initial().end(); 			\
	 ++S)

#define for_each_const_(T, S, C) \
    for (typename T::const_iterator S = C.begin();	\
	 S != C.end();					\
         ++S)

// These macros can be use instead of some method calls.
// This is really tricky and dirty but so useful !
// !! * must be well documented * !!
#define zero_	zero(SELECT(typename series_elt_t::value_t))
#define one_	identity(SELECT(typename series_elt_t::value_t))
#define empty_ identity(SELECT(typename monoid_elt_t::value_t))
#define wzero_  zero(SELECT(typename weight_t::value_t))

#endif // TOOLS_USUAL_MACROS_HH
