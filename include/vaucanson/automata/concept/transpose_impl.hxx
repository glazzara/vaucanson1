// transpose_impl.hxx
//
// VCSN_HEADER

#ifndef AUTOMATA_TRANSPOSE_IMPL_HXX
# define AUTOMATA_TRANSPOSE_IMPL_HXX

# include <functional>

# include <vaucanson/automata/concept/transpose_impl.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/fundamental/slots.hh>
# include <vaucanson/misc/ref.hh>

namespace vcsn
{

  // methods of |template<typename EdgeIterator> struct transposed_edge_iterator|

  template<typename EdgeIterator> 
  transposed_edge_iterator<EdgeIterator>::transposed_edge_iterator()
    : EdgeIterator()
  {}

  template<typename EdgeIterator> 
  transposed_edge_iterator<EdgeIterator>::
  transposed_edge_iterator(const EdgeIterator& other)
    : EdgeIterator(other)
  {}

  template<typename EdgeIterator>
  unsigned transposed_edge_iterator<EdgeIterator>::aim() const
  { 
    return EdgeIterator::origin(); 
  }

  template<typename EdgeIterator>
  unsigned transposed_edge_iterator<EdgeIterator>::origin() const
  { 
    return EdgeIterator::aim(); 
  }
  

  //
  // TransposeImpl
  //
  // Description : it is an automaton adapter to view an automaton as its
  //               transposed (no data copied.)


    template <typename OtherImpl, class TransposeLabelFun>
    TransposeImpl<OtherImpl, TransposeLabelFun>::TransposeImpl() 
    {
      impl_ref_.reset(impl_ = new impl_t());
    }

    template <typename OtherImpl, class TransposeLabelFun>
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    TransposeImpl(const TransposeImpl& other)
      : impl_ref_(other.impl_ref_), impl_(other.impl_)
    {}

    template <typename OtherImpl, class TransposeLabelFun>
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    TransposeImpl(const utility::ref<impl_t>& r)
      : impl_ref_(r), impl_(r.get())
    {
      assert(impl_ != 0);
    }

    template <typename OtherImpl, class TransposeLabelFun>
    typename automaton_traits<OtherImpl>::states_ret_t
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    states() const
    { 
      return impl().states(); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    typename automaton_traits<OtherImpl>::edges_ret_t
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    edges() const
    { 
      return impl().edges(); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    typename automaton_traits<OtherImpl>::final_ret_t
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    initial() const
    { 
      return impl().final(); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    typename automaton_traits<OtherImpl>::initial_ret_t
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    final() const
    { 
      return impl().initial(); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    typename OtherImpl::tag_t& 
    TransposeImpl<OtherImpl, TransposeLabelFun>::tag() 
    { 
      return impl().tag(); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    const typename OtherImpl::tag_t& 
    TransposeImpl<OtherImpl, TransposeLabelFun>::tag() const 
    { 
      return impl().tag(); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    unsigned 
    TransposeImpl<OtherImpl, TransposeLabelFun>::add_state()
    { 
      return impl().add_state(); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    unsigned 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    add_edge(unsigned from, unsigned to, const label_t& label)
    { 
      // FIXME : transpose label.
      return impl().add_edge(to, from, transpose_label_fun_(label)); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    del_state(unsigned s)
    { 
      impl().del_state(s); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    del_edge(unsigned e)
    { 
      impl().del_edge(e); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    safe_del_state(unsigned s)
    { 
      impl().safe_del_state(s); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    bool 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    has_state(unsigned s) const
    { 
      return impl().has_state(s); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    bool 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    has_edge(unsigned e) const
    { 
      return impl().has_edge(e); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    template<typename Iter>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    delta_states(Iter out, unsigned from) const
    { 
      impl().rdelta_states(out, from);  
    }

    template <typename OtherImpl, class TransposeLabelFun>
    template<typename Iter>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    delta_edges(Iter out, unsigned from) const
    { 
      impl().rdelta_edges(out, from); 
    }
    
    template <typename OtherImpl, class TransposeLabelFun>
    template<typename Iter, typename T>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    delta_states(Iter out, unsigned from, const T& q) const
    { 
      impl().rdelta_states(out, from, q); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    template<typename Iter, typename T>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    delta_edges(Iter out, unsigned from, const T& q) const
    { 
      impl().rdelta_edges(out, from, q); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    template<typename Iter>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    rdelta_states(Iter out, unsigned from) const
    { 
      impl().delta_states(out, from); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    template<typename Iter>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    rdelta_edges(Iter out, unsigned from) const
    { 
      impl().delta_edges(out, from); 
    }
    
    template <typename OtherImpl, class TransposeLabelFun>
    template<typename Iter, typename T>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    rdelta_states(Iter out, unsigned from, const T& q) const
    { 
      impl().delta_states(out, from, q); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    template<typename Iter, typename T>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    rdelta_edges(Iter out, unsigned from, const T& q) const
    { 
      impl().delta_edges(out, from, q); 
    }
     
    template <typename OtherImpl, class TransposeLabelFun>
    bool 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    is_initial(unsigned s) const
    { 
      return impl().is_final(s); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    bool 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    is_final(unsigned s) const
    { 
      return impl().is_initial(s); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    set_initial(unsigned s)
    { 
      impl().set_final(s); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    unset_initial(unsigned s)
    { 
      impl().unset_final(s); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    template<typename T>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    set_initial(unsigned s, const Element<series_t, T>& v)
    { 
      impl().set_final(s, v); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    set_final(unsigned s)
    { 
      impl().set_initial(s); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    unset_final(unsigned s)
    { 
      impl().unset_initial(s); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    template<typename T>
    void 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    set_final(unsigned s, const Element<series_t, T>& v)
    { 
      impl().set_initial(s, v); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    Element<typename OtherImpl::series_t, typename OtherImpl::series_value_t>
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    get_initial(unsigned s) const
    { 
      return impl().get_final(s); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    Element<typename OtherImpl::series_t, typename OtherImpl::series_value_t>
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    get_final(unsigned s) const
    { 
      return impl().get_initial(s); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    unsigned 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    origin_of(unsigned e) const
    { 
      return impl().aim_of(e); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    unsigned 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    aim_of(unsigned e) const
    { 
      return impl().origin_of(e); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    typename automaton_traits<OtherImpl>::label_ret_t
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    label_of(unsigned e) const
    { 
      // FIXME : transpose label
      return transpose_label_fun_(impl().label_of(e)); 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    OtherImpl::series_t& 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    series() 
    { 
      return impl().series(); 
    }
    
    template <typename OtherImpl, class TransposeLabelFun>
    const typename OtherImpl::series_t& 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    series() const 
    { 
      return impl().series(); 
    }

    // not for public use:
    // FIXME : so, use another permission. Why is it not private ?

    template <typename OtherImpl, class TransposeLabelFun>
    OtherImpl& 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    impl() 
    { 
      return *impl_; 
    }
    
    template <typename OtherImpl, class TransposeLabelFun>
    const OtherImpl& 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    impl() const 
    { 
      return *impl_; 
    }

    template <typename OtherImpl, class TransposeLabelFun>
    utility::ref<OtherImpl>& 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    ref() 
    { 
      return impl_ref_; 
    }
    
    template <typename OtherImpl, class TransposeLabelFun>
    const utility::ref<OtherImpl>& 
    TransposeImpl<OtherImpl, TransposeLabelFun>::
    ref() const 
    { 
      return impl_ref_; 
    }

  template<typename Auto>
  typename transpose_traits<Auto>::transpose_t
  transpose_view(const Auto& a)
  {
    typedef transpose_traits<Auto>		t;    
    typename t::transpose_ref_t			tref;
    
    tref.reset(new typename t::transpose_impl_t(a.value()));
    return typename t::transpose_t(a.set(), tref);
  }

} // vcsn

#endif
