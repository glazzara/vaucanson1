// reverse_visitor.hxx: this file is part of the Vaucanson project.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_REVERSE_VISITOR_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_REVERSE_VISITOR_HXX

# include <vaucanson/algebra/implementation/series/rat/reverse_visitor.hh>

namespace vcsn
{

  namespace rat
  {

    template <class Semiring, class Word, class Weight>
    ReverseVisitor<Semiring, Word, Weight>::
    ReverseVisitor(const SemiringBase<Semiring>& s) : s_ (s)
    {}

    template <class Semiring, class Word, class Weight>
    void
    ReverseVisitor<Semiring, Word, Weight>::
    product(rat::Node<Word, Weight>* lhs, rat::Node<Word, Weight>* rhs)
    {
      lhs->accept(*this);
      rhs->accept(*this);
      swap(lhs, rhs);
    }

    template <class Semiring, class Word, class Weight>
    void
    ReverseVisitor<Semiring, Word, Weight>::left_weight(Weight& w)
    {
      w = transpose(w);
    }

    template <class Semiring, class Word, class Weight>
    void
    ReverseVisitor<Semiring, Word, Weight>::right_weight(Weight& w)
    {
      w = transpose(s_, w);
    }

    template <class Semiring, class Word, class Weight>
    void
    ReverseVisitor<Semiring, Word, Weight>::constant(Word& w)
    {
      w = mirror(w);
    }

    template <class Semiring, class Word, class Weight>
    template <class S>
    Weight
    ReverseVisitor<Semiring, Word, Weight>::
    transpose(const SeriesBase<S>& s, Weight& w)
    {
      Element<S, Weight> e (s, w);
      e.transpose();
      return e.value();
    }

    template <class Semiring, class Word, class Weight>
    template <class S>
    Weight
    ReverseVisitor<Semiring, Word, Weight>::
    transpose(const SemiringBase<S>&, Weight& w)
    {
      return w;
    }

  } // End of namespace rat.

  namespace algebra
  {

    template <typename S, typename Word, typename Weight>
    rat::exp<Word, Weight>&
    DefaultTransposeFun< S, rat::exp<Word, Weight> >::
    operator () (const S& s, const rat::exp<Word, Weight>& exp)
    {
      rat::exp<Word, Weight>* rexp = new rat::exp<Word, Weight> (exp);
      rat::ReverseVisitor<S::semiring_t, Word, Weight> rv (s.semiring());

      rexp.accept(rv);
      return *rexp;
    }

  } // End of namespace algebra.

} // End of namespace vcsn.

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_REVERSE_VISITOR_HXX
