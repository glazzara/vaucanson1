// commands_macros.hh: this file is part of Vaucanson.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008, 2009, 2010 The Vaucanson Group.
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
 * @author Micha�l Cadilhac <michael.cadilhac@lrde.org>
 *
 * Commands declaration macros.
 */

/*-----------------------------------------------.
| Command entries ; meant for arg parsing & co.  |
`-----------------------------------------------*/

# define COMMAND_ENTRY_CN_(Name, CodeName, Params, NParams, Docstring, Expert) \
  { # Name, CodeName ## _command, Params, NParams, Docstring, Expert }
# define COMMAND_ENTRY_CN(Name, CodeName, BlockParams, Docstring)	\
  COMMAND_ENTRY_CN_ (Name, CodeName, BlockParams, Docstring, 0)
# define COMMAND_ENTRY(Name, BlockParams, Docstring)		\
  COMMAND_ENTRY_CN_ (Name, Name, BlockParams, Docstring, 0)
# define COMMAND_ENTRY_EXPERT_CN(Name, CodeName, BlockParams, Docstring) \
  COMMAND_ENTRY_CN_ (Name, CodeName, BlockParams, Docstring, 1)
# define COMMAND_ENTRY_EXPERT(Name, BlockParams, Docstring) \
  COMMAND_ENTRY_CN_ (Name, Name, BlockParams, Docstring, 1)
# define COMMAND_GROUP(Text, Group...)		\
  { 0, 0, 0, 0, Text, 0 },			\
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
ALPHABET_DEFINITION(letter_type)

#endif // ! COMMANDS_MACROS_HH
