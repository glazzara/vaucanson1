// size_visitor.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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
//    * Robert Bigaignon <robert.bigaignon@lrde.epita.fr>
//

#ifndef   	SIZE_VISITOR_HXX_
# define   	SIZE_VISITOR_HXX_

# include <vaucanson/algebra/implementation/series/rat/length_visitor.hh>

# include <algorithm>

namespace vcsn {

  namespace rat {

    template<typename M_, typename W_>
    void
    LengthVisitor<M_,W_>::sum_or_product(const Node<M_, W_>* left_,
					 const Node<M_, W_>* right_)
    {
      left_->accept(*this);
      right_->accept(*this);
    }

    template<typename M_, typename W_>
    void
    LengthVisitor<M_, W_>::weight_or_star(const Node<M_, W_>* node)
    {
      node->accept(*this);
    }

    template<typename M_, typename W_>
    void
    LengthVisitor<M_, W_>::product(const Node<M_, W_>* left_,
				   const Node<M_, W_>* right_)
    {
      sum_or_product(left_, right_);
    }

    template<typename M_, typename W_>
    void
    LengthVisitor<M_, W_>::sum(const Node<M_, W_>* left_,
			       const Node<M_, W_>* right_)
    {
      sum_or_product(left_, right_);
    }

    template<typename M_, typename W_>
    void
    LengthVisitor<M_, W_>::star(const Node<M_, W_>* node)
    {
      weight_or_star(node);
    }

    template<typename M_, typename W_>
    void
    LengthVisitor<M_, W_>::left_weight(const W_&, const Node<M_, W_>* node)
    {
      weight_or_star(node);
    }

    template<typename M_, typename W_>
    void
    LengthVisitor<M_, W_>::right_weight(const W_&, const Node<M_, W_>* node)
    {
      weight_or_star(node);
    }

    template<typename M_, typename W_>
    void
    LengthVisitor<M_, W_>::constant(const M_&)
    {
      ++s_;
    }

    template<typename M_, typename W_>
    void LengthVisitor<M_, W_>::zero()
    {
      ++s_;
    }

    template<typename M_, typename W_>
    void LengthVisitor<M_, W_>::one()
    {
      ++s_;
    }

    template<typename M_, typename W_>
    size_t LengthVisitor<M_, W_>::get() const
    {
      return s_;
    }

  } // End of namespace rat.

} // End of namespace vcsn.



#endif	    /* !SIZE_VISITOR_HXX_ */
