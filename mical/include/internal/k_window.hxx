// k_window.hxx
//
// MICAL_HEADER


#ifndef   K_WINDOW_HXX_
# define   K_WINDOW_HXX_

#include <internal/k_window.hh>

using std::queue;

namespace mical {


  template <class Letter>
  KWindow<Letter>::
  KWindow(unsigned k) : k_(k)
  { }

  template <class Letter>
  template <template<class> class Value1, template<class> class Value2>
  KWindow<Letter>::
  KWindow(unsigned k,
	  Element<
	  FreeMonoid<Element<AlphabetSet<Letter>, Value1<Letter> > >, 
	  Value2<Letter> > str): k_(k)
  { 
    insert(str);
  }

  template <class Letter>
  template <template<class> class Value1, template<class> class Value2>
  void 
  KWindow<Letter>::
  insert(Element<
	 FreeMonoid<Element<AlphabetSet<Letter>, Value1<Letter> > >, 
	 Value2<Letter> > str)
  {
    typedef 
      Element<
      FreeMonoid<Element<AlphabetSet<Letter>, Value1<Letter> > >, 
      Value2<Letter> > 
      Word; 

    for (typename Word::iterator i = str.begin(); i != str.end(); i++)
      insert(*i);
  }

  template <class Letter>
  void 
  KWindow<Letter>::
  insert(Letter l)
  {
    while (window_.size() >= k_)
      window_.pop();
    window_.push(l);
  }

  template <class Letter>
  void 
  KWindow<Letter>::
  reduce(unsigned size)
  {
    for (unsigned i = 0; i < size; i++)
      window_.pop();
  }

  template <class Letter>
  void 
  KWindow<Letter>::
  clear()
  {
    while (!window_.empty())
    window_.pop();
  }
  
  template <class Letter>
  template <template<class> class Value1, template<class> class Value2>
  Element<
    FreeMonoid<Element<AlphabetSet<Letter>, Value1<Letter> > >, 
    Value2<Letter> 
  > 
  KWindow<Letter>::
  get_window(Element<
	     FreeMonoid<Element<AlphabetSet<Letter>, Value1<Letter> > >, 
	     Value2<Letter> > sample)
  {
    typedef 
      Element<
      FreeMonoid<Element<AlphabetSet<Letter>, Value1<Letter> > >, 
      Value2<Letter> 
      > Word;

    Word str;
    queue<Letter> work = window_;

    while (work.size())
      {
	str *= work.front();
	work.pop();
      }
    
    return str;
  }

  template <class Letter>
  unsigned
  KWindow<Letter>::size()
  {
    return window_.size();
  }

} // mical

#endif /* !K_WINDOW_HXX_ */

