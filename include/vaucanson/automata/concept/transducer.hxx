<<<<<<< .working
<<<<<<< .working
<<<<<<< .working
// transducer.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HXX
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HXX

#include <vaucanson/automata/concept/transducer_base.hh>

namespace vcsn {

  template <class Series>
  Transducer<Series>::Transducer(const series_t& s):
    series_(s)
  {}

  template <class Series>
  const typename Transducer<Series>::series_t&
  Transducer<Series>::series() const
  {
    return series_;
  }

  template <class S, class T>
  inline
  typename identity_transducer_helper<S, T>::ret
  partial_identity(const Element<S, T>& a)
  {
    typedef Element<S, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    typedef typename identity_transducer_helper<S, T>::ret  ret_t;
    typedef typename ret_t::serie_t output_serie_t;
    typedef typename serie_t::support_t support_t;
    typedef typename ret_t::set_t set_t;
    typedef typename set_t::series_t o_series_t;
    set_t s(o_series_t(a.set().series(), a.set().series().monoid()));
    ret_t ret(s);
    std::vector<hstate_t> conv(a.states().size());

    for_each_state(s, a)
      conv[ret.add_state()] = *s;
    for_each_edge(e, a)
      {
	serie_t t = a.serie_of(*e);
	serie_t s(t);
	output_serie_t os(ret.set().series());
	support_t supp = s.supp();
	for_each_const_(support_t, m, supp)
	  {
	    serie_t tmp(a.set().series());
	    tmp.assoc(*m, s.get(*m));
	    os.assoc(*m, tmp);
	  }
	hedge_t f = ret.add_serie_edge(conv[a.origin_of(*e)],
				       conv[a.aim_of(*e)],
				       os);
      }
    // FIXME: set initial/final weights.
    for_each_initial_state(i, a)
      ret.set_initial(conv[*i], a.get_initial(*i));
    for_each_final_state(f, a)
      ret.set_final(conv[*f], a.get_final(*f));
    return ret;
  }

} // vcsn

#endif // VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HXX
=======
// transducer.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HXX
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HXX

#include <vaucanson/automata/concept/transducer_base.hh>

namespace vcsn {

  template <class Series>
  Transducer<Series>::Transducer(const series_t& s):
    series_(s)
  {}

  template <class Series>
  const typename Transducer<Series>::series_t&
  Transducer<Series>::series() const
  {
    return series_;
  }

  template <class S, class T>
  inline
  typename identity_transducer_helper<S, T>::ret
  partial_identity(const Element<S, T>& a)
  {
    typedef Element<S, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    typedef typename identity_transducer_helper<S, T>::ret  ret_t;
    typedef typename ret_t::serie_t output_serie_t;
    typedef typename serie_t::support_t support_t;
    typedef typename ret_t::set_t set_t;
    typedef typename set_t::series_t o_series_t;
    set_t s(o_series_t(a.set().series(), a.set().series().monoid()));
    ret_t ret(s);
    std::vector<hstate_t> conv(a.states().size());

    for_each_state(s, a)
      conv[ret.add_state()] = *s;
    for_each_edge(e, a)
      {
	serie_t t = a.serie_of(*e);
	serie_t s(t);
	output_serie_t os(ret.set().series());
	support_t supp = s.supp();
	for_each_const_(support_t, m, supp)
	  {
	    serie_t tmp(a.set().series());
	    tmp.assoc(*m, s.get(*m));
	    os.assoc(*m, tmp);
	  }
	hedge_t f = ret.add_serie_edge(conv[a.origin_of(*e)],
				       conv[a.aim_of(*e)],
				       os);
      }
    // FIXME: set initial/final weights.
    for_each_initial_state(i, a)
      ret.set_initial(conv[*i]);
    for_each_final_state(f, a)
      ret.set_final(conv[*f]);
    return ret;
  }

} // vcsn

#endif // VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HXX
>>>>>>> .merge-right.r335
=======
// transducer.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HXX
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HXX

#include <vaucanson/automata/concept/transducer_base.hh>

namespace vcsn {

  template <class Series>
  Transducer<Series>::Transducer(const series_t& s):
    series_(s)
  {}

  template <class Series>
  const typename Transducer<Series>::series_t&
  Transducer<Series>::series() const
  {
    return series_;
  }

  template <class S, class T>
  inline
  typename identity_transducer_helper<S, T>::ret
  partial_identity(const Element<S, T>& a)
  {
    typedef Element<S, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    typedef typename identity_transducer_helper<S, T>::ret  ret_t;
    typedef typename ret_t::serie_t output_serie_t;
    typedef typename serie_t::support_t support_t;
    typedef typename ret_t::set_t set_t;
    typedef typename set_t::series_t o_series_t;
    set_t s(o_series_t(a.set().series(), a.set().series().monoid()));
    ret_t ret(s);
    std::vector<hstate_t> conv(a.states().size());

    for_each_state(s, a)
      conv[ret.add_state()] = *s;
    for_each_edge(e, a)
      {
	serie_t t = a.serie_of(*e);
	serie_t s(t);
	output_serie_t os(ret.set().series());
	support_t supp = s.supp();
	for_each_const_(support_t, m, supp)
	  {
	    serie_t tmp(a.set().series());
	    tmp.assoc(*m, s.get(*m));
	    os.assoc(*m, tmp);
	  }
	hedge_t f = ret.add_serie_edge(conv[a.origin_of(*e)],
				       conv[a.aim_of(*e)],
				       os);
      }
    // FIXME: set initial/final weights.
    for_each_initial_state(i, a)
      ret.set_initial(conv[*i], a.get_initial(*i));
    for_each_final_state(f, a)
      ret.set_final(conv[*f], a.get_final(*f));
    return ret;
  }

} // vcsn

#endif // VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HXX
>>>>>>> .merge-right.r339
=======
// transducer.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HXX
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HXX

#include <vaucanson/automata/concept/transducer_base.hh>

namespace vcsn {

  template <class Series>
  Transducer<Series>::Transducer(const series_t& s):
    series_(s)
  {}

  template <class Series>
  const typename Transducer<Series>::series_t&
  Transducer<Series>::series() const
  {
    return series_;
  }

  template <class S, class T>
  inline
  typename identity_transducer_helper<S, T>::ret
  partial_identity(const Element<S, T>& a)
  {
    typedef Element<S, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    typedef typename identity_transducer_helper<S, T>::ret  ret_t;
    typedef typename ret_t::serie_t output_serie_t;
    typedef typename serie_t::support_t support_t;
    typedef typename ret_t::set_t set_t;
    typedef typename set_t::series_t o_series_t;
    set_t s(o_series_t(a.set().series(), a.set().series().monoid()));
    ret_t ret(s);
    std::vector<hstate_t> conv(a.states().size());

    for_each_state(s, a)
      conv[ret.add_state()] = *s;
    for_each_edge(e, a)
      {
	serie_t t = a.serie_of(*e);
	serie_t s(t);
	output_serie_t os(ret.set().series());
	support_t supp = s.supp();
	for_each_const_(support_t, m, supp)
	  {
	    serie_t tmp(a.set().series());
	    tmp.assoc(*m, s.get(*m));
	    os.assoc(*m, tmp);
	  }
	hedge_t f = ret.add_serie_edge(conv[a.origin_of(*e)],
				       conv[a.aim_of(*e)],
				       os);
      }
    // FIXME: set initial/final weights.
    for_each_initial_state(i, a)
      ret.set_initial(conv[*i], a.get_initial(*i));
    for_each_final_state(f, a)
      ret.set_final(conv[*f], a.get_final(*f));
    return ret;
  }

} // vcsn

#endif // VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HXX
>>>>>>> .merge-right.r340
