// random_visitor.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_RANDOM_VISITOR_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_RANDOM_VISITOR_HXX

# include <algorithm>

# include <vaucanson/misc/contract.hh>
# include <vaucanson/algebra/implementation/series/rat/random_visitor.hh>
# include <vaucanson/algebra/implementation/series/rat/nodes.hh>

namespace vcsn {

  namespace rat {

    template <typename M_, typename W_>
    RandomVisitor<M_, W_>::RandomVisitor(unsigned nb_star_max) :
      not_empty(false),
      nb_star_max_(nb_star_max)
    {}

    template <typename M_, typename W_>
    RandomVisitor<M_, W_>::RandomVisitor() :
      not_empty(false),
      nb_star_max_(nb_star_max_default)
    {}

    template<typename M_, typename W_>
    void
    RandomVisitor<M_,W_>::product(const Node<M_, W_>* left_,
				  const Node<M_, W_>* right_)
    {
      M_ tmp;
      right_->accept(*this);
      tmp = w_;
      left_->accept(*this);
      // FIXME : M_ += M_ assumed here.
      w_ += tmp;
    }

    template <class M_, class W_>
    void
    RandomVisitor<M_,W_>::left_weight(const W_&, const Node<M_, W_>* node)
    {
      node->accept(*this);
    }

    template <class M_, class W_>
    void
    RandomVisitor<M_,W_>::right_weight(const W_&, const Node<M_, W_>* node)
    {
      node->accept(*this);
    }

    template<typename M_, typename W_>
    void
    RandomVisitor<M_,W_>::sum(const Node<M_, W_>* left_,
			      const Node<M_, W_>* right_)
    {
      unsigned r = rand() * 2 / RAND_MAX;
      if (r < 1)
	left_->accept(*this);
      else
	right_->accept(*this);
    }

    template<typename M_, typename W_>
    void
    RandomVisitor<M_,W_>::star(const Node<M_, W_>* node)
    {
      not_empty = true;
      unsigned n = rand() * nb_star_max_ / RAND_MAX;
      M_       tmp;

      for (unsigned i = 0; i < n; ++i)
	{
	  node->accept(*this);
	  // FIXME: M_ += M_ assumed here.
	  tmp += w_;
	}
      w_ = tmp;
    }

    template<typename M_, typename W_>
    void
    RandomVisitor<M_,W_>::constant(const M_& m)
    {
      not_empty = true;
      w_ = m;
    }

    template <class M_, class W_>
    void
    RandomVisitor<M_,W_>::one()
    {
      w_ = M_();
      not_empty = true;
    }

    template <class M_, class W_>
    void
    RandomVisitor<M_,W_>::zero()
    {
    }

    template<typename M_, typename W_>
    M_ RandomVisitor<M_,W_>::get() const
    {
      assertion(not_empty);
      return w_;
    }

  } // rat

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_RANDOM_VISITOR_HXX
