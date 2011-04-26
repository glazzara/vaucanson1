// commands.hh: this file is part of Vaucanson.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2010, 2011 The Vaucanson Group.
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
#ifndef COMMANDS_HH
# define COMMANDS_HH

/**
 * @file commands.hh
 *
 * TAF-Kit command map.
 */

#include "common.hh"
#include "getters.hh"

#include <vector>
#include <string>
#include <map>
#include <iosfwd>

struct arguments_t;

// Parameters to commands.
enum command_params {
  None,
  Exp,
  Aut,
  AutExp,
  AutAut,
  AutInt,
  AutWord,
  AutWeight,
};

struct command_t
{
  // Section of the command.
  const char* section;
  // Associated function.
  int (*command)(const arguments_t&);
  // Description of the parameters.
  command_params params;
  // Number of parameters.
  int n_params;
  // Short documentation of the command.
  const char* docstring;
  // Set EXPERT to true for commands that should be shown by
  // --list-all-commands but not --list-commands.
  bool expert;
};

class command_map
{
public:
  typedef int (*command_ptr)(const arguments_t&);

  static void register_cmd(const char* section,
			   const char* name,
			   int (*command)(const arguments_t&),
			   command_params params,
			   const char* docstring,
			   bool expert = false);

  static const command_t* lookup(const std::string& str);

  static std::ostream& list(std::ostream& ostr, bool expert = false);

  static int execute(const arguments_t& args);

private:
  typedef std::map<std::string, command_t> map_t;
  static map_t& map_();
};


# define COMMAND_ENTRY_CN_(Name, CodeName, Params, Docstring, Expert) \
  register_cmd(sec, #Name, CodeName##_command, Params, Docstring, Expert);
# define COMMAND_ENTRY_CN(Name, CodeName, BlockParams, Docstring)	\
  COMMAND_ENTRY_CN_ (Name, CodeName, BlockParams, Docstring, 0)
# define COMMAND_ENTRY(Name, BlockParams, Docstring)		\
  COMMAND_ENTRY_CN_ (Name, Name, BlockParams, Docstring, 0)
# define COMMAND_ENTRY_EXPERT_CN(Name, CodeName, BlockParams, Docstring) \
  COMMAND_ENTRY_CN_ (Name, CodeName, BlockParams, Docstring, 1)
# define COMMAND_ENTRY_EXPERT(Name, BlockParams, Docstring) \
  COMMAND_ENTRY_CN_ (Name, Name, BlockParams, Docstring, 1)

#define BEGIN_COMMAND_GROUP(Name, Text)		\
  namespace {					\
  class register_##Name : public command_map	\
  {						\
  public:					\
    register_##Name()				\
    {						\
      const char* sec = Text;

#define END_COMMAND_GROUP } } reg_; }

#endif /* !COMMANDS_HH */
