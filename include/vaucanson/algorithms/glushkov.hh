// glushkov.hh
//
// $Id$
// VCSN_HEADER
#ifndef ALGORITHMS_GLUSHKOV_HH
# define ALGORITHMS_GLUSHKOV_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algebra/concrete/series/krat.hh>

namespace vcsn {

  /*---------.
  | glushkov |
  `---------*/
  template<typename A,      typename T, 
	   typename Letter, typename Weight>
  void
  glushkov(Element<A, T>&, const rat::exp<Letter, Weight>&);
  
} // vcsn

# include <vaucanson/algorithms/glushkov.hxx>

#endif // ALGORITHMS_GLUSHKOV_HH
