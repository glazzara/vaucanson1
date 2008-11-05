// transducer.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HH
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/transducer_base.hh>

namespace vcsn {

  template <typename Series, typename Kind>
  // FIXME: Rename to TransducerSet (see Trac #3)
  struct Transducer;

  /// Dynamic traits for transducers.
  template <typename Series, typename Kind>
  struct dynamic_traits<Transducer<Series, Kind> >
    : dynamic_traits<TransducerBase<Series> >
  {
    static const bool ret = dynamic_traits<Series>::ret;
  };

  /// Specialization of MetaElement for transducers.
  template <typename Series, typename Kind, typename T>
  struct MetaElement<Transducer<Series, Kind>, T>
    : MetaElement<TransducerBase<Transducer<Series, Kind> >, T>
  {};

  /// Virtual types for transducers.
  template <typename Series, typename Kind>
  struct virtual_types<Transducer<Series, Kind> >
  {
    typedef Series		series_set_t;
    typedef Kind		kind_t;
  };

  /// Final class for the set of transducers.
  template <typename Series, typename Kind>
  class Transducer
    : public TransducerBase<Transducer<Series, Kind> >,
      private SetSlot<Series>
  {
  public:
    typedef Transducer<Series, Kind>			     self_t;
    typedef typename virtual_types<self_t>::series_set_t     series_set_t;
    typedef typename virtual_types<self_t>::kind_t           kind_t;

    Transducer(const series_set_t&);

    const series_set_t&	series() const;

  };


  /*------------------------.
  | INPUT PROJECTION TRAITS |
  `------------------------*/

  template <typename S, typename T>
  struct input_projection_helper
  { };

  template <typename S, typename K, typename T>
  struct input_projection_helper<Transducer<S, K>, T>
  {
    typedef Transducer<S, K> structure_t;

    typedef Element<structure_t, T> automaton_t;

    typedef typename structure_t::series_set_t::semiring_t
    typeof_auto_series_set_t;

    typedef typename structure_t::series_set_t::monoid_t auto_monoid_t;

    typedef typename typeof_auto_series_set_t::semiring_t auto_semiring_t;
    typedef typename algebra::mute_series_traits<typeof_auto_series_set_t,
						 auto_semiring_t,
						 auto_monoid_t>::ret
    auto_series_set_t;

    typedef typename input_projection_traits<T>::ret auto_impl_t;
    typedef Element<Automata<auto_series_set_t, K>, auto_impl_t> ret;

    static ret make_input_projection_automaton(const automaton_t& t);
  };

  template <typename S, typename K, typename T>
  struct input_projection_helper<Automata<S, K>, T>
  {
    typedef Automata<S, K> structure_t;

    typedef Element<structure_t, T> automaton_t;

    typedef typename structure_t::series_set_t typeof_auto_series_set_t;

    typedef typename structure_t::series_set_t::semiring_t auto_semiring_t;

    typedef typename structure_t::series_set_t::monoid_t::first_monoid_t
    auto_monoid_t;

    typedef typename algebra::mute_series_traits<typeof_auto_series_set_t,
						 auto_semiring_t,
						 auto_monoid_t>::ret
    auto_series_set_t;

    typedef typename fmp_input_projection_traits<T>::ret auto_impl_t;
    typedef Element<Automata<auto_series_set_t, K>, auto_impl_t> ret;

    static ret make_input_projection_automaton(const automaton_t& t);
  };

  /*-------------------------.
  | OUTPUT PROJECTION TRAITS |
  `-------------------------*/

  template <typename S, typename T>
  struct output_projection_helper
  { };

  // RW transducers
  template <typename S, typename K, typename T>
  struct output_projection_helper<Transducer<S, K>, T>
  {
    typedef Transducer<S, K> structure_t;

    typedef Element<structure_t, T> automaton_t;

    typedef typename structure_t::series_set_t::semiring_t
    typeof_auto_series_set_t;

    typedef typename structure_t::series_set_t::semiring_t::monoid_t
    auto_monoid_t;

    typedef typename typeof_auto_series_set_t::semiring_t auto_semiring_t;
    typedef typename algebra::mute_series_traits<typeof_auto_series_set_t,
						 auto_semiring_t,
						 auto_monoid_t>::ret
    auto_series_set_t;

    typedef typename output_projection_traits<T>::ret auto_impl_t;
    typedef Element<Automata<auto_series_set_t, K>, auto_impl_t> ret;

    static ret make_output_projection_automaton(const automaton_t& t);
  };

  // FMP Transducers
  // FIXME: it should be automata over a free monoid product
  // FIXME: we cannot use output_projection_traits, because
  // it constructs the type by assuming that the automaton is RW
  template <typename S, typename K, typename T>
  struct output_projection_helper<Automata<S, K>, T>
  {
    typedef Automata<S, K> structure_t;

    typedef Element<structure_t, T> automaton_t;

    typedef typename structure_t::series_set_t typeof_auto_series_set_t;

    typedef typename structure_t::series_set_t::monoid_t::second_monoid_t
    auto_monoid_t;

    typedef typename typeof_auto_series_set_t::semiring_t auto_semiring_t;
    typedef typename algebra::mute_series_traits<typeof_auto_series_set_t,
						 auto_semiring_t,
						 auto_monoid_t>::ret
    auto_series_set_t;

    typedef typename fmp_output_projection_traits<T>::ret auto_impl_t;
    typedef Element<Automata<auto_series_set_t, K>, auto_impl_t> ret;

    static ret make_output_projection_automaton(const automaton_t& t);
  };

  /*----------------.
  | IDENTITY TRAITS |
  `----------------*/

  template <typename S, typename K, typename T>
  struct identity_transducer_helper
  {
    typedef typename S::series_set_t	 series_set_t;
    typedef typename series_set_t::monoid_t  monoid_t;
    typedef typename series_set_t::semiring_t semiring_t;
    typedef typename algebra::mute_series_traits<series_set_t, series_set_t, monoid_t>
    ::ret    tseries_set_t;
    typedef typename extension_traits<T>::ret impl_t;
    typedef Element<Transducer<tseries_set_t, K>, impl_t> ret;
  };

  template <typename S, typename K, typename T>
  typename identity_transducer_helper<S, K, T>::ret
  partial_identity(const Element<S, T>&);

  template <typename Series, typename Kind>
  bool
  operator==(const Transducer<Series, Kind>&, const Transducer<Series, Kind>&);

} // ! vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/automata/concept/transducer.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HH
