
#ifndef RIG_HH_
#define RIG_HH_

#include <stack>
#include <vector>
#include <algorithm>
#include <utility>

#include <vaucanson/fundamental/element.hh>
#include <vaucanson/automata/concept/automata_base.hh>

#include <algorithms/fusion.hh>

namespace gi {
  
  using namespace vcsn;
  using namespace mical;

  template<typename A, typename T, typename W>
  struct FactoryBorderSet 
  {
    typedef Element<A,T> automaton_t;

    typedef struct container
    {
      container(automaton_t first_,
		std::pair<hstate_t, hstate_t> second_,
		bool is_elt_of_bs_)
	: first(first_), second(second_), is_elt_of_bs(is_elt_of_bs_) {}

      automaton_t first;
      std::pair<hstate_t, hstate_t> second;
      bool is_elt_of_bs;
    } container_t;

    typedef std::stack<container_t>  stack_t;


    FactoryBorderSet(const automaton_t& a, const std::set<W>& negative_sample)
      : negative_sample_(negative_sample)
    {
      pstack.push(container_t(a, get_first_states(a), true));
    }
    
    void clear()
    {
      container_t tmp = pstack.back();
      pstack.clear();
      pstack.push(tmp);
    }
    
    unsigned depth()
    {
      return pstack.size();
    }

    automaton_t next()
    {
      // next
    }

    automaton_t course_depth()
    {
      using std::cout;
      using std::endl;
      
      automaton_t svg;
      svg.create();

      if (pstack.size() && (pstack.top().first.states().size() != 1))
	{
	  container_t act = pstack.top();
	  automaton_t tmp_auto, param;
	  bool last = false;

	  while (!last)
	    {
	      tmp_auto = act.first;
	      tmp_auto.emancipate();
	      get_son(act.first, act.second, last);

	      cout << last << " " << act.second.first << " " <<  act.second.second << endl;
	      cout << "BEFORE  NB_EDGES " << tmp_auto.edges().size() 
		   << " NB_STATES " << tmp_auto.states().size() << endl;
	      fusion(tmp_auto, act.second.first, act.second.second);
	      cout << "AFTER   NB_EDGES " << tmp_auto.edges().size() 
		   << " NB_STATES " << tmp_auto.states().size() << endl;
	      
	      if (!last)
		if (is_not_compatible(tmp_auto, negative_sample_))
		  {
		    cout << " ===========================> IS_NOT_COMPATIBLE (PUSH)" << endl;
		    pstack.top().second = act.second;
		    act.is_elt_of_bs = false;
		    pstack.top().is_elt_of_bs = false;
		    param = tmp_auto;
		    param.emancipate();
		    
		    pstack.push(container_t(param, get_first_states(param), true));
		    return course_depth();
		  }
	    }
	  pstack.pop();	   
	  
	  cout << "----------------------------> POP" << endl;
	  if (act.is_elt_of_bs)
	    {
	      cout << " WINNER !! " << endl;
	      return act.first;
	    }
	  return course_depth();
	}
      if (pstack.size())
	return pstack.top().first;
      return svg;
    }

  private:

    stack_t pstack;
    std::set<W> negative_sample_;

    std::pair<hstate_t, hstate_t> get_first_states(const automaton_t& a)
    {
      using std::sort;
      using std::copy;

      if (!a.states().size() || (a.states().size() == 1))
	return std::pair<hstate_t, hstate_t>();

      hstate_t vect[a.states().size()];
 
      copy(a.states().begin(), a.states().end(),
	   vect);
  
      sort(vect, vect + (sizeof(vect) / sizeof(hstate_t)));
 
      return std::pair<hstate_t, hstate_t>(vect[0], vect[0]);
    }

    void get_son(const automaton_t& a, 
		  std::pair<hstate_t, hstate_t>& f_states,
		  bool& last)
    {
      using namespace std;
      using std::sort;
      using std::copy;

      std::pair<hstate_t, hstate_t> svg;
      hstate_t vect_tmp[a.states().size()];
      std::vector<hstate_t> vect;      

      // we need that a is the same automaton that previously !!!
      if (!a.states().size())
	{
	  last = true;
	  return;
	}

      // don't see this code, is not exist      
      copy(a.states().begin(), a.states().end(),
	   vect_tmp);

      sort(vect_tmp, vect_tmp + (sizeof(vect_tmp) / sizeof(hstate_t)));

      for (unsigned i = 0; i < a.states().size(); ++i)
	vect.push_back(vect_tmp[i]);
      // you can open your eyes now
      
      if (f_states.second != *(--vect.end()))
	f_states.second = *(++find(vect.begin(), vect.end(), f_states.second));
      else
	if (f_states.first != *(--vect.end()))
	  {
	    f_states.first = *(++find(vect.begin(), vect.end(), f_states.first));
	    if (f_states.first == *(--vect.end()))
	      {
		last = true;
		return;
	      }
	    f_states.second = *(++find(vect.begin(), vect.end(), f_states.first));
	  }
	else
	  {
	    last = true;
	    return;
	  }
      last = false;
    }

  };



} // gi

#include <algorithms/rig.hxx>

#endif
