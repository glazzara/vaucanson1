/************************************
 * <vaucanson/fundamental/op_traits.hh> *
 ************************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef FUNDAMENTAL_OP_TRAITS_HH
# define FUNDAMENTAL_OP_TRAITS_HH

# include <vaucanson/fundamental/predefs.hh>

namespace vcsn {

    template<typename S1, typename S2, typename T1, typename T2>
    struct op_add_traits
    {
      typedef Element<S1, T1> ret_t;
    };

    template<typename S1, typename S2, typename T1, typename T2>
    struct op_sub_traits
    {
      typedef Element<S1, T1> ret_t;
    };

    template<typename S1, typename S2, typename T1, typename T2>
    struct op_mul_traits
    {
      typedef Element<S1, T1> ret_t;
    };

    template<typename S1, typename S2, typename T1, typename T2>
    struct op_div_traits
    {
      typedef Element<S1, T1> ret_t;
    };

    template<typename S1, typename S2, typename T1, typename T2>
    struct op_mod_traits
    {
      typedef Element<S1, T1> ret_t;
    };

} // vcsn

#endif // FUNDAMENTAL_OP_TRAITS_HH
