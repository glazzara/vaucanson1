// automata.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2007, 2008 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_CONCEPT_AUTOMATA_HH
# define VCSN_AUTOMATA_CONCEPT_AUTOMATA_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/design_pattern/slots.hh>

namespace vcsn
{

  template <class Series>
  // FIXME: Rename to AutomatonSet (see Trac #3)
  struct Automata;

  /// Dynamic traits for automata.
  template <class Series>
  struct dynamic_traits<Automata<Series> >
    : dynamic_traits<AutomataBase<Automata<Series> > >
  {
      static const bool ret = dynamic_traits<Series>::ret;
  };

  /// MetaElement specialization for automata.
  template <class Series, typename T>
  struct MetaElement<Automata<Series>, T>
    : MetaElement<AutomataBase<Automata<Series> >, T>
  {};

  /// Virtual types for automata.
  template <class Series>
  struct virtual_types<Automata<Series> >
    : virtual_types<AutomataBase<Automata<Series> > >
  {
      typedef Series series_set_t;
  };


  /// Final class for the set of automata.
  template <class Series>
  class Automata
    : public AutomataBase<Automata<Series> >,
      private SetSlot<Series>
  {
    public:
      typedef Automata<Series> self_t;
      typedef Series series_set_t;

      Automata(const series_set_t&);

      const series_set_t&	series() const;
  };

  template <typename S, typename T>
  struct projection_traits<Automata<S>, T>
  {
    typedef Automata<S> structure_t;
    typedef T impl_t;

    typedef Element<structure_t, impl_t> automaton_t;

    typedef typename automaton_t::series_set_elt_t series_set_elt_t;

    typedef typename structure_t::series_set_t series_set_t;

    typedef typename structure_t::series_set_t::semiring_t semiring_t;

    typedef typename structure_t::series_set_t::monoid_t monoid_t;

    typedef typename impl_t::monoid_elt_value_t monoid_elt_value_t;

    typedef typename monoid_t::alphabet_t alphabet_t;

    typedef typename algebra::alphabet_traits<typename alphabet_t::set_t,
					      typename alphabet_t::value_t>
					      alphabet_traits_t;

    typedef typename algebra::word_traits<monoid_t, monoid_elt_value_t>
					  word_traits_t;

    typedef typename word_traits_t::first_monoid_t first_monoid_t;

    typedef typename word_traits_t::second_monoid_t second_monoid_t;

    typedef typename algebra::mute_series_traits<series_set_t,
						 semiring_t,
						 first_monoid_t>::ret
						 first_series_t;

    typedef typename algebra::mute_series_traits<series_set_t,
						 semiring_t,
						 second_monoid_t>::ret
						 second_series_t;

    typedef typename mute_graph_impl_traits<impl_t, word_traits_t>::
	first_projection_t first_impl_t;

    typedef typename mute_graph_impl_traits<impl_t, word_traits_t>::
	second_projection_t second_impl_t;

    typedef Element<Automata<first_series_t>, first_impl_t>
	first_projection_t;

    typedef Element<Automata<second_series_t>, second_impl_t>
	second_projection_t;

    // These are only "makers". Ie they will not contruct the projection.
    // See the relevant algorithms.
    static first_projection_t first_projection(const automaton_t&);
    static second_projection_t second_projection(const automaton_t&);

    typedef automaton_traits<first_impl_t> first_series_traits_t;

    typedef automaton_traits<second_impl_t> second_series_traits_t;

    typedef Element<first_series_t,
		    typename first_series_traits_t::series_set_elt_value_t>
	series_first_projection_t;

    typedef Element<second_series_t,
		    typename second_series_traits_t::series_set_elt_value_t>
	series_second_projection_t;

    // FIXME: As for now we limit series projection here. In the future,
    // we will move it in series_traits.
    static series_first_projection_t
	series_first_projection(const first_series_t&,
				const series_set_elt_t&);
    static series_second_projection_t
	series_second_projection(const second_series_t&,
				 const series_set_elt_t&);
  };

// Some usefull types to manipulate pair letters automaton.
# define AUTOMATON_PROJECTION_TYPES()						\
      typedef algebra::alphabet_traits<alphabet_t::set_t,			\
	      alphabet_t::value_t> alphabet_traits_t;				\
      typedef alphabet_traits_t::first_projection_t				\
	      first_projection_alphabet_t;					\
      typedef alphabet_traits_t::second_projection_t				\
	      second_projection_alphabet_t;					\
										\
      typedef algebra::word_traits<monoid_elt_t::set_t,				\
	      monoid_elt_t::value_t> word_traits_t;				\
      typedef word_traits_t::first_monoid_t first_monoid_t;			\
      typedef word_traits_t::second_monoid_t second_monoid_t;			\
      typedef word_traits_t::first_projection_t first_projection_word_t;	\
      typedef word_traits_t::second_projection_t second_projection_word_t;	\
										\
      typedef projection_traits<automata_set_t, automaton_impl_t>		\
	      projection_traits_t;						\
      typedef projection_traits_t::first_projection_t				\
	      first_projection_automaton_t;					\
      typedef projection_traits_t::second_projection_t				\
	      second_projection_automaton_t

  template <class Series>
  bool
  operator==(const Automata<Series>&, const Automata<Series>&);

} // ! vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/automata/concept/automata.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_CONCEPT_AUTOMATA_HH
