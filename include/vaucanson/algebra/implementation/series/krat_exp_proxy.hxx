// krat_exp_proxy.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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

#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PROXY_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PROXY_HXX

namespace vcsn {

  namespace algebra {

    template <class S, class T>
    krat_exp_proxy<S, T>::krat_exp_proxy(Element<S, T> exp) :
      self(exp)
    {
    }

    template <class S, class T>
    krat_exp_virtual&
    krat_exp_proxy<S, T>::operator=(krat_exp_virtual& exp)
    {
      self = (dynamic_cast<krat_exp_proxy<S, T>*> (&exp))->self;
      return *this;
    }

    template <class S, class T>
    krat_exp_virtual*
    krat_exp_proxy<S, T>::operator+(krat_exp_virtual* exp)
    {
      return new krat_exp_proxy<S, T>(self + (dynamic_cast<krat_exp_proxy<S, T>*> (exp))->self);
    }

    template <class S, class T>
    krat_exp_virtual*
    krat_exp_proxy<S, T>::operator*(krat_exp_virtual* exp)
    {
      return new krat_exp_proxy<S, T>(self * (dynamic_cast<krat_exp_proxy<S, T>*> (exp))->self);
    }

    template <class S, class T>
    void
    krat_exp_proxy<S, T>::star()
    {
      self.star();
    }

    template <class S, class T>
    void
    krat_exp_proxy<S, T>::left_weight(semiring_virtual* sem)
    {
      self = (dynamic_cast<semiring_proxy<S, T>*> (sem))->self * self;
    }

    template <class S, class T>
    void
    krat_exp_proxy<S, T>::right_weight(semiring_virtual* sem)
    {
      self = self * (dynamic_cast<semiring_proxy<S, T>*> (sem))->self;
    }

    template <class S, class T>
    semiring_proxy<S, T>::semiring_proxy(semiring_elt_t& sem) :
      self(sem)
    {
    }

    template <class S, class T>
    semiring_virtual&
    semiring_proxy<S, T>::operator=(semiring_virtual& sem)
    {
      self = (dynamic_cast<semiring_proxy<S, T>*> (&sem))->self;
      return *this;
    }

  } // algebra

} // vcsn
#endif // !VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PROXY_HXX //
