// translate.hxx
//
// VCSN_HEADER

#ifndef AUTOMATA_COPY_HXX
#define AUTOMATA_COPY_HXX

# include <vaucanson/automata/concept/translate.hh>
# include <vaucanson/automata/concept/handlers.hh>
# include <map>

namespace vcsn
{

  template<typename lhs_t, typename rhs_t, typename F>
  void auto_translate_edges(lhs_t& dst_,
			    const rhs_t& from,
			    const F& translate_fun)
  {
    lhs_t dst;
    std::map<hstate_t, hstate_t> stmap;

    dst.create();
    dst.series() = from.series();
    for (typename rhs_t::state_iterator i = from.states().begin();
	 i != from.states().end();
	 ++i)
      {
	hstate_t s = dst.add_state();
	dst.set_final(s, from.get_final(*i));
	dst.set_initial(s, from.get_initial(*i));
	stmap[*i] = s;
      }

    for (typename rhs_t::edge_iterator i = from.edges().begin();
	 i != from.edges().end();
	 ++i)
      dst.add_serie_edge(stmap[i.origin()], stmap[i.aim()], translate_fun(from.serie_of(*i)));

    dst_.swap(dst);
  }

  template<typename auto_t, typename F>
  auto_t auto_translate_edges(const auto_t& from, const F& translate_fun)
  {
    auto_t dst;
    auto_translate(dst, from, translate_fun);
    return dst;
  }
  
  
} //vcsn


#endif
