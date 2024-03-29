// out_display.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2007, 2011 The Vaucanson Group.
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

/**
 * @file out_display.hxx
 *
 * Out_display method, useful for xml_display and dot_display.
 *
 * @author Florent Terrones <florent.terrones@lrde.epita.fr>
 */

#ifndef VCSN_TOOLS_OUT_DISPLAY_HXX
# define VCSN_TOOLS_OUT_DISPLAY_HXX

# include <vaucanson/tools/out_display.hh>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

namespace vcsn {

  namespace tools {

    template <class S, class T>
    bool
    out_display(const AutomataBase<S>&,
		const T&,
		const Element<S, T>& a,
		const std::string& name,
		const bool bg,
		const char *const argv[],
		void (*function)(std::ostream& o,
				 const Element<S, T>& a,
				 const std::string& name))

    {
      int filedes[2];
      if (pipe(filedes))
	return false;

      pid_t child_pid = fork();
      if (child_pid)
	{
	  close(filedes[0]);
	  if (child_pid == -1)
	    {
	      close(filedes[1]);
	      return false;
	    }
	  else
	    {
	      // FIXME: That trick is dirty!
	      {
		std::cout.flush();
		int old = dup(STDOUT_FILENO);
		if (old != -1)
		  dup2(filedes[1], STDOUT_FILENO);
		close(filedes[1]);

		function(std::cout, a, name);

		if (old != -1)
		  {
		    dup2(old, STDOUT_FILENO);
		    close(old);
		  }
	      }
	      return bg or waitpid(child_pid, NULL, 0) == child_pid;
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
	  execvp(argv[0], const_cast<char *const *>(argv));
	  std::cerr << "Failed to execute `" << argv[0] << "'." << std::endl;
	  exit(1);
	}
    }

  } // End of namespace tools.

} // End of namespace vcsn.

#endif // ! VCSN_TOOLS_OUT_DISPLAY_HXX
