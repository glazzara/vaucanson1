// boost_functors.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007 The Vaucanson Group.
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

#ifndef VCSN_AUTOMATON_IMPLEMENTATION_BOOSTG_BOOST_FUNCTORS_HXX
# define VCSN_AUTOMATON_IMPLEMENTATION_BOOSTG_BOOST_FUNCTORS_HXX

# include <vaucanson/automata/implementation/boostg/boostg_functors.hh>
# include <vaucanson/automata/implementation/boostg/initial_value.hh>

namespace vcsn
{
  namespace boostg
  {

    /*-------------------------------------------------.
    | Functor used to update a label in a multi_index. |
    `-------------------------------------------------*/

    template<typename HLabel>
    update_hlabel<HLabel>::update_hlabel(const HLabel& i_)
      : i(i_)
    {}

    template<typename HLabel>
    void
    update_hlabel<HLabel>::operator()(HLabel &key)
    {
      key = i;
    }


    template<typename HState, typename Series>
    update_label<InitialValue<HState, Series> >::update_label(const Series& i_)
      : i(i_)
    {
    }

    template<typename HState, typename Series>
    void
    update_label<InitialValue<HState, Series> >::operator()(InitialValue<HState, Series>& elt)
    {
      elt.second = i;
    }

  }
}

#endif // ! VCSN_AUTOMATON_IMPLEMENTATION_BOOSTG_BOOST_FUNCTORS_HXX

