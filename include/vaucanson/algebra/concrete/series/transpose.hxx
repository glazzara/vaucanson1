// transpose.hxx
//
// $Id$
// VCSN_HEADER
#ifndef ALGEBRA_CONCRETE_SERIES_TRANSPOSE_HXX
# define ALGEBRA_CONCRETE_SERIES_TRANSPOSE_HXX

namespace vcsn {

  namespace algebra {

    template <class S, class T>
    T 
    DefaultTransposeFun<S, T>::operator()(const S&, const T& label) const
    {
      assert(!"Default transposition is not defined.");
    }

  } // algebra

} // vcsn

# include <vaucanson/algebra/concrete/series/transpose.hxx>

#endif // ALGEBRA_SERIES_CONCRETE_TRANSPOSE_HH
