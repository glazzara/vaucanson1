// fsm_dump.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef MISC_FSM_DUMP_HH
# define MISC_FSM_DUMP_HH

# include <map>
# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/tools/usual.hh>

namespace vcsn {
  
  namespace misc {

    /*---------.
    | fsm_dump |
    `---------*/
    // Description :
    //   - Basic and non configurable pretty-printer in the 'fsm' format
    //   
    // Constraints :
    //   - Every elements (series, state_content ...) must be printable
    //
    template <typename St, typename auto_t>
    void fsm_dump(St& out, const auto_t& a)
    {
      AUTOMATON_TYPES(auto_t);
      if (a.initial().size() > 1)
	{
	  auto_t b(a);
	  hstate_t i = b.add_state();
	  for (initial_iterator j = b.initial().begin(); 
	       j != b.initial().end(); ++j)
	    b.add_spontaneous(i, *j);
	  b.clear_initial();
	  b.set_initial(i);
	  fsm_dump(out, b);
	  return ;
	}
      if (a.states().size() == 0)
	return;

      typename auto_t::initial_iterator initial = a.initial().begin();
      std::set<hedge_t> succ;

      a.deltac(succ, *initial, delta_kind::edges());
      for (typename std::set<hedge_t>::const_iterator e = succ.begin();
	   e != succ.end();
	   ++e)
	  out << *initial << "\t" << a.aim_of(*e) << "\t" 
	      << a.serie_of(*e) << "\t 0" 
	      << std::endl;
      for (typename auto_t::state_iterator s = a.states().begin();
	   s != a.states().end();
	   ++s)
	if (!a.is_initial(*s))
	{
	  succ.clear();
	  a.deltac(succ, *s, delta_kind::edges());
	  for (typename std::set<hedge_t>::const_iterator e = succ.begin();
	       e != succ.end();
	       ++e)
	    out << *s << "\t" << a.aim_of(*e) << "\t" 
		<< a.serie_of(*e) << "\t 0" 
	       << std::endl;
	}
      for (typename auto_t::final_iterator f = a.final().begin();
	   f != a.final().end(); ++f)
	out << *f << "\t 0" << std::endl;
      SAVE_AUTOMATON_DOT("/tmp/","fsm_out", a, 0); 
    }
	 
    /*---------.
    | fsm_load |
    `---------*/
    enum data_e 
      {
	final,
	edge
      };

    struct line_data 
      {
	data_e	     type;
	unsigned int from;
	unsigned int to;
	char	     letter;
	float	     weight;
      };

    std::pair<std::string, std::string>
    next_token(std::string line)
    {
      std::string token;
      std::string::iterator i = line.begin();
      while ((i != line.end()) && ((*i == '\t') 
				   || (*i == ' ') || (*i == '\0')))
	++i;
      for (;i != line.end();++i)
	{
	  if ((*i == '\t') || (*i == ' ') 
	      || (*i == '\n') || (*i == '\0'))
	    break;
	  else
	    token.push_back(*i);
	}
      if (i != line.end())
	{
	  ++i;
	  return std::make_pair(token, 
				std::string(line, 
					    (unsigned)(i - line.begin()), 
					    (unsigned)(line.end() - i + 1)));
	}
      else
	return std::make_pair(token, std::string());
    }

    template <typename St, typename AutoType_>
    void fsm_load(St& in, AutoType_& a)
    {
      AUTOMATON_TYPES(AutoType_);

      // read everything and build the alphabet.
      alphabet_t		alpha;
      unsigned			nb = 0;
      std::vector<line_data>	stock;
      std::string		line;
      std::pair<std::string,    std::string> tmp;
      std::vector<std::string>	tokens;

      while (!in.eof())
	{
	  tokens.clear();
	  ++nb;
	  stock.resize(nb);
	  getline(in, line);
	  while (true)
	    { 
	      tmp = next_token(line);
	      line = tmp.second;
	      tokens.push_back(tmp.first);
	      if (line.length() == 0)
		break;
	    }
	  if (tokens.size() == 1)
	    {
	      stock[nb-1].type = final;
	      stock[nb-1].from = atoi(tokens[0].c_str());
	      stock[nb-1].weight = 0.;
	    }
	  else if (tokens.size() == 2)
	    {
	      stock[nb-1].type = final;
	      stock[nb-1].from = atoi(tokens[0].c_str());
	      stock[nb-1].weight = atof(tokens[1].c_str());
	    }
	  else if (tokens.size() == 4)
	    {
	      stock[nb-1].type   = edge;
	      stock[nb-1].from   = atoi(tokens[0].c_str());
	      stock[nb-1].to     = atoi(tokens[1].c_str());
	      stock[nb-1].letter = tokens[2][0];
	      stock[nb-1].weight = atof(tokens[3].c_str());
	      alpha.insert(stock[nb-1].letter);
	    }
	}
      // construct the automaton.
      monoid_t	  monoid(alpha);
      weights_t   semiring;
      series_t	  series(semiring, monoid);
      automaton_t automaton;
      automaton.create();
      automaton.series() = series;
      std::map<int, hstate_t> to_h;

      for (typename std::vector<line_data>::const_iterator i = stock.begin();
	   i != stock.end(); ++i)
	{
	  if (i->type == edge)
	    {
	      if (to_h.find(i->from) == to_h.end())
		to_h[i->from] = automaton.add_state();
	      if (to_h.find(i->to) == to_h.end())
		to_h[i->to] = automaton.add_state();
	      if (i == stock.begin())
		automaton.set_initial(to_h[i->from]);
	      automaton.add_letter_edge(to_h[i->from], 
					to_h[i->to], 
					i->letter);
	    }
	  else if (i->type == final)
	    {
	      if (to_h.find(i->from) == to_h.end())
		to_h[i->from] = automaton.add_state();
	      automaton.set_final(to_h[i->from]);
	    }
	}
      a = automaton;
      std::cerr << a.states().size() << std::endl;
      std::cerr << to_h.size() << std::endl;
      SAVE_AUTOMATON_DOT("/tmp/","fsm_in", a, 0); 
    }

  } // misc 
  
} // vcsn

#endif // MISC_FSM_DUMP_HH
