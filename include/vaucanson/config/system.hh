// system.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_CONFIG_SYSTEM_HH
# define VCSN_CONFIG_SYSTEM_HH

# define _ISOC99_SOURCE 1
# include <vaucanson/config/pconf.hh>
#ifdef HAVE_LIMITS
#define USE_CXX_LIMITS
#undef HAVE_LIMITS
#endif

# include <cmath>

#if (defined __GNUC__) && (__GNUC__ < 3) 
# include <stl_config.h>
#  undef __STL_BEGIN_RELOPS_NAMESPACE
#  define __STL_BEGIN_RELOPS_NAMESPACE namespace rel_ops {
#  undef __STL_END_RELOPS_NAMESPACE
#  define __STL_END_RELOPS_NAMESPACE }
#  define __STL_USE_NAMESPACES
# include <vaucanson/config/rel_ops_work_around_g++2.hh>
#endif

#endif // VCSN_CONFIG_SYSTEM_HH
