// finite_support_conversion.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_FINITE_SUPPORT_CONVERSION_HH
# define VCSN_ALGORITHMS_FINITE_SUPPORT_CONVERSION_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file finite_support_conversion.hh
 *
 * Conversion between finite support application types.
 *
 * This file  contains a generic  algorithm to convert  finite support
 * applications from one type to another.
 *
 * @see finite_support_convert()
 */
/** @} */

// INTERFACE: void finite_support_convert(Exp& dst, const Series& org) { return vcsn::finite_support_convert(dst, org); }
// INTERFACE: void finite_support_convert(Series& dst, const Exp& org) { return vcsn::finite_support_convert(dst, org); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn
{

  /** @addtogroup algorithms *//** @{ */

  /**
   * Finite support conversion.
   *
   * This algorithm  copies the value of a  finite support application
   * to another, possibly changing its type.
   *
   * @param org The source application to convert.
   * @param dst The destination application.
   */
  template<typename S, typename T, typename Ss, typename Ts>
  void
  finite_support_convert(Element<S, T>& dst, const Element<Ss, Ts>& org);

  /** @} */

}

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/finite_support_conversion.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_FINITE_SUPPORT_CONVERSION_HH
