// one_rule_rewriting.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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
#ifndef ONE_RULE_REWRITING_HH
# define ONE_RULE_REWRITING_HH

#include <string>
#include <sstream>

#include <vaucanson/misc/contract.hh>
#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/boolean_transducer.hh>
#include <vaucanson/algorithms/transpose.hh>
#include <vaucanson/algorithms/krat_exp_expand.hh>
#include <vaucanson/tools/dot_display.hh>

/**
 * @file one_rule_rewriting.hh
 *
 * Generate boolean transducers from a rule rewriting
 * system with only one rule (X -> Y).
 *
 */

namespace ORR
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::boolean_transducer;

  /**
   * Generate a boolean transducer who apply the rule by reading
   * a word from left to right.
   *
   * @param from
   *   A string containing the word being replaced.
   * @param to
   *   A string containing the replacement word.
   * @param A
   *   The alphabet used by the first word.
   * @param B
   *   The alphabet used by the second word.
   * @return
   *   The cautious left automaton.
   */
  automaton_t
  replace_left(const std::string& from, const std::string& to,
	       const alphabet_t& A,
	       const alphabet_t& B);

  /**
   * Generate a boolean transducer who apply the rule by reading
   * a word from right to left.
   *
   * @param from
   *   A string containing the word being replaced.
   * @param to
   *   A string containing the replacement word.
   * @param A
   *   The alphabet used by the first word.
   * @param B
   *   The alphabet used by the second word.
   * @return
   *   The cautious right automaton.
   */
  automaton_t
  replace_right(const std::string& from, const std::string& to,
		const alphabet_t& A,
		const alphabet_t& B);

  //
  // Internal functions
  //

  /**
   * Convert one word from a source alphabet to a destition
   * alphabet using the provided map.
   *
   * @param conv_map
   *   A map between two alphabets.
   * @param str
   *   A word to convert.
   * @return
   *   The word after convertion.
   */
  std::string
  alpha_convert(const std::map<letter_t, letter_t>& conv_map,
		const std::string& str);

  /**
   * Create a mapping beetween two alphabets with the same number
   * of letters.
   *
   * @param A
   *   The source alphabet.
   * @param B
   *   The destination alphabet.
   * @return
   *   The desired mapping.
   */
  std::map<letter_t, letter_t>
  alpha_map(const alphabet_t& A,
	    const alphabet_t& B);

  /**
   * FIXME: Document stuff!
   *
   */
  std::string
  prefsuf(const std::string& u, const std::string& v);

  /**
   * Evaluate an automaton on a word and print the result.
   *
   * @param t
   *   The automaton being used for evaluation.
   * @param name
   *   The name of the automaton.
   * @param interactive
   *   Interactive mode.
   * @param str
   *   Word to evaluate the automaton on.
   * @return
   *   The evaluation result.
   */
  std::string
  eval_an_expression(const automaton_t& t,
		     const std::string& name,
		     bool interactive = true,
		     const std::string& str = "");

} // ! ORR

# include "one_rule_rewriting.hxx"

#endif // ! ONE_RULE_REWRITING_HH
