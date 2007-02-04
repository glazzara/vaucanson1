// meta_element_root.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_DESIGN_PATTERN_META_ELEMENT_ROOT_HH
# define VCSN_DESIGN_PATTERN_META_ELEMENT_ROOT_HH

/** @addtogroup design_pattern *//** @{ */
/**
 * @file meta_element_root.hh
 *
 * @brief Definition of the specialization of @c MetaElement for the root
 *        @c Structure.
 */
/** @} */

# include <vaucanson/design_pattern/structure.hh>
# include <vaucanson/design_pattern/syntactic_decorator.hh>

namespace vcsn {

  /** @addtogroup design_pattern *//** @{ */

  /*--------------------------------.
  | Documentation about MetaElement |
  `--------------------------------*/

  /**
   * @class MetaElement
   *
   * Parent class of Element.
   *
   * MetaElement provides most of the services of Element. It has three
   * roles:
   *
   * - specify the interface of @c Element<S, T>,
   * - offer additional abstract services implemented using only services
   *   in the specified interfaces,
   * - link services to their external implementations.
   *
   * Of course this class must be specialized over S and T, and no generic
   * implementation is provided.
   *
   * For additional genericity,  the hierarchy between concepts should
   * be mapped  to a hierarchy  of between their specialization  of
   * @c MetaElement.
   *
   * @see
   *  - @c Element
   *  - @ref meta_element_structure_t "MetaElement\< Structure\<S\>, T\>"
   */

  /*--------------------------------.
  | MetaElement<Structure<Self>, T> |
  `--------------------------------*/

  /**
   * The base class that glues structural elements to implementation values.
   *
   * @c MetaElement<Structure<Self>, T> is the specialization that is at
   * the top of all the hierarchy of Vaucanson. It inherits, and thus
   * is decorated with, @c SyntacticDecorator<Self, T>.
   *
   * @see
   *     - @c SyntacticDecorator
   *     - @c MetaElement
   *     - @c Element
   *     - @c Structure
   *
   * @anchor meta_element_structure_t
   */

  template<class S, typename T>
  struct MetaElement<Structure<S>, T>
    : SyntacticDecorator<S, T>
  {
  protected:
    //@{
    /// Protected constructor for class abstraction.
    MetaElement();
    MetaElement(const MetaElement& other);
    //@}
  };

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/design_pattern/meta_element_root.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_DESIGN_PATTERN_META_ELEMENT_ROOT_HH
