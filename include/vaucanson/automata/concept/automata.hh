// automata.hh
//
// $Id$
// VCSN_HEADER
#ifndef AUTOMATA_AUTOMATA_HH
# define AUTOMATA_AUTOMATA_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/ref.hh>

namespace vcsn {

  struct Automata;
  
  template<>
  struct MetaSet<Automata>
  {
    static const bool dynamic_set = false;
    
  };
  
  template<typename T>
  struct MetaElement<Automata, T>
    : MetaElement<AutomataBase<Automata>, T>
  { };
  
  template<typename T>
  bool op_contains(const Automata& a, const utility::ref<T>& r);
  
  struct Automata
    : AutomataBase<Automata>
  { };



  template<typename T>
  struct automaton_traits<utility::ref<T> >
   : automaton_traits<T>
  { };
  
}


# include <vaucanson/automata/concept/automata.hxx>
# include <vaucanson/automata/concept/automaton_impl.hh>

#endif

