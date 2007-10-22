// commands_macros.hh: this file is part of Vaucanson.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006 The Vaucanson Group.
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

#ifndef COMMANDS_MACROS_HH
# define COMMANDS_MACROS_HH

/**
 * @file commands_macros.hh
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * Commands declaration macros.
 */

/*----------------------------.
| Generic command definitions |
`----------------------------*/

// Syntactic sugar
# define NAME(Name) Name,
# define ARG_KIND(Type) get_ ## Type,
# define ALGO(Algo) Algo
# define ALGOS(Algo1, Algo2) Algo1, Algo2
# define CODE(Code) Code,
# define RETURNVALUE(ReturnValue) (ReturnValue)

# ifdef GLOBAL_RESULT
#  define KEEP_AUTOMATON(Output) GLOBAL_RESULT.keep (Output),
#  define KEEP(Output) GLOBAL_RESULT.keep (Output),
#  define PRINT_RESULT(Output) GLOBAL_RESULT.init ();		\
                               GLOBAL_RESULT.stream << Output;	\
                               GLOBAL_RESULT.finalize ()
#  define SET_RETURN_VALUE(ReturnValue)		\
            GLOBAL_RESULT.status = ReturnValue
# else
#  define KEEP(Output) echo_ (Output),
#  define KEEP_AUTOMATON(Output)					\
            echo_ (automaton_saver (Output, string_out (), XML ())),
#  define PRINT_RESULT(Output) echo_ (Output)
#  define SET_RETURN_VALUE(ReturnValue) ((void) 0)
# endif /* !GLOBAL_RESULT */

# define OUTPUT(Output) PRINT_RESULT(Output),
# define OUTPUT_ON_VERBOSE(Output) PRINT_RESULT((args.verbose ? Output : "")),

# ifdef GLOBAL_RESULT						\

# endif /* !GLOBAL_RESULT */					\

// Command without any special form.
# define DEFINE_COMMAND_(CodeName, Code, Output, ReturnValue)	\
  static int CodeName ## _command (const arguments_t& args)	\
  {								\
    Code;							\
    Output;							\
    SET_RETURN_VALUE(ReturnValue);				\
    return ReturnValue;						\
  }
# define DEFINE_COMMAND(BlockArgs) DEFINE_COMMAND_ (BlockArgs)

// Command associated to Algo named Algo_command that takes one argument.
# define DEFINE_ONE_ARG_COMMAND_(GetArg, Algo)		\
  DEFINE_COMMAND (NAME (Algo)				\
		  CODE (/* Empty */)			\
		  KEEP_AUTOMATON (			\
		    Algo (GetArg (args.args[1])))	\
		  RETURNVALUE (0))
# define DEFINE_ONE_ARG_COMMAND(BlockArgs) DEFINE_ONE_ARG_COMMAND_ (BlockArgs)

// Command named CodeName_command that takes one arg and uses two algos.
# define DEFINE_ONE_ARG_COMMAND_TWO_ALGOS_(CodeName, GetArg, Algo1, Algo2) \
  DEFINE_COMMAND (NAME (CodeName)					   \
		  CODE (/* Empty */)					   \
		  KEEP_AUTOMATON (					   \
		    Algo1(Algo2(get_aut (args.args[1]))))		   \
		  RETURNVALUE (0))
# define DEFINE_ONE_ARG_COMMAND_TWO_ALGOS(BlockArgs)	\
  DEFINE_ONE_ARG_COMMAND_TWO_ALGOS_ (BlockArgs)

// Command named Algo_command that takes two args and uses @c Algo .
# define DEFINE_TWO_ARGS_COMMAND_(GetArg, Algo)		\
  DEFINE_COMMAND (NAME (Algo)				\
		  CODE (/* Empty */)			\
		  KEEP_AUTOMATON (			\
		    Algo (GetArg (args.args[1]),	\
			  GetArg (args.args[2])))	\
		  RETURNVALUE (0))
# define DEFINE_TWO_ARGS_COMMAND(BlockArgs)	\
  DEFINE_TWO_ARGS_COMMAND_ (BlockArgs)

// Command just doing a is_@c Property .
# define DEFINE_IS_PROPERTY_COMMAND(Property)				\
  DEFINE_COMMAND (NAME (is_ ## Property)				\
		  CODE (						\
		    bool b = is_ ## Property (get_aut (args.args[1])))	\
		  OUTPUT_ON_VERBOSE (					\
		    (b ? "Entry is " # Property "\n":			\
		     "Entry is not " # Property "\n"))			\
		  RETURNVALUE (b ? 0 : 1))

/*-----------------------------------------------.
| Command entries ; meant for arg parsing & co.  |
`-----------------------------------------------*/

# define COMMAND_ENTRY_CN_(Name, CodeName, Params, NParams, Docstring)	\
  { # Name, CodeName ## _command, Params, NParams, Docstring }
# define COMMAND_ENTRY_CN(Name, CodeName, BlockParams, Docstring)	\
  COMMAND_ENTRY_CN_ (Name, CodeName, BlockParams, Docstring)
# define COMMAND_ENTRY(Name, BlockParams, Docstring)		\
  COMMAND_ENTRY_CN_ (Name, Name, BlockParams, Docstring)
# define COMMAND_GROUP(Text, Group...)		\
  { 0, 0, 0, 0, Text },				\
    Group

# define Exp "exp", 1
# define Aut "aut", 1
# define AutAut "aut1 aut2", 2
# define AutInt "aut n", 2
# define AutWord "aut word", 2
# define AutExp "aut exp", 2
# define File "file", 1
# define Nil "", 0

#endif /* !COMMANDS_MACROS_HH */
