// series.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_HH

#include <vaucanson/algebra/concept/series_base.hh>
#include <vaucanson/design_pattern/slots.hh>


namespace vcsn {

  namespace algebra {

    /*-------------------------.
    | Series<Semiring, Monoid> |
    `-------------------------*/

    struct semiring_slot_tag {};
    struct monoid_slot_tag {};

    /// This is the final class for series.
    template<typename Semiring, typename Monoid>
    struct Series
      : SeriesBase<Series<Semiring, Monoid> >, 
	private SetSlot<Semiring, semiring_slot_tag>, 
	private SetSlot<Monoid, monoid_slot_tag>
    {
      Series(const Semiring& w, const Monoid& m);
      Series(const Series& other);

      const Semiring&	semiring() const;

      const Monoid&	monoid() const;

    };

    template<typename W, typename M>
    bool operator==(const Series<W, M>&,
		    const Series<W, M>&);


    template <class W, class M, class NewW, class NewM>
    struct mute_series_traits<Series<W, M>, NewW, NewM >
    {
      typedef Series<NewW, NewM> ret;
    };

    template <class W, class M, class NewW, class NewM>
    typename mute_series_traits<Series<W, M>, NewW, NewM >::ret
    mute_series(const Series<W, M>& s, const NewW& w, const NewM& m);

  } // algebra

  /*-----------------------------.
  | MetaElement<Series<W, M>, T> |
  `-----------------------------*/

  /// Specialization of MetaElement for series.
  template <class W, class M, class T>
  struct MetaElement<algebra::Series<W, M>, T> :
    public MetaElement<algebra::SeriesBase<algebra::Series<W, M> >, T>
  { };

  /*-----------------------------.
  | dynamic_traits<Series<W, M>> |
  `-----------------------------*/

  /// Dynamic traits for series.
  template<typename W, typename M>
  struct dynamic_traits<algebra::Series<W, M> >
    : dynamic_traits<algebra::SeriesBase<algebra::Series<W, M> > >
  {
    static const bool ret =
      dynamic_traits<W>::ret || dynamic_traits<M>::ret;

  };

  /*----------------------------.
  | virtual_types<Series<W, N>> |
  `----------------------------*/

  /// Virtual types for series.
  template<typename W, typename M>
  struct virtual_types<algebra::Series<W, M> >
    : virtual_types<algebra::SeriesBase<algebra::Series<W, M> > >
  {
    typedef algebra::mul_kind semigroup_kind;

    typedef W semiring_t;
    typedef M monoid_t;
  };

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algebra/implementation/series/series.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_HH
