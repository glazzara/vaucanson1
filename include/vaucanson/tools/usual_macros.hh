// usual_macros.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TOOLS_USUAL_MACROS_HH
# define VCSN_TOOLS_USUAL_MACROS_HH

# include <fstream>

#define for_all_const(T, I, C) \
   for (T::const_iterator I = (C).begin(); I != (C).end(); ++I)

#define for_all(T, I, C) \
   for (T::iterator I = (C).begin(); I != (C).end(); ++I)

#define for_all_const_(T, I, C) \
   for (typename T::const_iterator I = (C).begin(); I != (C).end(); ++I)

#define for_all_(T, I, C) \
   for (typename T::iterator I = (C).begin(); I != (C).end(); ++I)


#define INHERIT_TYPEDEF_(From, Type) \
   typedef typename From::Type Type;

#define AUTOMATON_TYPES_(AutoType,Prefix)							\
 typedef AutoType						Prefix##automaton_t;		\
 typedef typename AutoType::set_t				Prefix##automata_set_t;		\
 typedef typename AutoType::states_t				Prefix##states_t;		\
 typedef typename AutoType::state_iterator			Prefix##state_iterator;		\
 typedef typename AutoType::edges_t				Prefix##edges_t;		\
 typedef typename AutoType::edge_iterator			Prefix##edge_iterator;		\
 typedef typename AutoType::initial_t				Prefix##initial_t;		\
 typedef typename AutoType::final_t				Prefix##final_t;		\
 typedef typename AutoType::initial_iterator			Prefix##initial_iterator;	\
 typedef typename AutoType::final_iterator			Prefix##final_iterator;		\
 typedef typename AutoType::monoid_t				Prefix##monoid_t;		\
 typedef typename AutoType::monoid_elt_t			Prefix##monoid_elt_t;		\
 typedef typename Prefix##monoid_elt_t::value_t			Prefix##monoid_elt_value_t;	\
 typedef typename AutoType::semiring_t				Prefix##semiring_t;		\
 typedef typename AutoType::series_set_t			Prefix##series_set_t;		\
 typedef typename AutoType::series_set_elt_value_t		Prefix##series_set_elt_value_t;	\
 typedef typename AutoType::series_set_elt_t			Prefix##series_set_elt_t;	\
 typedef typename Prefix##series_set_elt_t::semiring_elt_t	Prefix##semiring_elt_t;		\
 typedef typename Prefix##semiring_elt_t::value_t		Prefix##semiring_elt_value_t;	\
 typedef typename AutoType::label_t				Prefix##label_t;		\
 typedef typename AutoType::tag_t				Prefix##tag_t;

#define AUTOMATON_TYPES_EXACT_(AutoType,Prefix)						\
 typedef AutoType					Prefix##automaton_t;		\
 typedef AutoType::set_t				Prefix##automata_set_t;		\
 typedef AutoType::states_t				Prefix##states_t;		\
 typedef AutoType::state_iterator			Prefix##state_iterator;		\
 typedef AutoType::edges_t				Prefix##edges_t;		\
 typedef AutoType::edge_iterator			Prefix##edge_iterator;		\
 typedef AutoType::initial_t				Prefix##initial_t;		\
 typedef AutoType::final_t				Prefix##final_t;		\
 typedef AutoType::initial_iterator			Prefix##initial_iterator;	\
 typedef AutoType::final_iterator			Prefix##final_iterator;		\
 typedef AutoType::monoid_t				Prefix##monoid_t;		\
 typedef AutoType::monoid_elt_t				Prefix##monoid_elt_t;		\
 typedef Prefix##monoid_elt_t::value_t			Prefix##monoid_elt_value_t;	\
 typedef AutoType::semiring_t				Prefix##semiring_t;		\
 typedef AutoType::series_set_t				Prefix##series_set_t;		\
 typedef AutoType::series_set_elt_value_t		Prefix##series_set_elt_value_t;	\
 typedef AutoType::series_set_elt_t			Prefix##series_set_elt_t;	\
 typedef Prefix##series_set_elt_t::semiring_elt_t	Prefix##semiring_elt_t;		\
 typedef Prefix##semiring_elt_t::value_t		Prefix##semiring_elt_value_t;	\
 typedef AutoType::label_t				Prefix##label_t;		\
 typedef AutoType::tag_t				Prefix##tag_t;

#define AUTOMATON_TYPES(AutoType)           AUTOMATON_TYPES_(AutoType,)
#define AUTOMATON_TYPES_EXACT(AutoType)	    AUTOMATON_TYPES_EXACT_(AutoType,)


// The following macros assume you have used a macro AUTOMATON_TYPES*
// previously.

#define AUTOMATON_FREEMONOID_TYPES_(Autotype, Prefix)						\
 typedef typename Prefix##monoid_t::alphabets_elt_t		Prefix##alphabets_elt_t;	\
 typedef typename Prefix##monoid_t::alphabet_t			Prefix##alphabet_t;		\
 typedef typename Prefix##alphabet_t::const_iterator		Prefix##alphabet_iterator;	\
 typedef typename Prefix##alphabet_t::letter_t			Prefix##letter_t;

#define AUTOMATON_FREEMONOID_TYPES_EXACT_(Autotype, Prefix)				\
 typedef Prefix##monoid_t::alphabets_elt_t		Prefix##alphabets_elt_t;	\
 typedef Prefix##monoid_t::alphabet_t			Prefix##alphabet_t;		\
 typedef Prefix##alphabet_t::const_iterator		Prefix##alphabet_iterator;	\
 typedef Prefix##alphabet_t::letter_t			Prefix##letter_t;


#define AUTOMATON_FREEMONOID_TYPES(Autotype)		\
				AUTOMATON_FREEMONOID_TYPES_(Autotype,)
#define AUTOMATON_FREEMONOID_TYPES_EXACT(Autotype)	\
				AUTOMATON_FREEMONOID_TYPES_EXACT_(Autotype,)



# define AUTOMATA_SET_TYPES(AutoSet)				\
typedef AutoSet					automata_set_t;	\
typedef typename automata_set_t::series_set_t	series_set_t;	\
typedef typename series_set_t::monoid_t		monoid_t;	\
typedef typename series_set_t::semiring_t	semiring_t;	\
typedef typename monoid_t::alphabet_t		alphabet_t;	\
typedef typename alphabet_t::letter_t		letter_t;


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

#define for_each_(T, S, C)			\
    for (typename T::iterator S = C.begin();	\
	 S != C.end();				\
         ++S)

#define remove_in(S, V) \
    S.erase(std::remove(S.begin(), S.end(), V), S.end())

#define SAVE_AUTOMATON_DOT(Dir, Name, Auto, Index)		\
    {								\
      std::ostringstream s;					\
      s << Dir << "/" << Name << "_" << Index << ".dot";	\
      std::ofstream f(s.str().c_str());				\
      vcsn::tools::dot_dump(f, Auto, Name);			\
    }

#define SAVE_AUTOMATON_DOT_SIMPLE(Name, Auto)			\
    {								\
      std::ostringstream s;					\
      s << Name << ".dot";					\
      std::ofstream f(s.str().c_str());				\
      vcsn::tools::dot_dump(f, Auto, Name);				\
    }

#define RAND___(Max)						\
((unsigned) int(((float) rand() / (float) RAND_MAX) * Max));

// Some useful macros for XML.
#ifndef VCSN_NDEBUG
# define XML_FAIL(S) \
   std::cerr << "Implement for " << typeid(S).name() << std::endl; \
   exit(1)
#else
# define XML_FAIL(S)
#endif
#define FAIL(S) { std::cerr << (S) << std::endl; exit(1); }
#define STR2XML(S) xercesc::XMLString::transcode(S)

//

// These macros can be use instead of some method calls.
// This is really tricky and dirty but so useful !
// !! * must be well documented * !!
#define zero_	zero(SELECT(typename series_set_elt_t::value_t))
#define one_	identity(SELECT(typename series_set_elt_t::value_t))
#define empty_	identity(SELECT(typename monoid_elt_t::value_t))
#define wzero_  zero(SELECT(typename semiring_elt_t::value_t))

#endif // ! VCSN_TOOLS_USUAL_MACROS_HH
