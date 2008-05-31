// krat_exp_proxy.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PROXY_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PROXY_HH
# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup series *//** @{ */
    /**
    ** @interface semiring_virtual
    ** @brief Virtual pure class used by bison to deal with vaucanson's
    **	      templated structures
    */
    struct semiring_virtual
    {
      virtual semiring_virtual& operator=(semiring_virtual& sem) = 0;
      virtual ~semiring_virtual() {}
    };

    /**
    ** @interface krat_exp_virtual
    ** @brief Virtual pure class used by bison to deal with vaucanson's
    **	      templated structures
    */
    struct krat_exp_virtual
    {
      /* Virtual fonctions used in the parser */
      virtual krat_exp_virtual& operator=(krat_exp_virtual& exp) = 0;
      virtual krat_exp_virtual* operator+(krat_exp_virtual* exp) = 0;
      virtual krat_exp_virtual* operator*(krat_exp_virtual* exp) = 0;
      virtual void star() = 0;
      virtual void left_weight(semiring_virtual* sem) = 0;
      virtual void right_weight(semiring_virtual* sem) = 0;
      virtual ~krat_exp_virtual() {}
    };

    /**
    ** @struct krat_exp_proxy
    ** @brief Proxy over Vaucanson Element
    */
   template <class S, class T>
    struct krat_exp_proxy : public krat_exp_virtual
    {
      typedef typename Element<S, T>::monoid_elt_t monoid_elt_t;

      // Constructors && Destructor
      krat_exp_proxy(Element<S, T> exp);
      ~krat_exp_proxy() {}

      krat_exp_virtual& operator=(krat_exp_virtual& exp);
      krat_exp_virtual* operator+(krat_exp_virtual* exp);
      krat_exp_virtual* operator*(krat_exp_virtual* exp);
      void star();
      void left_weight(semiring_virtual* sem);
      void right_weight(semiring_virtual* sem);

      // Attibutes
      Element<S, T> self;
    };

    /**
    ** @struct semiring_proxy
    ** @brief Proxy over Vaucanson Semiring
    */
    template <class S, class T>
    struct semiring_proxy : public semiring_virtual
    {
      typedef typename Element<S, T>::semiring_elt_t semiring_elt_t;

      //Constructor && Destructor
      semiring_proxy(semiring_elt_t& sem);
      ~semiring_proxy() {}

      semiring_virtual& operator=(semiring_virtual& sem);

      // Attibutes
      semiring_elt_t self;
    };

    /** @} */
    /** @} */
  } // algebra

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/series/krat_exp_proxy.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PROXY_HH //
