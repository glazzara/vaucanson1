/*
** This is a template file for a graph structure in Vaucanson
** This template includes everything which is required to implement
** a new structure. Feel free to add new includes or others types in
** your structure.
** However, be aware that only the types provided in the original templates
** are propagated in the automaton/transducer traits.
**
** Don't forget to run the add-vcsn-impl.sh tool when you are finished.
** This tool will generate the proper headers to use your structure with Vaucanson.
**
** Many object and tools can be found in vaucanson/misc/ and vaucanson/tools/
** For instance, vaucanson/misc/contract.hh and vaucanson/misc/static.hh can
** be useful to do static testing and set post and pre conditions.
*/

#ifndef #IMPL_NAME_#_GRAPH_IMPL_HH
# define #IMPL_NAME_#_GRAPH_IMPL_HH

# include <set>
# include <map>
# include <vector>

# include <vaucanson/misc/support.hh>
# include <vaucanson/misc/static.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/transducer_base.hh>
# include <vaucanson/automata/concept/automata_kind.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/automata/implementation/kind_adapter.hh>
# include <vaucanson/automata/implementation/geometry.hh>

namespace vcsn
{
  namespace #IMPL_NAME#
  {
    /// Graph
    template <class K, class WordValue, class WeightValue,
	      class SeriesValue, class Letter, class Tag, class GeometryCoords>
    class Graph
    {
      public:


	/*******\
	| Types |
	\*******/

	/// Self type definition.
	typedef Graph<K, WordValue, WeightValue, SeriesValue,
		      Letter, Tag, GeometryCoords>	self_t;

	//Quick typedef based on the types passed as parameters to the template.
	typedef WeightValue				semiring_elt_value_t;
	typedef WordValue				monoid_elt_value_t;
	typedef WordValue				word_value_t;
	typedef SeriesValue				series_set_elt_value_t;
	typedef Letter					letter_t;
	typedef Tag					tag_t;

	/// Typedefs on automaton related graphs elements.
	typedef typename LabelOf<K, WordValue, WeightValue, SeriesValue, Letter>
	  ::ret						label_t;

	/*
	** These types are the state and transition descriptor type. They are useful
	** when you want to refer to one of these outside the graph.
	**
	** These types must be a handler object. (cf. automata/concept/handlers.h{xx,h}
	**
	** In theory, you should be able to change the type contained in this handler.
	** However, currently, it is not safe to do it and many parts of Vaucanson
	** may not compile anymore...
	*/
	typedef handler<state_h, int>			hstate_t;
	typedef handler<transition_h, int>		htransition_t;

	//This is just a renaming to preserve the vocabulary consistence.
	typedef htransition_t				hedge_t;

	/*
	** Types related to the containers returned in case we need to iterate over
	** the states or the transitions in an algorithm.
	**
	** We highly recommand using the Support and SupportIterator object to encapsulate
	** your container.
	** If you do not want to use it, then you must follow its interface.
	** You can find support.h{h,xx} in vaucanson/misc/.
	**
	** WARNING: whenever a container of one of this type is returned through an accessor,
	**	    a copy is made. So, if you do not use the Support object, be sure to
	**	    consider this. A copy of a Support object is free since it only
	**	    contains a reference to the actual container.
	*/
	typedef misc::Support<StateContainer>		states_t;
	typedef misc::Support<EdgeContainer>		edges_t;

	/*
	** Types related to the containers returned in case we need to iterate over
	** the initial and final transitions in an algorithm.
	**
	** We highly recommand using the Support and SupportIterator object to encapsulate
	** your container.
	** If you do not want to use it, then you must follow its interface.
	** You can find support.h{h,xx} in vaucanson/misc/.
	**
	** WARNING: whenever a container of one of this type is returned through an accessor,
	**	    a copy is made. So, if you do not use the Support object, be sure to
	**	    consider this. A copy of a Support object is free since it only
	**	    contains a reference to the actual container.
	*/
	typedef misc::Support<initial_t>		initial_support_t;
	typedef misc::Support<final_t>			final_support_t;

	//Nothing to change here.
	typedef geometry<hstate_t, hedge_t, GeometryCoords> geometry_t;


	/*********\
	| Methods |
	\*********/

	Graph();

	/*
	** This constructor can pre-allocate data-structures.
	**
	** WARNING: reserve_number_of_state != number_of_state.
	**	    This is a pre-allocation ONLY. the graph
	**	    does not have any states after the initialization.
	*/
	Graph(unsigned reserve_number_of_state,
	      unsigned reserve_number_of_edge);

	/// Return states set.
	states_t	    states() const;

	/// Return edges set.
	edges_t		    edges() const;

	/// Initial/final state supports.
	initial_support_t   initial() const;
	final_support_t	    final() const;

	/** @name State's manipulation
	** @{ */
	bool		    has_state(hstate_t n) const;

	hstate_t	    add_state();

	/// Remove state \a n.
	///
	/// \pre \a n is a state of this graph.
	void		    del_state(hstate_t n);

	/// Change whether a state is initial or not.
	/// \param s  the state
	/// \param v  its associated label
	/// \param z  the zero for the labels
	///
	/// \note If v == z then state is removed from the set of initial
	/// states.  Because of this, one cannot simply write
	/// \code
	/// typename automaton_t::series_set_elt_t some_weight = ...;
	/// for_all_final_states(f, aut)
	///   lhs.set_final(*f, aut.get_final(*f) * some_weight);
	/// \endcode
	/// because if \c some_weight is equal to \c z, then the state
	/// is removed from the set of final states, and invalidates all
	/// the iterators: the loop is broken.
	void		    set_initial(hstate_t s,
					const series_set_elt_value_t& v,
					const series_set_elt_value_t& z);
	const series_set_elt_value_t&
			    get_initial(hstate_t,
					const series_set_elt_value_t&) const;
	bool		    is_initial(hstate_t s,
				       const series_set_elt_value_t&) const;

	void		    clear_initial();

	/// Change whether a state is final or not.
	/// \param s  the state
	/// \param v  its associated label
	/// \param z  the zero for the labels
	///
	/// \sa set_initial().
	void		    set_final(hstate_t,
				      const series_set_elt_value_t&,
				      const series_set_elt_value_t&);
	const series_set_elt_value_t&
			    get_final(hstate_t,
				      const series_set_elt_value_t&) const;
	bool		    is_final(hstate_t s,
				     const series_set_elt_value_t&) const;

	void		    clear_final();
	/** @}*/


	/** @name Edge's manipulation
	** @{ */
	bool		    has_edge(hedge_t n) const;

	hedge_t		    add_edge(hstate_t h1,
				     hstate_t h2,
				     const label_t& v);
	void		    del_edge(hedge_t e);

	hstate_t	    src_of(hedge_t e1) const;
	hstate_t	    dst_of(hedge_t e2) const;

	const label_t&	    label_of(hedge_t n) const;
	void		    update(hedge_t, label_t);
	/** @} */

	/** @name Only automaton related methods
	** @{ */
	/// Check the consistency of an automata.
	template <class S>
	bool		    exists(const AutomataBase<S>& s) const;

	/// Delta, Reverse deltas, for functor and iterator.
	/// Nothing to change here.
# define DECLARE_DELTA_FUNCTION(DeltaName, DKind)			\
	template <class OutputIterator, typename Query>			\
	void DeltaName(OutputIterator res, hstate_t from,		\
		       const Query& q, ::vcsn::delta_kind::DKind) const
	DECLARE_DELTA_FUNCTION (delta, states);
	DECLARE_DELTA_FUNCTION (delta, transitions);
	DECLARE_DELTA_FUNCTION (rdelta, states);
	DECLARE_DELTA_FUNCTION (rdelta, transitions);
# undef DECLARE_DELTA_FUNCTION

# define DECLARE_DELTAF_BOOL_FUNCTION(DeltaName, DKind, IsBool)		\
	template <class Functor, typename Query>			\
	void DeltaName(Functor& fun, hstate_t from,			\
		       const Query& q, ::vcsn::delta_kind::DKind,	\
		       misc::IsBool ## _t) const
	DECLARE_DELTAF_BOOL_FUNCTION (deltaf, states, true);
	DECLARE_DELTAF_BOOL_FUNCTION (deltaf, states, false);
	DECLARE_DELTAF_BOOL_FUNCTION (deltaf, transitions, true);
	DECLARE_DELTAF_BOOL_FUNCTION (deltaf, transitions, false);
	DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, states, true);
	DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, states, false);
	DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, transitions, true);
	DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, transitions, false);
# undef DECLARE_DELTAF_BOOL_FUNCTION

# define DECLARE_DELTAF_FUNCTION(DeltaName)				\
	template <class Functor, typename Query, typename DKind>	\
	void DeltaName(Functor& fun, hstate_t from,			\
		       const Query& q, ::vcsn::delta_kind::kind<DKind>) const
	DECLARE_DELTAF_FUNCTION (deltaf);
	DECLARE_DELTAF_FUNCTION (rdeltaf);

# undef DECLARE_DELTAF_FUNCTION

	/** @}*/

	//Implementation not required. Never used in Vaucanson.
	self_t&		    clone() const;

	/** @name Tag access
	** @{ */
	tag_t&		    tag();
	const tag_t&	    tag() const;
	/** @}*/

	/** @name Geometry access
	** @{ */
	geometry_t&	    geometry();
	const geometry_t&   geometry() const;
	/** @}*/

      //Feel free to add attributes as needed.
      private:
	geometry_t	    geometry_;
	tag_t		    tag_;
    };


# define TParam								\
    template <class S, class WordValue, class WeightValue, class SeriesValue, \
	      class Letter, class Tag, class GeometryCoords>
# define GRAPH \
    Graph<Kind, WordValue, WeightValue, SerieValue, \
	  Letter, Tag, GeometryCoords>



    TParam
    ADAPT_ADD_LETTER_TRANSITION_TO_SERIES_LABEL(Graph<labels_are_series,
						WordValue, WeightValue,
						SeriesValue, Letter, Tag,
						GeometryCoords>);

    TParam
    ADAPT_LETTER_OF_TO_SERIES_LABEL(Graph<labels_are_series,
				    WordValue, WeightValue,
				    SeriesValue, Letter, Tag,
				    GeometryCoords>);

    TParam
    ADAPT_WORD_OF_TO_SERIES_LABEL(Graph<labels_are_series,
				  WordValue, WeightValue,
				  SeriesValue, Letter, Tag,
				  GeometryCoords>);

    TParam
    ADAPT_WORD_OF_TO_LETTERS_LABEL(Graph<labels_are_letters,
				   WordValue, WeightValue,
				   SeriesValue, Letter, Tag,
				   GeometryCoords>);

    TParam
    ADAPT_SERIE_OF_TO_LETTERS_LABEL(Graph<labels_are_letters,
				    WordValue, WeightValue,
				    SeriesValue, Letter, Tag,
				    GeometryCoords>);

    TParam
    ADAPT_ADD_SERIE_TRANSITION_TO_LETTERS_LABEL(Graph<labels_are_letters,
						WordValue, WeightValue,
						SeriesValue, Letter, Tag,
						GeometryCoords>);

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    Tag&		    op_tag(const AutomataBase<I>&,
				   Graph<Kind, WordValue, WeightValue,
				   SerieValue, Letter, Tag,
				   GeometryCoords>&);

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    const Tag&		    op_tag(const AutomataBase<I>&,
				   const Graph<Kind, WordValue, WeightValue,
				   SerieValue, Letter, Tag, GeometryCoords>&);

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    typename GRAPH::geometry_t&
			    op_geometry(const AutomataBase<I>&,
					Graph<Kind, WordValue, WeightValue,
					SerieValue, Letter, Tag, GeometryCoords>&);

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    const typename GRAPH::geometry_t&
			    op_geometry(const AutomataBase<I>&,
					const Graph<Kind, WordValue,
					WeightValue, SerieValue, Letter, Tag,
					GeometryCoords>&);
# undef TParam
# undef GRAPH

  } // End of namespace #VCSN_NAME_#


  /*
  ** Here follow the different traits. Remove/comment if you don't want
  ** to use this implementation in an automaton or a transducer.
  ** Usually, you do not need to do touch anything.
  */

  // This implementation can be used as an implementation of automaton.
  VCSN_MAKE_AUTOMATON_TRAITS(#IMPL_NAME#::Graph);

  // This implementation can be used as a transducer one.
  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag,
	    class GeometryCoords>
  struct transducer_traits<#IMPL_NAME#::Graph<Kind,
					 WordValue,
					 WeightValue,
					 SeriesValue,
					 Letter,
					 Tag,
					 GeometryCoords> >
  {
    typedef WordValue	      input_monoid_elt_value_t;
    typedef typename algebra::series_traits<WeightValue>::monoid_elt_value_t
			      output_monoid_elt_value_t;
    typedef typename algebra::series_traits<WeightValue>::semiring_elt_value_t
			      output_semiring_elt_value_t;
  };

  // Explain how to project type of transducer into input automaton type.
  template <class S,
	    class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag,
	    class GeometryCoords>
  struct projection_traits<S, #IMPL_NAME#::Graph<Kind,
					    WordValue,
					    WeightValue,
					    SeriesValue,
					    Letter,
					    Tag,
					    GeometryCoords> >
  {
    typedef #IMPL_NAME#::Graph<Kind, WordValue, WeightValue, SeriesValue,
			  Letter, Tag, GeometryCoords>
			      self_t;
    typedef typename transducer_traits<self_t>::output_semiring_elt_value_t
			      semiring_elt_value_t;
    typedef typename transducer_traits<self_t>::input_monoid_elt_value_t
			      monoid_elt_value_t;
    typedef typename algebra::mute_series_impl<SeriesValue,
					       semiring_elt_value_t,
					       monoid_elt_value_t>::ret
			      series_set_elt_value_t;

    typedef
    #IMPL_NAME#::Graph<Kind,
		  monoid_elt_value_t,
		  semiring_elt_value_t,
		  series_set_elt_value_t,
		  Letter,
		  Tag,
		  GeometryCoords>
			      ret;
  };

  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag,
	    class GeometryCoords>
  struct output_projection_traits<#IMPL_NAME#::Graph<Kind,
						WordValue,
						WeightValue,
						SeriesValue,
						Letter,
						Tag, GeometryCoords> >
  {
    typedef #IMPL_NAME#::Graph<Kind, WordValue, WeightValue, SeriesValue,
			  Letter, Tag, GeometryCoords>
			      self_t;

    typedef typename automaton_traits<self_t>::semiring_elt_value_t
			      series_set_elt_value_t;

    typedef typename
    algebra::series_traits<series_set_elt_value_t>::monoid_elt_value_t
			      monoid_elt_value_t;

    typedef typename
    algebra::series_traits<series_set_elt_value_t>::semiring_elt_value_t
			      semiring_elt_value_t;

    typedef
    #IMPL_NAME#::Graph<Kind,
		  monoid_elt_value_t,
		  semiring_elt_value_t,
		  series_set_elt_value_t,
		  Letter,
		  Tag,
		  GeometryCoords>
			      ret;
  };

  // Explain how to extend an input automaton into a transducer.
  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag,
	    class GeometryCoords>
  struct extension_traits<#IMPL_NAME#::Graph<Kind,
					WordValue,
					WeightValue,
					SeriesValue,
					Letter,
					Tag,
					GeometryCoords> >
  {
    typedef #IMPL_NAME#::Graph<Kind, WordValue, WeightValue,
			  SeriesValue, Letter, Tag, GeometryCoords>
			      self_t;
    typedef typename automaton_traits<self_t>::monoid_elt_value_t
			      monoid_elt_value_t;
    typedef typename algebra::mute_series_impl<SeriesValue,
					       SeriesValue,
					       monoid_elt_value_t>::ret
			      series_set_elt_value_t;

    typedef
    #IMPL_NAME#::Graph<Kind,
		  monoid_elt_value_t,
		  SeriesValue,
		  series_set_elt_value_t,
		  Letter,
		  Tag,
		  GeometryCoords>
			      ret;
  };
} // Enf of namespace vcsn


# include <vaucanson/automata/implementation/light_graph_impl.hxx>

#endif // ! #IMPL_NAME_#_GRAPH_IMPL_HH
