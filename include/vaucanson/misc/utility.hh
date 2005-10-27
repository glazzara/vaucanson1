// utility.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_UTILITY_HH
# define VCSN_MISC_UTILITY_HH

/** @addtogroup utility Utility constructs for Vaucanson *//** @{ */

/**
 * The namespace for utility constructs.
 *
 * This namespace holds all C++ constructs that are used by Vaucanson
 * but are not Vaucanson-specific.
 */
namespace utility {}

/**
 * @file selectors.hh
 * Definition of type argument macros.
 */
#include <vaucanson/misc/selectors.hh>

/**
 * @file unique.hh
 * Declarations for the type canonicalization tools.
 */
#include <vaucanson/misc/unique.hh>

/**
 * @file misc/static.hh
 * Definition of metaprogrammation helpers.
 */
#include <vaucanson/misc/static.hh>

/**
 * @file random.hh
 * Definition of random generators.
 */
#include <vaucanson/misc/random.hh>

/**
 * @file contract.hh
 * Definition of contract macros.
 */
#include <vaucanson/misc/contract.hh>

/**
 * @file limits.hh
 *
 * Wrapper about the numeric limits for Vaucanson
 *
 * This file defines the utility trait @c vcsn::limits, by using
 * standard C++ @c std::numeric_limits if available, or the
 * standard C limits if @c USE_C_LIMITS is defined.
 */
#include <vaucanson/misc/limits.hh>

/** @} */

#endif // ! VCSN_MISC_UTILITY_HH
