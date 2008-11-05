// library_commands.hh: this file is part of Vaucanson.
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
#ifndef AUTOMATON_LIBRARY_COMMANDS_HH
# define AUTOMATON_LIBRARY_COMMANDS_HH

/**
 * @file library_commands.hh
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * Automaton library related commands.
 */

# include "common.hh"

# include CONTEXT_HEADER
# ifdef WITH_TWO_ALPHABETS
#  include <vaucanson/xml/contexts/fmp.hh>
# endif
# include <vaucanson/xml/XML.hh>

using namespace CONTEXT_NAMESPACE;

using namespace vcsn;
using namespace vcsn::tools;
using vcsn::xml::XML;

# include <iostream>
# include <sys/types.h>
# include <dirent.h>

# include "getters.hh"
# include "commands.hh"
# include "commands_macros.hh"

# include "progname.h"

  /*--------------------------------------------.
  | Command definitions for Automaton Library.  |
  `--------------------------------------------*/

static std::string get_automata_path (const arguments_t& args)
{
  const char* base_path = getenv ("VCSN_DATA_PATH");
  const char* lib_dir = "automata";
  if (base_path == 0)
    base_path = VCSN_DATA_PATH;
  const std::string type = program_name + 5; // Strip "vcsn-".
  std::string path = std::string (base_path) + "/" + lib_dir + "/" + type;

  DIR* directory = opendir (path.c_str ());
  if (not directory)
    FAIL (std::string ("Error: Cannot open ") + path + ".\n"
	  "Please set VCSN_DATA_PATH to the Vaucanson data directory,\n"
	  "containing `" + lib_dir + "'.");
  closedir (directory);
  return path;
}

static int list_automata_command (const arguments_t& args)
{
  DIR* directory = opendir (get_automata_path (args).c_str ());
  dirent* file;
  std::set<std::string> files;

  while ((file = readdir (directory)))
  {
    std::string filename = file->d_name;
    if (filename.rfind (".xml") == filename.size() - 4)
      files.insert (filename);
  }
  closedir (directory);
  echo ("The following automata are predefined:");
  for_all (std::set<std::string>, ifile, files)
    echo ("  - " << ifile->substr (0, ifile->size () - 4));
  return 0;
}

static int dump_automaton_command (const arguments_t& args)
{
  std::string file = get_automata_path (args) + "/" + args.args[1] + ".xml";
  std::ifstream in (file.c_str ());

  if (in.fail ())
  {
    std::cerr << "Error: cannot open `" << file << "'." << std::endl;
    exit (-3);
  }
  PRINT_RESULT (in.rdbuf ());
  return 0;
}

#endif /* !AUTOMATON_LIBRARY_COMMANDS_HH */
