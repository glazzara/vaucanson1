<<<<<<< .working
// transducer.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey 
// and Regis-Gianas.
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

#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HH
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HH

# include <vaucanson/automata/concept/transducer_base.hh>

namespace vcsn {

  template <class Series>
  struct Transducer;
  
   template <class Series>
   struct dynamic_traits<Transducer<Series> >
   {
     static const bool ret = dynamic_traits<Series>::ret;    
   };
 
  template <class Series, typename T>
  struct MetaElement<Transducer<Series>, T>
    : MetaElement<TransducerBase<Transducer<Series> >, T>
  {};

  template <class Series>
  struct virtual_types<Transducer<Series> >
  {
    typedef Series		series_t;
  };
    
  template <class Series>
  class Transducer
    : public TransducerBase<Transducer<Series> >
  {
  public:
    typedef Transducer<Series>				     self_t;
    typedef typename virtual_types<self_t>::series_t	     series_t;

    Transducer(const series_t&);

    const series_t&	series() const;

  private:
    series_t	series_;
  };

  template <class S, class T>
  struct identity_transducer_helper
  {
    typedef typename S::series_t	 series_t;
    typedef typename series_t::monoid_t  monoid_t;
    typedef typename series_t::weights_t weights_t;
    typedef typename algebra::mute_series_traits<series_t, series_t, monoid_t>
    ::ret    tseries_t;
    typedef typename extension_traits<T>::ret impl_t;
    typedef Element<Transducer<tseries_t>, impl_t> ret;
  };

  template <class S, class T>
  typename identity_transducer_helper<S, T>::ret
  partial_identity(const Element<S, T>&);

} // vcsn

# include <vaucanson/automata/concept/transducer.hxx>

#endif // VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HH
=======
// transducer.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey 
// and Regis-Gianas.
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

#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HH
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HH

# include <vaucanson/automata/concept/transducer_base.hh>

namespace vcsn {

  template <class Series>
  struct Transducer;
  
  template <class Series>
  struct MetaSet<Transducer<Series> >
  {
    static const bool dynamic_set = MetaSet<Series>::dynamic_set;    
  };
  
  template <class Series, typename T>
  struct MetaElement<Transducer<Series>, T>
    : MetaElement<TransducerBase<Transducer<Series> >, T>
  {};

  namespace traits {
    
    template <class Series>
    struct virtual_types<Transducer<Series> >
    {
      typedef Series		series_t;
    };
    
  } // traits.


  template <class Series>
  class Transducer
    : public TransducerBase<Transducer<Series> >
  {
  public:
    typedef Transducer<Series>				     self_t;
    typedef typename traits::virtual_types<self_t>::series_t series_t;

    Transducer(const series_t&);

    const series_t&	series() const;

  private:
    series_t	series_;
  };

  template <class S, class T>
  struct identity_transducer_helper
  {
    typedef typename S::series_t	 series_t;
    typedef typename series_t::monoid_t  monoid_t;
    typedef typename series_t::weights_t weights_t;
    typedef typename mute_series_traits<series_t, series_t, monoid_t>::ret
    tseries_t;
    typedef typename extension_traits<T>::ret impl_t;
    typedef Element<Transducer<tseries_t>, impl_t> ret;
  };

  template <class S, class T>
  typename identity_transducer_helper<S, T>::ret
  partial_identity(const Element<S, T>&);

} // vcsn

# include <vaucanson/automata/concept/transducer.hxx>

#endif // VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HH
>>>>>>> .merge-right.r315
