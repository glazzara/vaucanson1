// transducer.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HH
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/transducer_base.hh>

namespace vcsn {

  template <class Series>
  struct Transducer;

  /// Dynamic traits for transducers.
  template <class Series>
  struct dynamic_traits<Transducer<Series> >
  {
    static const bool ret = dynamic_traits<Series>::ret;
  };

  /// Specialization of MetaElement for transducers.
  template <class Series, typename T>
  struct MetaElement<Transducer<Series>, T>
    : MetaElement<TransducerBase<Transducer<Series> >, T>
  {};

  /// Virtual types for transducers.
  template <class Series>
  struct virtual_types<Transducer<Series> >
  {
    typedef Series		series_set_t;
  };

  /// This is the final class for the set of transducers.
  template <class Series>
  class Transducer
    : public TransducerBase<Transducer<Series> >
  {
  public:
    typedef Transducer<Series>				     self_t;
    typedef typename virtual_types<self_t>::series_set_t	     series_set_t;

    Transducer(const series_set_t&);

    const series_set_t&	series() const;

  private:
    series_set_t	series_;
  };

  template <class S, class T>
  struct output_projection_helper
  {
    typedef typename S::series_set_t::semiring_t
    typeof_auto_series_set_t;
    typedef typename S::series_set_t::monoid_t              auto_monoid_t;
    typedef typename typeof_auto_series_set_t::semiring_t           auto_semiring_t;
    typedef typename algebra::mute_series_traits<typeof_auto_series_set_t,
						 auto_semiring_t,
						 auto_monoid_t>::ret
    auto_series_set_t;

    typedef typename output_projection_traits<T>::ret          auto_impl_t;
    typedef Element<Automata<auto_series_set_t>,
		    auto_impl_t>      ret;
  };

  template <class S, class T>
  struct identity_transducer_helper
  {
    typedef typename S::series_set_t	 series_set_t;
    typedef typename series_set_t::monoid_t  monoid_t;
    typedef typename series_set_t::semiring_t semiring_t;
    typedef typename algebra::mute_series_traits<series_set_t, series_set_t, monoid_t>
    ::ret    tseries_set_t;
    typedef typename extension_traits<T>::ret impl_t;
    typedef Element<Transducer<tseries_set_t>, impl_t> ret;
  };

  template <class S, class T>
  typename identity_transducer_helper<S, T>::ret
  partial_identity(const Element<S, T>&);

  template <class Series>
  bool
  operator==(const Transducer<Series>&, const Transducer<Series>&);

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/automata/concept/transducer.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HH
