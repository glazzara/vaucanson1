/****************************************
 * <vaucanson/automata/relabel_impl.hh> *
 ****************************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef AUTOMATA_RELABEL_IMPL_HH
# define AUTOMATA_RELABEL_IMPL_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/ref.hh>
# include <vaucanson/misc/converter.hh>
# include <vaucanson/misc/functors.hh>
# include <vaucanson/automata/concept/transpose_impl.hh>

namespace vcsn
{
  template<typename Fun, typename EdgeIterator>
  struct relabeled_edge_iterator
    : EdgeIterator
  {
    relabeled_edge_iterator();

    relabeled_edge_iterator(const relabeled_edge_iterator& other);

    typename Fun::result_type label() const;

    relabeled_edge_iterator& operator=(const relabeled_edge_iterator& other);
      
    relabeled_edge_iterator& operator++();

    relabeled_edge_iterator& operator--();

    relabeled_edge_iterator operator++(int);

    relabeled_edge_iterator operator--(int);

    // not for public use:
    explicit relabeled_edge_iterator(const EdgeIterator& i,
				     const Fun& fun);

  protected:
    Fun fun_;
  };

  template<typename Fun, typename Edges>
  struct EdgesAdapter
  {
    EdgesAdapter(const Fun& f, const Edges& e);

    EdgesAdapter(const EdgesAdapter& other);

    typedef 
    relabeled_edge_iterator<Fun, typename Edges::const_iterator> 
    const_iterator;
    
    const_iterator begin() const;

    const_iterator end() const;

    const_iterator find(unsigned i) const;

    const_iterator operator[](unsigned i) const;

    void erase(const_iterator i);

    void erase(unsigned idx);

    size_t size() const;

    bool empty() const;

  protected:
    Fun			fun_;
    const Edges&	e_;
  };

  template<typename OtherImpl, 
	   typename Kind,
	   typename Series, typename SeriesT,
	   typename LabelTranslator, 
	   typename SerieTranslator
	   = 
	   utility::converter
	   <Element<typename OtherImpl::series_t,
			     typename OtherImpl::series_value_t>,
	    Element<Series, SeriesT> > >
  class RelabelImpl
  {
  protected:
    typedef OtherImpl		impl_t;
    utility::ref<impl_t>	impl_ref_;
    impl_t*			impl_;
    Series			series_;
    LabelTranslator		lfun_;
    SerieTranslator		sfun_;

  public:
    typedef Kind				adapter_kind_t;
    typedef typename OtherImpl::tag_t		tag_t;

    typedef Series				series_t;
    typedef SeriesT				series_value_t;
    typedef Element<Series, SeriesT>    	series_elt_t;

    typedef typename LabelTranslator::result_type label_t;

    typedef typename OtherImpl::states_t	states_t;
    typedef EdgesAdapter<LabelTranslator, typename OtherImpl::edges_t> edges_t;

    RelabelImpl();
    
    RelabelImpl(const RelabelImpl& other);

    RelabelImpl(const utility::ref<impl_t>& r, 
		const Series& s,
		const LabelTranslator& lfun,
		const SerieTranslator& sfun);

    typename automaton_traits<impl_t>::states_ret_t
    states() const;

    edges_t edges() const;

    typename automaton_traits<impl_t>::initial_ret_t
    initial() const;

    typename automaton_traits<impl_t>::final_ret_t
    final() const;

    tag_t& tag();
    
    const tag_t& tag() const;

#ifndef NDEBUG
    unsigned add_state();

    template<typename T>
    unsigned add_edge(unsigned from, unsigned to, const T& l);
#endif

    // these 3 are goodies, BUT only goodies.
    void del_state(unsigned s);

    void del_edge(unsigned e);

    void safe_del_state(unsigned s);

    bool has_state(unsigned s) const;

    bool has_edge(unsigned e) const;

    template<typename Iter>
    void delta_states(Iter out, unsigned from) const;

    template<typename Iter>
    void delta_edges(Iter out, unsigned from) const;
    
    template<typename Iter, typename T>
    void delta_states(Iter out, unsigned from, const T& q) const;

    template<typename Iter, typename T>
    void delta_edges(Iter out, unsigned from, const T& q) const;

    template<typename Iter>
    void rdelta_states(Iter out, unsigned from) const;

    template<typename Iter>
    void rdelta_edges(Iter out, unsigned from) const;
    
    template<typename Iter, typename T>
    void rdelta_states(Iter out, unsigned from, const T& q) const;

    template<typename Iter, typename T>
    void rdelta_edges(Iter out, unsigned from, const T& q) const;
     
    bool is_initial(unsigned s) const;

    bool is_final(unsigned s) const;

    // goodies
    void set_initial(unsigned s);

    void unset_initial(unsigned s);

    void set_final(unsigned s);

    void unset_final(unsigned s);

#ifndef NDEBUG
    template<typename T>
    void set_initial(unsigned s, const T& t);

    template<typename T>
    void unset_initial(unsigned s, const T& t);

    template<typename T>
    void set_final(unsigned s, const T& t);

    template<typename T>
    void unset_final(unsigned s, const T& t);
#endif
    
    series_elt_t
    get_initial(unsigned s) const;

    series_elt_t
    get_final(unsigned s) const;

    unsigned origin_of(unsigned e) const;

    unsigned aim_of(unsigned e) const;

    label_t label_of(unsigned e) const;

    series_t& series();

    const series_t& series() const;

    // not for public use:

    impl_t& impl();
    
    const impl_t& impl() const;

    utility::ref<impl_t>& ref();

    const utility::ref<impl_t>& ref() const;

  };

  template<typename I, typename K, typename S, typename T, 
	   typename Lf, 
	   typename Sf>
  struct automaton_traits<RelabelImpl<I, K, S, T, Lf, Sf> >
    : automaton_traits<I>
  {
    typedef K					adapter_kind_t;
    typedef S					series_t;
    typedef typename Sf::result_type		series_elt_t;
    typedef typename series_elt_t::value_t	series_value_t;
    // assert(series_value_t == T)

    typedef typename Lf::result_type		label_t;

    typedef 
    transposed_edge_iterator<typename automaton_traits<I>::edge_iterator> 
    edge_iterator;

    typedef typename Lf::result_type label_ret_t;
    typedef EdgesAdapter<Lf, typename automaton_traits<I>::edges_t> edges_ret_t;
    typedef EdgesAdapter<Lf, typename automaton_traits<I>::edges_t> edges_t;
  };

  template<typename Auto, typename K, typename S, typename T, typename Lf, typename Sf>
  struct relabel_traits
  {
    typedef typename Auto::value_t original_ref_t;
    typedef typename original_ref_t::element_type original_impl_t;

    typedef RelabelImpl<original_impl_t, K, S, T, Lf, Sf> relabel_impl_t;
    typedef utility::ref<relabel_impl_t> relabel_ref_t;
    typedef Element<typename Auto::set_t, relabel_ref_t> relabel_t;
  };

  template<typename Auto, typename K, typename S, typename T, typename Lf, typename Sf>
  typename relabel_traits<Auto, K, S, T, Lf, Sf>::relabel_t
  relabel_view(const Auto& a, 
	       K kind, 
	       const S& series, 
	       SELECTOR(T),
	       const Lf& lfun,
	       const Sf& sfun);


}

# include <vaucanson/automata/concept/relabel_impl.hxx>

#endif
