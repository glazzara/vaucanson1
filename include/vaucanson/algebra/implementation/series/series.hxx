// series.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_HXX

# include <vaucanson/algebra/implementation/series/series.hh>
# include <vaucanson/misc/unique.hh>

namespace vcsn {

  namespace algebra {

    /*------------------------.
    | Series<Semiring, Monoid> |
    `------------------------*/

    template<typename Semiring, typename Monoid>
    Series<Semiring, Monoid>::Series(const Semiring& w, const Monoid& m)
      : SetSlot<Semiring,semiring_slot_tag>(w),
	SetSlot<Monoid,monoid_slot_tag>(m)
    {}

    template<typename Semiring, typename Monoid>
    Series<Semiring, Monoid>::Series(const Series& other) :
      SeriesBase<Series<Semiring,Monoid> >(other),
      SetSlot<Semiring,semiring_slot_tag>(other),
      SetSlot<Monoid,monoid_slot_tag>(other)
    {}

    template<typename Semiring, typename Monoid>
    const Semiring& Series<Semiring, Monoid>::semiring() const
    {
      return static_cast<const SetSlot<Semiring,semiring_slot_tag>* >(this)->_structure_get();
    }

    template<typename Semiring, typename Monoid>
    const Monoid& Series<Semiring, Monoid>::monoid() const
    {
      return static_cast<const SetSlot<Monoid,monoid_slot_tag>* >(this)->_structure_get();
    }

    template<typename W, typename M>
    bool operator==(const Series<W, M>& s1,
		    const Series<W, M>& s2)
    {
      return & s1.monoid() == & s2.monoid() &&
	& s1.semiring() == & s2.semiring();
    }

    template <class W, class M, class NewW, class NewM>
    typename mute_series_traits<Series<W, M>, NewW, NewM >::ret
    mute_series(const Series<W, M>& s, const NewW& w, const NewM& m)
    {
      return mute_series_traits<Series<W, M>, NewW, NewM >::ret(w, m);
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_SERIES_HXX
