#ifndef VAUCANSON_Z2Z_AUTOMATON_STRUCTURES_HH
# define VAUCANSON_Z2Z_AUTOMATON_STRUCTURES_HH

# include <vaucanson/config/pconf.hh>
# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/contexts/bmig/z2z_automaton_structures.hh>
# include <vaucanson/contexts/listg/z2z_automaton_structures.hh>
# if !defined(ALIAS_z2z_automaton)
#  define ALIAS_z2z_automaton
namespace vcsn
{
  namespace z2z_automaton = vcsn::VCSN_DEFAULT_GRAPH_IMPL::z2z_automaton;
}
# endif
# if !defined(COMMON_TRAITS)
#  define COMMON_TRAITS
namespace vcsn
{
  VCSN_MAKE_STANDARD_OF_TRAITS(vcsn::VCSN_DEFAULT_GRAPH_IMPL::Graph);
}
# endif
#endif // !VAUCANSON_Z2Z_AUTOMATON_STRUCTURES_HH
