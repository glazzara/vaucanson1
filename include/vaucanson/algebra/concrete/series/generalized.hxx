// generalized.hxx
//
// $Id$
// VCSN_HEADER
#ifndef VAUCANSON_ALGEBRA_CONCRETE_GENERALIZED_HXX
# define VAUCANSON_ALGEBRA_CONCRETE_GENERALIZED_HXX

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
				const polynom<Tm, Tw>& p_value)
    {
      typedef rat::exp<Tm, Tw> kexp_t;
      kexp_t	exp;

      if (p_value == identity_value(SELECT2(Series<W, M>), 
				    SELECT2(polynom<Tm, Tw>)))
	return kexp_t::one();
      
      if (p_value == zero_value(SELECT2(Series<W, M>), 
				SELECT2(polynom<Tm, Tw>)))
	return kexp_t::zero();

      for (typename polynom<Tm, Tw>::const_iterator p = p_value.begin();
	   p != p_value.end();
	   ++p)
	if (exp == kexp_t::zero())
	  exp = (*p).second *  kexp_t::constant((*p).first);
	else
	  exp += (*p).second *  kexp_t::constant((*p).first);
      return exp;
    }

  } // algebra

} // vcsn

#endif // VAUCANSON_ALGEBRA_CONCRETE_GENERALIZED_HXX
