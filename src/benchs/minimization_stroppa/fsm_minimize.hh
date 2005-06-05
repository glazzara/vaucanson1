#ifndef VCSN_EXT_ALGORITHMS_FSM_MINIMIZE_HH
#define VCSN_EXT_ALGORITHMS_FSM_MINIMIZE_HH

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

#endif  // VCSN_EXT_ALGORITHMS_FSM_MINIMIZE_HH
