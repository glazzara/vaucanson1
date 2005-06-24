// init.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.

// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_BENCHS_MINIMIZATION_STROPPA_INIT_HXX
# define VCSN_BENCHS_MINIMIZATION_STROPPA_INIT_HXX



#include <vaucanson/automata/concept/automata_base.hh>
#include <vaucanson/automata/concept/transducer_base.hh>
#include <vaucanson/tools/usual_macros.hh>

//#include <vaucanson/algorithms/determinize.hh>
//#include <vaucanson/algorithms/minimization_moore.hh>
#include <vaucanson/automata/concept/copy.hh>


#include <vector>
#include <map>

#include <fstream>
#include <iostream>

#include <vaucanson/tools/fsm_dump.hh>


namespace vcsn {



  // Works if word is a container of letters
  template<typename A, typename input_t, typename W>
  void
  do_init_with_word(const AutomataBase<A>&      a_set,
                    input_t&                    a,
                    const W&                    word)
  {
    AUTOMATON_TYPES(input_t);

    hstate_t current_state = a.add_state();
    a.set_initial(current_state);

    for_all_const_(W, letter_p, word)
      {
        hstate_t new_state = a.add_state();
        a.add_letter_edge(current_state, new_state, (*letter_p));
        current_state = new_state;
      }

    a.set_final(current_state);
  }



  // Works if word is a container of letters
  // input_monoid == output_monoid
  template<typename A, typename input_t, typename W>
  void
  do_init_with_word(const TransducerBase<A>&    t_set,
                    input_t&                    t,
                    const W&                    word)
  {
    AUTOMATON_TYPES(input_t);

    hstate_t current_state = t.add_state();
    t.set_initial(current_state);

    for_all_const_(W, letter_p, word)
      {
        hstate_t new_state = t.add_state();
        t.add_io_edge(current_state, new_state, (*letter_p), (*letter_p));
        current_state = new_state;
      }

    t.set_final(current_state);
  }


  template<typename S, typename T, typename W>
  void
  init_with_word(Element<S, T>& a,
                 const W&       word)
  {
    do_init_with_word(a.set(), a, word);
  }



  // same as init_with_word with self epsilon-transition added on each state
  template<typename A, typename input_t, typename W>
  void
  do_full_init_with_word(const AutomataBase<A>& a_set,
                         input_t&               a,
                         const W&               word)
  {
    AUTOMATON_TYPES(input_t);

    do_init_with_word(a.set(), a, word);
    for_each_state(s_p, a)
      {
        a.add_spontaneous( (*s_p), (*s_p));
      }
  }

  template<typename S, typename T, typename W>
  void
  full_init_with_word(Element<S, T>&    a,
                      const W&          word)
  {
    do_full_init_with_word(a.set(), a, word);
  }





  template<typename A, typename input_t, template<class> class C, typename W>
  void
  do_init_with_language(const AutomataBase<A>&,
                        input_t&                a,
                        const C<W>&             language)
  {
    AUTOMATON_TYPES(input_t);


    // Prefix automaton:
    hstate_t initial_state = a.add_state();
    a.set_initial(initial_state);

    hstate_t current_state;
    std::vector<hedge_t> edges;
    for_all_const_(C<W>, word_p, language)
      {
        current_state = initial_state;
        for_all_const_(W, letter_p, (*word_p))
          {
            edges.clear();
            a.letter_deltac(edges, current_state, (*letter_p), delta_kind::edges());
            if (edges.size()) // should be 0 or 1
              {
                current_state = a.aim_of(*(edges.begin()));
              }
            else
              {
                hstate_t new_state = a.add_state();
                a.add_letter_edge(current_state, new_state, *letter_p);
                current_state = new_state;
              }
          }
        a.set_final(current_state);
      }
  }


  template<typename S, typename T, template<class> class C, typename W>
  void
  init_with_language(Element<S, T>&     a,
                     const C<W>&        language)
  {
    do_init_with_language(a.structure(), a, language);
  }





  // General: Works with series
  // precondition: weights can be added and divided.
  // precondition: labels can be seen as letter.
  template<typename A, typename input_t,
	   template<typename> class C, typename W, template<typename> class D>
  void
  do_init_with_weighted_language(const AutomataBase<A>& a_set,
				 input_t& a,
                                 const C<W>& words,
                                 const D<typename
				 input_t::semiring_elt_value_t>& weights)
  {

    AUTOMATON_TYPES(input_t);

    input_t b(a.set());

    // Automaton creation
    init_with_language(b, words);
    //    std::cout << "automaton constructed\n";


    // Determinization and minimization through FSM
    std::ofstream tmp_o_file("init_o_tmp.fsm");
    tools::fsm_dump(tmp_o_file, b);
    tmp_o_file.close();
#ifdef INT_AUTOMATA
    system("fsmcompile init_o_tmp.fsm | fsmdeterminize | fsmminimize | fsmprint > init_i_tmp.fsm");
#else
    system("fsmcompile -ialpha.syms init_o_tmp.fsm | fsmdeterminize | fsmminimize | fsmprint -ialpha.syms > init_i_tmp.fsm");
#endif
    std::ifstream tmp_i_file("init_i_tmp.fsm");

    tools::fsm_load(tmp_i_file, b);

    tmp_i_file.close();

    //    std::cout << "determinization and minimization done\n";

//     // Determinization
//     b = determinize(b);
//     // Minimization
//     b = minimization_moore(b);


    // Maps for states and edges weights
    std::map<hedge_t, semiring_elt_value_t>     edges_weights;
    std::map<hstate_t, semiring_elt_value_t>    states_weights;
    std::map<hstate_t, semiring_elt_value_t>    final_states_weights;

    semiring_elt_value_t wzero = a.series().semiring().wzero_.value();


    // Maps initialization with zeros
    for_each_edge(e_p, b) {
      edges_weights[(*e_p)] = wzero;
    }
    for_each_state(s_p, b) {
      states_weights[(*s_p)] = wzero;
    }
    for_each_final_state(s_p, b) {
      final_states_weights[(*s_p)] = wzero;
    }

    assertion(b.initial().size());
    hstate_t initial_state = (*(b.initial().begin()));


    // Filling weights
    typename C<W>::const_iterator                       word_p;
    typename D<semiring_elt_value_t>::const_iterator    weight_p;

    std::vector<hedge_t> cont;
    for ( word_p = words.begin(), weight_p = weights.begin();
          word_p != words.end();
          ++word_p, ++weight_p )
      {
        hstate_t current_state = initial_state;

        for_all_const_(W, l_p, (*word_p))
          {
            states_weights[current_state] += (*weight_p);
            cont.clear();

            b.letter_deltac(cont, current_state, *l_p, delta_kind::edges());
            assertion(cont.size());

            edges_weights[cont[0]] += (*weight_p);
            current_state = b.aim_of(cont[0]);
          }
        assertion(b.is_final(current_state));

        states_weights[current_state] += (*weight_p);
        final_states_weights[current_state] += (*weight_p);
      }


    // Normalization
    semiring_elt_value_t final_weight;
    hstate_t origin;
    for_each_edge(edge_p, b)
      {
        origin = b.origin_of( (*edge_p));
        if (! states_weights[origin]) {
          final_weight = 0;
        }
        else {
          final_weight = edges_weights[(*edge_p)] / states_weights[origin];
        }

        series_set_elt_t s(b.series());
        s.assoc(b.word_of(*edge_p), final_weight);
        b.update(*edge_p, s.value()); // safe ?
      }


    for_each_final_state(s_p, b) 
      {
        series_set_elt_t s(b.series());
        if ( !states_weights[ (*s_p)])
          {
            s.value_set(b.series().monoid().empty_.value(), 0);
          }
        s.value_set(b.series().monoid().empty_.value(), final_states_weights[(*s_p)] / states_weights[(*s_p)] );
        b.set_final( (*s_p), s);
      }

    b.set_initial(initial_state, b.series().one_ );

    auto_copy(a, b);

  }



  template<typename S, typename T, template<typename> class C, typename W, template<typename> class D>
  void
  init_with_weighted_language(Element<S, T>&                                            a,
                              const C<W>&                                               words,
                              const D<typename Element<S, T>::semiring_elt_value_t>&    weights)
  {
    do_init_with_weighted_language(a.set(), a, words, weights);
  }


}  // vcsn




#endif // ! VCSN_BENCHS_MINIMIZATION_STROPPA_INIT_HXX
