#ifndef DOT_FORMAT_HXX
# define DOT_FORMAT_HXX

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
		  << " [label=\"" << a.get_initial(*i) << "\"];" << std::endl;
	      ++count;
	    }
	  if (a.is_final(*i))
	    {
	      out << name_ << count 
		  << " [style=invis,label=\"\",width=.01,height=.01];" << std::endl 
		  << name_ << c << " -> "  << name_ << count 
		  << " [label=\""<< a.get_final(*i) <<"\"];" << std::endl;
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
	  out << "[label=\"" << conv(a, a.serie_of(*i)) << "\"];" << std::endl;
	}
      out << "}" << std::endl;
    }
  }
}


#endif
