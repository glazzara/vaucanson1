// element_op_traits.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_DESIGN_PATTERN_ELEMENT_OP_TRAITS_HH
# define VCSN_DESIGN_PATTERN_ELEMENT_OP_TRAITS_HH

/** @addtogroup design_pattern *//** @{ */
/** @addtogroup operators *//** @{ */
/**
 * @file element_op_traits.hh
 * @brief Declaration of default arithmetical operator traits for @c Element
 */
/** @} */
/** @} */

#include <vaucanson/design_pattern/predecls.hh>

namespace vcsn {

  /** @addtogroup design_pattern *//** @{ */
  /** @addtogroup operators *//** @{ */

  /*--------------.
  | op_add_traits |
  `--------------*/

  /** The type of the result of addition between two Element instances.
   * By default, the result type is the type of the first argument.
   */
  template<typename S1, typename S2, typename T1, typename T2>
  struct op_add_traits
  {
    typedef Element<S1, T1> ret_t;
  };

  /*--------------.
  | op_sub_traits |
  `--------------*/

  /** The type of the result of substraction between two Element instances.
   * By default, the result type is the type of the first argument.
   */
  template<typename S1, typename S2, typename T1, typename T2>
  struct op_sub_traits
  {
    typedef Element<S1, T1> ret_t;
  };

  /*--------------.
  | op_mul_traits |
  `--------------*/

  /** The type of the result of multiplication between two Element instances.
   * By default, the result type is the type of the first argument.
   */
  template<typename S1, typename S2, typename T1, typename T2>
  struct op_mul_traits
  {
    typedef Element<S1, T1> ret_t;
  };

  /*--------------.
  | op_div_traits |
  `--------------*/

  /** The type of the result of division between two Element instances.
   * By default, the result type is the type of the first argument.
   */
  template<typename S1, typename S2, typename T1, typename T2>
  struct op_div_traits
  {
    typedef Element<S1, T1> ret_t;
  };


  /*--------------.
  | op_mod_traits |
  `--------------*/

  /** The type of the result of modulus between two Element instances.
   * By default, the result type is the type of the first argument.
   */
  template<typename S1, typename S2, typename T1, typename T2>
  struct op_mod_traits
  {
    typedef Element<S1, T1> ret_t;
  };

  /** @} */
  /** @} */

} // vcsn

#endif // ! VCSN_DESIGN_PATTERN_ELEMENT_OP_TRAITS_HH
