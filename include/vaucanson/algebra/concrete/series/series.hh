// series.hh
//
// VCSN_HEADER

#ifndef ALGEBRA_SERIES_HH
# define ALGEBRA_SERIES_HH

#include <vaucanson/algebra/concept/series_base.hh>

namespace vcsn {

  namespace algebra {

    /*------------------------.
    | Series<Weights, Monoid> |
    `------------------------*/

    template<typename Weights, typename Monoid>
    struct Series
      : SeriesBase<Series<Weights, Monoid> >
    {
      Series();
      Series(const Weights& w, const Monoid& m);
      Series(const Series& other);

      Weights&		weights();
      const Weights&	weights() const;

      Monoid&		monoid();
      const Monoid&	monoid() const;

    protected:
      Weights		weights_;
      Monoid		monoid_;
    };    

  }

  /*-----------------------------.
  | MetaElement<Series<W, M>, T> |
  `-----------------------------*/
  
  template <class W, class M, class T>
  struct MetaElement<Series<W, M>, T> :
    public MetaElement<SeriesBase<Series<W, M> >, T>
  {};

    /*----------------------.
    | MetaSet<Series<W, M>> |
    `----------------------*/

    template<typename W, typename M>
    struct MetaSet<Series<W, M> >
    {
      typedef algebra::mul_kind semigroup_kind;

      static const bool dynamic_set = 
      MetaSet<W>::dynamic_set || MetaSet<M>::dynamic_set;
		       
    };

  namespace traits {

    template<typename W, typename M>
    struct virtual_types<algebra::Series<W, M> >
    {
      typedef W weights_t;
      typedef M monoid_t;
    };

  } // traits

} // vcsn

# include <vaucanson/algebra/concrete/series/series.hxx>

#endif
