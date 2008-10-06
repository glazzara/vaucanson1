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

  template <class Series>
  struct Transducer;

  /// Dynamic traits for transducers.
  template <class Series>
  struct dynamic_traits<Transducer<Series> >
    : dynamic_traits<TransducerBase<Series> >
  {
    static const bool ret = dynamic_traits<Series>::ret;
  };

  /// Specialization of MetaElement for transducers.
  template <class Series, typename T>
  struct MetaElement<Transducer<Series>, T>
    : MetaElement<TransducerBase<Transducer<Series> >, T>
  {};

  /// Virtual types for transducers.
  template <class Series>
  struct virtual_types<Transducer<Series> >
  {
    typedef Series		series_set_t;
  };

  /// Final class for the set of transducers.
  template <class Series>
  class Transducer
    : public TransducerBase<Transducer<Series> >,
      private SetSlot<Series>
  {
  public:
    typedef Transducer<Series>				     self_t;
    typedef typename virtual_types<self_t>::series_set_t     series_set_t;

    Transducer(const series_set_t&);

    const series_set_t&	series() const;

  };


  /*------------------------.
  | INPUT PROJECTION TRAITS |
  `------------------------*/

  template <class S, class T>
  struct input_projection_helper
  { };

  template <class S, class T>
  struct input_projection_helper<Transducer<S>, T>
  {
    typedef typename Transducer<S>::series_set_t::semiring_t
    typeof_auto_series_set_t;

    typedef typename Transducer<S>::series_set_t::monoid_t auto_monoid_t;

    typedef typename typeof_auto_series_set_t::semiring_t auto_semiring_t;
    typedef typename algebra::mute_series_traits<typeof_auto_series_set_t,
						 auto_semiring_t,
						 auto_monoid_t>::ret
    auto_series_set_t;

    typedef typename projection_traits<T>::ret auto_impl_t;
    typedef Element<Automata<auto_series_set_t>, auto_impl_t> ret;
  };

  template <class S, class T>
  struct input_projection_helper<Automata<S>, T>
  {
    typedef Automata<S> structure_t;

    typedef typename structure_t::series_set_t typeof_auto_series_set_t;

    typedef typename structure_t::series_set_t::semiring_t auto_semiring_t;

    typedef typename structure_t::series_set_t::monoid_t::first_monoid_t
    auto_monoid_t;

    typedef typename algebra::mute_series_traits<typeof_auto_series_set_t,
						 auto_semiring_t,
						 auto_monoid_t>::ret
    auto_series_set_t;

    typedef typename fmp_projection_traits<T>::ret auto_impl_t;
    typedef Element<Automata<auto_series_set_t>, auto_impl_t> ret;
  };

  /*-------------------------.
  | OUTPUT PROJECTION TRAITS |
  `-------------------------*/

  template <class S, class T>
  struct output_projection_helper
  { };

  // RW transducers
  template <class S, class T>
  struct output_projection_helper<Transducer<S>, T>
  {
    typedef Transducer<S> structure_t;

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
    typedef Element<Automata<auto_series_set_t>, auto_impl_t> ret;
  };

  // FMP Transducers
  // FIXME: it should be automata over a free monoid product 
  // FIXME: we cannot use output_projection_traits, because
  // it constructs the type by assuming that the automaton is RW
  template <class S, class T>
  struct output_projection_helper<Automata<S>, T>
  {
    typedef Automata<S> structure_t;

    typedef typename structure_t::series_set_t typeof_auto_series_set_t;

    typedef typename structure_t::series_set_t::monoid_t::second_monoid_t
    auto_monoid_t;

    typedef typename typeof_auto_series_set_t::semiring_t auto_semiring_t;
    typedef typename algebra::mute_series_traits<typeof_auto_series_set_t,
						 auto_semiring_t,
						 auto_monoid_t>::ret
    auto_series_set_t;

    typedef typename fmp_output_projection_traits<T>::ret auto_impl_t;
    typedef Element<Automata<auto_series_set_t>, auto_impl_t> ret;
  };

  /*----------------.
  | IDENTITY TRAITS |
  `----------------*/

  template <class S, class T>
  struct identity_transducer_helper
  {
    typedef typename S::series_set_t	 series_set_t;
    typedef typename series_set_t::monoid_t  monoid_t;
    typedef typename series_set_t::semiring_t semiring_t;
    typedef typename algebra::mute_series_traits<series_set_t, series_set_t, monoid_t>
    ::ret    tseries_set_t;
    typedef typename extension_traits<T>::ret impl_t;
    typedef Element<Transducer<tseries_set_t>, impl_t> ret;
  };

  template <class S, class T>
  typename identity_transducer_helper<S, T>::ret
  partial_identity(const Element<S, T>&);

  template <class Series>
  bool
  operator==(const Transducer<Series>&, const Transducer<Series>&);

} // ! vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/automata/concept/transducer.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HH
