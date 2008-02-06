// boostg_handlers_op.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_HANDLERS_OP_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_HANDLERS_OP_HXX

# include <vaucanson/misc/contract.hh>
# include <vaucanson/automata/concept/handlers.hh>


//Operator for htransition_t storing iterators
#define HOPERATOR(Op)					\
template<typename T, typename U, typename V>		\
bool operator Op (const handler<transition_h, boost::multi_index::detail::hashed_index_iterator<T, U, V> >& h1,\
                  const handler<transition_h, boost::multi_index::detail::hashed_index_iterator<T, U, V> >& h2)\
{							\
  if (h1.value()->from_ == h2.value()->from_)		\
    return h1.value()->to_ Op h2.value()->to_;		\
  else							\
    return h1.value()->from_ Op h2.value()->from_;	\
}

namespace vcsn
{
  HOPERATOR(<);
  HOPERATOR(>);
  HOPERATOR(<=);
  HOPERATOR(>=);
}
#undef HOPERATOR

#define HOPERATOR(Op)					\
template<typename T, typename U, typename V>		\
bool operator Op (const handler<transition_h,		\
				boost::multi_index::detail::hashed_index_iterator<T, U, V> >& h1,\
                  const handler<transition_h,		\
				boost::multi_index::detail::hashed_index_iterator<T, U, V> >& h2)\
{							\
  return h1.value() Op h2.value();			\
}
namespace vcsn
{
  HOPERATOR(==);
  HOPERATOR(!=);
}
#undef HOPERATOR




#define HOPERATOR(Op)					\
inline							\
bool operator Op (const handler<state_h, boost::shared_ptr<std::size_t> >& h1,\
                  const handler<state_h, boost::shared_ptr<std::size_t> >& h2)\
{ return int(h1) Op int(h2); }

namespace vcsn
{
  HOPERATOR(==);
  HOPERATOR(!=);
  HOPERATOR(<);
  HOPERATOR(>);
  HOPERATOR(<=);
  HOPERATOR(>=);
}
#undef HOPERATOR

#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_HANDLERS_OP_HXX

