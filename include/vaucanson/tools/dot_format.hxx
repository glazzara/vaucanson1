// dot_format.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_TOOLS_DOT_FORMAT_HXX
# define VCSN_TOOLS_DOT_FORMAT_HXX

# include <vaucanson/tools/dot_format.hh>
# include <vaucanson/automata/concept/handlers.hh>
#include <map>

namespace vcsn
{
  namespace io
  {
    inline dot::dot(const std::string& name)
      : name_(name)
    {}

    template<typename Saver, typename Conv>
    void dot::operator()(std::ostream& out, const Saver& s, const Conv& conv) const
    {
      typedef typename Saver::automaton_t auto_t;
      const auto_t& a = s.automaton();

      unsigned count = 0;
      std::map<hstate_t, unsigned> state_map;

      out << "digraph vcsn {" << std::endl
	  << "label=\"" << name_ << ' ' << a << "\";" << std::endl
	  << "node [shape=circle];" << std::endl;

      for (typename auto_t::state_iterator i = a.states().begin();
	   i != a.states().end();
	   ++i)
	{
	  unsigned c = state_map[*i] = count++;
	  if (a.is_initial(*i))
	    {
	      out << name_ << count 
		  << " [style=invis,label=\"\",width=.01,height=.01];" << std::endl
		  << name_ << count << " -> " << name_ << c 
		  << " [label=\"" << conv(a, a.get_initial(*i)) << "\"];" << std::endl;
	      ++count;
	    }
	  if (a.is_final(*i))
	    {
	      out << name_ << count 
		  << " [style=invis,label=\"\",width=.01,height=.01];" << std::endl 
		  << name_ << c << " -> "  << name_ << count 
		  << " [label=\""<< conv(a, a.get_final(*i)) <<"\"];" << std::endl;
	      ++count;
	    }
	  out << name_ << c << " [label=\"" << *i << "\"];" << std::endl;
	}
      for (typename auto_t::edge_iterator i = a.edges().begin();
	   i != a.edges().end();
	   ++i)
	{
	  out << name_ << state_map[a.origin_of(*i)] 
	      << " -> " 
	      << name_ << state_map[a.aim_of(*i)];
	  out << " [label=\"" << conv(a, a.serie_of(*i)) << "\"];" << std::endl;
	}
      out << "}" << std::endl;
    }
  }
}


#endif // VCSN_TOOLS_DOT_FORMAT_HXX