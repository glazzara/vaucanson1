// k_window.hh
//
// MICAL_HEADER

#ifndef   K_WINDOW_HH_
# define   K_WINDOW_HH_

#include <vaucanson/algebra/concrete/predefs.hh>
#include <queue>

using std::queue;

namespace mical {

  template <class Letter>
  struct KWindow
  {
    KWindow(unsigned k); 
    
    template <template<class> class Value1, template<class> class Value2>
    KWindow(unsigned k,
	    Element<
	    FreeMonoid<Element<AlphabetSet<Letter>, Value1<Letter> > >, 
	    Value2<Letter> > str); 

    template <template<class> class Value1, template<class> class Value2>
    void insert(Element<
		FreeMonoid<Element<AlphabetSet<Letter>, Value1<Letter> > >, 
		Value2<Letter> > str);

    void insert(Letter l);

    unsigned size();

    void reduce(unsigned size);

    void clear();

    template <template<class> class Value1, template<class> class Value2>
    Element<
      FreeMonoid<Element<AlphabetSet<Letter>, Value1<Letter> > >, 
      Value2<Letter> 
    > get_window(Element<
		 FreeMonoid<Element<AlphabetSet<Letter>, Value1<Letter> > >, 
		 Value2<Letter> > sample);
    

  private:

    unsigned k_;
    queue<Letter> window_;

  };

} // mical

#include <internal/k_window.hxx>

#endif /* !K_WINDOW_HH_ */
