// vauto.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_DEMOS_VAUCANSWIG_META_VAUTO_HH
# define VCSN_DEMOS_VAUCANSWIG_META_VAUTO_HH

#include "vcontext.hh"
#include <fstream>
#include <cstdlib>
#include <string>
#include <stdexcept>

namespace vcsn
{
  struct virtual_automaton
  {
    virtual const virtual_context &context() const = 0;

    virtual bool has_state(int) const = 0;
    virtual bool has_edge(int) const = 0;
    virtual void del_state(int) = 0;
    virtual void del_edge(int) = 0;

    virtual std::list<int> states() const = 0;
    virtual std::list<int> edges() const = 0;

    virtual int add_state() = 0;
    void add_states(int);
    virtual int add_spontaneous(int, int) = 0;
    virtual int add_letter_edge(int, int, char) = 0;
    virtual int add_lw_edge(int, int, int, const std::string&) = 0;
    virtual int add_rw_edge(int, int, const std::string&, int) = 0;
    virtual int add_lrw_edge(int, int, int, const std::string&, int) = 0;

    virtual std::string label_of(int) const = 0;

    virtual int origin_of(int) const = 0;
    virtual int aim_of(int) const = 0;

    virtual void clear_initial() = 0;
    virtual std::list<int> initial() const = 0;
    virtual bool is_initial(int) const = 0;
    virtual void unset_initial(int) = 0;
    virtual void set_initial(int) = 0;
    virtual void set_initial(int, char) = 0;
    virtual void set_initial_lw(int, int, char) = 0;
    virtual void set_initial_lw(int, int) = 0;
    virtual void set_initial_rw(int, char, int) = 0;
    virtual void set_initial_rw(int, int) = 0;
    virtual void set_initial_lrw(int, int, char, int) = 0;
    virtual void set_initial_lrw(int, int, int) = 0;
    virtual std::string initial_label(int) = 0;

    virtual void clear_final() = 0;
    virtual std::list<int> final() const = 0;
    virtual bool is_final(int) const = 0;
    virtual void unset_final(int) = 0;
    virtual void set_final(int) = 0;
    virtual void set_final(int, char) = 0;
    virtual void set_final_lw(int, int, char) = 0;
    virtual void set_final_lw(int, int) = 0;
    virtual void set_final_rw(int, char, int) = 0;
    virtual void set_final_rw(int, int) = 0;
    virtual void set_final_lrw(int, int, char, int) = 0;
    virtual void set_final_lrw(int, int, int) = 0;
    virtual std::string final_label(int) = 0;

    virtual std::list<int> delta(int, bool states_only = true) const = 0;
    virtual std::list<int> letter_delta(int, char, bool states_only = true) const = 0;
    virtual std::list<int> spontaneous_delta(int, bool states_only = true) const = 0;

    virtual std::list<int> rdelta(int, bool states_only = true) const = 0;
    virtual std::list<int> letter_rdelta(int, char, bool states_only = true) const = 0;
    virtual std::list<int> spontaneous_rdelta(int, bool states_only = true) const = 0;

    virtual std::string describe() const = 0;
    virtual std::string as_dot(const char *name = "automaton") const = 0;
    void dot_run(const char *fname, const char *cmd = "gv", const char *name = "automaton") const;
    virtual ~virtual_automaton();
  };
}

#endif // VCSN_DEMOS_VAUCANSWIG_META_VAUTO_HH
