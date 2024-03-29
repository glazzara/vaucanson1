// gen_random.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The
// Vaucanson Group.
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
#ifndef VCSN_TOOLS_GEN_RANDOM_HH
# define VCSN_TOOLS_GEN_RANDOM_HH

# include <vaucanson/misc/selectors.hh>
# include <vaucanson/algebra/implementation/monoid/monoid_rep.hh>
# include <vaucanson/automata/concept/transducer.hh>

// We can have letter types with very large cardinal
// (say int letters). So we clip the max size to
// ALPHABET_MAX_SIZE to ensure the test-suite will
// be able to generate random automata with max-sized
// alphabets.
# define ALPHABET_MAX_SIZE 1024

namespace vcsn {

  namespace tools {

    /*---------------------.
    | GenRandomAutomataSet |
    `---------------------*/

    class GenRandomAutomataSet
    {
      public:

	template <class AutoSet>
	  static AutoSet generate(SELECTOR(AutomataBase<AutoSet>),
	      unsigned nb_letter = 0);

	template <class AutoSet>
	  static AutoSet generate(SELECTOR(TransducerBase<AutoSet>),
	      unsigned input_nb_letter = 0,
	      unsigned output_nb_letter = 0);
    };


    /*------------------.
    | GenRandomAutomata |
    `------------------*/

    template <class TAutomata, class AutomataSetGenerator = GenRandomAutomataSet>
      class GenRandomAutomata
      {
	public:
	  typedef typename TAutomata::set_t	automata_set_t;
      typedef typename TAutomata::hstate_t hstate_t;

	public:
	  GenRandomAutomata();

	  TAutomata empty(unsigned nb_letter = 0);
	  TAutomata empty(const automata_set_t& set);

	  TAutomata generate(unsigned nb_state, unsigned nb_transition,
	      unsigned istate = 1, unsigned fstate = 1,
	      unsigned nb_letter = 0);
	  TAutomata generate(const automata_set_t& set,
	      unsigned nb_state, unsigned nb_transition,
	      unsigned istate = 1, unsigned fstate = 1);

	  TAutomata generate_dfa(unsigned nb_state,
	      unsigned size_alphabet = 0,
	      unsigned fstate = 1);
	  TAutomata generate_dfa(const automata_set_t& set,
	      unsigned nb_state,
	      unsigned fstate = 1);

	  TAutomata generate_with_epsilon(unsigned nb_state, unsigned nb_transition,
	      unsigned nb_epsilon_min,
	      unsigned nb_epsilon_max);
	  TAutomata generate_with_epsilon(const automata_set_t& set,
	      unsigned nb_state, unsigned nb_transition,
	      unsigned nb_epsilon_min,
	      unsigned nb_epsilon_max);

	  TAutomata generate_normalized(unsigned nb_state, unsigned density = 3);
	  TAutomata generate_normalized(const automata_set_t& set,
	      unsigned nb_state, unsigned density = 3);


	private:

	  unsigned nb_transition_circle(TAutomata work, hstate_t state);
	  void     del_transition_circle(TAutomata& work, hstate_t state);

      };

    static unsigned alea(unsigned max);

  } // ! tools

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/tools/gen_random.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_TOOLS_GEN_RANDOM_HH
