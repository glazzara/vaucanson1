// krat_exp_realtime.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_REALTIME_HH
# define VCSN_ALGORITHMS_KRAT_EXP_REALTIME_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file krat_exp_realtime.hh
 *
 * Declarations of the realtime() algorithm for rational expressions.
 *
 * @see realtime()
 */
/** @} */

// INTERFACE: Exp realtime(const Exp& e) { return vcsn::realtime(e); }

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/krat_exp_realtime.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

/*
 * Include the declaration of realtime().
 *
 * Must  be  included _after_  the  .hxx  file  because it  needs  the
 * declarations of do_realtime_here() and do_realtime().
 */
# include <vaucanson/algorithms/realtime_decl.hh>

#endif // ! VCSN_ALGORITHMS_KRAT_EXP_REALTIME_HH
