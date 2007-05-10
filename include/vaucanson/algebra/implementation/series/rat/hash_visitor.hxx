// hash_visitor.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_HASH_VISITOR_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_HASH_VISITOR_HXX

# include <boost/functional/hash/hash.hpp>
# include <vaucanson/algebra/implementation/series/rat/dump_visitor.hh>
# include <vaucanson/algebra/implementation/series/rat/nodes.hh>

namespace vcsn {

  namespace rat {

    template <class Word, class Weight>
    HashVisitor<Word, Weight>::HashVisitor()
	: seed_(0)
    {
    }

    template <class Word, class Weight>
    HashVisitor<Word, Weight>::~HashVisitor()
    {}

    template <class Word, class Weight>
    void
    HashVisitor<Word, Weight>::product(const node_t* lhs, const node_t* rhs)
    {
      lhs->accept(*this);
      ::boost::hash_combine(seed_, '.');
      rhs->accept(*this);
    }

    template <class Word, class Weight>
    void
    HashVisitor<Word, Weight>::sum(const node_t* lhs, const node_t* rhs)
    {
      lhs->accept(*this);
      ::boost::hash_combine(seed_, '+');
      rhs->accept(*this);
    }

    template<class Word, class Weight>
    void
    HashVisitor<Word, Weight>::star(const node_t* node)
    {
      node->accept(*this);
      ::boost::hash_combine(seed_, '*');
    }

    template<class Word, class Weight>
    void
    HashVisitor<Word, Weight>::left_weight(const semiring_elt_value_t& w, const node_t* node)
    {
      ::boost::hash_combine(seed_, w);
      node->accept(*this);
    }

    template<class Word, class Weight>
    void
    HashVisitor<Word, Weight>::right_weight(const semiring_elt_value_t& w, const node_t* node)
    {
      ::boost::hash_combine(seed_, ' ');
      ::boost::hash_combine(seed_, w);
      node->accept(*this);
    }

    template<class Word, class Weight>
    void
    HashVisitor<Word, Weight>::constant(const monoid_elt_value_t& m)
    {
      ::boost::hash_combine(seed_, m);
    }

    template<class Word, class Weight>
    void
    HashVisitor<Word, Weight>::zero()
    {
      ::boost::hash_combine(seed_, rat::zero());
    }

    template<class Word, class Weight>
    void
    HashVisitor<Word, Weight>::one()
    {
      ::boost::hash_combine(seed_, rat::id());
    }

    template<class Word, class Weight>
    std::size_t
    HashVisitor<Word, Weight>::hash_value()
    {
      return seed_;
    }


  } // rat

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_HASH_VISITOR_HXX
