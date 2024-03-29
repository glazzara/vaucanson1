// bmig_handlers_op.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007, 2008, 2009 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BMIG_BMIG_HANDLERS_OP_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_BMIG_BMIG_HANDLERS_OP_HXX

# include <vaucanson/misc/contract.hh>
# include <vaucanson/automata/concept/handlers.hh>


//Operator for htransition_t storing iterators
#define HOPERATOR(Op)					\
template<typename T, typename U>			\
bool operator Op (const handler<transition_h, boost::multi_index::detail::hashed_index_iterator<T, U> >& h1,\
                  const handler<transition_h, boost::multi_index::detail::hashed_index_iterator<T, U> >& h2)\
{							\
  if (h1.value()->from_ == h2.value()->from_)		\
    if (h1.value()->to_ == h2.value()->to_)		\
      return h1.value()->label_ Op h2.value()->label_;	\
    else						\
      return h1.value()->to_ Op h2.value()->to_;	\
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
template<typename T, typename U>			\
bool operator Op (const handler<transition_h,		\
				boost::multi_index::detail::hashed_index_iterator<T, U> >& h1,\
                  const handler<transition_h,		\
				boost::multi_index::detail::hashed_index_iterator<T, U> >& h2)\
{							\
  return h1.value() Op h2.value();			\
}
namespace vcsn
{
  HOPERATOR(==);
  HOPERATOR(!=);
}
#undef HOPERATOR




#define HOPERATOR(Op)								\
inline										\
bool operator Op (const handler<state_h, boost::shared_ptr<std::size_t> >& h1,	\
                  const handler<state_h, boost::shared_ptr<std::size_t> >& h2)	\
{										\
  return h1.value() Op h2.value();						\
}

namespace vcsn
{
  HOPERATOR(==);
  HOPERATOR(!=);
  HOPERATOR(<);

  inline
  bool operator> (const handler<state_h, boost::shared_ptr<std::size_t> >& h1,
		  const handler<state_h, boost::shared_ptr<std::size_t> >& h2)
  {
    return h2 > h1;
  }

  inline
  bool operator<= (const handler<state_h, boost::shared_ptr<std::size_t> >& h1,
		   const handler<state_h, boost::shared_ptr<std::size_t> >& h2)
  {
    return h1 < h2 || h1 == h2;
  }

  inline
  bool operator>= (const handler<state_h, boost::shared_ptr<std::size_t> >& h1,
		   const handler<state_h, boost::shared_ptr<std::size_t> >& h2)
  {
    return !(h1 < h2);
  }
}
#undef HOPERATOR

#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_BMIG_BMIG_HANDLERS_OP_HXX

