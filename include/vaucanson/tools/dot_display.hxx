// dot_display.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_TOOLS_DOT_DISPLAY_HXX
# define VCSN_TOOLS_DOT_DISPLAY_HXX

# include <vaucanson/tools/dot_display.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/dot_dump.hh>

# include <ostream>
# include <string>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace vcsn {

  namespace tools {

    template <class S, class T>
    bool
    dot_display(const AutomataBase<S>&,
		const T&,
		const Element<S, T>& a,
		const std::string& name,
		const std::string& prog,
		const bool bg)
    {
      int filedes[2];
      if (pipe(filedes))
	return false;

      pid_t child_pid = fork();
      if (child_pid)
	{
	  close(filedes[0]);
	  if (child_pid == -1)
	    return false;
	  else
	    {
	      // FIXME: That trick is dirty!
	      {
		std::cout.flush();
		int old = dup(STDOUT_FILENO);
		dup2(filedes[1], STDOUT_FILENO);
		close(filedes[1]);

		dot_dump(std::cout, a, name);

		dup2(old, STDOUT_FILENO);
		close(old);
	      }
	      return bg or waitpid(child_pid, NULL, 0) == child_pid;
	    }
	}
      else
	{
	  close(filedes[1]);
	  dup2(filedes[0], STDIN_FILENO);
	  close(filedes[0]);
	  execlp(prog.c_str(), prog.c_str(), "-", 0);
	  return false;
	}
    }

    template <class S, class T>
    bool
    dot_display(const Element<S, T>& a,
		const std::string& name,
		const std::string& prog,
		const bool bg)
    {
      return dot_display(a.structure(), a.value(), a, name, prog, bg);
    }

  } // End of namespace tools.

} // End of namespace vcsn.

#endif // VCSN_TOOLS_GEN_RANDOM_HXX
