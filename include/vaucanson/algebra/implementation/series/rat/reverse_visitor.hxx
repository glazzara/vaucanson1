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

    template <class Word, class Weight>
    void
    ReverseVisitor<Word, Weight>::product(rat::Node<Word, Weight>* lhs,
					  rat::Node<Word, Weight>* rhs)
    {
      lhs->accept(*this);
      rhs->accept(*this);
      swap(lhs, rhs);
    }

  } // End of namespace rat.

  namespace algebra
  {

    template <typename S, typename Word, typename Weight>
    rat::exp<Word, Weight>&
    DefaultTransposeFun< S, rat::exp<Word, Weight> >::
    operator () (const S&, const rat::exp<Word, Weight>& exp)
    {
      rat::exp<Word, Weight>*	   rexp = new rat::exp<Word, Weight> (exp);
      rat::ReverseVisitor<Word, Weight> rv;

      rexp.accept(rv);
      return *rexp;
    }

  } // End of namespace algebra.

} // End of namespace vcsn.

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_REVERSE_VISITOR_HXX
