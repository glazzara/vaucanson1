// automata.hxx
//
// $Id$
// VCSN_HEADER
#ifndef AUTOMATA_AUTOMATA_HXX
# define AUTOMATA_AUTOMATA_HXX

#include <vaucanson/automata/concept/automata_base.hh>
#include <vaucanson/misc/ref.hh>

namespace vcsn {

  template<typename T>
  bool op_contains(const Automata& a, const utility::ref<T>& r)
  { 
    return true; 
  }
  
} // vcsn

#endif // AUTOMATA_AUTOMATA_HXX
