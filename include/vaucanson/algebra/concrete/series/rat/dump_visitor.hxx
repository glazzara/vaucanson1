// dump_visitor.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_RAT_DUMP_VISITOR_HXX
# define VCSN_ALGEBRA_CONCRETE_SERIES_RAT_DUMP_VISITOR_HXX

# include <iostream>
# include <set>
# include <vaucanson/algebra/concrete/series/rat/dump_visitor.hh>
# include <vaucanson/algebra/concrete/series/rat/nodes.hh>

namespace vcsn {

  namespace rat {

    template <class M_, class W_>
    DumpVisitor<M_,W_>::DumpVisitor(std::ostream& o,
				    const std::set<typename M_::value_type>&
				    escaped,
				    const char* zero,
				    const char* one)
      : o_(o),
	escaped_(escaped),
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
      for (typename M_::const_iterator i = m.begin(); i != m.end(); ++i)
	{
	  if (escaped_.find(*i) != escaped_.end())
	    o_ << "\\";
	  o_ << *i;
	}
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

#endif // VCSN_ALGEBRA_CONCRETE_SERIES_RAT_DUMP_VISITOR_HXX
