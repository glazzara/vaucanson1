// dump_visitor.hh
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

#ifndef RAT_DUMP_VISITOR_HH
# define RAT_DUMP_VISITOR_HH

# include <iostream>
# include <vaucanson/algebra/concrete/series/rat/nodes.hh>

namespace vcsn {

  namespace rat {

    template<typename M_, typename W_>
    class DumpVisitor : public ConstNodeVisitor<M_, W_>
    {
    public:
      DumpVisitor(std::ostream& o,
		  const char *zero = "0",
		  const char *one = "1");

      virtual void 
      product(const Node<M_, W_>* left_, const Node<M_, W_>* right_);

      virtual void 
      sum(const Node<M_, W_>* left_, const Node<M_, W_>* right_);

      virtual void 
      star(const Node<M_, W_>* node);

      virtual void 
      left_weight(const W_& w, const Node<M_, W_>* node);

      virtual void 
      right_weight(const W_& w, const Node<M_, W_>* node);

      virtual void 
      constant(const M_& m);

      virtual void zero();

      virtual void one();

    protected:
      std::ostream& o_;
      const char *z_;
      const char *i_;
    };
      
  } // rat

} // vcsn

# include <vaucanson/algebra/concrete/series/rat/dump_visitor.hxx>

#endif // RAT_DUMP_VISITOR_HH
