// transpose_impl.hh
//
// $Id$
// VCSN_HEADER

#ifndef AUTOMATA_TRANSPOSE_IMPL_HH
# define AUTOMATA_TRANSPOSE_IMPL_HH

# include <functional>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/fundamental/slots.hh>
# include <vaucanson/misc/ref.hh>
# include <vaucanson/algorithms/transpose.hh>

# include <vaucanson/algebra/concrete/series/transpose.hh>
# include <vaucanson/algebra/concrete/series/rat/exp.hh>

namespace vcsn
{
  template<typename EdgeIterator>
  struct transposed_edge_iterator
    : public EdgeIterator
  {
    transposed_edge_iterator();

    transposed_edge_iterator(const EdgeIterator& other);

    unsigned aim() const;

    unsigned origin() const;
  };


  //
  // TransposeImpl
  //
  // Description : it is an automaton adapter to view an automaton as its
  //               transposed (no data copied.)

  template
  <
    typename OtherImpl, 
    class TransposeLabelFun 
  >
  class TransposeImpl : public OtherImpl::adapter_kind_t
  {
  protected:
    typedef OtherImpl				impl_t;
    // FIXME : these attributes are odd.
    utility::ref<impl_t>			impl_ref_;
    impl_t*					impl_;
    TransposeLabelFun				transpose_label_fun_;

  public:
    typedef typename OtherImpl::adapter_kind_t  adapter_kind_t;
    typedef typename OtherImpl::tag_t		tag_t;
    typedef typename OtherImpl::series_t	series_t;
    typedef typename OtherImpl::series_value_t  series_value_t;

    typedef typename OtherImpl::label_t		label_t;
    typedef typename OtherImpl::states_t	states_t;
    typedef typename OtherImpl::edges_t		edges_t;

    TransposeImpl();

    TransposeImpl(const TransposeImpl& other);

    TransposeImpl(const utility::ref<impl_t>& r);

    typename automaton_traits<impl_t>::states_ret_t
    states() const;

    typename automaton_traits<impl_t>::edges_ret_t
    edges() const;

    typename automaton_traits<impl_t>::final_ret_t
    initial() const;

    typename automaton_traits<impl_t>::initial_ret_t
    final() const;

    tag_t& tag();

    const tag_t& tag() const;

    unsigned add_state();

    unsigned add_edge(unsigned from, unsigned to, const label_t& label);

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

    void set_initial(unsigned s);

    void unset_initial(unsigned s);

    template<typename T>
    void set_initial(unsigned s, const Element<series_t, T>& v);

    void set_final(unsigned s);

    void unset_final(unsigned s);

    template<typename T>
    void set_final(unsigned s, const Element<series_t, T>& v);

    Element<series_t, series_value_t>
    get_initial(unsigned s) const;

    Element<series_t, series_value_t>
    get_final(unsigned s) const;

    unsigned origin_of(unsigned e) const;

    unsigned aim_of(unsigned e) const;

    typename automaton_traits<impl_t>::label_ret_t
    label_of(unsigned e) const;

    series_t& series();
    
    const series_t& series() const;

    // not for public use:
    // FIXME : so, use another permission. Why is it not private ?

    impl_t& impl();
    
    const impl_t& impl() const;

    utility::ref<impl_t>& ref();
    
    const utility::ref<impl_t>& ref() const;

  };

  template<typename I, typename F>
  struct automaton_traits<TransposeImpl<I, F> >
    : automaton_traits<I>
  {
    typedef typename automaton_traits<I>::initial_t	final_t;
    typedef typename automaton_traits<I>::final_t	initial_t;
    typedef typename automaton_traits<I>::initial_ret_t final_ret_t;
    typedef typename automaton_traits<I>::final_ret_t	initial_ret_t;

    typedef 
    transposed_edge_iterator<typename automaton_traits<I>::edge_iterator> 
    edge_iterator;
  };


  template<typename Auto>
  struct transpose_traits
  {
    typedef typename Auto::value_t		       	   original_ref_t;
    typedef typename original_ref_t::element_type	   original_impl_t;

    typedef TransposeImpl
    <
      original_impl_t, 
      // FIXME: this is broken. We need to be more intelligent.
      DefaultTransposeFun<
      typename Auto::series_t, 
      typename original_impl_t::label_t>
    > transpose_impl_t;
    typedef utility::ref<transpose_impl_t>		   transpose_ref_t;
    
    typedef 
    Element<typename Auto::set_t, transpose_ref_t> 
    transpose_t;
  };

  
  template<typename Auto>
  typename transpose_traits<Auto>::transpose_t
  transpose_view(const Auto& a);

} // vcsn

# include <vaucanson/automata/concept/transpose_impl.hxx>

#endif
