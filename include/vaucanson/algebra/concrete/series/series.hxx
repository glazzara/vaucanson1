// series.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_SERIES_HXX
# define VCSN_ALGEBRA_CONCRETE_SERIES_SERIES_HXX

# include <vaucanson/algebra/concrete/series/series.hh>
# include <vaucanson/misc/unique.hh>

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
      : weights_(utility::unique::get(w)), monoid_(utility::unique::get(m)) 
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

    template<typename W, typename M>
    bool operator==(const Series<W, M>& s1, 
		    const Series<W, M>& s2)
    {
      return s1.monoid() == s2.monoid() &&
	s1.weights() == s2.weights();
    }

    template <class W, class M, class NewW, class NewM>
    typename mute_series_traits<Series<W, M>, NewW, NewM >::ret
    mute_series(const Series<W, M>& s, const NewW& w, const NewM& m)
    {
      return mute_series_traits<Series<W, M>, NewW, NewM >::ret(w, m);
    }

  } // algebra

} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_SERIES_SERIES_HXX
