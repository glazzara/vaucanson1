// dot_dump.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef MISC_DOT_DUMP_HH
# define MISC_DOT_DUMP_HH

#include <map>

#include <vaucanson/automata/concept/handlers.hh>

namespace vcsn {
  
  namespace misc {

    /*---------.
    | dot_dump |
    `---------*/
    // Description :
    //   - Basic and non configurable pretty-printer in the 'dot' format
    //
    // Constraints :
    //   - Every elements (series, state_content ...) must be printable
    //
    template <typename St, typename auto_t, typename name_t>
    void dot_dump_do_graph(St& out, const auto_t& a, const name_t& name)
    {
      unsigned			count = 0;
      std::map<hstate_t, int>	state_map;

      out << "node [shape=circle];\n";
      for (typename auto_t::state_iterator i = a.states().begin();
	   i != a.states().end();
	   ++i)
	{
	  state_map[*i] = count;
	  int c = count++;
	  if (a.is_initial(*i))
	    {
	      out << name << count 
		  << " [style=invis,label=\"\",width=.01,height=.01];\n"
		  << name << count 
		  << " -> " << name << c 
		  << " [label=\"" << a.get_initial(*i) << "\"];\n";
	      ++count;
	    }
	  if (a.is_final(*i))
	    {
	      out << name << count 
		  << " [style=invis,label=\"\",width=.01,height=.01];\n" 
		  << name << c 
		  << " -> " 
		  << name << count 
		  << " [label=\""<< a.get_final(*i) <<"\"];\n";
	      ++count;
	    }
	  out << name << c
	      << " [label=\"" << *i << "\"];\n";
	}
      for (typename auto_t::edge_iterator i = a.edges().begin();
	   i != a.edges().end();
	   ++i)
	{
	  out << name << state_map[i.origin()] 
	      << " -> " 
	      << name << state_map[i.aim()]
	      << " [";

	  // fixme: read as series instead
	  out << "label=\"" << a.serie_of(*i) << "\"";

	  out << "];\n";
	}
    }

    template<typename St, typename auto_t, typename name_t>
    void dot_dump(St& o, const auto_t& a, const name_t& name)
    {
      o << "digraph vcsn {\n"
	<< "label=\"" << name << ' ' << a << "\";\n";
      dot_dump_do_graph(o, a, name);
      o << "}" << std::endl;
    }

//     template <class Self_>
//     void dot_in_out_dump(std::ostream& o, 
// 			 const Automaton<Self_>&in, const Automaton<Self_>& out,
// 			 const std::string& name)
//     {
//       o << "digraph vcsn {" << std::endl
// 	<< "ratio=fill; size=\"8,6\";"
// 	<< "subgraph clusterinput {"
// 	<< "ratio=fill;"
// 	<< "color=black; label=\"Input\";";
//       dot_graph_dump(o, in.canonical_view(), "in");
//       o << "InputNode [style=invis,label=\"\",width=.01,height=.01];"
// 	<< "} subgraph clusteroutput {"
// 	<< "ratio=fill;"
// 	<< "color=black; label=\"Output\";"; 
//       dot_graph_dump(o, out.canonical_view(), "out");
//       o << "OutputNode [style=invis,label=\"\",width=.01,height=.01];"
//       // FIXME : a line between the two ?
// 	<< "} " 
// 	<< "InputNode -> OutputNode [label=\"" << name << "\"];" 
// 	<< "}" << std::endl;
//     }

//     template <class Self_, class InAutomaton_>
//     void dot_in_list_out_dump(std::ostream& o, 
// 			      const std::list<InAutomaton_*>& in_list, 
// 			      const Automaton<Self_>& out,
// 			      const std::string& name)
//     {
//       int count = 0;

//       o << "digraph vcsn {" << std::endl
// 	<< "ratio=fill; size=\"8,6\";";
//       for (typename std::list<InAutomaton_*>::const_iterator in = in_list.begin();
// 	   in != in_list.end();
// 	   ++in)
// 	{
// 	  ++count;	  
// 	  o << "subgraph clusterinput" << count << " {"
// 	    << "ratio=fill;"
// 	    << "color=black; label=\"Input" << count << "\";" ;
// 	  std::stringstream str;
// 	  str << "in" << count << std::ends;
// 	  dot_graph_dump(o, (*in)->canonical_view(), str.str());
// 	  o << std::endl
// 	    << "InputNode" << count
// 	    << "[style=invis,label=\"\",width=.01,height=.01];" << std::endl;
// 	  o << "}" << std::endl;
// 	  if (count != 1)
// 	    o << "InputNode" << (count-1) << " -> " << "InputNode" << count << std::endl;
// 	}
//       o << "subgraph clusteroutput {"
// 	<< "ratio=fill;"
// 	<< "color=black; label=\"Output\";"; 
//       dot_graph_dump(o, out.canonical_view(), "out");
//       o << "OutputNode [style=invis,label=\"\",width=.01,height=.01];"
// 	<< "} " 
// 	<< "InputNode" << count 
// 	<< " -> OutputNode [label=\"" << name << "\"];" 
// 	<< "}" << std::endl;
//     }
	 
  } // misc
  
} // vcsn

#endif // MISC_DOT_DUMP_HH
