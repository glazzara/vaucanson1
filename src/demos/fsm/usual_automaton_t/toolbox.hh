// toolbox.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_DEMOS_UTILITIES_FSM_USUAL_AUTOMATON_T_TOOLBOX_HH
# define VCSN_DEMOS_UTILITIES_FSM_USUAL_AUTOMATON_T_TOOLBOX_HH

# include <vaucanson/tools/usual.hh>
# include <set>

typedef vcsn::tools::usual_automaton_t	automaton_t;

const automaton_t::series_set_t&  series();

#endif // ! VCSN_DEMOS_UTILITIES_FSM_USUAL_AUTOMATON_T_TOOLBOX_HH