// transpose.hh
//
// $Id$
// VCSN_HEADER
#ifndef ALGEBRA_SERIES_TRANSPOSE_HH
# define ALGEBRA_SERIES_TRANSPOSE_HH

namespace vcsn {

  namespace algebra {

    template <class S, class T>
    struct DefaultTransposeFun
    {
      T operator()(const S&, const T& T) const;
    };

  } // algebra

} // vcsn

# include <vaucanson/algebra/concrete/series/transpose.hxx>

#endif // ALGEBRA_SERIES_CONCRETE_TRANPOSE_HH
