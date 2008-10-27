#include <queue>
#include <set>
#include <map>

#include <vaucanson/boolean_automaton.hh>

namespace vcsn {

  // to be applied only to "realtime" automata

  boolean_automaton::monoid_elt_t
  shortest(const vcsn::boolean_automaton::automaton_t& autom){
    using namespace vcsn::boolean_automaton;
    using namespace std;

    monoid_t themonoid = autom.structure().series().monoid();
    map<hstate_t,monoid_elt_t*> theword; // a pointer to the shortest word read at this state
    queue<hstate_t> thequeue;

    monoid_elt_t empty_word=themonoid.identity(SELECT(monoid_elt_value_t));

    for_all_initial_states(j, autom) {
      theword[*j] = &empty_word;
      if (autom.is_final(*j))
	return empty_word;
      thequeue.push(*j);
    }

    typedef set<hstate_t> setstate_t;
    setstate_t sta;
    while (not thequeue.empty()) {
      hstate_t i = thequeue.front();
      thequeue.pop();
      for_all_letters(a, themonoid.alphabet()){
	sta.clear();
	autom.letter_deltac(sta, i, *a, delta_kind::states());
	// sta is the set of successors of i by *a
	for_all_const(setstate_t, j, sta)
	  if (theword.find(*j) == theword.end()){
            // *j is in the map only if it has been seen before, otherwise:
	    theword[*j] = new monoid_elt_t((*theword[i]) * (*a));
	    if (autom.is_final(*j))
	      return *theword[*j];
	    thequeue.push(*j);
	  }
      }
    }
    cerr << "Empty language" << endl;
    return empty_word;
  }

}
