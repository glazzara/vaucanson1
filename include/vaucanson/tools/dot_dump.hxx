// dot_dump.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_TOOLS_DOT_DUMP_HXX
# define VCSN_TOOLS_DOT_DUMP_HXX

# include <string>
# include <vaucanson/tools/io.hh>
# include <vaucanson/tools/dot_format.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/transducer_base.hh>

namespace vcsn {

  namespace tools {

    template <class S, class Auto>
    void dot_dump(const AutomataBase<S>&,
		  std::ostream& o,
		  const Auto& a,
		  const std::string& name)
    {
      o << automaton_saver(a, io::string_out(), io::dot(name));
    }

    template <class S, class Auto>
    void dot_dump(const TransducerBase<S>& s,
		  std::ostream& o,
		  const Auto& a,
		  const std::string& name)
    {
      o << automaton_saver(a, io::string_out(), io::transducer_dot(name));
    }

    template <typename Auto>
    void dot_dump(std::ostream& o, const Auto& a, const std::string& name)
    {
      dot_dump(a.set(), o, a, name);
    }

  } // tools

} // vcsn

#endif // VCSN_TOOLS_GEN_RANDOM_HXX
