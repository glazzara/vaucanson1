//
// predefs.hh
// 
// Made by (Maxime Rey)
// Login   <max@nirgal>
// 
// Started on  Mon Mar 31 20:17:19 2003 Maxime Rey
// Last update Wed Apr  2 19:21:21 2003 Maxime Rey
//

#ifndef   PREDEFS_HH_
# define   PREDEFS_HH_

#include <vaucanson/fundamental/element.hh>
#include <vaucanson/automata/concept/automata.hh>

#include <set>

using namespace vcsn;
using std::set;

namespace mical {

template <class A, class T, class W>
void add_edge(Element<A, T>& a, hstate_t src, hstate_t dst, W label)
{
  set<hedge_t> delta;

  a.deltac(delta, src, delta_kind::edges());

  for (typename set<hedge_t>::iterator i = delta.begin(); i != delta.end(); i++)
    if ((a.label_of(*i) == label) && (a.aim_of(*i) == dst))
      return;

  a.add_edge(src, dst, label);
}

template <class A, class T, class W>
void add_letter_edge(Element<A, T>& a, hstate_t src, hstate_t dst, W label)
{
  set<hedge_t> delta;

  a.deltac(delta, src, delta_kind::edges());

  for (typename set<hedge_t>::iterator i = delta.begin(); i != delta.end(); i++)
    if ((a.label_of(*i).begin()->first == label) 
	&& (a.aim_of(*i) == dst))
      return;

  a.add_letter_edge(src, dst, label);
}

} // mical

#endif /* !PREDEFS_HH_ */
