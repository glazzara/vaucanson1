// commands_macros.hh: this file is part of Vaucanson.
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

#ifndef COMMANDS_MACROS_HH
# define COMMANDS_MACROS_HH

# include <boost/spirit/core.hpp>

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

/*----------------------------.
| Letter type macro helpers.  |
`----------------------------*/

# define DEFAULT_FROM_TRAITS(name, letter_type) \
const std::string \
default_##name () \
{ \
  return vcsn::algebra::letter_traits<letter_type>::default_##name (); \
}

# define SET_DEFAULT(letter_type) \
void set_default(vcsn::algebra::token_representation_t& arg) \
{ \
  typedef vcsn::algebra::letter_traits<letter_type> traits_t; \
  arg.open_par = traits_t::default_open_par(); \
  arg.close_par = traits_t::default_close_par(); \
  arg.plus = traits_t::default_plus(); \
  arg.times = traits_t::default_times(); \
  arg.star = traits_t::default_star(); \
  arg.one = traits_t::default_epsilon(); \
  arg.zero = traits_t::default_zero(); \
  arg.open_weight = traits_t::default_open_weight(); \
  arg.close_weight = traits_t::default_close_weight(); \
  arg.spaces.clear(); \
  arg.spaces.push_back(traits_t::default_space()); \
}

// We can not pass rules by value (hence the references).
# define ALPHABET_DEFINITION(letter_type) \
void \
if_is_char_letter(boost::spirit::rule<boost::spirit::scanner<const char*> >& def, \
		  const boost::spirit::rule<boost::spirit::scanner<const char*> >& case_true, \
		  const boost::spirit::rule<boost::spirit::scanner<const char*> >& case_false) \
{ \
  def = misc::static_if< \
  misc::static_eq<vcsn::algebra::letter_traits<letter_type>::is_char_letter, misc::true_t>::value, \
  boost::spirit::rule<boost::spirit::scanner<const char*> >&, \
  boost::spirit::rule<boost::spirit::scanner<const char*> >& \
  >::choose(case_true, case_false); \
}

// Setup letter context.
# define LETTER_CONTEXT(letter_type) \
SET_DEFAULT(letter_type) \
DEFAULT_FROM_TRAITS(open_par, letter_type) \
DEFAULT_FROM_TRAITS(close_par, letter_type) \
DEFAULT_FROM_TRAITS(plus, letter_type) \
DEFAULT_FROM_TRAITS(times, letter_type) \
DEFAULT_FROM_TRAITS(star, letter_type) \
DEFAULT_FROM_TRAITS(epsilon, letter_type) \
DEFAULT_FROM_TRAITS(zero, letter_type) \
DEFAULT_FROM_TRAITS(open_weight, letter_type) \
DEFAULT_FROM_TRAITS(close_weight, letter_type) \
DEFAULT_FROM_TRAITS(space, letter_type) \
ALPHABET_DEFINITION(letter_type)

#endif // ! COMMANDS_MACROS_HH
