// light_support.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_LIGHT_LIGHT_SUPPORT_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_LIGHT_LIGHT_SUPPORT_HXX

namespace vcsn
{
  namespace misc
  {

    /*------------------.
    | SupportIterator.  |
    `------------------*/

    //Specialization for std::vector<handler<state_h, U> >
    template <typename U>
    SupportIterator<std::vector<handler<state_h, U> > >::SupportIterator (vector_iterator mp)
      : i (mp)
    {}

    template <typename U>
    handler<state_h, int>
    SupportIterator<std::vector<handler<state_h, U> > >::operator* () const
    {
      return handler<state_h, int>(*i);
    }

    template <typename U>
    SupportIterator<std::vector<handler<state_h, U> > >&
    SupportIterator<std::vector<handler<state_h, U> > >::operator++ ()
    {
      ++i;
      return *this;
    }

    template <typename U>
    SupportIterator<std::vector<handler<state_h, U> > >&
    SupportIterator<std::vector<handler<state_h, U> > >::operator-- ()
    {
      --i;
      return *this;
    }

    template <typename U>
    SupportIterator<std::vector<handler<state_h, U> > >
    SupportIterator<std::vector<handler<state_h, U> > >::operator++ (int)
    {
      SupportIterator<std::vector<handler<state_h, U> > > tmp = *this;
      ++i;
      return tmp;
    }

    template <typename U>
    bool
    SupportIterator<std::vector<handler<state_h, U> > >::operator!= (const SupportIterator& o) const
    {
      return o.i != i;
    }

    template <typename U>
    bool
    SupportIterator<std::vector<handler<state_h, U> > >::operator== (const SupportIterator& o) const
    {
      return ! (*this != o);
    }

  }
}

#endif // !VCSN_AUTOMATA_IMPLEMENTATION_LIGHT_LIGHT_SUPPORT_HXX

