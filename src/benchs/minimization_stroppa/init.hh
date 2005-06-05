//////////////////////
//
// $Id:
//
/////////////////////


#ifndef VCSN_EXT_ALGORITHMS_INIT_HH
#define VCSN_EXT_ALGORTIHMS_INIT_HH



namespace vcsn {


  /** @addtogroup algorithms *//** @{ */


  /*----------------.
  | init_with_word  |
  `----------------*/
  /**
   * @brief Initializes an automaton with a single word.
   *
   * This function initializes an automaton so that it recognizes an input word.
   *
   * @param a An empty automaton
   * @param word The input word
   *
   * @see full_init_with_word
   * @see init_with_language
   * @see init_with_weighted language
   */
  template<typename S, typename T, typename W>
  void
  init_with_word(Element<S, T>& a,
                 const W&       word);


  /*---------------------.
  | full_init_with_word  |
  `---------------------*/
  /**
   * @brief Initializes an automaton with a single word.
   *
   * This function initializes an automaton so that it recognizes an input word.
   * An epsilon transition from each state to itself is added to avoid
   * error when composing with a transducer containing epsilon transition.
   *
   * @param a An empty automaton
   * @param word The input word
   *
   * @see init_with_word
   * @see init_with_language
   * @see init_with_weighted language
   */
  template<typename S, typename T, typename W>
  void
  full_init_with_word(Element<S, T>&    a,
                      const W&          word);


  /*--------------------.
  | init_with_language  |
  `--------------------*/
  /**
   * @brief Initializes an automaton with a finite language.
   *
   * This function initializes an automaton so that it recognizes an input finite language.
   * Moreover, it constructs the language prefix tree, so the automaton is deterministic.
   *
   * @param a An empty automaton
   * @param language The input language (a container of word).
   *
   * @see init_with_word
   * @see full_init_with_word
   * @see init_with_weighted_language
   */
  template<typename S, typename T, template<class> class C, typename W>
  void
  init_with_language(Element<S, T>&     a,
                     const C<W>&        language);


  /*-----------------------------.
  | init_with_weighted_language  |
  `-----------------------------*/
  /**
   * @brief Initializes an automaton with a finite weighted language.
   *
   * This function initializes an automaton so that it recognizes an input finite weighted language.
   *
   * @param a An empty automaton
   * @param words The input language words (a container of word).
   * @param weights The input language weights (a container of weights associated to words).
   *
   * @see init_with_word
   * @see full_init_with_word
   * @see init_with_language
   */
  template<typename S, typename T, template<typename> class C, typename W, template<typename> class D>
  void
  init_with_weighted_language(Element<S, T>&                                            a,
                              const C<W>&                                               words,
                              const D<typename Element<S, T>::semiring_elt_value_t>&    weights);


  /** @} */


}  // vcsn

#include <minimization_stroppa/init.hxx>

#endif  // VCSN_EXT_ALGORITHMS_INIT_HH
