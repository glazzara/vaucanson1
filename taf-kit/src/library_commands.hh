// library_commands.hh: this file is part of Vaucanson.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008, 2009 The Vaucanson Group.
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

# include <sys/stat.h>
# include <unistd.h>

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

static const std::list<std::string>&
get_automata_path(const arguments_t& args)
{
  static std::list<std::string> path_list;

  if (path_list.empty())
    {
      const char* base_path = getenv("VCSN_DATA_PATH");
      if (base_path == 0)
	base_path = VCSN_DATA_PATH;

      // Strip "vcsn-" from the program name.
      const char* suffix = strrchr(program_name, '/');
      suffix = suffix ? suffix + 6 : program_name + 5;

      const std::string lib_dir = std::string("/automata/") + suffix;

      std::string path;

      while (*base_path)
	{
	  const char* sep = strchr(base_path, ':');

	  if (sep == base_path)
	    {
	      // Ignore an empty path.
	      ++ base_path;
	      continue;
	    }

	  // Did we find a colon?
	  if (sep > 0)
	    path = std::string(base_path, sep - base_path) + lib_dir;
	  else
	    path = std::string(base_path) + lib_dir;

	  base_path = sep + 1;

	  struct stat s;

	  if ((stat(path.c_str(), &s) == 0) && (S_ISDIR(s.st_mode)))
	    {
	      path_list.push_back(path);
	    }

	  // No colon found, do not loop.
	  if (sep == 0)
	    break;
	}

      if (path_list.empty())
	FAIL(std::string ("Error: Cannot open ") + path + ".\n"
	     "Please set VCSN_DATA_PATH to the Vaucanson data directory,\n"
	     "containing `" + lib_dir + "'.");
    }
  return path_list;
}

static int
list_automata_command(const arguments_t& args)
{
  const std::list<std::string>& path_list = get_automata_path(args);

  std::set<std::string> files;

  for (std::list<std::string>::const_iterator i = path_list.begin();
       i != path_list.end(); ++i)
    {
      DIR* directory = opendir(i->c_str());
      dirent* file;

      while ((file = readdir(directory)))
	{
	  std::string filename = file->d_name;
	  if (filename.rfind(".xml") == filename.size() - 4)
	    files.insert(filename);
	}
      closedir(directory);
    }

  if (files.empty())
    {
      echo("No automata are predefined for this type.");
    }
  else
    {
      echo("The following automata are predefined:");
      for_all(std::set<std::string>, ifile, files)
	echo("  - " << *ifile);
    }
  return 0;
}

#endif /* !AUTOMATON_LIBRARY_COMMANDS_HH */
