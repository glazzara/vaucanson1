// usual_macros.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 The Vaucanson Group.
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
# include <boost/preprocessor/cat.hpp>

/// Import the Type from From qualified with Qual, with a Typename prepended.
# define IMPORT_TYPEDEF_TYPENAME(From, Qual, Type, Typename) \
  typedef Typename From::Type Qual ## Type


/// Import the Type from From qualified with Qual, without a typename.
# define IMPORT_QUALIFIED_TYPEDEF(From, Qual, Type)		\
  IMPORT_TYPEDEF_TYPENAME(From, Qual, Type,)

/// Import the Type from From qualified with Qual, without a typename.
# define IMPORT_QUALIFIED_TYPEDEF_(From, Qual, Type)			\
  IMPORT_TYPEDEF_TYPENAME(From, Qual, Type, typename)


/// Import the Type from From, with a typename.
# define IMPORT_TYPEDEF_(From, Type)		\
  IMPORT_QUALIFIED_TYPEDEF_(From, ,Type)

/// Import the Type from From, without a typename.
# define IMPORT_TYPEDEF(From, Type)		\
  IMPORT_QUALIFIED_TYPEDEF(From, ,Type)




# define AUTOMATON_TYPES_MAYBE_TYPENAME(AutoType, Prefix, Typename)	\
  typedef AutoType						Prefix##automaton_t; \
  typedef Typename AutoType::set_t				Prefix##automata_set_t;	\
  typedef Typename AutoType::states_t				Prefix##states_t; \
  typedef Typename AutoType::state_iterator			Prefix##state_iterator;	\
  typedef Typename AutoType::transitions_t			Prefix##transitions_t; \
  typedef Typename AutoType::transition_iterator		Prefix##transition_iterator; \
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
  typedef Typename AutoType::tag_t				Prefix##tag_t; \
  typedef Typename AutoType::hstate_t				Prefix##hstate_t; \
  typedef Typename AutoType::htransition_t			Prefix##htransition_t;

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



/*------------.
| Iterating.  |
`------------*/
# define for_all_iterator(ConstIteratorType, I, C)		\
  for (ConstIteratorType I = (C).begin(); I != (C).end(); ++I)

/// Iteration given an iterator type, iterator name, and container.
# define for_all_const_iterator(IteratorType, I, C)		\
  for (IteratorType I = (C).begin(), I##_end = (C).end(); I##_end != I; ++I)


/// Iteration given a non-template container type.
# define for_all_const(T, I, C)				\
  for_all_iterator(T::const_iterator, I, C)

# define for_all(T, I, C)				\
  for_all_iterator(T::iterator, I, C)


/// Iteration given a template container type.
# define for_all_const_(T, I, C)			\
  for_all_const_iterator(typename T::const_iterator, I, C)

# define for_all_(T, I, C)				\
  for_all_iterator(typename T::iterator, I, C)


// The following macros assume you have used a macro AUTOMATON_TYPES*
// previously.

# define for_all_letters(I, A)			\
  for_all_iterator (alphabet_iterator, I, A)

# define for_all_states(I, A)			\
  for_all_iterator (state_iterator, I, (A).states())

# define for_all_transitions(I, A)			\
  for_all_iterator (transition_iterator, I, (A).transitions())

# define for_all_initial_states(I, A)			\
  for_all_iterator (initial_iterator, I, (A).initial())

# define for_all_final_states(I, A)			\
  for_all_iterator (final_iterator, I, (A).final())

# define for_all_letters_(Prefix, I, A)			\
  for_all_iterator (Prefix##alphabet_iterator, I, A)

# define for_all_states_(Prefix, I, A)			\
  for_all_iterator (Prefix##state_iterator, I, (A).states())

# define for_all_transitions_(Prefix, I, A)			\
  for_all_iterator (Prefix##transition_iterator, I, (A).transitions())

# define for_all_initial_states_(Prefix, I, A)			\
  for_all_iterator (Prefix##initial_iterator, I, (A).initial())

# define for_all_final_states_(Prefix, I, A)			\
  for_all_iterator (Prefix##final_iterator, I, (A).final())


//Const versions of the previous macros.
//You should always use these macros unless you need to erase over iteration.
# define for_all_const_letters(I, A)			\
  for_all_const_iterator (alphabet_iterator, I, A)

# define for_all_const_states(I, A)			\
  for_all_const_iterator (state_iterator, I, (A).states())

# define for_all_const_transitions(I, A)			\
  for_all_const_iterator (transition_iterator, I, (A).transitions())

# define for_all_const_initial_states(I, A)			\
  for_all_const_iterator (initial_iterator, I, (A).initial())

# define for_all_const_final_states(I, A)			\
  for_all_const_iterator (final_iterator, I, (A).final())

# define for_all_const_letters_(Prefix, I, A)			\
  for_all_const_iterator (Prefix##alphabet_iterator, I, A)

# define for_all_const_states_(Prefix, I, A)			\
  for_all_const_iterator (Prefix##state_iterator, I, (A).states())

# define for_all_const_transitions_(Prefix, I, A)			\
  for_all_const_iterator (Prefix##transition_iterator, I, (A).transitions())

# define for_all_const_initial_states_(Prefix, I, A)			\
  for_all_const_iterator (Prefix##initial_iterator, I, (A).initial())

# define for_all_const_final_states_(Prefix, I, A)			\
  for_all_const_iterator (Prefix##final_iterator, I, (A).final())



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
# define VCSN_EMPTY_	identity(SELECT(typename monoid_elt_t::value_t))
# define wzero_	zero(SELECT(typename semiring_elt_t::value_t))
# define wone_	identity(SELECT(typename semiring_elt_t::value_t))


# define VARIANT_INCLUDE_FILE(PATH, FILE, SUFFIX) \
    <PATH/BOOST_PP_CAT(FILE, SUFFIX)>

# define GRAPH_IMPL_HEADER \
    VARIANT_INCLUDE_FILE(VCSN_GRAPH_IMPL_INCLUDE_PATH,VCSN_GRAPH_IMPL,_graph_impl.hh)

# define GRAPH_DEFAULT_IMPL_HEADER \
    VARIANT_INCLUDE_FILE(VCSN_GRAPH_IMPL_INCLUDE_PATH,VCSN_DEFAULT_GRAPH_IMPL,_graph_impl.hh)

# define GRAPH_CONTEXT_HEADER(Impl, Context) \
    VARIANT_INCLUDE_FILE(VCSN_CONTEXT_INCLUDE_PATH,Impl,/Context)

# define GRAPH_CONTEXT_HEADER_(Context) \
    <VCSN_CONTEXT_INCLUDE_PATH/VCSN_GRAPH_IMPL/Context>

# include <vaucanson/misc/global_timer.hh>

#endif // ! VCSN_MISC_USUAL_MACROS_HH
