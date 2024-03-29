// gen_book.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_TOOLS_GEN_BOOK_HXX
# define VCSN_TOOLS_GEN_BOOK_HXX

# include <vaucanson/tools/gen_book.hh>
# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/automata/concept/handlers.hh>
namespace vcsn {

  namespace tools {

    template <class Auto_>
    Auto_	lombardy(unsigned size)
    {
      AUTOMATON_TYPES(Auto_);
      AUTOMATON_FREEMONOID_TYPES(Auto_);
      // FIXME:add assert "we want automaton on char."
      alphabets_elt_t	alpha;
      alpha.insert('a');
      alpha.insert('b');
      monoid_t		monoid (alpha);
      semiring_t	semiring;
      series_set_t	series (semiring, monoid);
      automaton_t	automaton;
      automaton.create();
      automaton.series() = series;
      hstate_t		initial = automaton.add_state();
      hstate_t		c	= initial;

      for (unsigned i = 0; i < size; ++i)
      {
	hstate_t	next = automaton.add_state();
	automaton.add_letter_transition(c, c, 'a');
	automaton.add_letter_transition(c, next, 'b');
	automaton.set_initial(c);
	c = next;
      }
      automaton.set_final(c);
      automaton.set_initial(c);
      automaton.add_letter_transition(c, initial, 'a');
      return automaton;
    }

  } // tools

} // vcsn

#endif // ! VCSN_TOOLS_GEN_BOOK_HXX
