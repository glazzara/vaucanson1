// handlers.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_HANDLERS_HH
# define VCSN_AUTOMATA_CONCEPT_HANDLERS_HH

# include <iostream>

namespace vcsn {

  struct state_h
  {};

  struct transition_h
  {};

  template<typename Tag>
  class handler
  {
    public:
      typedef Tag kind;

      handler();

      handler(int h);

      handler(const handler& h);

      handler& operator=(const handler& h);

      handler& operator=(int h);

      int value() const;

      operator int () const;

    protected:
      int v_;
  };

  typedef handler<state_h> hstate_t;
  typedef handler<transition_h> htransition_t;

  template<typename kind>
  bool operator==(const handler<kind>& h1,
		  const handler<kind>& h2);

  template<typename kind>
  bool operator!=(const handler<kind>& h1,
		  const handler<kind>& h2);

  template<typename kind>
  bool operator<(const handler<kind>& h1,
		 const handler<kind>& h2);

  template<typename kind>
  bool operator>(const handler<kind>& h1,
		 const handler<kind>& h2);

  template<typename kind>
  bool operator<=(const handler<kind>& h1,
		  const handler<kind>& h2);

  template<typename kind>
  bool operator>=(const handler<kind>& h1,
		  const handler<kind>& h2);

} // vcsn

namespace std {

  template <typename kind>
  std::ostream&
  operator<<(std::ostream& out, const vcsn::handler<kind>& h);

} // std


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/automata/concept/handlers.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_CONCEPT_HANDLERS_HH
