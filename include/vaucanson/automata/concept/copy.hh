// copy.hh
//
// $Id$
// VCSN_HEADER
#ifndef AUTOMATA_COPY_HH
# define AUTOMATA_COPY_HH

#include <vaucanson/automata/concept/handlers.hh>
#include <map>

namespace vcsn {

  template<typename lhs_t, typename rhs_t>
  void auto_copy(lhs_t& dst_,
		 const rhs_t& from);

  template<typename auto_t>
  auto_t auto_copy(const auto_t& from);

} // vcsn

# include <vaucanson/automata/concept/copy.hxx>

#endif
