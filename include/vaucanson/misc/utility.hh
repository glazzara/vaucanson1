// utility.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
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
