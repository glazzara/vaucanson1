// isomorph.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_ISOMORPH_HXX
# define VCSN_ALGORITHMS_ISOMORPH_HXX

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/misc/selectors.hh>

# include <vaucanson/tools/usual.hh>
# include <queue>
# include <set>
# include <list>
# include <utility>

namespace vcsn {


  /*---------.
  | isomorph |
  `---------*/
  
  using std::queue;
  using std::set;
  using std::pair;
  using std::list;
  
  typedef set<list<pair<hstate_t, hstate_t> > > possibility_t;
  typedef list<pair<hstate_t, hstate_t> > sub_possibility_t;


  template<typename A, typename T>
  bool 
  compatible_state(const Element<A, T>& a, const Element<A, T>& b,
		   const sub_possibility_t& l, 
		   const pair<hstate_t, hstate_t> & elt)
  {
    set<hstate_t> out_a;
    set<hstate_t> out_b;
    
    a.deltac(out_a, elt.first, delta_kind::states());
    b.deltac(out_b, elt.second, delta_kind::states());
    
    if ((out_a.size() != out_b.size()) 
	|| (!arrangement(l, out_a, out_b)))
      return false;
    return true;
  }


  bool can_add_pair(const sub_possibility_t& l,
		    const pair<hstate_t, hstate_t>& val)
  {
    for (sub_possibility_t::const_iterator i = l.begin(); i != l.end(); i++)
      if ((i->first == val.first) 
	  || (i->second == val.second))
	  return false;
    return true;
  }

  template<typename A, typename T>
  bool
  create_possibility(const Element<A, T>& a, const Element<A, T>& b,
		     const possibility_t& mother,
		     possibility_t::iterator i, 
		     sub_possibility_t sub_res)
  {
   if (i != mother.end())
     for (sub_possibility_t::const_iterator j = i->begin();
	  j != i->end(); j++)
       {
	 if (can_add_pair(sub_res, *j))
	   {
	     sub_res.push_back(*j);
	     bool res = create_possibility(a, b, mother, ++i, sub_res);
	     if (res) return true;
	     --i;
	     sub_res.pop_back();
	   }
       }
   else
     {
       bool cond = true;
       sub_possibility_t::const_iterator j = sub_res.begin(); 
       while ((j != sub_res.end()) && cond)
	 {
	   cond = compatible_state(a, b, sub_res, *j);
	   j++;
	 }
       if (cond) 
	 {
// 	   for (sub_possibility_t::const_iterator j = sub_res.begin(); 
// 		j != sub_res.end(); j++)
// 	     {
// 	       std::cout << "RESULT " << j->first << " " << j->second << " " ;
// 	     }
	   return true;
	 }
     }
   return false;
  }
  

  bool exists(const sub_possibility_t& l, const pair<hstate_t, hstate_t>& p)
  {
    for (sub_possibility_t::const_iterator i = l.begin(); i != l.end(); i++)
      if (*i == p) return true;
    return false;
  }

  bool arrangement(const sub_possibility_t& mother, 
		   set<hstate_t>& out_a,
		   set<hstate_t>& out_b)
  {
    if (out_a.size() == 0)
      return true;
    if (out_a.size() == 1)
      {
	if (exists(mother, 
		   pair<hstate_t, hstate_t>(*out_a.begin(), *out_b.begin()))
	    )
	  return true;
	return false;
      }
    else
      {
	bool res = false;
	for (set<hstate_t>::iterator i = out_a.begin(); 
	     i != out_a.end(); i++)
	  for (set<hstate_t>::iterator j = out_b.begin(); 
	       j != out_b.end(); j++)
	    {
	      if (exists(mother, pair<hstate_t, hstate_t>(*i, *j)))
		{
		  out_a.erase(*i);
		  out_b.erase(*j);
		  res = res || arrangement(mother, out_a, out_b);
		  out_a.insert(*i);
		  out_b.insert(*j);
		}
	    }
	return res;
      }
  }



  template<typename A, typename T>
  bool
  is_isomorph(const Element<A, T>& a, const Element<A, T>& b)
  {
    using namespace vcsn::tools;
    using std::queue;
    using std::set;
    using std::pair;
    using std::list;

    typedef Element<A, T> automaton_t;
   
    AUTOMATON_TYPES(automaton_t);        

    if ((a.states().size() != b.states().size())
	|| (a.edges().size() != b.edges().size())
	|| (a.initial().size() != b.initial().size())
	|| (a.final().size() != b.final().size())
	|| (a.initial().size() == 0))
      return false;
    
    // we can start with good suppositions

     possibility_t possibility;

     for (state_iterator i = a.states().begin(); 
	  i != a.states().end(); i++)
       {
	 bool bool_state = false;
	 sub_possibility_t sub_possibility;
	 for (state_iterator j = b.states().begin(); 
	      j != b.states().end(); j++)
	   {
	     set<hedge_t> out_a;
	     set<hedge_t> out_b;
	    
	     a.deltac(out_a, *i, delta_kind::edges());
	     b.deltac(out_b, *j, delta_kind::edges());
	    
	     bool bool_edge = true;
	     for (set<hedge_t>::iterator x = out_a.begin(); 
		  x != out_a.end(); x++)
	       {
		 set<hedge_t>::iterator y = out_b.begin();
		 while ((y != out_b.end()) && (a.serie_of(*x) != b.serie_of(*y)))
		   y++;
		 if (y == out_b.end()) 
		   bool_edge = false;
	       }
	     if (out_a.size() != out_b.size())
	       bool_edge = false;

	     bool_state = bool_state || bool_edge;
	     if ((bool_edge) && 
		 ((a.is_initial(*i) && b.is_initial(*j))
		  || (a.is_final(*i) && b.is_final(*j))
		  || ((!a.is_final(*i) && !a.is_initial(*i)) 
		      && (!b.is_final(*j) && !b.is_initial(*j)))
		  )
		 )
	       sub_possibility.push_back(pair<hstate_t, hstate_t>(*i, *j));
	   }
	 if (!bool_state)
	   return false;
	 possibility.insert(sub_possibility);
       }
     
      return create_possibility(a, b, possibility, possibility.begin(), 
				sub_possibility_t());
  }


  

  

} // vcsn


#endif // VCSN_ALGORITHMS_ISOMORPH_HXX
