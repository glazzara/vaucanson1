// thompson.hh
//
// $Id$
// VCSN_HEADER
#ifndef ALGORITHMS_THOMPSON_HH
# define ALGORITHMS_THOMPSON_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algebra/concrete/series/rat/exp.hh>

namespace vcsn {

  /*---------.
  | thompson |
  `---------*/
  template<typename A,      typename T, 
	   typename Letter, typename Weight>
  void
  thompson(Element<A, T>&, const rat::exp<Letter, Weight>&);
  
} // vcsn

# include <vaucanson/algorithms/thompson.hxx>

#endif // ALGORITHMS_THOMPSON_HH
