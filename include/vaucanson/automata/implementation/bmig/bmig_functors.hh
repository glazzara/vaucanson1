// bmig_functors.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007, 2008 The Vaucanson Group.
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

#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BMIG_BMIG_FUNCTORS_HH_
# define VCSN_AUTOMATA_IMPLEMENTATION_BMIG_BMIG_FUNCTORS_HH_

# include <functional>
# include <vaucanson/automata/implementation/bmig/initial_value.hh>

namespace vcsn
{
  namespace bmig
  {
    template<typename T>
    struct update_label;

    template<typename HState, typename Series>
    struct update_label<InitialValue<HState, Series> >
      : public std::unary_function<InitialValue<HState, Series>, void>
    {
      update_label(const Series& i_);
      void operator()(InitialValue<HState, Series>& key);

      Series i;
    };


    // Functor used to update the label of a transition.
    //
    // Boost::multi_index only provides const iterators and modifying some data
    // in such a container is a special operation which may require to reorder
    // several sets internaly. Thus, a special method is provided, update(), which
    // uses such functors.
    //
    // See implementation in automata/implementation/bmig/boost_functors.hxx.
    template<typename HLabel>
    struct update_hlabel : public std::unary_function<HLabel, void>
    {
      update_hlabel(const HLabel& i_);
      void operator()(HLabel &key);

      HLabel i;
    };

  } //bmig
} //vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/automata/implementation/bmig/bmig_functors.hxx>
# endif // !VCSN_USE_INTERFACE_ONLY || VCSN_USE_LIB

#endif // !VCSN_AUTOMATA_IMPLEMENTATION_BMIG_BMIG_FUNCTORS_HH_

