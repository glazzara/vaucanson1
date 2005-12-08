// predecls.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_DESIGN_PATTERN_PREDECLS_HH
# define VCSN_DESIGN_PATTERN_PREDECLS_HH

/** @addtogroup design_pattern *//** @{ */
/**
 * @file predecls.hh
 *
 * Forward declarations of the design pattern template classes of Vaucanson.
 */
/** @} */

# include <vaucanson/config/system.hh>

/// The main namespace of the Vaucanson library.
namespace vcsn {

  /** @addtogroup design_pattern *//** @{ */

  template<typename S>
  struct dynamic_traits;

  template<typename S, typename T>
  struct SyntacticDecorator;

  template<typename S, typename T>
  struct MetaElement;

  template<typename S, typename T>
  struct Element;

  struct default_slot_tag {};

  template<typename S, typename Tag = default_slot_tag>
  struct SetSlot;

  template<typename Self>
  struct Structure;

  template<typename Self>
  struct virtual_types;

  struct undefined_type {};


  /** @} */

} // vcsn

#endif // ! VCSN_DESIGN_PATTERN_PREDECLS_HH
