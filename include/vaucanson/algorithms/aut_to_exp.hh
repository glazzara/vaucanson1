// aut_to_exp.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2008 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_AUT_TO_EXP_HH
# define VCSN_ALGORITHMS_AUT_TO_EXP_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   aut_to_exp.hh
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Tue Jun 24 19:21:17 2003
 *
 * @brief  This file provides converter from automaton to expression.
 *
 * @see aut_to_exp()
 */
/** @} */

// INTERFACE: Exp aut_to_exp(const GenAutomaton& a) { return vcsn::aut_to_exp(*a); }
// INTERFACE: Exp aut_to_exp(const GenAutomaton& a, const vcsn::DMChooser& b) { return vcsn::aut_to_exp(*a, b); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Returns a series which describes the language of the automaton.
   *
   * This algorithm works on every kind of series. However, if, during
   * the computation,  it must take  the star of  it, it can  fail. By
   * passing  a "generalized"  automaton,  that is  an automaton  with
   * rational  expression as  label,  you  will be  sure  to have  the
   * algorithm succeed since we can always take the star of a rational
   * expression.
   *
   * @param a The automaton to convert.
   *
   * @return A rational series that describes the language of the automaton.
   * @see generalized()
   */
  template<typename A, typename AI>
  typename Element<A, AI>::series_set_elt_t
  aut_to_exp(const Element<A, AI>& a);

  /**
   * Returns a series which describes the language of the automaton.
   *
   * This algorithm works on every kind of series. However, if, during
   * the computation,  it must take  the star of  it, it can  fail. By
   * passing  a "generalized"  automaton,  that is  an automaton  with
   * rational  expression as  label,  you  will be  sure  to have  the
   * algorithm succeed since we can always take the star of a rational
   * expression.
   *
   * @param a The automaton to work on.
   * @param c An object-function that returns the next state to remove
   *          from the current state and the automaton.
   *
   * @return A rational series that describes the language of the automaton.
   * @see generalized()
   */
  template<typename A, typename AI, typename Chooser>
  typename Element<A, AI>::series_set_elt_t
  aut_to_exp(const Element<A, AI>& a, const Chooser& c);

  /** @} */



  /**
   * Default chooser for aut_to_exp().
   *
   * @pre There must be at least one state in the automaton.
   * @see aut_to_exp()
   */
  struct DefaultChooser
  {
      template <class Auto_>
      typename Auto_::hstate_t
      operator()(const Auto_& a) const;
  };

  /**
   * Choose randomly a state between all currently choosable
   * @see aut_to_exp()
   */

  struct RandomChooser
  {
      /**
       * @pre @a a must not be the empty automaton.
       */
      template <class Auto_>
      typename Auto_::hstate_t
      operator()(const Auto_& a) const;
  };


  struct HChooser
  {
      template <class Auto_>
      typename Auto_::hstate_t
      operator()(const Auto_& a) const;
  };

  /**
   * Choose a state accordingly to an heuristic.
   *
   * @see CIAA 2004, "Approximation to the Samllest Regular Expression for a Given Regular Language"
   * by M. Delago et J. Morais
   */
  struct DMChooser
  {
      /**
       * @pre @a a must not be the empty automaton.
       */
      template <class Auto_>
      typename Auto_::hstate_t
      operator()(const Auto_& a) const;
  };

  /**
   * Chooser for aut_to_exp().
   *
   * This chooser is built using a std::list<unsigned int>.  It returns
   * the states of the automaton in the same order as in the list.
   *
   * @see aut_to_exp().
   */
  class ListChooser
  {
    typedef std::list<unsigned int> list_t;
  public :
    ListChooser(const list_t& l);

    template <class Auto_>
    typename Auto_::hstate_t operator() (const Auto_& a);

  private :
    list_t list_;
    list_t::const_iterator pos_;
  };

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/aut_to_exp.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_AUT_TO_EXP_HH
