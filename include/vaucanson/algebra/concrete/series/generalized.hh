// generalized.hh
//
// $Id$
// VCSN_HEADER
#ifndef VAUCANSON_ALGEBRA_CONCRETE_SERIES_GENERALIZED_HH
# define VAUCANSON_ALGEBRA_CONCRETE_SERIES_GENERALIZED_HH

# include <vaucanson/algebra/concept/algebra_base.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/concrete/series/polynoms.hh>
# include <vaucanson/algebra/concrete/series/krat.hh>

namespace vcsn {

  namespace algebra {
    
    /*----------------------.
    | Generalized converter |
    `----------------------*/
    template<typename Tm, typename Tw, typename W, typename M>
    rat::exp<Tm, Tw> op_convert(SELECTOR2(rat::exp<Tm, Tw>),
				SELECTOR2(Series<W, M>),
				const polynom<Tm, Tw>& p_value);


  } // algebra

} // vcsn

# include <vaucanson/algebra/concrete/series/generalized.hxx>

#endif // VAUCANSON_ALGEBRA_CONCRETE_SERIES_GENERALIZED_HH
