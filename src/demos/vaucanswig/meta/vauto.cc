// vauto.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#include "vauto.hh"
#include <vaucanson/misc/unique.hcc>
#include <fstream>
#include <stdexcept>
#include <cstdlib>

namespace vcsn
{
  void virtual_automaton::dot_run(const char *fname, const char *cmd, const char *name) const
  {
    {
      std::ofstream of(fname);
      if (!of)
	throw std::runtime_error("could not open file for writing");
      of << this->as_dot(name);
    }
    system((std::string(cmd) + ' ' + fname).c_str());
  }

  void virtual_automaton::add_states(int nr)
  {
    if (nr < 0)
      throw std::runtime_error("negative number of states requested");
    for (int i = 0; i < nr; ++i)
      this->add_state();
  }

  virtual_automaton::~virtual_automaton() {}
}

