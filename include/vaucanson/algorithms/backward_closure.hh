#ifndef  VCSN_ALGORITHMS_BACKWARD_CLOSURE_HH
# define VCSN_ALGORITHMS_BACKWARD_CLOSURE_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  /** 
   * Complete in place the given automaton to make it close over
   * epsilon transition. 
   * 
   * @param a the weighted automaton to close.
   *
   * @see forward_closure_here
   * @see forward_closure
   * @see backward_closure_here
   */
  template<typename A, typename T>
  void
  backward_closure_here(Element<A, T>& a);

  /** 
   * Complete the given automaton into a copy to make it close over
   * epsilon transition. 
   *
   * @param a the weighted automaton to close.
   *
   * @see forward_closure
   * @see forward_closure_here
   * @see backward_closure_here
   */
  template<typename A, typename T>
  Element<A, T>
  backward_closure(const Element<A, T>& a);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/backward_closure.hxx>

#endif // VCSN_ALGORITHMS_BACKWARD_CLOSURE_HH
