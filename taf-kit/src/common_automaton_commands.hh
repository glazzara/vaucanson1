// common_automaton_commands.hh: this file is part of Vaucanson.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008 The Vaucanson Group.
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
#ifndef COMMON_AUTOMATON_COMMANDS_HH
# define COMMON_AUTOMATON_COMMANDS_HH

/**
 * @file   common_automaton_commands.hh
 * @author Guillaume Leroi
 * @date   Mon Jul 24 16:57:33 2006
 *
 * @brief Commands declarations and definitions specific for automata.
 *
 */

# include "common.hh"

# include CONTEXT_HEADER
# ifdef WITH_TWO_ALPHABETS
#  include <vaucanson/xml/contexts/fmp.hh>
# endif
# include <vaucanson/xml/XML.hh>
# include <vaucanson/tools/dot_display.hh>
# include <vaucanson/tools/dot_dump.hh>

using namespace CONTEXT_NAMESPACE;

using namespace vcsn;
using namespace vcsn::tools;
using vcsn::xml::XML;

# include <cstdlib>
# include <iostream>

# include "getters.hh"
# include "edition_commands.hh"
# include "library_commands.hh"
# include "commands.hh"
# include "commands_macros.hh"


  /*---------------------------------------.
  | Command definition (RatExp excluded).  |
  `---------------------------------------*/


DEFINE_IS_PROPERTY_COMMAND (ambiguous);

DEFINE_IS_PROPERTY_COMMAND (complete);

//DEFINE_IS_PROPERTY_COMMAND (normalized);

DEFINE_IS_PROPERTY_COMMAND (realtime);

DEFINE_IS_PROPERTY_COMMAND (standard);

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (complete));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (realtime));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (coaccessible));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (accessible));

//DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
//			ALGO (normalize));

DEFINE_ONE_ARG_COMMAND_TWO_ALGOS (NAME (quotient)
				  ARG_KIND (aut)
				  ALGOS (quotient, realtime));

DEFINE_COMMAND (NAME (union)
		CODE (/* Empty */)
		KEEP_AUTOMATON (
		  sum (get_aut (args.args[1]),
		       get_aut (args.args[2])))
		RETURNVALUE (0));

DEFINE_TWO_ARGS_COMMAND (ARG_KIND (aut)
			 ALGO (product));

DEFINE_TWO_ARGS_COMMAND (ARG_KIND (aut)
			 ALGO (concatenate));

DEFINE_COMMAND (NAME (eval)
		CODE (
		      automaton_t a = realtime (get_aut (args.args[1]));
		      semiring_elt_t b = eval (a, get_word (a, args.args[2])).value();
		     )
		OUTPUT (b << std::endl)
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (power)
		CODE (int n = atoi (args.args[2]);
		      automaton_t a = get_aut (args.args[1]);
		      automaton_t p (a);
		      for (int i = 1; i < n; ++i)
			p = product (p, a))
		KEEP_AUTOMATON (p)
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (standardize)
		CODE (automaton_t a = get_aut (args.args[1]);
		      standardize (a))
		KEEP_AUTOMATON(a)
		RETURNVALUE (0));

# ifdef FIRST_PROJECTION_CONTEXT
DEFINE_COMMAND (NAME (first_projection)
		CODE (
		  automaton_t src = get_aut(args.args[1]);
		  vcsn::CONTEXT::projection_traits_t::first_projection_t a =
		  vcsn::CONTEXT::projection_traits_t::first_projection(src);
		  first_projection(src, a))
		KEEP_AUTOMATON (a)
		RETURNVALUE (0));
# endif

# ifdef SECOND_PROJECTION_CONTEXT
DEFINE_COMMAND (NAME (second_projection)
		CODE (
		  automaton_t src = get_aut(args.args[1]);
		  vcsn::CONTEXT::projection_traits_t::second_projection_t a =
		  vcsn::CONTEXT::projection_traits_t::second_projection(src);
		  second_projection(src, a))
		KEEP_AUTOMATON (a)
		RETURNVALUE (0));
# endif

# define DEFINE_COMMAND_OF_STANDARD(Algo)			\
  DEFINE_COMMAND (NAME (Algo ## _of_standard)			\
		  CODE (automaton_t a = get_aut (args.args[1]);	\
			automaton_t b = get_aut (args.args[2]);	\
			if (!is_standard (a))			\
			  standardize (a);			\
			if (!is_standard (b))			\
			  standardize (b);			\
			Algo ## _of_standard_here (a, b))	\
		  KEEP_AUTOMATON (a)				\
		  RETURNVALUE(0))

DEFINE_COMMAND_OF_STANDARD(union);

DEFINE_COMMAND_OF_STANDARD(concat);

#undef DEFINE_COMMAND_OF_STANDARD

DEFINE_COMMAND (NAME (star_of_standard)
		CODE (automaton_t a = get_aut (args.args[1]);
		      if (!is_standard (a))
		        standardize (a);
		      star_of_standard_here (a))
		KEEP_AUTOMATON (a)
		RETURNVALUE(0));

# ifdef FIRST_PROJECTION_CONTEXT
#  define FIRST_PROJECTION_COMMAND_ENTRY \
COMMAND_ENTRY (first_projection, Aut, \
	       "Give the first projection of `aut'."),
# else
#  define FIRST_PROJECTION_COMMAND_ENTRY
# endif

# ifdef SECOND_PROJECTION_CONTEXT
#  define SECOND_PROJECTION_COMMAND_ENTRY \
COMMAND_ENTRY (second_projection, Aut, \
	       "Give the second projection of `aut'."),
# else
#  define SECOND_PROJECTION_COMMAND_ENTRY
# endif

# define USE_GENERIC_AUTOMATON_COMMAND_GROUP()				\
  COMMAND_GROUP (							\
    "Generic algorithms for automata:",					\
									\
    COMMAND_ENTRY (accessible, Aut,					\
		   "Give the maximal accessible subautomaton of `aut'."), \
    FIRST_PROJECTION_COMMAND_ENTRY					\
    SECOND_PROJECTION_COMMAND_ENTRY					\
    COMMAND_ENTRY (eps_removal, Aut,					\
		   "Give `aut' closed over epsilon transitions."),	\
    COMMAND_ENTRY (eps_removal_sp, Aut,					\
		   "Give `aut' closed over epsilon transitions."),	\
    COMMAND_ENTRY_CN (co-accessible, coaccessible, Aut,			\
		      "Give the maximal coaccessible subautomaton of `aut'."), \
    COMMAND_ENTRY (complete, Aut, "Give the complete version of `aut'."), \
    COMMAND_ENTRY (concatenate, AutAut, "Concatenate `aut1' and `aut2'."), \
    /*  COMMAND_ENTRY (normalize, Aut,					\
        "Give the Thompson-normalized automaton of `aut'."), */		\
    COMMAND_ENTRY (power, AutInt, "Give the power of `aut' by `n'."),	\
    COMMAND_ENTRY (product, AutAut, "Give the product of `aut1' by `aut2'." ),	\
    COMMAND_ENTRY (quotient, Aut, "Give the quotient of `aut'."),	\
    COMMAND_ENTRY (realtime, Aut, "Give the realtime version of `aut'."), \
    COMMAND_ENTRY (standardize, Aut, "Give the standard automaton of `aut'."),	\
    COMMAND_ENTRY (union_of_standard, AutAut,				\
		   "Give the union of standard automata."),		\
    COMMAND_ENTRY (concat_of_standard, AutAut,				\
		   "Give the concatenation of standard automata."),	\
    COMMAND_ENTRY (star_of_standard, Aut,				\
		   "Give the star of automaton `aut'."),	\
    COMMAND_ENTRY (union, AutAut, "Give the union of `aut1' and `aut2'."),	\
    COMMAND_ENTRY (transpose, Aut, "Transpose the automaton `aut'."),	\
    COMMAND_ENTRY (trim, Aut, "Trim the automaton `aut'.")		\
									\
    )									\


#endif // ! COMMON_AUTOMATON_COMMANDS_HH
