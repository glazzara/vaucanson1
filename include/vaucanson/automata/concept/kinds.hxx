/*********************************
 * <vaucanson/automata/kinds.hxx> *
 *********************************/

/* this file is part of the Vaucanson project */
#ifndef AUTOMATA_KINDS_HXX
# define AUTOMATA_KINDS_HXX

#include <iterator>
#include <cassert>
#include <algorithm>

#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concept/algebra_base.hh>
#include <vaucanson/automata/concept/handlers.hh>

namespace vcsn
{
  

  
  
  template<typename Series, typename MonoidElt, typename Weight, typename L>  
  ls_delta_letter_query<Series, MonoidElt, Weight, L>::
  ls_delta_letter_query(const Series& s, const L& l)
    : s_(s), 
      l_(op_convert(SELECT(typename MonoidElt::value_t),
			     SELECT(typename MonoidElt::set_t),
			     l))
  {}
  
  template<typename Series, typename MonoidElt, typename Weight, typename L>
  template<typename Label>
  bool ls_delta_letter_query<Series, MonoidElt, Weight, L>::
  operator()(const Label& label) const
  {
    return (op_series_get(s_.get(), label, l_)
	    != zero_value(SELECT(typename Weight::set_t), 
				   SELECT(typename Weight::value_t)));
  }



    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    Element<Series, SeriesT>
    AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
    serie_of(hedge_t e) const
    { 
      return series_elt_t(auto_self().series(),
			  auto_self().label_of(e));
    }

    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    const SeriesT& 
    AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
    serie_value_of(hedge_t e) const
    {
      return auto_self().label_of(e);
    }

    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    bool 
    AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
    is_spontaneous(hedge_t e) const
    {
      return auto_self().label_of(e) == 
	algebra::identity_value(SELECT(Series), SELECT(SeriesT));
    }

    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    template<typename L>
    L 
    AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
    letter_of(SELECTOR(L), hedge_t e) const
    {
      return *algebra::op_begin(auto_self().series().monoid(), 
				auto_self().label_of(e).begin()->first);
    }

  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  typename Element<Series, SeriesT>::monoid_elt_t
  AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
  word_of(hedge_t e) const
  {
    const LabelT& l = auto_self().label_of(e);
    
    return monoid_elt_t(auto_self().series().monoid(),
			l.begin()->first);
  }

    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    const typename Element<Series, SeriesT>::monoid_elt_t::value_t& 
    AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
    word_value_of(hedge_t e) const
    {
      return auto_self().label_of(e).begin()->first;
    }

  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  template<typename S>
  hedge_t 
  AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
  add_serie_edge(hstate_t from, hstate_t to, 
		 const S& e)
    { 
      return auto_self().add_edge(from, to, e.value()); 
    }

  template<typename Self, typename Series, typename SeriesT, typename LabelT>
    hedge_t
  AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
  add_spontaneous(hstate_t from, hstate_t to)			   
    {
      return auto_self().add_edge(from, to, algebra::identity_value(SELECT(Series), SELECT(SeriesT)));
    }

    template<typename Self, typename Series, typename SeriesT, typename LabelT>
  template<typename L>
  hedge_t 
  AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
  add_letter_edge(hstate_t from, hstate_t to,
		  const L& l)
    { 
      return auto_self().add_edge(from, to, 
				  series_elt_t(auto_self().series(),
					       monoid_elt_t(auto_self().series().monoid(),
							    l)
					       ).value()
				  );
    }

#define DELTA_IMPL(Name, Type, Kind_type)                                            \
    template<typename Self, typename Series, typename SeriesT, typename LabelT>			\
    template<typename OutputIterator, typename L>							\
    void                                                                                               \
    AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::                                        \
    letter_ ## Name (OutputIterator res, hstate_t from, const L& l, Kind_type k) const	\
    {													\
      return auto_self().value()-> Name ## _ ## Type							\
	(res, from,											\
	 ls_delta_letter_query<Series, monoid_elt_t, weight_t, L>					\
	 (auto_self().series(), l));						 			\
    }										                        \
    template<typename Self, typename Series, typename SeriesT, typename LabelT>			\
    template<typename Container, typename L>								\
    void                                                                                                \
    AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::                                        \
    letter_ ## Name ## c (Container &dst, hstate_t from, const L& l, Kind_type k) const	\
    {													\
      std::insert_iterator<Container> i(dst, dst.begin());						\
      return auto_self().value()-> Name ## _ ## Type							\
	(i, from,											\
	 ls_delta_letter_query<Series, monoid_elt_t, weight_t, L>					\
	 (auto_self().series(), l));									\
    }

    DELTA_IMPL(delta, edges, delta_kind::edges);
    DELTA_IMPL(rdelta, edges, delta_kind::edges);

    DELTA_IMPL(delta, states, delta_kind::states);
    DELTA_IMPL(rdelta, states, delta_kind::states);
#undef DELTA_IMPL

    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    Self& 
    AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
    auto_self()
    { return static_cast<Self&>(*this); }

    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    const Self& 
    AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
    auto_self() const
    { return static_cast<const Self&>(*this); }



  /*-----------------------------------------------------------.
  | Automaton labels are pairs (weight value, monoidelt value) |
  `-----------------------------------------------------------*/

  
  template<typename Monoid, typename L>
  lc_delta_letter_query<Monoid, L>::
  lc_delta_letter_query(const Monoid& m, const L& l)
    : m_(m), l_(l)
  {}
  
  template<typename Monoid, typename L>
  template<typename Label>
  bool 
  lc_delta_letter_query<Monoid, L>::
  operator()(const Label& label) const
    {
      typedef typename Element
	<Monoid, typename Label::second_type>::const_iterator letter_iterator;
      
      letter_iterator b = op_begin(m_.get(), label.second);
      letter_iterator e = op_end(m_.get(), label.second);
      
      return std::find(b, e, l_) != e;
    }





  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  Element<Series, SeriesT>
  AutoKind<labels_are_couples, Self, Series, SeriesT, LabelT>::
  serie_of(hedge_t e) const
  { 
    const LabelT& label = auto_self().label_of(e);
    const Series& s = auto_self().series();
    
    series_elt_t se(s, monoid_elt_t(s.monoid(), label.second));
    return see *= weight_t(s.weights(), label.first);
  }
  
  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  const SeriesT 
  AutoKind<labels_are_couples, Self, Series, SeriesT, LabelT>::
  serie_value_of(hedge_t e) const
  {
    const LabelT& label = auto_self().label_of(e);
    const Series& s = auto_self().series();
    
    series_elt_t se(s, monoid_elt_t(s.monoid(), label.second));
    return (se *= weight_t(s.weights(), label.first)).value();
  }

    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    bool 
    AutoKind<labels_are_couples, Self, Series, SeriesT, LabelT>::
    is_spontaneous(hedge_t e) const
    {
      const LabelT& label = auto_self().label_of(e);

      return label.second == identity_value(SELECT(monoid_t), SELECT(typename monoid_elt_t::value_t));
    }

    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    template<typename L>
    L 
    AutoKind<labels_are_couples, Self, Series, SeriesT, LabelT>::
    letter_of(SELECTOR(L), hedge_t e) const
    {
      return *algebra::op_begin(auto_self().series().monoid(), 
				auto_self().label_of(e).second);
    }

    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    typename Element<Series, SeriesT>::monoid_elt_t 
    AutoKind<labels_are_couples, Self, Series, SeriesT, LabelT>::
    word_of(hedge_t e) const
    {
      const LabelT& l = auto_self().label_of(e);

      return monoid_elt_t(auto_self().series().monoid(),
			  l.second);
    }

    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    const typename Element<Series, SeriesT>::monoid_elt_t::value_t& 
    AutoKind<labels_are_couples, Self, Series, SeriesT, LabelT>::
    word_value_of(hedge_t e) const
    {
      return auto_self().label_of(e).second;
    }

    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    template<typename S>
    hedge_t 
    AutoKind<labels_are_couples, Self, Series, SeriesT, LabelT>::
    add_serie_edge(hstate_t from, hstate_t to, 
		   const S& e)
    { 
      assert(e.is_finite_app());
      hedge_t x;

      typedef typename S::value_t supp_t;
      for (typename supp_t::const_iterator i = e.supp().begin();
	   i != e.supp().end();
	   ++i)
	x = auto_self().add_edge(from, to, std::make_pair(i->second, i->first));

      return x;
    }

    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    hedge_t 
    AutoKind<labels_are_couples, Self, Series, SeriesT, LabelT>::
    add_spontaneous(hstate_t from, hstate_t to)			   
    {
      return auto_self().add_edge(from, to, 
				  std::make_pair(identity_value(SELECT(monoid_t), 
								SELECT(typename monoid_elt_t::value_t)), 
						 identity_value(SELECT(weights_t), 
								SELECT(typename weight_t::value_t)))
				  );
    }


    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    template<typename L>
    hedge_t 
    AutoKind<labels_are_couples, Self, Series, SeriesT, LabelT>::
    add_letter_edge(hstate_t from, hstate_t to,
		    const L& l)
    { 
      return auto_self().add_edge
	(from, to, 
	 std::make_pair(identity_value(SELECT(weights_t), SELECT(typename weight_t::value_t)),
			monoid_elt_t(auto_self().series().monoid(), l).value()));
    }

#define DELTA_IMPL(Name, Type, Kind_type)								\
  template<typename Self, typename Series, typename SeriesT, typename LabelT>                           \
    template<typename OutputIterator, typename L>							\
    void                                                                                                \
    AutoKind<labels_are_couples, Self, Series, SeriesT, LabelT>::                                       \
    letter_ ## Name (OutputIterator res, hstate_t from, const L& l, Kind_type k) const	\
    {													\
      return auto_self().value()-> Name ## _ ## Type							\
	(res, from,											\
	 lc_delta_letter_query<monoid_t, L>(auto_self().series().monoid(),				\
					    l));							\
    }													\
  template<typename Self, typename Series, typename SeriesT, typename LabelT>                           \
    template<typename Container, typename L>								\
    void                                                                                         \
    AutoKind<labels_are_couples, Self, Series, SeriesT, LabelT>::                                 \
    letter_ ## Name (Container &dst, hstate_t from, const L& l, Kind_type k) const		\
    {													\
      std::insert_iterator<Container> i(dst, dst.begin());						\
      return auto_self().value()-> Name ## _ ## Type							\
	(i, from,											\
	 lc_delta_letter_query<monoid_t, L>(auto_self().series().monoid(),				\
					    l));							\
    }

    DELTA_IMPL(delta, edges, delta_kind::edges);
    DELTA_IMPL(rdelta, edges, delta_kind::edges);

    DELTA_IMPL(delta, edges, delta_kind::states);
    DELTA_IMPL(rdelta, edges, delta_kind::states);
#undef DELTA_IMPL


    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    Self& 
    AutoKind<labels_are_couples, Self, Series, SeriesT, LabelT>::
    auto_self() { return static_cast<Self&>(*this); }

    template<typename Self, typename Series, typename SeriesT, typename LabelT>
    const Self& 
    AutoKind<labels_are_couples, Self, Series, SeriesT, LabelT>::
    auto_self() const { return static_cast<Self&>(*this); }

}



#endif
