// get_structcomp_sample.hxx
//
// MICAL_HEADER

#ifndef   GET_STRUCTCOMP_SAMPLE_HXX_
# define   GET_STRUCTCOMP_SAMPLE_HXX_

#include <vaucanson/algebra/concrete/free_monoid/predefs.hh>

#include <algorithm>
#include <set>
#include <utility>

namespace mical { 

  using namespace vcsn;
  using namespace vcsn::algebra::char_letter;
  using std::set;
  using std::pair;

  typedef set<hedge_t> delta_edge_t;

  template<typename A, typename T, typename W>
  void
  get_structcomp_sample(const Element<A, T>& a, 
			W str,
			hstate_t current,
			pair<set<hedge_t>, set<hstate_t> >& used,
			set<W>& sample)
  {
    using std::find; 


    
    delta_edge_t tmp, delta_edge;
    
    a.deltac(tmp, current, delta_kind::edges());

    if (find(used.second.begin(), used.second.end(), current) != used.second.end())
      {
	set_difference(tmp.begin(), tmp.end(),
		       used.first.begin(), used.first.end(),
		       inserter(delta_edge, delta_edge.begin()));
	if (!delta_edge.size())
	  {
	    unsigned size = sample.size();

	    sample.insert(str);
	    
	    if (size == sample.size())
	      {
		for (set<Word>::iterator i = sample.begin(); 
		     i != sample.end(); i++)
		  std::cout << "SAMPLE " << *i << std::endl;

		std::cout << "POUET " << str << std::endl;
		a.deltac(delta_edge, current, delta_kind::edges());
	      }
	  }
      }
    else
      {
	if (find(a.final().begin(), a.final().end(), current)
	    != a.final().end())
	  {
	    std::cout << "AJOUT !! " << current << " " << str << std::endl;
	    sample.insert(str);
	    used.second.insert(current);
	  }	
	delta_edge = tmp; 
      }	    
    
    for (delta_edge_t::iterator i = delta_edge.begin(); 
	 i != delta_edge.end(); i++)
      {
	used.first.insert(*i);
	
	Word svg = str;
	str = str * a.label_of(*i).begin()->first;
	
	std::cout << "ACTUAL " << a.label_of(*i).begin()->first << " " 
		  << str << " " << current << " " <<  a.aim_of(*i) << std::endl;
	
	get_structcomp_sample(a, str, a.aim_of(*i), used, sample);
	
	str = svg;
      }
  }

} // mical


#endif /* !GET_STRUCTCOMP_SAMPLE_HXX_ */

