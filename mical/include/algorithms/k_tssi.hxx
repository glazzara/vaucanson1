// k_tssi.hh
//
// MICAL_HEADER



#ifndef   K_TSSI_HXX_
# define   K_TSSI_HXX_

#include <algorithms/k_tssi.hh>
#include <internal/k_window.hh>

#include <map>

namespace mical {

  using namespace vcsn;
  using std::set;
  using std::map;

  template <typename A, typename T, typename Word>
  void
  k_tssi(Element<A, T>& a, unsigned k, const set<Word>& sample)
  {
    KWindow<typename Word::set_t::letter_t> win(k);

    map<Word, hstate_t> mappy;
    
    hstate_t first = a.add_state();
    a.set_initial(first);
    
    mappy[Word()] = first;
    
    for (typename set<Word>::iterator i = sample.begin(); 
	 i != sample.end(); i++)
      {
	win.clear();
	add_word(a, i->begin(), first, win, mappy);
      }
  }
  
  template <typename A, typename T, typename Word>
  void
  add_word(Element<A, T>& a, 
	   typename Word::const_iterator p, 
	   hstate_t current,
	   KWindow<typename Word::set_t::letter_t>& k_window,
	   map<Word, hstate_t>& tab)
  {
    typename map<Word, hstate_t>::iterator res;

    if (*p != 0)
      {
	k_window.insert(*p);

	if ((res = tab.find(k_window.get_window(Word()))) == tab.end())
	  {
	    hstate_t newo = a.add_state();
	
	    tab[k_window.get_window(Word())] = newo;
	
	    a.add_letter_edge(current, newo, *p);
	
	    add_word(a, ++p, newo, k_window, tab);
	  }
	else
	  {
	    a.add_letter_edge(current, res->second, *p);
	    add_word(a, ++p, res->second, k_window, tab);
	  }
      }
    else
      a.set_final(current);
  }


} // mical

#include <algorithms/k_tssi.hxx>

#endif /* !K_TSSI_HXX_ */



