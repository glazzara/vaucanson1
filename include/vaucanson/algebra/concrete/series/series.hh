// series.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_SERIES_HH
# define VCSN_ALGEBRA_CONCRETE_SERIES_SERIES_HH

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
  struct MetaElement<algebra::Series<W, M>, T> :
    public MetaElement<algebra::SeriesBase<algebra::Series<W, M> >, T>
  { };

    /*-----------------------------.
    | dynamic_traits<Series<W, M>> |
    `-----------------------------*/

  template<typename W, typename M>
  struct dynamic_traits<algebra::Series<W, M> >
    : dynamic_traits<algebra::SeriesBase<algebra::Series<W, M> > >
  {
    static const bool ret = 
      dynamic_traits<W>::ret || dynamic_traits<M>::ret;
    
  };
  
  template<typename W, typename M>
  struct virtual_types<algebra::Series<W, M> >
    : virtual_types<algebra::SeriesBase<algebra::Series<W, M> > >
  {
    typedef algebra::mul_kind semigroup_kind;
    
    typedef W weights_t;
    typedef M monoid_t;
  };
  
} // vcsn

template<typename W, typename M>
bool operator==(const vcsn::algebra::Series<W, M>&, const vcsn::algebra::Series<W, M>&);

# include <vaucanson/algebra/concrete/series/series.hxx>

#endif // VCSN_ALGEBRA_CONCRETE_SERIES_SERIES_HH
