// fundamental/op_traits.hh
//
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

#ifndef FUNDAMENTAL_OP_TRAITS_HH
# define FUNDAMENTAL_OP_TRAITS_HH

#include <vaucanson/fundamental/predefs.hh>

namespace vcsn {

  /*! \addtogroup fundamental
   *  \@{
   */

  /*--------------.
  | op_add_traits |
  `--------------*/
  //! The type of the result of addition between 2 Elements.
  /*! This is a trait to determine the result of addition between 2 Elements.
   */
  template<typename S1, typename S2, typename T1, typename T2>
  struct op_add_traits
  {
    typedef Element<S1, T1> ret_t;
  };
  
  /*--------------.
  | op_sub_traits |
  `--------------*/
  //! The type of the result of substraction between 2 Elements.
  /*! This is a trait to determine the result of substraction between
    2 Elements.
   */
  template<typename S1, typename S2, typename T1, typename T2>
  struct op_sub_traits
  {
    typedef Element<S1, T1> ret_t;
  };

  /*--------------.
  | op_mul_traits |
  `--------------*/
  //! The type of the result of multiplication between 2 Elements.
  /*! This is a trait to determine the result of multiplication
    between 2 Elements.
   */
  template<typename S1, typename S2, typename T1, typename T2>
  struct op_mul_traits
  {
    typedef Element<S1, T1> ret_t;
  };

  /*--------------.
  | op_div_traits |
  `--------------*/
  //! The type of the result of division between 2 Elements.
  /*! This is a trait to determine the result of division between 2 Elements.
   */
  template<typename S1, typename S2, typename T1, typename T2>
  struct op_div_traits
  {
    typedef Element<S1, T1> ret_t;
  };
  

  /*--------------.
  | op_mod_traits |
  `--------------*/
  //! The type of the result of modulo between 2 Elements.
  /*! This is a trait to determine the result of modulo between 2 Elements.
   */
  template<typename S1, typename S2, typename T1, typename T2>
  struct op_mod_traits
  {
    typedef Element<S1, T1> ret_t;
  };

} // vcsn

#endif // FUNDAMENTAL_OP_TRAITS_HH
