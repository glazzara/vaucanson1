// series.hxx
//
// VCSN_HEADER

#ifndef ALGEBRA_SERIES_HXX
# define ALGEBRA_SERIES_HXX

# include <vaucanson/algebra/concrete/series/series.hh>

namespace vcsn {

  namespace algebra {

    /*------------------------.
    | Series<Weights, Monoid> |
    `------------------------*/
    
    template<typename Weights, typename Monoid>
    Series<Weights, Monoid>::Series() : weights_(), monoid_() 
    {}
    
    template<typename Weights, typename Monoid>
    Series<Weights, Monoid>::Series(const Weights& w, const Monoid& m)
      : weights_(w), monoid_(m) 
    {}
    
    template<typename Weights, typename Monoid>
    Series<Weights, Monoid>::Series(const Series& other) : 
      SeriesBase<Series<Weights,Monoid> >(other),
      weights_(other.weights_), 
      monoid_(other.monoid_)
    {}
    
    template<typename Weights, typename Monoid>
    Weights& Series<Weights, Monoid>::weights()
    { 
      return weights_; 
    }
    
    template<typename Weights, typename Monoid>
    const Weights& Series<Weights, Monoid>::weights() const
    { 
      return weights_; 
    }
    
    template<typename Weights, typename Monoid>
    Monoid& Series<Weights, Monoid>::monoid()
    { 
      return monoid_; 
    }
    
    template<typename Weights, typename Monoid>
    const Monoid& Series<Weights, Monoid>::monoid() const
    { 
      return monoid_; 
    }

  } // algebra

} // vcsn

#endif
