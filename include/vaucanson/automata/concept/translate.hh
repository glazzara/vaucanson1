// translate.hh
//
// VCSN_HEADER

#ifndef AUTOMATA_COPY_HH
#define AUTOMATA_COPY_HH

# include <vaucanson/automata/concept/handlers.hh>
# include <map>

namespace vcsn
{

  template<typename lhs_t, typename rhs_t, typename F>
  void auto_translate_edges(lhs_t& dst_,
			    const rhs_t& from,
			    const F& translate_fun);

  template<typename auto_t, typename F>
  auto_t auto_translate_edges(const auto_t& from, const F& translate_fun);

}

# include <vaucanson/automata/concept/translate.hxx>

#endif
