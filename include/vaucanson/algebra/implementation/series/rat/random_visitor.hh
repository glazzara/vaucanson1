// random_visitor.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_RAT_RANDOM_VISITOR_HH
# define VCSN_ALGEBRA_CONCRETE_SERIES_RAT_RANDOM_VISITOR_HH

# include <algorithm>
# include <vaucanson/algebra/implementation/series/rat/nodes.hh>

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


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algebra/implementation/series/rat/random_visitor.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_ALGEBRA_CONCRETE_SERIES_RAT_RANDOM_VISITOR_HH
