// transpose.hh
//
// VCSN_HEADER

#ifndef AUTOMATA_TRANSPOSE_HH
#define AUTOMATA_TRANSPOSE_HH

# include <vaucanson/automata/concept/transpose_impl.hh>
# include <vaucanson/automata/concept/copy.hh>

namespace vcsn
{
  template<typename lhs_t, typename rhs_t>
  void auto_transpose(lhs_t& dst_,
		      const rhs_t& from);

  template<typename auto_t>
  auto_t auto_transpose(const auto_t& from);

} //vcsn

# include <vaucanson/automata/concept/transpose.hxx>

#endif
