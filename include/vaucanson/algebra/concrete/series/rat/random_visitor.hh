// random_visitor.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef RAT_RANDOM_VISITOR_HH
# define RAT_RANDOM_VISITOR_HH

# include <algorithm>
# include <vaucanson/algebra/concrete/series/rat/nodes.hh>

namespace vcsn {

  namespace rat {

    template<typename M_, typename W_>
    class RandomVisitor : public ConstNodeVisitor<M_, W_>
    {
    public:
      static const unsigned nb_star_max_default /* = 5 */;

      RandomVisitor(unsigned nb_star_max);
      RandomVisitor();

      virtual void 
      product(const Node<M_, W_>* left_, const Node<M_, W_>* right_);
      virtual void 
      sum(const Node<M_, W_>* left_, const Node<M_, W_>* right_);

      virtual void 
      star(const Node<M_, W_>* node);

      virtual void left_weight(const W_&, const Node<M_, W_>*);
      virtual void right_weight(const W_&, const Node<M_, W_>*);

      virtual void 
      constant(const M_& m);
      virtual void zero();
      virtual void one();

      M_ get() const;

    protected:
      M_		w_;
      bool		not_empty;
      unsigned		nb_star_max_;
    };

  } // rat

} // vcsn

# include <vaucanson/algebra/concrete/series/rat/random_visitor.hxx>

#endif // RAT_RANDOM_VISITOR_HH
