// generate_random_krat.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004 The Vaucanson Group.
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
#include <iostream>
#include <fstream>
#include <vaucanson/r_automaton.hh>
#include <vaucanson/z_automaton.hh>
#include <vaucanson/boolean_automaton.hh>


using namespace vcsn;

void		generate_random_expression() {
  srand(time(0));
  
  // Alphabet {a, b}
  boolean_automaton::alphabet_t alphabet_ab;
  alphabet_ab.insert('a');
  alphabet_ab.insert('b');
  boolean_automaton::monoid_t monoid_ab(alphabet_ab);
  // Alphabet { \, .}
  boolean_automaton::alphabet_t alphabet_weird;
  alphabet_weird.insert('\\');
  alphabet_weird.insert('.');
  boolean_automaton::monoid_t monoid_weird(alphabet_weird);

  
  // Building series.
  boolean_automaton::semiring_t semiring_b;
  boolean_automaton::series_set_t s_b_ab(semiring_b, monoid_ab);
  boolean_automaton::series_set_t s_b_weird(semiring_b, monoid_weird);
  
  z_automaton::semiring_t semiring_i;
  z_automaton::series_set_t s_i_ab(semiring_i, monoid_ab);
  z_automaton::series_set_t s_i_weird(semiring_i, monoid_weird);

  r_automaton::semiring_t semiring_f;
  r_automaton::series_set_t s_f_ab(semiring_f, monoid_ab);
  r_automaton::series_set_t s_f_weird(semiring_f, monoid_weird);

  
  // Opening output file for boolean. Name must follow:
  // random_krat_exp_SemiringImplType_Alphabet 
  // with SemiringImplType in {b, i, f} (ie bool, int, float)
  // with Alphabet in {ab, weird}
  std::ofstream out_file_b_ab("random_krat_exp_b_ab");
  std::ofstream out_file_b_weird("random_krat_exp_b_weird");

  // Opening output file for int. 
  std::ofstream out_file_i_ab("random_krat_exp_i_ab");
  std::ofstream out_file_i_weird("random_krat_exp_i_weird");

  // Opening output file for float. 
  std::ofstream out_file_f_ab("random_krat_exp_f_ab");
  std::ofstream out_file_f_weird("random_krat_exp_f_weird");

  
  // Generating 2500 expressions.
  for (int i = 0; i < 2500; ++i)
    {
      // For boolean.
      boolean_automaton::krat_exp_t exp_b0 =
	s_b_ab.choose(SELECT(boolean_automaton::krat_exp_t::value_t));
      out_file_b_ab << exp_b0 << std::endl;
      boolean_automaton::krat_exp_t exp_b1 =
	s_b_weird.choose(SELECT(boolean_automaton::krat_exp_t::value_t));
      out_file_b_weird << exp_b1 << std::endl;

      // For int.
      z_automaton::krat_exp_t exp_i0 =
	s_i_ab.choose(SELECT(z_automaton::krat_exp_t::value_t));
      out_file_i_ab << exp_i0 << std::endl;
      z_automaton::krat_exp_t exp_i1 =
	s_i_weird.choose(SELECT(z_automaton::krat_exp_t::value_t));
      out_file_i_weird << exp_i1 << std::endl;
      
      // For float (same expressions are used for double).
      r_automaton::krat_exp_t exp_f0 =
	s_f_ab.choose(SELECT(r_automaton::krat_exp_t::value_t));
      out_file_f_ab << exp_f0 << std::endl;
      r_automaton::krat_exp_t exp_f1 =
	s_f_weird.choose(SELECT(r_automaton::krat_exp_t::value_t));
      out_file_f_weird << exp_f1 << std::endl;
    }
}

int		main() {
  generate_random_expression();
  return 0;
}

