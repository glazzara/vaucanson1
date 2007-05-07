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
# include <vaucanson/design_pattern/predecls.hh>

namespace vcsn {

  struct state_h
  {};

  struct transition_h
  {};

  template<typename Tag, typename Type>
  class handler
  {
    public:
      typedef Tag kind;

      handler();

//      handler(Type h);

      handler(const Type& h);

      handler(const handler& h);

      handler& operator=(const handler& h);

      handler& operator=(Type h);

      Type value() const;

      operator Type () const;

    protected:
      Type v_;
  };

  template<typename Tag, typename Type>
  bool operator==(const handler<Tag, Type>& h1,
		  const handler<Tag, Type>& h2);

  template<typename Tag, typename Type>
  bool operator!=(const handler<Tag, Type>& h1,
		  const handler<Tag, Type>& h2);

  template<typename Tag, typename Type>
  bool operator<(const handler<Tag, Type>& h1,
		 const handler<Tag, Type>& h2);

  template<typename Tag, typename Type>
  bool operator>(const handler<Tag, Type>& h1,
		 const handler<Tag, Type>& h2);

  template<typename Tag, typename Type>
  bool operator<=(const handler<Tag, Type>& h1,
		  const handler<Tag, Type>& h2);

  template<typename Tag, typename Type>
  bool operator>=(const handler<Tag, Type>& h1,
		  const handler<Tag, Type>& h2);

} // vcsn

namespace std {

  template <typename Tag, typename Type>
  std::ostream&
  operator<<(std::ostream& out, const vcsn::handler<Tag, Type>& h);

} // std


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/automata/concept/handlers.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_CONCEPT_HANDLERS_HH
