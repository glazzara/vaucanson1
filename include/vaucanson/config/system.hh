// system.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_CONFIG_SYSTEM_HH
# define VCSN_CONFIG_SYSTEM_HH

/** @addtogroup conf System configuration *//** @{ */
/**
 * @file system.hh
 * @brief System-wide configuration helpers
 *
 * This file contains global configuration checks for the Vaucanson
 * library. 
 * 
 * In especially includes @c config.h if the @c HAVE_CONFIG_H is
 * defined, and attempts to force G++ v2.95 to use namespaces in the
 * STL definitions.
 *
 * @see @c math.hh
 */
/** @} */

# ifdef HAVE_CONFIG_H
#  include <config.h>
# endif 

#ifdef HAVE_PRETTY_FUNCTION
# define PRETTY_FUNCTION() __PRETTY_FUNCTION__
#else
# define PRETTY_FUNCTION() static_cast<const char*>(0)
#endif

# ifndef IGNORE_PCONF_HH
#  include <vaucanson/config/pconf.hh>
# endif

# include <vaucanson/config/math.hh>

#if (defined __GNUC__) && (__GNUC__ < 3) 
# include <stl_config.h>
#  undef __STL_BEGIN_RELOPS_NAMESPACE
#  define __STL_BEGIN_RELOPS_NAMESPACE namespace rel_ops {
#  undef __STL_END_RELOPS_NAMESPACE
#  define __STL_END_RELOPS_NAMESPACE }
#  define __STL_USE_NAMESPACES
#endif

// FIXME: these should be tested

# if (defined __GNUC__)
#  define XUNUSED(X) X __attribute__ ((__unused__))
# else
#  define XUNUSED(X) /* unused */
# endif

#endif // VCSN_CONFIG_SYSTEM_HH
