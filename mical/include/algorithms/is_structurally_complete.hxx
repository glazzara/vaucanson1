
#ifndef   IS_STRUCTURALLY_COMPLETE_HXX_
# define   IS_STRUCTURALLY_COMPLETE_HXX_

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <utility>

#include <vaucanson/algebra/concrete/free_monoid/predefs.hh>
#include <vaucanson/algorithms/trim.hh>

#include <assert.h>

using namespace vcsn;

namespace mical {

  using std::set;
  using std::vector;
  using std::pair;

  // A METTRE DANS LES TYPES BUILTINS !
  typedef set<hedge_t> delta_edge_t;
  typedef set<hstate_t> delta_state_t;
  typedef pair<delta_edge_t, hstate_t> used_t;
  typedef set<used_t> acceptation_t;
  typedef set<acceptation_t> set_acceptation_t;
  typedef vector<acceptation_t> i_familly_t;

  template<typename A, typename T, typename W>
  bool
  is_structurally_complete(const Element<A, T>& a, 
			   set<W> sample)
  {
    // ELAGUAGE !!
    Element<A, T> work = trim(a);
    work.emancipate();
    
    return it_exists_acceptation(work, get_indexed_familly(work, sample));
  }
  
  
  template<typename A, typename T>
  bool
  it_exists_acceptation(const Element<A, T>& a,
			const i_familly_t& i_familly)
  {
    unsigned height = 0;
    acceptation_t acceptation;
    bool res = false;

    it_exists_acceptation_(a, i_familly, height, acceptation, res);
    
    return res;
  }

  template<typename A, typename T>
  void
  it_exists_acceptation_(const Element<A, T>& a,
			 const i_familly_t& i_familly,
			 unsigned height,
			 acceptation_t acceptation,
			 bool& res)
  {
    if (height >= i_familly.size())
      {
	delta_state_t tmp;
	delta_edge_t tmp_edge;
	
	for (typename acceptation_t::iterator i = acceptation.begin();
	     i != acceptation.end(); i++)
	  {
	    tmp.insert(i->second);
	    set_union(tmp_edge.begin(), tmp_edge.end(),
		      i->first.begin(), i->first.end(),
		      inserter(tmp_edge, tmp_edge.begin()));
	  }
// 	for (typename delta_state_t::iterator i = tmp.begin(); i != tmp.end(); i++)
// 	  std::cout << *i << " ";
// 	std::cout << "    " << tmp_edge.size() << std::endl;

	if ((tmp_edge.size() == a.edges().size()) 
	    && (tmp.size() == a.final().size()))
	  {
	    res = true;
	    acceptation.clear();
	    return;
	  }
      }
    else
      for (typename acceptation_t::iterator i = 
	     i_familly[height].begin();
	   i != i_familly[height].end(); i++)
	{
	  acceptation.insert(*i);
	  
	  it_exists_acceptation_(a, i_familly, height + 1, 
				   acceptation, res);
	  
	  if (res) return;

	  acceptation.erase(*i);
	}
  }  

  // return an indexed familly of all acceptations for all words
  template<typename A, typename T, typename W>
  i_familly_t
  get_indexed_familly(const Element<A, T>& a, 
		      set<W> sample)
  {
    typedef Element<A,T> auto_t;
    typedef typename std::set<W> samples_t;

    acceptation_t acceptation;
    i_familly_t i_familly;

    for (typename samples_t::iterator i = sample.begin();
	 i != sample.end(); ++i)
      {
	acceptation.clear();

	for (typename auto_t::initial_iterator j = a.initial().begin();
	     j != a.initial().end(); ++j)
	  {
	    used_t used;
	    depth_compute(a, i->begin(), *j, acceptation, used);
	  }

	if (acceptation.size() != 0)
	  i_familly.push_back(acceptation);
      }
    return i_familly;
  }

  // get all used edges possible for an acceptation of one word
  template<typename A, typename T, typename W_iterator>
  void
  depth_compute(const Element<A, T>& a,
		W_iterator pos,
		hstate_t current,
		acceptation_t& set_accept,
		used_t& accept)
   {
    using std::find;    
    
    if (*pos == 0)
      {
	if (find(a.final().begin(), a.final().end(), current)
	    != a.final().end())
	  {
	    accept.second = current;
	    set_accept.insert(accept);

	    // std::cout << "FINAL STATES " << current << std::endl;
	  }
      }
    else
      {
	delta_edge_t delta_edge;
	
	a.letter_deltac(delta_edge, current, *pos, delta_kind::edges());
	for (delta_edge_t::iterator i = delta_edge.begin(); 
	     i != delta_edge.end(); i++)
	  {
	    // std::cout << a.origin_of(*i) << " " << a.aim_of(*i)  << std::endl;
	    
	    accept.first.insert(*i);
	    depth_compute(a, ++pos, a.aim_of(*i), set_accept, accept);
	    pos--;

	    // std::cout << "POP" << std::endl;

	    accept.first.erase(*i);
	  }
      }
  }
  
  
} // vcsn


#endif /* !IS_STRUCTURALLY_COMPLETE_HXX_ */
