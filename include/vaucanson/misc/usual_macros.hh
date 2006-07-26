// usual_macros.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_USUAL_MACROS_HH
# define VCSN_MISC_USUAL_MACROS_HH

# include <fstream>
# include <vaucanson/config/system.hh>

# define INHERIT_TYPEDEF_(From, Type)		\
  typedef typename From::Type Type;

# define AUTOMATON_TYPES_MAYBE_TYPENAME(AutoType, Prefix, Typename)	\
  typedef AutoType						Prefix##automaton_t; \
  typedef Typename AutoType::set_t				Prefix##automata_set_t;	\
  typedef Typename AutoType::states_t				Prefix##states_t; \
  typedef Typename AutoType::state_iterator			Prefix##state_iterator;	\
  typedef Typename AutoType::transitions_t			Prefix##transitions_t; \
  typedef Typename AutoType::transition_iterator		Prefix##transition_iterator; \
  typedef Typename AutoType::initial_t				Prefix##initial_t; \
  typedef Typename AutoType::final_t				Prefix##final_t; \
  typedef Typename AutoType::initial_iterator			Prefix##initial_iterator; \
  typedef Typename AutoType::final_iterator			Prefix##final_iterator;	\
  typedef Typename AutoType::monoid_t				Prefix##monoid_t; \
  typedef Typename AutoType::monoid_elt_t			Prefix##monoid_elt_t; \
  typedef Typename Prefix##monoid_elt_t::value_t		Prefix##monoid_elt_value_t; \
  typedef Typename AutoType::semiring_t				Prefix##semiring_t; \
  typedef Typename AutoType::series_set_t			Prefix##series_set_t; \
  typedef Typename AutoType::series_set_elt_value_t		Prefix##series_set_elt_value_t;	\
  typedef Typename AutoType::series_set_elt_t			Prefix##series_set_elt_t; \
  typedef Typename Prefix##series_set_elt_t::semiring_elt_t	Prefix##semiring_elt_t;	\
  typedef Typename Prefix##semiring_elt_t::value_t		Prefix##semiring_elt_value_t; \
  typedef Typename AutoType::label_t				Prefix##label_t; \
  typedef Typename AutoType::tag_t				Prefix##tag_t;

# define AUTOMATON_TYPES_(AutoType,Prefix)			\
  AUTOMATON_TYPES_MAYBE_TYPENAME(AutoType, Prefix, typename)

# define AUTOMATON_TYPES_EXACT_(AutoType,Prefix)	\
  AUTOMATON_TYPES_MAYBE_TYPENAME(AutoType, Prefix, )

# define AUTOMATON_TYPES(AutoType)	    AUTOMATON_TYPES_(AutoType,)
# define AUTOMATON_TYPES_EXACT(AutoType)    AUTOMATON_TYPES_EXACT_(AutoType,)


// The following macros assume you have used a macro AUTOMATON_TYPES*
// previously.

# define AUTOMATON_FREEMONOID_TYPES_(Autotype, Prefix)			\
  typedef typename Prefix##monoid_t::alphabets_elt_t		Prefix##alphabets_elt_t; \
  typedef typename Prefix##monoid_t::alphabet_t			Prefix##alphabet_t; \
  typedef typename Prefix##alphabet_t::const_iterator		Prefix##alphabet_iterator; \
  typedef typename Prefix##alphabet_t::letter_t			Prefix##letter_t;

# define AUTOMATON_FREEMONOID_TYPES_EXACT_(Autotype, Prefix)		\
  typedef Prefix##monoid_t::alphabets_elt_t		Prefix##alphabets_elt_t; \
  typedef Prefix##monoid_t::alphabet_t			Prefix##alphabet_t; \
  typedef Prefix##alphabet_t::const_iterator		Prefix##alphabet_iterator; \
  typedef Prefix##alphabet_t::letter_t			Prefix##letter_t;


# define AUTOMATON_FREEMONOID_TYPES(Autotype)	\
  AUTOMATON_FREEMONOID_TYPES_(Autotype,)
# define AUTOMATON_FREEMONOID_TYPES_EXACT(Autotype)	\
  AUTOMATON_FREEMONOID_TYPES_EXACT_(Autotype,)



# define AUTOMATA_SET_TYPES(AutoSet)				\
  typedef AutoSet				automata_set_t;	\
  typedef typename automata_set_t::series_set_t	series_set_t;	\
  typedef typename series_set_t::monoid_t	monoid_t;	\
  typedef typename series_set_t::semiring_t	semiring_t;	\
  typedef typename monoid_t::alphabet_t		alphabet_t;	\
  typedef typename alphabet_t::letter_t		letter_t;


# define for_all_const(T, I, C)				\
  for (T::const_iterator I = (C).begin(),		\
	 I ## _end = (C).end(); I != I ## _end; ++I)

# define for_all(T, I, C)				\
  for (T::iterator I = (C).begin(),			\
	 I ## _end = (C).end(); I != I ## _end; ++I)

# define for_all_const_(T, I, C)			\
  for (typename T::const_iterator I = (C).begin(),	\
	 I ## _end = (C).end(); I != I ## _end; ++I)

# define for_all_(T, I, C)				\
  for (typename T::iterator I = (C).begin(),		\
	 I ## _end = (C).end(); I != I ## _end; ++I)

// The following macros assume you have used a macro AUTOMATON_TYPES*
// previously.

# define for_all_letters(I, A)				\
  for (alphabet_iterator I = (A).begin(),		\
	 I ## _end = (A).end(); I != I ## _end; ++I)

# define for_all_states(I, A)					\
  for (state_iterator I = (A).states().begin(),			\
	 I ## _end = (A).states().end(); I != I ## _end; ++I)

# define for_all_transitions(I, A)					\
  for (transition_iterator I = (A).transitions().begin(),		\
	 I ## _end = (A).transitions().end(); I != I ## _end; ++I)

# define for_all_final_states(I, A)				\
  for (final_iterator I = (A).final().begin(),			\
	 I ## _end = (A).final().end(); I != I ## _end; ++I)

# define for_all_initial_states(I, A)				\
  for (initial_iterator I = (A).initial().begin(),		\
	 I ## _end = (A).initial().end(); I != I ## _end; ++I)

# define remove_in(S, V)				\
  S.erase(std::remove(S.begin(), S.end(), V), S.end())

# define RAND___(Max)						\
  ((unsigned) int(((float) rand() / (float) RAND_MAX) * Max));

// Some useful macros for XML.
# ifndef VCSN_NDEBUG
#  define XML_FAIL(S)							\
  do {									\
    std::cerr << "Implement for " << typeid(S).name() << std::endl;	\
    exit(1);								\
  } while (0)
# else
#  define XML_FAIL(S)
# endif
# define FAIL(S) { std::cerr << (S) << std::endl; exit(1); }

// These macros can be use instead of some method calls.
// This is really tricky and dirty but so useful !
// !! * must be well documented * !!
# define zero_	zero(SELECT(typename series_set_elt_t::value_t))
# define one_	identity(SELECT(typename series_set_elt_t::value_t))
# define empty_	identity(SELECT(typename monoid_elt_t::value_t))
# define wzero_	zero(SELECT(typename semiring_elt_t::value_t))

#endif // ! VCSN_MISC_USUAL_MACROS_HH
