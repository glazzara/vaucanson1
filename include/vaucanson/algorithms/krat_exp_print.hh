// krat_exp_print.hh


#ifndef VCSN_ALGORITHMS_KRAT_EXP_PRINT_HH
# define VCSN_ALGORITHMS_KRAT_EXP_PRINT_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file krat_exp_print.hh
 *
 * This file contains the declarations for the krat_exp_print() algorithm.
 *
 * @see krat_exp_print()
 */
/** @} */

#include <vaucanson/algebra/concrete/series/rat/exp.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// Print a krat expression under several formats.
  template<typename Letter, typename Weight>
  void krat_exp_print(const rat::exp<Letter, Weight>& kexp,
		      const unsigned& mode = 0);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/krat_exp_print.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGORITHMS_KRAT_EXP_PRINT_HH
