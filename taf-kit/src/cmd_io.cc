// cmd_io.cc: this file is part of Vaucanson.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2010, 2011, 2012 The Vaucanson Group.
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

#include "commands.hh"
#include "edition_commands.hh"
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <cstdlib>

static int
data_command(const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);
  g_res.stream << "States: " << a.states().size () << std::endl
	       << "Transitions: " << a.transitions().size () << std::endl
	       << "Initial states: " << a.initial().size () << std::endl
	       << "Final states: " << a.final().size () << std::endl;
  return 0;
}


static int
cat_command(const arguments_t& args)
{
  g_res.keep(get_aut(args, 1));
  return 0;
}

static int
display_command(const arguments_t& args)
{
  return display_aut(get_aut(args, 1), args, 1);
}

static int
gui_command(const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);

  int filedes[2];
  if (pipe(filedes))
    {
      g_res.stream << "Cannot create pipe." << std::endl;
      return 1;
    }

  pid_t child_pid = fork();
  if (child_pid)
    {
      close(filedes[0]);
      if (child_pid == -1)
	{
	  g_res.stream << "Cannot fork." << std::endl;
	  close(filedes[1]);
	  return 1;
	}
      else
	{
	  std::cout.flush();
	  int old = dup(STDOUT_FILENO);
	  if (old != -1)
	    dup2(filedes[1], STDOUT_FILENO);
	  close(filedes[1]);

	  write_aut(a, std::cout);

	  if (old != -1)
	    {
	      dup2(old, STDOUT_FILENO);
	      close(old);
	    }
	  return 0;
	}
    }
  else
    {
      close(filedes[1]);
      dup2(filedes[0], STDIN_FILENO);
      close(filedes[0]);
      // execvp will treat its second argument as if it was
      // "const char* const*".  See the following page for an
      // explanation of why it is only declared as "char* const*".
      // http://www.opengroup.org/onlinepubs/000095399/functions/exec.html

      const char* vgijar = getenv("VGIJAR");
      if (vgijar)
	{
	  const char* const argv[] = {"java", "-jar", vgijar, "-", 0};
	  execvp(argv[0], const_cast<char *const *>(argv));
	}

      // If running java failed, or ig VGIJAR is not defined, try to
      // run a command called vgi.
      const char* const argv[] = {"vgi", "-", 0};
      execvp(argv[0], const_cast<char *const *>(argv));

      std::cerr << "Failed to execute `" << argv[0] << "'.\n"
		<< "You should either define an environment variable VGIJAR "
		<< "that points to the\nlocation of `vgi.jar', or have on your "
		<< "PATH a script `vgi' that starts VGI." << std::endl;
      exit(1);
    }
}


BEGIN_COMMAND_GROUP(io_commands,
	    "0. Input/Output functions:");
COMMAND_ENTRY(data, Aut, Text, "Print useful infos about `aut'.");
COMMAND_ENTRY(cat, Aut, Aut, "Return `aut'.");
COMMAND_ENTRY(display, Aut, None, "Display `aut'.");
COMMAND_ENTRY(edit, Aut, None, "Create or edit an automaton interactively.");
COMMAND_ENTRY(gui, Aut, None,
	      "launch VGI to create or edit an automaton interactively.");
END_COMMAND_GROUP
