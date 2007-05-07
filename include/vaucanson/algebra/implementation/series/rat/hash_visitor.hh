// hash_visitor.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_HASH_VISITOR_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_HASH_VISITOR_HH

# include <ostream>
# include <string>
# include <set>

# include <vaucanson/algebra/implementation/series/rat/exp.hh>

namespace vcsn
{

  namespace rat
  {

    template <class Word, class Weight>
    class HashVisitor : public ConstNodeVisitor<Word, Weight>
    {
    public:

      typedef Word			monoid_elt_value_t;
      typedef Weight			semiring_elt_value_t;
      typedef Node<Word, Weight>	node_t;

    public:

      HashVisitor();
      virtual ~HashVisitor();

      virtual void product(const node_t* lhs, const node_t* rhs);
      virtual void sum(const node_t* lhs, const node_t* rhs);
      virtual void star(const node_t* node);
      virtual void left_weight(const semiring_elt_value_t& w, const node_t* node);
      virtual void right_weight(const semiring_elt_value_t& w, const node_t* node);
      virtual void constant(const monoid_elt_value_t& m);
      virtual void zero();
      virtual void one();

      std::size_t hash_value();

    protected:
      std::size_t	seed_;
    };
  } // End of namespace rat.

} // End of namespace vcsn.

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/series/rat/hash_visitor.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DUMP_VISITOR_HH
