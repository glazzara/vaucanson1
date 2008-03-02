/*
** This is a template file for a graph structure in Vaucanson
** This template includes everything which is required to implement
** a new structure. Feel free to add new includes.
**
** Don't forget to run the add-vcsn-impl.sh tool when you are finished.
** This tool will generate the proper headers to use your structure with Vaucanson.
**
** Many object and tools can be found in vaucanson/misc/ and vaucanson/tools/
** For instance, vaucanson/misc/contract.hh and vaucanson/misc/static.hh can
** be useful to do static testing and set post and pre conditions.
**
** DEBUG: if you want, you can write some code enabled only during the debug process of your
**	  development. Just write the code as follow:
**
**	  #ifdef VCSN_DEBUG
**	    your_code
**	  #endif
**
**	  The postconditions and preconditions functions use this mechanism.
*/

#ifndef #IMPL_NAME_#_GRAPH_IMPL_HXX
# define #IMPL_NAME_#_GRAPH_IMPL_HXX

# include <fstream>
# include <sstream>
# include <algorithm>
# include <utility>

# include "#IMPL_NAME#_graph_impl.hh"
# include <vaucanson/misc/contract.hh>
# include <vaucanson/misc/static.hh>

namespace vcsn
{
  namespace #IMPL_NAME#
  {

    /*--------------------.
    | Convenient macros.  |
    `--------------------*/
    //You DO NOT need to change anything to these macros.
    # define TParam								\
    template <class Kind, class WordValue, class WeightValue,		\
            class SeriesValue, class Letter, class Tag, class GeometryCoords>

    # define GClass								\
    Graph<Kind, WordValue, WeightValue, SeriesValue, Letter, Tag, GeometryCoords>


    /*-------------------------.
    | Graph's implementation.  |
    `-------------------------*/

    /*---------------.
    | Constructors.  |
    `---------------*/

    TParam
    GClass::Graph()
    { }

    TParam
    GClass::Graph (unsigned reserve_number_of_state,
                   unsigned reserve_number_of_edge)
    {

    }

    /*------------------.
    | Basic accessors.  |
    `------------------*/

    TParam
    typename GClass::states_t
    GClass::states() const
    {

    }

    TParam
    typename GClass::edges_t
    GClass::edges() const
    {

    }

    TParam
    typename GClass::initial_support_t
    GClass::initial() const
    {

    }

    TParam
    typename GClass::final_support_t
    GClass::final() const
    {

    }


    /*----------------------.
    | States manipulation.  |
    `----------------------*/

    TParam
    bool
    GClass::has_state(const hstate_t& n) const
    {

    }

    TParam
    typename GClass::hstate_t
    GClass::get_state(int n) const
    {

    }

    TParam
    typename GClass::hstate_t
    GClass::add_state()
    {

      postcondition(has_state(n));
    }

    TParam
    void
    GClass::del_state(const hstate_t& n)
    {
      precondition (has_state(n));

      postcondition(!has_state(n));
    }

    TParam
    void
    GClass::set_initial(const hstate_t& n,
			const series_set_elt_value_t& v,
			const series_set_elt_value_t& z)
    {

    }

    TParam
    const typename GClass::series_set_elt_value_t&
    GClass::get_initial(const hstate_t& n,
			const series_set_elt_value_t& z) const
    {

    }

    TParam
    bool
    GClass::is_initial(const hstate_t& s,
		       const series_set_elt_value_t& z) const
    {

    }

    TParam
    void
    GClass::clear_initial()
    {

    }

    TParam
    void
    GClass::set_final(const hstate_t& n,
		      const series_set_elt_value_t& v,
		      const series_set_elt_value_t& z)
    {

    }

    TParam
    const typename GClass::series_set_elt_value_t&
    GClass::get_final(const hstate_t& n,
		      const series_set_elt_value_t& z) const
    {

    }

    TParam
    bool
    GClass::is_final(const hstate_t& s,
		     const series_set_elt_value_t& z) const
    {

    }

    TParam
    void
    GClass::clear_final()
    {

    }


    /*---------------------.
    | Edges manipulation.  |
    `---------------------*/

    TParam
    bool
    GClass::has_edge(const hedge_t& e) const
    {

    }

    TParam
    typename GClass::hedge_t
    GClass::add_edge(const hstate_t& n1,
		     const hstate_t& n2,
		     const label_t& v)
    {
      precondition(has_state(n1));
      precondition(has_state(n2));

    }

    TParam
    void
    GClass::del_edge(const hedge_t& e)
    {
      precondition (has_edge(e));

      postcondition(!has_edge(e));
    }


    TParam
    typename GClass::hstate_t
    GClass::src_of(const hedge_t& e1) const
    {
      precondition(has_edge(e1));

    }

    TParam
    typename GClass::hstate_t
    GClass::dst_of(const hedge_t& e2) const
    {
      precondition(has_edge(e2));

    }

    TParam
    const typename GClass::label_t&
    GClass::label_of(const hedge_t& n) const
    {
      precondition(has_edge(n));

    }

    TParam
    void
    GClass::update(const hedge_t& e, const label_t& l)
    {
      precondition(has_edge(e));

    }


    TParam
    template <class S>
    bool
    GClass::exists(const AutomataBase<S>& s) const
    {

    }

    /*------------------.
    | Delta functions.  |
    `------------------*/

    // Classical ones.

    // Define delta and rdelta functions which will retrieve all the
    // needed information about outgoing/ingoing transitions: either the
    // transitions themselves or the opposite state.
    // The result is stored in a container "res".
    TParam
    template <class OutputIterator, class Query>
    void
    GClass::delta(OutputIterator res,
                  const hstate_t& from,
                  const Query& query,
                  ::vcsn::delta_kind::states) const
    {
      assertion(has_state(from));

    }

    TParam
    template <class OutputIterator, class Query>
    void
    GClass::delta(OutputIterator res,
                  const hstate_t& from,
                  const Query& query,
                  ::vcsn::delta_kind::transitions) const
    {
      assertion(has_state(from));

    }

    TParam
    template <class OutputIterator, class Query>
    void
    GClass::rdelta(OutputIterator res,
                  const hstate_t& from,
                  const Query& query,
                  ::vcsn::delta_kind::states) const
    {
      assertion(has_state(from));

    }

    TParam
    template <class OutputIterator, class Query>
    void
    GClass::rdelta(OutputIterator res,
                  const hstate_t& from,
                  const Query& query,
                  ::vcsn::delta_kind::transitions) const
    {
      assertion(has_state(from));

    }

    // Delta with functor.  Much more than the previous one, because
    // functor is statically checked for return type of its operator(),
    // and behave differently if it is bool: loop breaks if false is
    // returned.
    TParam
    template <typename Functor, class Query>
    void
    GClass::deltaf(Functor& fun,
		   const hstate_t& from,
                   const Query& query,
                   ::vcsn::delta_kind::states,
                   misc::true_t) const
    {
      assertion(has_state(from));

    }

    TParam
    template <typename Functor, class Query>
    void
    GClass::deltaf(Functor& fun,
		   const hstate_t& from,
	           const Query& query,
		   ::vcsn::delta_kind::states,
		   misc::false_t) const
    {
      assertion(has_state(from));

    }

    TParam
    template <typename Functor, class Query>
    void
    GClass::deltaf(Functor& fun,
		   const hstate_t& from,
	           const Query& query,
		   ::vcsn::delta_kind::transitions,
		   misc::true_t) const
    {
      assertion(has_state(from));

    }

    TParam
    template <typename Functor, class Query>
    void
    GClass::deltaf(Functor& fun,
		   const hstate_t& from,
	           const Query& query,
		   ::vcsn::delta_kind::transitions,
		   misc::false_t) const
    {
      assertion(has_state(from));

    }

    TParam
    template <typename Functor, class Query>
    void
    GClass::rdeltaf(Functor& fun,
		   const hstate_t& from,
	           const Query& query,
		   ::vcsn::delta_kind::states,
		   misc::true_t) const
    {
      assertion(has_state(from));

    }

    TParam
    template <typename Functor, class Query>
    void
    GClass::rdeltaf(Functor& fun,
		   const hstate_t& from,
	           const Query& query,
		   ::vcsn::delta_kind::states,
		   misc::false_t) const
    {
      assertion(has_state(from));

    }

    TParam
    template <typename Functor, class Query>
    void
    GClass::rdeltaf(Functor& fun,
		   const hstate_t& from,
	           const Query& query,
		   ::vcsn::delta_kind::transitions,
		   misc::true_t) const
    {
      assertion(has_state(from));

    }

    TParam
    template <typename Functor, class Query>
    void
    GClass::rdeltaf(Functor& fun,
		   const hstate_t& from,
	           const Query& query,
		   ::vcsn::delta_kind::transitions,
		   misc::false_t) const
    {
      assertion(has_state(from));

    }

    // Helpers for static dispatch.
    // You should not need to change that.
    // Good documentation about this part will come later.
    namespace deltaf_helper {
      template <typename T, typename R, typename Arg>
      char is_returning_bool_helper (R (T::*) (Arg));

      template <typename T, typename Arg>
      int is_returning_bool_helper (bool (T::*) (Arg));

      # define is_returning_bool(T)					  \
      (sizeof (deltaf_helper::is_returning_bool_helper (T)) == sizeof (int))
    }

    # define DEFINE_DELTAF_HELPER(DeltaName)				\
    TParam								\
    template <typename Functor, class Query, typename DKind>		\
    void								\
    GClass::DeltaName(Functor& fun,					\
                    hstate_t from,					\
                    const Query& query,					\
                    delta_kind::kind<DKind> k) const			\
    {									\
      DeltaName (fun, from, query, k,					\
            BOOL_TO_TYPE (is_returning_bool (&Functor::operator ())) ());\
    }

    DEFINE_DELTAF_HELPER (deltaf);
    DEFINE_DELTAF_HELPER (rdeltaf);

    # undef DEFINE_DELTAF_HELPER
    # undef is_returning_bool

    /*------.
    | Tag.  |
    `------*/

    //These are default implementations. You may want to change them.

    TParam
    inline
    Tag& GClass::tag()
    {
      return tag_;
    }

    TParam
    const Tag& GClass::tag() const
    {
      return tag_;
    }

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
              class Letter, class Tag, class GeometryCoords, class I>
    Tag& op_tag(const AutomataBase<I>&,
                Graph<Kind, WordValue, WeightValue,
                SerieValue ,Letter, Tag, GeometryCoords>& v)
    {
      return v.tag();
    }

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
              class Letter, class Tag, class GeometryCoords, class I>
    const Tag& op_tag(const AutomataBase<I>&,
                      const Graph<Kind, WordValue, WeightValue,
                      SerieValue ,Letter, Tag, GeometryCoords>& v)
    {
      return v.tag();
    }


    /*-----------.
    | Geometry.  |
    `-----------*/

    template <class Kind, class WordValue, class WeightValue, class SeriesValue,
              class Letter, class Tag, class GeometryCoords, class I>
    typename GClass::geometry_t&
    op_geometry(const AutomataBase<I>&,
                Graph<Kind, WordValue, WeightValue,
                SeriesValue, Letter, Tag, GeometryCoords>& v)
    {
      return v.geometry();
    }

    template <class Kind, class WordValue, class WeightValue, class SeriesValue,
              class Letter, class Tag, class GeometryCoords, class I>
    const typename GClass::geometry_t&
    op_geometry(const AutomataBase<I>&,
                const Graph<Kind, WordValue, WeightValue,
                SeriesValue, Letter, Tag, GeometryCoords>& v)
    {
      return v.geometry();
    }


    TParam
    const typename GClass::geometry_t&
    GClass::geometry() const
    {
      return geometry_;
    }

    TParam
    typename GClass::geometry_t&
    GClass::geometry()
    {
      return geometry_;
    }


    // Remove macros to avoid name clashes.
# undef TParam
# undef GClass
  }
}

#endif // ! #IMPL_NAME_#_GRAPH_IMPL_HXX

