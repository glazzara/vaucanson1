// depth_visitor.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DEPTH_VISITOR_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DEPTH_VISITOR_HH

# include <cstddef>

# include <vaucanson/algebra/implementation/series/rat/nodes.hh>

namespace vcsn {

  namespace rat {

    template<typename M_, typename W_>
    class DepthVisitor : public ConstNodeVisitor<M_, W_>
    {
    protected:
      void
      sum_or_product(const Node<M_, W_>* left_, const Node<M_, W_>* right_);
      void
      weight_or_star(const Node<M_, W_>* node);

    public:
      virtual void
      product(const Node<M_, W_>* left_, const Node<M_, W_>* right_);

      virtual void
      sum(const Node<M_, W_>* left_, const Node<M_, W_>* right_);

      virtual void
      star(const Node<M_, W_>* node);

      virtual void
      left_weight(const W_&, const Node<M_, W_>* node);

      virtual void
      right_weight(const W_&, const Node<M_, W_>* node);

      virtual void
      constant(const M_& m);

      virtual void zero();

      virtual void one();

      size_t get() const;

    protected:
      size_t		d;
    };

  } // rat

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/implementation/series/rat/depth_visitor.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DEPTH_VISITOR_HH
