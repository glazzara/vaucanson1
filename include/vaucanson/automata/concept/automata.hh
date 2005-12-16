// automata.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_CONCEPT_AUTOMATA_HH
# define VCSN_AUTOMATA_CONCEPT_AUTOMATA_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/design_pattern/slots.hh>

namespace vcsn {

  template <class Series>
  struct Automata;

  /// Dynamic traits for automata.
  template <class Series>
  struct dynamic_traits<Automata<Series> >
    : dynamic_traits<AutomataBase<Automata<Series> > >
  {
    static const bool ret = dynamic_traits<Series>::ret;
  };

  /// MetaElement specialization for automata.
  template <class Series, typename T>
  struct MetaElement<Automata<Series>, T>
    : MetaElement<AutomataBase<Automata<Series> >, T>
  {};

  /// Virtual types for automata.
  template <class Series>
  struct virtual_types<Automata<Series> >
    : virtual_types<AutomataBase<Automata<Series> > >
  {
    typedef Series series_set_t;
  };


  /// Final class for the set of automata.
  template <class Series>
  class Automata
    : public AutomataBase<Automata<Series> >,
      private SetSlot<Series>
  {
  public:
    typedef Automata<Series> self_t;
    typedef Series series_set_t;

    Automata(const series_set_t&);

    const series_set_t&	series() const;
  };

  template <class Series>
  bool
  operator==(const Automata<Series>&, const Automata<Series>&);

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/automata/concept/automata.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_CONCEPT_AUTOMATA_HH
