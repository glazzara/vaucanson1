// series.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_SERIES_HH
# define VCSN_ALGEBRA_CONCRETE_SERIES_SERIES_HH

#include <vaucanson/algebra/concept/series_base.hh>
#include <vaucanson/fundamental/slots.hh>


namespace vcsn {

  namespace algebra {

    /*------------------------.
    | Series<Semiring, Monoid> |
    `------------------------*/

    template<typename Semiring, typename Monoid>
    struct Series
      : SeriesBase<Series<Semiring, Monoid> >
    {
      Series(const Semiring& w, const Monoid& m);
      Series(const Series& other);

      const Semiring&	semiring() const;

      const Monoid&	monoid() const;

    protected:
      SetSlot<Semiring>  semiring_;
      SetSlot<Monoid>	monoid_;
    };    

    template<typename W, typename M>
    bool operator==(const Series<W, M>&, 
		    const Series<W, M>&);
    

    template <class W, class M, class NewW, class NewM>
    struct mute_series_traits<Series<W, M>, NewW, NewM >
    {
      typedef Series<NewW, NewM> ret;
    };

    template <class W, class M, class NewW, class NewM>
    typename mute_series_traits<Series<W, M>, NewW, NewM >::ret
    mute_series(const Series<W, M>& s, const NewW& w, const NewM& m);

  } // algebra

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
    
    typedef W semiring_t;
    typedef M monoid_t;
  };
  
} // vcsn

# include <vaucanson/algebra/concrete/series/series.hxx>

#endif // VCSN_ALGEBRA_CONCRETE_SERIES_SERIES_HH
