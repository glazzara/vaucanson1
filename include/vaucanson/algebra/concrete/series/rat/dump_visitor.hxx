// dump_visitor.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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

#ifndef RAT_DUMP_VISITOR_HXX
# define RAT_DUMP_VISITOR_HXX

# include <iostream>
# include <vaucanson/algebra/concrete/series/rat/dump_visitor.hh>
# include <vaucanson/algebra/concrete/series/rat/nodes.hh>

namespace vcsn {

  namespace rat {

    template <class M_, class W_>
    DumpVisitor<M_,W_>::DumpVisitor(std::ostream& o,
				    const char *zero = "0",
				    const char *one = "1") 
      : o_(o),
	z_(zero),
	i_(one)
    {}

    template <class M_, class W_>
    void 
    DumpVisitor<M_,W_>::product(const Node<M_, W_>* left_, 
				const Node<M_, W_>* right_)
    { 
      o_ << "(";
      left_->accept(*this);
      o_ << ".";
      right_->accept(*this);
      o_ << ")";
    }

    template <class M_, class W_>
    void 
    DumpVisitor<M_,W_>::sum(const Node<M_, W_>* left_, 
			    const Node<M_, W_>* right_)
    { 
      o_ << "(";
      left_->accept(*this);
      o_ << "+";
      right_->accept(*this);
      o_ << ")";
    }

    template <class M_, class W_>
    void 
    DumpVisitor<M_,W_>::star(const Node<M_, W_>* node)
    { 
      //	  o_ << "(";
      node->accept(*this);
      o_ << "*"; // << ")";
    }

    template <class M_, class W_>
    void 
    DumpVisitor<M_,W_>::left_weight(const W_& w, const Node<M_, W_>* node)
    { 
      o_ << "(" << w << " ";
      node->accept(*this);
      o_ << ")";
    }

    template <class M_, class W_>
    void 
    DumpVisitor<M_,W_>::right_weight(const W_& w, const Node<M_, W_>* node)
    { 
      o_ << "(";
      node->accept(*this);
      o_ << " " << w << ")";
    }

    template <class M_, class W_>
    void 
    DumpVisitor<M_,W_>::constant(const M_& m)
    { 
      o_ << m; 
    }

    template <class M_, class W_>
    void DumpVisitor<M_,W_>::zero()
    { 
      o_ << z_; 
    }

    template <class M_, class W_>
    void DumpVisitor<M_,W_>::one()
    { 
      o_ << i_; 
    }
      
  } // rat

} // vcsn

#endif // RAT_DUMP_VISITOR_HXX
