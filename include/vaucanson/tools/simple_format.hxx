// simple_format.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_TOOLS_SIMPLE_FORMAT_HXX
# define VCSN_TOOLS_SIMPLE_FORMAT_HXX

# include <vaucanson/tools/simple_format.hh>
# include <string>

namespace vcsn
{
  namespace io
  {
    template<typename Saver, typename Conv>
    void simple::operator()(std::ostream& o, const Saver& s, const Conv& conv) const
    {
      typedef typename Saver::automaton_t auto_t;
      const auto_t& a = s.automaton();
      unsigned count = 1;

      o << "# States list" << std::endl;
      for (typename auto_t::state_iterator i = a.states().begin();
	   i != a.states().end();
	   ++i, ++count)
	{
	  o << 's' << *i << ' ';
	  if (a.is_initial(*i))
	    o << "i[" << conv(a, a.get_initial(*i)) << "] "; 
	  if (a.is_final(*i))
	    o << "f[" << conv(a, a.get_final(*i)) << "]";
	  o << std::endl;
	}

      o << std::endl;
      o << "# Transitions list" << std::endl;
      for (typename auto_t::edge_iterator i = a.edges().begin();
	   i != a.edges().end();
	   ++i)
	{
	  o << 's' << a.origin_of(*i) << ' '
	    << 's' << a.aim_of(*i) << ' ';
	  if (a.is_spontaneous(*i))
	    o << 'S';
	  else
	    o << "l[" << conv(a, a.series_of(*i)) << "]" << std::endl;
	}
      o << '.' << std::endl;
    }

    void get_delimited_exp(std::istream& in, std::string& s)
    {
      std::string::size_type	i = 1;
      
      // Ignore the first '['
      in.ignore();
      // Readline
      std::getline(in, s, ']');
      for (i = 0; i < s.size() && s[s.size() - i - 1] == '\\' ; ++i)
	;

      // While the final ']' is escaped, read again and concat
      while (i % 2 == 1)
      {
        std::string	tmp;

	s = s + "]";
        std::getline(in, tmp, ']');
	s = s + tmp;
	for (i = 0; i < tmp.size() && tmp[tmp.size() - i - 1] == '\\' ; ++i)
	  ;
      }
    }

    template<typename Loader>
    void simple::operator()(std::istream& in, Loader& l) const
    {
      bool done = false;
      unsigned from, to;
      char cmd;
      std::string str;
      while (in && !done)
	{
	  in >> cmd;
	  switch(cmd)
	    {
	    case 's': // Definition of a state
	      from = to;
	      in >> to;
	      l.add_state(to);
	      break;
	    case 'i': // The previous state is an initial one
	      get_delimited_exp(in, str);
	      l.set_initial(to, str);
	      break;
	    case 'f': // The previous state is a final one
	      get_delimited_exp(in, str);
	      l.set_final(to, str);
	      break;
	    case 'l': // The label of transition between the 2 previous states
	      get_delimited_exp(in, str);
	      l.add_edge(from, to, str);
	      break;
	    case 'S': // A spontaneous transions between the 2 previous states
	      l.add_spontaneous(from, to);
	      break;
	    case '.':
	      done = true;
	      break;
	    case '#': // The start of a comment
	      std::getline(in, str);
	      break;
	    default: // Ignore other caracters
	      break;
	    }
	}
    }
  }
}

#endif // ! VCSN_TOOLS_SIMPLE_FORMAT_HXX
