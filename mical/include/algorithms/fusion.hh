

#ifndef   FUSION_HH_
# define   FUSION_HH_

#include <vaucanson/automata/concept/automata_base.hh>
#include <vaucanson/fundamental/element.hh>
#include <vaucanson/tools/usual.hh>

namespace mical {

  using namespace vcsn;

  template<typename A, typename T>
  void
  fusion(Element<A, T>& a, 
	 hstate_t lhs,
	 hstate_t rhs);
  
  template<typename A, typename T>
  Element<A, T>
  get_fusion(const Element<A, T>& a, 
	     hstate_t lhs,
	     hstate_t rhs);

} // mical

#include <algorithms/fusion.hxx>

#endif /* !FUSION_HH_ */
