// mggi.hh
//
// MICAL_HEADER

#ifndef   MGGI_HH_
# define   MGGI_HH_

namespace mical {

  template <class A, class T, class Alphabet, class Func>
  void mggi(Element<A, T>& a, Alphabet alphabet, 
	    const set<Element<A, T>::monoid_elt_t>& sample,
	    Func convert);
  

} // mical


#endif /* !MGGI_HH_ */
