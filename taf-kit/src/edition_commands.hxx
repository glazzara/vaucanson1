// edition_commands.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008, 2010 The Vaucanson Group.
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
#ifndef EDITION_COMMANDS_HXX
# define EDITION_COMMANDS_HXX

/**
 * @file edition_commands.hxx
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * This file contains the implementations of @c edit_automaton_command
 * and @c define_automaton_command .
 * @note Should not be put in a .cc file, as CONTEXT_* macros
 *	 could change from one compilation to another.
 */

extern "C" {
# ifdef HAVE_TERMCAP_H
#  include <termcap.h>
# elif HAVE_NCURSES_TERMCAP_H
#  include <ncurses/termcap.h>
# else
#  undef PC
/* Termcap requires these variables, whether we access them or not. */
char *BC, *UP;
char PC;      /* Pad character */
short ospeed; /* Terminal output baud rate */
extern int tgetnum(...), tgetflag(...), tgetent(...);
extern char *tgetstr(...), *tgoto(...);
extern void tputs(...);
# endif
}

# include <iostream>
# include <fstream>
# include <string>
# include <stdexcept>

# include "common.hh"

# include CONTEXT_HEADER
# include <vaucanson/misc/static.hh>

# include "getters.hh"
# include "edition_commands.hh"

# define type_equal(T1, T2) (misc::static_eq < T1, T2 >::value)
# define discard_inputs() std::cin.ignore (LONG_MAX, '\n')

  /*---------------------------------------------------------.
  | Functions that interact with the user to let her edit an |
  | automaton                                                |
  `---------------------------------------------------------*/

namespace edition_commands
{
  using namespace CONTEXT_NAMESPACE;
  using namespace vcsn;

  /// Exception for cancelling.
  struct cancel {};

# ifdef WITH_WEIGHTS
  static semiring_elt_value_t get_semiring_elt_value()
  {
    echo_(" With weight: ");

    semiring_elt_value_t v;
    char first_char = std::cin.get();
    std::cin.unget();
    if (first_char == '\n')
    {
      discard_inputs();
      throw cancel();
    }
    std::cin >> v;
    if (std::cin.fail())
    {
      discard_inputs();
      std::cin.clear();
      throw std::logic_error ("invalid semiring element");
    }
    discard_inputs();
    return v;
  }
# endif

  /// Get an integer from the user.
  static int get_int()
  {
    int n = 0;
    char first_char = std::cin.get();
    std::cin.unget();
    if (first_char == '\n')
    {
      discard_inputs();
      throw cancel();
    }
    std::cin >> n;
    if (std::cin.fail() or n < 0)
    {
      discard_inputs();
      std::cin.clear();
      throw std::logic_error ("invalid number");
    }
    discard_inputs();
    return n;
  }

  /// Get a state of @c a from the user.
  static hstate_t get_state(const automaton_t& a)
  {
    unsigned n_state = get_int();

    if (not a.has_state(n_state))
    {
      std::ostringstream os;
      os << "no state " << n_state << " in automaton.";
      throw std::logic_error(os.str());
    }
    return a.get_state(n_state);
  }

  // Get a transition of @c a from the user.
  static htransition_t get_transition(automaton_t& a)
  {
    int n_trans = get_int();
    int cpt = n_trans;
    htransition_t trans;

    for_all_states(s, a)
    {
      for (automaton_t::delta_iterator h(a.value(), *s);
           ! h.done(); h.next())
	if (--cpt == 0)
	  return *h;
    }
    std::ostringstream os;
    os << "Error: no transition " << n_trans << ".";
    throw std::logic_error(os.str());
  }


  /// Add a certain amount of states to @c a .
  static void add_state(automaton_t& a)
  {
    echo_("  How many states to add ? ");

    int n_states = get_int();
    while (n_states--)
      a.add_state();
  }

  // Del a certain state of @c a .
  static void del_state (automaton_t& a)
  {
    echo_("  Delete state: ");
    hstate_t n_state = get_state(a);
    a.del_state(n_state);
  }

  // For classical automata (single alphabet) transitions are
  // labeled by rational expressions and we use ARGS to parse these
  // expressions.  In transducers (two alphabets) transitions are
  // labeled by pair of words and we only use parse_word().
  //
  // FIXME: It would be nice to output clean error messages when
  // parsing fails.
  static void add_transition (automaton_t& a, const arguments_t& args)
  {
    echo_("  Add a transition from state: ");
    hstate_t n_from = get_state (a);

    echo_("  To state: ");
    hstate_t n_to = get_state (a);

# ifndef WITH_TWO_ALPHABETS
    echo_("  Labeled by the expression: ");
    char ratexp[1024];
    std::cin.getline (ratexp, 1024);

    if (not ratexp[0])
      throw cancel();

    // The representations used to build the rat_exp are the same as the ones
    // specified in the automaton.
    a.add_series_transition(n_from, n_to,
			    make_rat_exp(a.structure().series().monoid().
					 alphabet(), ratexp,
					 *(a.structure().series().monoid().representation()),
					 *(a.structure().series().representation())));
# else
    // We don't parse ratexps, so we don't use these.
    (void) args;

    echo_(" First component labeled by the word: ");
    std::string str1;
    std::getline(std::cin, str1);
    Element<first_monoid_t, std::basic_string<first_monoid_t::letter_t> >
      word1(a.structure().series().monoid().first_monoid());
    parse_word(word1, str1);

    echo_(" Second component labeled by the word: ");
    std::string str2;
    std::getline(std::cin, str2);
    Element<second_monoid_t, std::basic_string<second_monoid_t::letter_t> >
      word2(a.structure().series().monoid().second_monoid());
    parse_word(word2, str2);

    // Construct a series from the two components.
    semiring_elt_t weight(a.structure().series().semiring());
#  ifdef WITH_WEIGHTS
    weight = get_semiring_elt_value();
#  else
    weight = true;
#  endif

    monoid_elt_t label(a.structure().series().monoid());
    label = monoid_elt_value_t(word1.value(), word2.value());
    series_set_elt_t s(a.structure().series());
    s.assoc(label, weight);
    a.add_series_transition(n_from, n_to, s);
# endif
  }

  /// Del a transition in @c a .
  static void del_transition (automaton_t& a)
  {
    echo_("  Delete transition: ");
    htransition_t trans = get_transition(a);
    a.del_transition(trans);
  }

  static const bool set_to_be = true;
  static const bool set_to_not_be = false;
  static const bool initial = true;
  static const bool final = false;
  /// Set or unset a state to be final or initial according to @c initial
  /// and @c want_set .
  static void set_unset_initial_final(automaton_t& a, bool want_set,
				      bool initial)
  {
    echo_("  For state: ");
    hstate_t n_state = get_state(a);
    series_set_elt_t *weight = 0;

# ifdef WITH_WEIGHTS
    if (want_set)
    {
      semiring_elt_value_t v = get_semiring_elt_value();
      weight = new series_set_elt_t(a.structure().series());
      weight->assoc(identity_value(SELECT(monoid_t),
				   SELECT(monoid_elt_value_t)), v);
    }
# endif

    if (initial)
      if (want_set)
	if (weight)
	  a.set_initial(n_state, *weight);
	else
	  a.set_initial(n_state);
      else
	a.unset_initial(n_state);
    else
      if (want_set)
	if (weight)
	  a.set_final(n_state, *weight);
	else
	  a.set_final(n_state);
      else
	a.unset_final(n_state);
  }

  /// Print the automaton @c a .
  static void print_automaton (automaton_t& a)
  {
# define Print_States(Text, For, ShowWeight, GetInFin)			\
    echo_(Text << ": ");						\
    {									\
      bool first = true;						\
      For (s, a)							\
      {									\
	if (first)							\
	{								\
	  first = false;						\
	  echo_(*s);							\
	}								\
	else								\
	  echo_(", " << *s);						\
	if (ShowWeight and not type_equal(semiring_elt_value_t, bool))	\
	  echo_(" (W: " <<						\
		 a.GetInFin(*s).					\
		 get(identity_value(SELECT(monoid_t),			\
				    SELECT(monoid_elt_value_t))) << ")"); \
      }									\
      if (first)							\
	echo_("(none)");						\
      echo("");								\
    }

    echo("Automaton description:");

    Print_States("  States", for_all_states,
		 false, get_initial /* Don't care */);
    Print_States("  Initial states", for_all_initial_states,
		 true, get_initial);
    Print_States("  Final states", for_all_final_states,
		 true, get_final);

    echo_ ("\n  Transitions: ");
    unsigned n_trans = 0;
    for_all_states(s, a)
    {
      for (automaton_t::delta_iterator h(a.value(), *s);
           ! h.done(); h.next())
      {
	++n_trans;
# ifndef WITH_TWO_ALPHABETS
	echo_("\n    " << n_trans << ": From " << *s << " to " << a.dst_of (*h)
	      << " labeled by " << a.series_of (*h));
# else
#  ifndef WITH_WEIGHTS
	echo_("\n    " << n_trans << ": From " << *s << " to " << a.dst_of (*h)
	      << " labeled by " << a.word_of (*h));
#  else
	echo_("\n    " << n_trans << ": From " << *s << " to " << a.dst_of (*h)
	      << " labeled by " << a.word_of (*h)
	      << " W: " << a.weight_of (*h));
#  endif
# endif
      }
    }
    if (not n_trans)
      echo_ ("(none)");
    echo ("\n");
  }

  static 
  void
  check_common_errors(automaton_t& a)
  {
    bool empty_init = a.initial().empty();
    bool empty_final = a.final().empty();
    if (empty_final && empty_init)
      {
	std::cerr << std::endl
		  << "Warning: automaton has no initial states nor final states"
		  << std::endl;
	return;
      }
    if (empty_init)
      {
	std::cerr << std::endl
		  << "Warning: automaton has no initial states" << std::endl;
	return;
      }
    if (empty_final)
      {
	std::cerr << std::endl
		  << "Warning: automaton has no final states" << std::endl;
	return;
      }
  }

  /// Interact with the user to let her choose an action.
  static bool ask_and_treat_choice(automaton_t& a, const arguments_t& args)
  {
    echo("Please choose your action:" << std::endl
	 << "  1. Add states." << std::endl
	 << "  2. Delete a state.\n" << std::endl
	 << "  3. Add a transition." << std::endl
	 << "  4. Delete a transition.\n" << std::endl
	 << "  5. Set a state to be initial." << std::endl
	 << "  6. Set a state not to be initial.\n" << std::endl
	 << "  7. Set a state to be final." << std::endl
	 << "  8. Set a state not to be final.\n" << std::endl
	 << "  9. Display the automaton in Dotty.\n" << std::endl
	 << "  10. Save and exit." << std::endl
	 << "  11. Exit without saving.\n" << std::endl);

    echo_("Your choice [1-11]: ");

    try {
      switch (get_int())
      {
      case 1: add_state(a); break;
      case 2: del_state(a); break;
      case 3: add_transition(a, args); break;
      case 4: del_transition(a); break;
      case 5: set_unset_initial_final(a, set_to_be, initial); break;
      case 6: set_unset_initial_final(a, set_to_not_be, initial); break;
      case 7: set_unset_initial_final(a, set_to_be, final); break;
      case 8: set_unset_initial_final(a, set_to_not_be, final); break;
      case 9: display_aut(a, args, 1); break;
      case 10: check_common_errors(a); return true;
      case 11: exit(0);
      }
    } catch (const std::logic_error& err) {
      // FIXME: this message will never be displayed
      warn ("Error: " << err.what ());
      std::cin.get ();
      std::cin.unget ();
      discard_inputs ();
    } catch (cancel) {}

    return false;
  }

  /// Main loop for edit_automaton.
  static void main_loop(automaton_t& a, const arguments_t& args)
  {
    char* term = getenv("TERM");
    char* cl = 0;

    if (term and (tgetent(0, term) != -1))
      cl = tgetstr("cl", 0);
    do
    {
      if (cl)
	tputs(cl, 1, putchar);
      print_automaton(a);
    } while (not ask_and_treat_choice(a, args));
  }

}

/// Edit automaton command ; let the user edit an automaton.
static int edit_command(const arguments_t& args)
{
  using namespace vcsn::tools;

# ifndef WITH_TWO_ALPHABETS
  automaton_t a = make_automaton(alphabet_t());
# else
  automaton_t a = make_automaton(first_alphabet_t(), second_alphabet_t());
# endif // !WITH_TWO_ALPHABETS

  if (!strcmp(args.args[1], "-"))
    {
      std::cerr << "Error: edit cannot handle piped commands."
		<< " If you want to edit an automaton, you must first save it."
		<< std::endl;
      exit(2);
    }

  std::string src = locate_file(args, args.args[1]);

  if (file_exists(src.c_str()))
    {
      a = get_aut(args, 1);
    }
  else
    {
      // We define the automaton from scratch: the user should have
      // specified the alphabet to use. The make_automaton function
      // will then choose wisely a good representation for all the
      // writing data.
# ifndef WITH_TWO_ALPHABETS
      a = make_automaton(get_alphabet(args.alphabet));
# else
      a = make_automaton(get_first_alphabet(args.alphabet1),
			 get_second_alphabet(args.alphabet2));
# endif // !WITH_TWO_ALPHABETS
    }

  // We can now overwrite any writing data by the new ones
  // provided on the command line (if any), before entering
  // the main loop.
  set_writing_data(a, args);

  edition_commands::main_loop(a, args);

  return write_aut(a, args, 1);
}


#endif // ! EDITION_COMMANDS_HXX
