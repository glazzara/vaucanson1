// boostg_handlers.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_HANDLERS_HH
# define VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_HANDLERS_HH

# include <vaucanson/automata/concept/handlers.hh>
# include <boost/multi_index_container.hpp>
# include <boost/multi_index/hashed_index.hpp>
# include <boost/shared_ptr.hpp>

namespace vcsn
{

  template <>
  class handler<state_h, boost::shared_ptr<unsigned> >
  {
    public:
      typedef state_h kind;
      typedef handler<state_h, boost::shared_ptr<unsigned> > self_t;

      handler();

      explicit handler(boost::shared_ptr<unsigned> h);

      handler(const self_t& h);

      self_t& operator=(const self_t& h);

      boost::shared_ptr<unsigned>  value() const;

      operator unsigned() const;

      bool is_valid() const;

    protected:
      boost::shared_ptr<unsigned>  v_;
  };

  using boost::multi_index::detail::hashed_index_iterator;

  template<typename T, typename U, typename V>
  bool operator==(const handler<transition_h, hashed_index_iterator<T, U, V> >& h1,
		  const handler<transition_h, hashed_index_iterator<T, U, V> >& h2);
  template<typename T, typename U, typename V>
  bool operator!=(const handler<transition_h, hashed_index_iterator<T, U, V> >& h1,
		  const handler<transition_h, hashed_index_iterator<T, U, V> >& h2);
  template<typename T, typename U, typename V>
  bool operator<(const handler<transition_h, hashed_index_iterator<T, U, V> >& h1,
		 const handler<transition_h, hashed_index_iterator<T, U, V> >& h2);
  template<typename T, typename U, typename V>
  bool operator>(const handler<transition_h, hashed_index_iterator<T, U, V> >& h1,
		 const handler<transition_h, hashed_index_iterator<T, U, V> >& h2);
  template<typename T, typename U, typename V>
  bool operator<=(const handler<transition_h, hashed_index_iterator<T, U, V> >& h1,
		  const handler<transition_h, hashed_index_iterator<T, U, V> >& h2);
  template<typename T, typename U, typename V>
  bool operator>=(const handler<transition_h, hashed_index_iterator<T, U, V> >& h1,
		  const handler<transition_h, hashed_index_iterator<T, U, V> >& h2);

  template<>
  bool operator==(const handler<state_h, boost::shared_ptr<unsigned> >& h1,
		  const handler<state_h, boost::shared_ptr<unsigned> >& h2);
  template<>
  bool operator!=(const handler<state_h, boost::shared_ptr<unsigned> >& h1,
		  const handler<state_h, boost::shared_ptr<unsigned> >& h2);
  template<>
  bool operator<(const handler<state_h, boost::shared_ptr<unsigned> >& h1,
		 const handler<state_h, boost::shared_ptr<unsigned> >& h2);
  template<>
  bool operator>(const handler<state_h, boost::shared_ptr<unsigned> >& h1,
		 const handler<state_h, boost::shared_ptr<unsigned> >& h2);
  template<>
  bool operator<=(const handler<state_h, boost::shared_ptr<unsigned> >& h1,
		  const handler<state_h, boost::shared_ptr<unsigned> >& h2);
  template<>
  bool operator>=(const handler<state_h, boost::shared_ptr<unsigned> >& h1,
		  const handler<state_h, boost::shared_ptr<unsigned> >& h2);


} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/automata/implementation/boostg/boostg_handlers.hxx>
# include <vaucanson/automata/implementation/boostg/boostg_handlers_op.hxx>
#endif // VCSN_USE_INTERFACE_ONLY

#endif

