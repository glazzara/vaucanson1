// transpose.hxx
//
// $Id$
// VCSN_HEADER

#ifndef AUTOMATA_TRANSPOSE_HXX
#define AUTOMATA_TRANSPOSE_HXX

#include <vaucanson/algorithms/transpose.hh>
#include <vaucanson/automata/concept/transpose_impl.hh>
#include <vaucanson/automata/concept/copy.hh>

namespace vcsn
{
  template<typename lhs_t, typename rhs_t>
  void auto_transpose(lhs_t& dst_,
		      const rhs_t& from)
  {
    auto_copy(dst_, transpose_view(from));
  }

  template<typename auto_t>
  auto_t auto_transpose(const auto_t& from)
  {
    auto_t dst;
    auto_transpose(dst, from);
    return dst;
  }

} //vcsn

#endif
