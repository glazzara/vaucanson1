// generalized.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//    * Michael Cadilhac <michael.cadilhac@lrde.epita.fr>
//
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_GENERALIZED_HH
# define VCSN_AUTOMATA_IMPLEMENTATION_GENERALIZED_HH

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/automata/concept/copy.hh>
# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/implementation/series/generalized.hh>
# include <vaucanson/algebra/implementation/series/rat/exp.hh>
# include <vaucanson/algebra/implementation/series/krat.hh>
# ifdef VCSN_FAST
#  include <vaucanson/automata/implementation/graph_fast.hh>
# else // VCSN_FAST
#  include <vaucanson/automata/implementation/graph.hh>
# endif // ! VCSN_FAST
# include <map>


namespace vcsn {

  /*----------------------.
  | Generalized automaton |
  `----------------------*/
  template <class Auto_>
  struct generalized_traits
  {
    // FIXME: static check on the concept of automaton
    typedef typename Auto_::series_set_t		series_set_t;
    typedef typename series_set_t::monoid_t		monoid_t;
    typedef typename Auto_::series_set_elt_t		series_set_elt_t;
    typedef typename series_set_elt_t::monoid_elt_t	monoid_elt_t;
    typedef typename monoid_elt_t::value_t		monoid_elt_value_t;
    typedef typename series_set_elt_t::semiring_elt_t	semiring_elt_t;
    typedef typename semiring_elt_t::value_t		semiring_elt_value_t;

    typedef vcsn::Element
    <vcsn::Automata<series_set_t>,
     Graph<labels_are_series,
	   monoid_elt_value_t,
	   semiring_elt_value_t,
	   rat::exp<monoid_elt_value_t, semiring_elt_value_t>,
	   typename monoid_t::letter_t,
	   NoTag>
    > automaton_t;
  };


  template <class Auto_>
  typename generalized_traits<Auto_>::automaton_t
  generalized(const Auto_& from);

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/automata/implementation/generalized.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_GENERALIZED_HH
