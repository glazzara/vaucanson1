// simple_format.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TOOLS_SIMPLE_FORMAT_HXX
# define VCSN_TOOLS_SIMPLE_FORMAT_HXX

# include <vaucanson/tools/simple_format.hh>
# include <string>

namespace vcsn
{
  namespace tools
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
      for (typename auto_t::transition_iterator i = a.transitions().begin();
	   i != a.transitions().end();
	   ++i)
      {
	o << 's' << a.src_of(*i) << ' '
	  << 's' << a.dst_of(*i) << ' ';
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
	    l.add_transition(from, to, str);
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
