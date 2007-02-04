// generalized_test.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_FREEMONOID_LABELED_GRAPHS_GENERALIZED_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_FREEMONOID_LABELED_GRAPHS_GENERALIZED_TEST_HH

# include <tests/check/tester.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/xml_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/automata/implementation/generalized.hh>

using namespace vcsn;

template <class Auto>
bool generalized_test(tests::Tester&)
{
  AUTOMATON_TYPES(Auto);
  TEST_MSG("Basic test on a well-known automaton.");
  GenRandomAutomata<Auto> gen;
  Auto	a = gen.generate(10,20);
  typename generalized_traits<Auto>::automaton_t a_ = generalized(a);
  return true;
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_FREEMONOID_LABELED_GRAPHS_GENERALIZED_TEST_HH
