// length_visitor.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_LENGTH_VISITOR_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_LENGTH_VISITOR_HXX

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



#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_LENGTH_VISITOR_HXX
