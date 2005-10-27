// tools.hh: this file is part of the Vaucanson project.
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
// `COPYING' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_BENCHS_MINIMIZATION_STROPPA_TOOLS_HH
# define VCSN_BENCHS_MINIMIZATION_STROPPA_TOOLS_HH


#include <iostream>


namespace ana {


  template<class E, class A>
  inline
  void
  AssertLevel1(A assertion, E exception)
  {
#ifdef DEBUG1
    if(!assertion) throw exception();
#endif
  }

  template<class E, class A>
  inline
  void
  AssertLevel2(A assertion, E exception)
  {
#ifdef DEBUG2
    if(!assertion) throw exception();
#endif
  }


  template<class E, class A>
  inline
  void
  AssertLevel3(A assertion, E exception)
  {
#ifdef DEBUG3
    if(!assertion) throw exception();
#endif
  }


  template<class E, class A>
  inline
  void
  Assert(A assertion, E exception)
  {
    if(!assertion) throw exception;
  }


  struct Cerr
  {
    Cerr(const char* error_message) {
      std::cout << error_message << "\n";
      exit(1);
    }
  };

  namespace misc {

    template<typename Word, typename Weight>
    std::pair< std::vector<Word>, std::vector<Weight> >
    file_to_vector_pair(const char *input);

  }


}  // ana


#include <minimization_stroppa/tools.hxx>

#endif  // ANA_MISC_TOOLS_HH












// dans une autre fonction,
// if () { throw My_Exception(); }
// try {
//fonction envoyant l'exception;
//}
//catch(Analogies::My_Exception e) {
// e.printerror();
//}
//catch(...) {
//throw; pour redeclencher
//}


//   namespace misc_tools {
//     template <class C>
//     std::vector<C> file_to_vector(std::ifstream& input);

//     template <class C>
//     std::vector<C> file_to_vector(const char *input);

//     void fsm_acceptor_to_fsm_transducer(std::ifstream& input, std::ofstream& output);

//     void word_to_fsm(const std::string& word, std::ofstream& fsm_file);

//   }
// }

