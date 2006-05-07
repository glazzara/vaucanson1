// system.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_CONFIG_SYSTEM_HH
# define VCSN_CONFIG_SYSTEM_HH

/** @addtogroup conf System configuration *//** @{ */
/**
 * @file system.hh
 * @brief System-wide configuration helpers
 *
 * Global configuration checks for the Vaucanson library.
 *
 * It especially attempts to force G++ v2.95 to use namespaces in the
 * STL definitions.
 *
 * @see @c math.hh
 */
/** @} */

# ifdef HAVE_PRETTY_FUNCTION
#  define PRETTY_FUNCTION() __PRETTY_FUNCTION__
# else
#  define PRETTY_FUNCTION() static_cast<const char*>(0)
# endif

# ifndef VCSN_INTERNAL_IGNORE_PCONF_HH
#  include <vaucanson/config/pconf.hh>
# endif

# include <vaucanson/config/math.hh>

# if (defined __GNUC__) && (__GNUC__ < 3)
# include <stl_config.h>
#  undef __STL_BEGIN_RELOPS_NAMESPACE
#  define __STL_BEGIN_RELOPS_NAMESPACE namespace rel_ops {
#  undef __STL_END_RELOPS_NAMESPACE
#  define __STL_END_RELOPS_NAMESPACE }
#  define __STL_USE_NAMESPACES
# endif

// Set VCSN_NDEBUG if NDEBUG is defined.
# ifdef NDEBUG
#  define VCSN_NDEBUG 1
# endif

// FIXME: these should be tested

# if (defined __GNUC__)
#  define XUNUSED(X) X __attribute__ ((__unused__))
# else
#  define XUNUSED(X) /* unused */
# endif

#endif // ! VCSN_CONFIG_SYSTEM_HH
