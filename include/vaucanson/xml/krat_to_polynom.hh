// krat_to_polynom.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
#ifndef VCSN_XML_KRAT_TO_POLYNOM_HH
# define VCSN_XML_KRAT_TO_POLYNOM_HH

# include <vaucanson/algebra/concrete/series/krat.hh>
# include <vaucanson/algebra/concrete/series/rat/nodes.hh>
# include <vaucanson/algebra/concrete/series/polynoms.hh>

// At this moment, it does not convert everything, the expression must be in
// disjonctive form.

namespace vcsn {

  namespace algebra {

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    class Krat2Polynom : public rat::ConstNodeVisitor<Tm, Ts>
    {
    protected:
      typedef rat::Node<Tm, Ts> node_t;

      polynom<Tm, Ts>	_p;
      bool		error;

      std::pair<Element<Sm, Tm>, Element<Ss, Ts> >
      explore_product(const node_t* n);

    public:
      Krat2Polynom() : _p(), error(false) {}

      bool
      has_error();

      polynom<Tm, Ts>
      get_polynom();

      virtual void
      product(const node_t* left_, const node_t* right_);

      virtual void
      sum(const node_t* left_, const node_t* right_);

      virtual void
      star(const node_t* node_);

      virtual void
      left_weight(const Ts& w, const node_t* node_);

      virtual void
      right_weight(const Ts& w, const node_t* node_);

      virtual void
      constant(const Tm& m_);

      virtual void
      one();

      virtual void
      zero();
    };

    class Unconvertible {};

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    Element<Series<Ss, Sm>, polynom<Tm, Ts> >
    krat_to_polynom(const Element<Series<Ss, Sm>, rat::exp<Tm, Ts> >&);
  }
}

# include <vaucanson/xml/krat_to_polynom.hxx>

#endif // VCSN_XML_KRAT_TO_POLYNOM_HH
