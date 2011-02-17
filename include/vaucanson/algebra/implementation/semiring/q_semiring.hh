// q_semiring.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2007, 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_SEMIRING_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_SEMIRING_HH

# include <vaucanson/algebra/concept/q_semiring.hh>

namespace vcsn {

  namespace algebra {

    RationalNumber indentity_value ();

    bool show_identuty_value ();

    RationalNumber zero_value ();

    bool op_contains ();
    // Mul
    void op_in_mul ();

    RationalNumber op_mul ();

    // Add
    void op_in_add ();

    RationalNumber op_add ();

    // Start ***
    bool op_starable ();

    void op_in_start ();

    ??? op_choose ();

    bool op_can_choose_non_starable ();

    // Pretty printer
    op_rout ();


  } // algebra

} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/semiring/q_semiring.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SEMIRING_Q_SEMIRING_HH
