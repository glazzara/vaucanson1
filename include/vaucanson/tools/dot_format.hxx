// dot_format.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_TOOLS_DOT_FORMAT_HXX
# define VCSN_TOOLS_DOT_FORMAT_HXX

# include <sstream>
# include <map>

# include <vaucanson/misc/escaper.hh>
# include <vaucanson/tools/dot_format.hh>
# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn
{
  namespace io
  {
    inline dot::dot(const std::string& name)
    {
      std::ostringstream os;
      std::set<char> to_escape;
      to_escape.insert('"');
      (utility::setesc(to_escape))(os) << utility::escaper<std::string>(name);
      name_ = std::string("\"") + os.str();
    }

    template<typename Saver, typename Conv>
    void dot::operator()(std::ostream& out, const Saver& s,
			 const Conv& conv) const
    {
      typedef typename Saver::automaton_t auto_t;
      const auto_t& a = s.automaton();
      unsigned count = 0;
      std::map<hstate_t, unsigned> state_map;

      out << "digraph vcsn {" << std::endl
	  << "label=\"" << name_.c_str() + 1 << ' ' << a << "\";" << std::endl
	  << "node [shape=circle];" << std::endl;

      for (typename auto_t::state_iterator i = a.states().begin();
	   i != a.states().end();
	   ++i)
	{
	  unsigned c = state_map[*i] = count++;
	  if (a.is_initial(*i))
	    {
	      out << name_ << count
		  << "\" [style=invis,label=\"\",width=.01,height=.01];"
		  << std::endl
		  << name_ << count << "\" -> " << name_ << c
		  << "\" [label=\"" << conv(a.structure(), a.get_initial(*i))
		  << "\"];" << std::endl;
	      ++count;
	    }
	  if (a.is_final(*i))
	    {
	      out << name_ << count
		  << "\" [style=invis,label=\"\",width=.01,height=.01];"
		  << std::endl
		  << name_ << c << "\" -> "  << name_ << count
		  << "\" [label=\""<< conv(a.structure(), a.get_final(*i))
		  <<"\"];" << std::endl;
	      ++count;
	    }
	  out << name_ << c << "\" [label=\"" << *i << "\"];" << std::endl;
	}
      for (typename auto_t::edge_iterator i = a.edges().begin();
	   i != a.edges().end();
	   ++i)
	{
	  out << name_ << state_map[a.origin_of(*i)]
	      << "\" -> "
	      << name_ << state_map[a.aim_of(*i)];
	  out << "\" [label=\"" << conv(a.structure(), a.series_of(*i))
	      << "\"];" << std::endl;
	}
      out << "}" << std::endl;
    }

    inline transducer_dot::transducer_dot(const std::string& name)
    {
      std::ostringstream os;
      std::set<char> to_escape;
      to_escape.insert('"');
      (utility::setesc(to_escape))(os) << utility::escaper<std::string>(name);
      name_ = std::string("\"") + os.str();
    }

    template<typename Saver, typename Conv>
    void transducer_dot::operator()(std::ostream& out, const Saver& s,
				    const Conv& conv) const
    {
      typedef typename Saver::automaton_t auto_t;
      AUTOMATON_TYPES(auto_t);
      const auto_t& a = s.automaton();
      unsigned count = 0;
      std::map<hstate_t, unsigned> state_map;

      out << "digraph vcsn {" << std::endl
	  << "label=\"" << name_.c_str() + 1 << ' ' << a << "\";" << std::endl
	  << "node [shape=circle];" << std::endl;

      for (typename auto_t::state_iterator i = a.states().begin();
	   i != a.states().end();
	   ++i)
	{
	  unsigned c = state_map[*i] = count++;
	  if (a.is_initial(*i))
	    {
	      out << name_ << count
		  << "\" [style=invis,label=\"\",width=.01,height=.01];"
		  << std::endl
		  << name_ << count << "\" -> " << name_ << c << '"';
	      std::ostringstream o;
	      series_set_elt_t ss = a.get_initial(*i);
	      for_each_const_(series_set_elt_t::support_t, s, ss.supp())
		o << conv(a.structure(), *s) << "|"
		  << ss.get(monoid_elt_t (a.structure().series().monoid(), *s))
		  << " ";
	      out << "[label=\"" << o.str() << "\"];"
		  << std::endl;
	      ++count;
	    }
	  if (a.is_final(*i))
	    {
	      out << name_ << count
		  << "\" [style=invis,label=\"\",width=.01,height=.01];"
		  << std::endl
		  << name_ << c << "\" -> " << name_ << count << '"';
	      std::ostringstream o;
	      series_set_elt_t ss = a.get_final(*i);
	      for_each_const_(series_set_elt_t::support_t, s, ss.supp())
		o << conv(a.structure(), *s) << "|"
		  << ss.get(monoid_elt_t (a.structure().series().monoid(), *s))
		  << " ";
	      out << "[label=\"" << o.str() << "\"];"
		  << std::endl;
	      ++count;
	    }
	  out << name_ << c << "\" [label=\"" << *i << "\"];" << std::endl;
	}
      for (typename auto_t::edge_iterator i = a.edges().begin();
	   i != a.edges().end();
	   ++i)
	{
	  out << name_ << state_map[a.origin_of(*i)]
	      << "\" -> "
	      << name_ << state_map[a.aim_of(*i)] << '"';
	  std::ostringstream o;
	  series_set_elt_t ss = a.series_of(*i);
	  for_each_const_(series_set_elt_t::support_t, s, ss.supp())
	    o << conv(a.structure(), *s) << "|"
	      << ss.get(monoid_elt_t (a.structure().series().monoid(), *s))
	      << " ";
	  out << "[label=\"" << o.str() << "\"];"
	      << std::endl;
	}
      out << "}" << std::endl;
    }

  } // tools
} // vcsn

#endif // ! VCSN_TOOLS_DOT_FORMAT_HXX
