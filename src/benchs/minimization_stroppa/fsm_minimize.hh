// fsm_minimize.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.

// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_BENCHS_MINIMIZATION_STROPPA_FSM_MINIMIZE_HH
# define VCSN_BENCHS_MINIMIZATION_STROPPA_FSM_MINIMIZE_HH

#include <vaucanson/tools/fsm_dump.hh>


namespace vcsn {

  template<typename S, typename T>
  void
  fsm_minimize(Element<S, T>& a)
  {
    typedef Element<S, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    // Determinization and minimization through FSM
    std::ofstream tmp_o_file("init_o_tmp.fsm");
    tools::fsm_dump(tmp_o_file, a);
    tmp_o_file.close();
  }


}  // vcsn

#endif // ! VCSN_BENCHS_MINIMIZATION_STROPPA_FSM_MINIMIZE_HH
