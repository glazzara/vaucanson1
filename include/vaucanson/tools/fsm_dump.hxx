// fsm_dump.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2004 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef TOOLS_FSM_DUMP_HXX
# define TOOLS_FSM_DUMP_HXX

# include <vaucanson/tools/fsm_dump.hh>
# include <map>
# include <set>
# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {
  
  namespace tools {

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
	  for_each_initial_state(j, b)
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
      for_all_const_(std::set<hedge_t>, e, succ)
	out << *initial << "\t" << a.aim_of(*e) << "\t" 
	    << a.series_of(*e) << "\t 0" 
	    << std::endl;
      for_each_state(s, a)
	if (!a.is_initial(*s))
	{
	  succ.clear();
	  a.deltac(succ, *s, delta_kind::edges());
	  for_all_const_(std::set<hedge_t>, e, succ)
	    out << *s << "\t" << a.aim_of(*e) << "\t" 
		<< a.series_of(*e) << "\t 0" 
		<< std::endl;
	}
      for_each_final_state(f, a)
	out << *f << "\t 0" << std::endl;
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
	      if (tmp.first.length() != 0)
		tokens.push_back(tmp.first);
	      if (line.length() == 0)
		break;
	    }
	  if (tokens.size() == 0)
	    {
	      nb--;
	      stock.resize(nb);
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
      semiring_t   semiring;
      series_set_t	  series(semiring, monoid);
      automata_set_t astructure(series);
      automaton_t automaton(aset);
      std::map<int, hstate_t> to_h;

      for_all_const_(std::vector<line_data>, i, stock)
	{
	  if (i->type == edge)
	    {
	      if (to_h.find(i->from) == to_h.end())
		to_h[i->from] = automaton.add_state();
	      if (to_h.find(i->to) == to_h.end())
		to_h[i->to] = automaton.add_state();
	      if (i == stock.begin())
		automaton.set_initial(to_h[i->from]);
	      // FIXME: please be generic w.r.t spontaneous transition.
	      if (i->letter == '1')
		automaton.add_spontaneous(to_h[i->from],
					  to_h[i->to]);
	      else
		automaton.add_letter_edge(to_h[i->from], 
					  to_h[i->to], 
					  letter_t(i->letter));
	    }
	  else if (i->type == final)
	    {
	      if (to_h.find(i->from) == to_h.end())
		to_h[i->from] = automaton.add_state();
	      automaton.set_final(to_h[i->from]);
	    }
	}
      a = automaton;
    }

  } // tools 
  
} // vcsn

#endif // TOOLS_FSM_DUMP_HH
