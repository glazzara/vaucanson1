#ifndef SIMPLE_FORMAT_HXX
# define SIMPLE_FORMAT_HXX

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

      for (typename auto_t::state_iterator i = a.states().begin();
	   i != a.states().end();
	   ++i, ++count)
	{
	  o << 's' << *i << ' ';
	  if (a.is_initial(*i))
	    o << 'i' << conv(a, a.get_initial(*i)) << std::endl; 
	  if (a.is_final(*i))
	    o << 'f' << conv(a, a.get_final(*i)) << std::endl;
	  if (!(count % 8))
	    o << std::endl;
	}
      for (typename auto_t::edge_iterator i = a.edges().begin();
	   i != a.edges().end();
	   ++i)
	{
	  o << 's' << a.origin_of(*i) << ' '
	    << 's' << a.aim_of(*i) << ' ';
	  if (a.is_spontaneous(*i))
	    o << 'S';
	  else
	    o << 'l' << conv(a, a.serie_of(*i)) << std::endl;
	}
      o << '.' << std::endl;
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
	    case 's':
	      from = to;
	      in >> to;
	      l.add_state(to);
	      break;
	    case 'i':
	      std::getline(in, str);
	      l.set_initial(to, str);
	      break;
	    case 'f':
	      std::getline(in, str);
	      l.set_final(to, str);
	      break;
	    case 'l':
	      std::getline(in, str);
	      l.add_edge(from, to, str);
	      break;
	    case 'S':
	      l.add_spontaneous(from, to);
	      break;
	    case '.':
	      done = true;
	      break;
	    default: // skip until EOL or EOF
	      std::getline(in, str);
	      break;
	    }
	}
    }
  }
}

#endif
