// relabel_impl.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef AUTOMATA_RELABEL_IMPL_HXX
# define AUTOMATA_RELABEL_IMPL_HXX

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/ref.hh>
# include <vaucanson/misc/converter.hh>
# include <vaucanson/misc/functors.hh>
# include <vaucanson/automata/concept/transpose_impl.hh>

namespace vcsn
{
 

    template<typename Fun, typename EdgeIterator>
    relabeled_edge_iterator<Fun, EdgeIterator>::
    relabeled_edge_iterator()
      : EdgeIterator(), fun_()
    {}

    template<typename Fun, typename EdgeIterator>
    relabeled_edge_iterator<Fun, EdgeIterator>::    
    relabeled_edge_iterator(const relabeled_edge_iterator& other)
      : EdgeIterator(other), fun_(other.fun_)
    {}

    template<typename Fun, typename EdgeIterator>
    typename Fun::result_type 
    relabeled_edge_iterator<Fun, EdgeIterator>::
    label() const
    { 
      return fun_(EdgeIterator::label()); 
    }

    template<typename Fun, typename EdgeIterator>
    relabeled_edge_iterator<Fun, EdgeIterator>& 
    relabeled_edge_iterator<Fun, EdgeIterator>::
    operator=(const relabeled_edge_iterator& other)
    {
      EdgeIterator::operator=(other);
      fun_ = other.fun_;
      return *this;
    }
      
    template<typename Fun, typename EdgeIterator>
    relabeled_edge_iterator<Fun, EdgeIterator>& 
    relabeled_edge_iterator<Fun, EdgeIterator>::
    operator++()
    {
      EdgeIterator::operator++();
      return *this;
    }

    template<typename Fun, typename EdgeIterator>
    relabeled_edge_iterator<Fun, EdgeIterator>& 
    relabeled_edge_iterator<Fun, EdgeIterator>::
    operator--()
    {
      EdgeIterator::operator--();
      return *this;
    }

    template<typename Fun, typename EdgeIterator>
    relabeled_edge_iterator<Fun, EdgeIterator> 
    relabeled_edge_iterator<Fun, EdgeIterator>::
    operator++(int)
    {
      relabeled_edge_iterator tmp(*this);
      EdgeIterator::operator++();
      return tmp;
    }

    template<typename Fun, typename EdgeIterator>
    relabeled_edge_iterator<Fun, EdgeIterator>
    relabeled_edge_iterator<Fun, EdgeIterator>::
    operator--(int)
    {
      relabeled_edge_iterator tmp(*this);
      EdgeIterator::operator--();
      return tmp;
    }

    // not for public use:
  template<typename Fun, typename EdgeIterator>
  relabeled_edge_iterator<Fun, EdgeIterator>::
  relabeled_edge_iterator(const EdgeIterator& i,
			  const Fun& fun)
    : EdgeIterator(i), fun_(fun)
  {}



  template<typename Fun, typename Edges>
  EdgesAdapter<Fun, Edges>::
  EdgesAdapter(const Fun& f, const Edges& e)
    : fun_(f), e_(e)
  {}

  template<typename Fun, typename Edges>
  EdgesAdapter<Fun, Edges>::
  EdgesAdapter(const EdgesAdapter& other)
    : fun_(other.fun_), e_(other.e_)
  {}
  
  
  template<typename Fun, typename Edges>
  relabeled_edge_iterator<Fun, typename Edges::const_iterator> 
  EdgesAdapter<Fun, Edges>::
  begin() const
  { 
    return const_iterator(e_.begin(), fun_); 
  }

    template<typename Fun, typename Edges>
    relabeled_edge_iterator<Fun, typename Edges::const_iterator> 
    EdgesAdapter<Fun, Edges>::
    end() const
    { 
      return const_iterator(e_.end(), fun_); 
    }

    template<typename Fun, typename Edges>
    relabeled_edge_iterator<Fun, typename Edges::const_iterator> 
    EdgesAdapter<Fun, Edges>::
    find(unsigned i) const
    { 
      return const_iterator(e_.find(i), fun_); 
    }

    template<typename Fun, typename Edges>
    relabeled_edge_iterator<Fun, typename Edges::const_iterator> 
    EdgesAdapter<Fun, Edges>::
    operator[](unsigned i) const
    { 
      return const_iterator(e_[i], fun_); 
    }

    template<typename Fun, typename Edges>
    void 
    EdgesAdapter<Fun, Edges>::
    erase(const_iterator i)
    { 
      e_.erase(*i); 
    }

    template<typename Fun, typename Edges>
    void 
    EdgesAdapter<Fun, Edges>::
    erase(unsigned idx)
    { 
      e_.erase(idx); 
    }

    template<typename Fun, typename Edges>
    size_t 
    EdgesAdapter<Fun, Edges>::
    size() const
    { 
      return e_.size(); 
    }

    template<typename Fun, typename Edges>
    bool 
    EdgesAdapter<Fun, Edges>::
    empty() const
    { 
      return e_.empty(); 
    }



    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    RelabelImpl<OtherImpl, Kind, Series, SeriesT, LabelTranslator, SerieTranslator>::
    RelabelImpl()
      : lfun_(),
	sfun_()
    {
      impl_ref_.reset(impl_ = new impl_t());
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    RelabelImpl(const RelabelImpl& other)
      : impl_ref_(other.impl_ref_), 
	impl_(other.impl_),
	lfun_(other.lfun_),
	sfun_(other.sfun_)
    {}

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    RelabelImpl(const utility::ref<impl_t>& r, 
		const Series& s,
		const LabelTranslator& lfun,
		const SerieTranslator& sfun)
      : impl_ref_(r), impl_(r.get()),
	series_(s),
	lfun_(lfun), sfun_(sfun)
    {
      assert(impl_ != 0);
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    typename automaton_traits<OtherImpl>::states_ret_t
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    states() const
    { 
      return impl().states(); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    EdgesAdapter<LabelTranslator, typename OtherImpl::edges_t>
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    edges() const
    { 
      return edges_t(lfun_, impl().edges()); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    typename automaton_traits<OtherImpl>::initial_ret_t
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    initial() const
    { 
      return impl().initial(); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    typename automaton_traits<OtherImpl>::final_ret_t
    RelabelImpl< OtherImpl, Kind, Series, 
		 SeriesT, LabelTranslator, SerieTranslator>::
    final() const
    { 
      return impl().final(); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    typename OtherImpl::tag_t& 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    tag() 
    { 
      return impl().tag(); 
    }
    
    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    const typename OtherImpl::tag_t& 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    tag() const 
    { 
      return impl().tag(); 
    }

#ifndef NDEBUG
    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    unsigned 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    add_state()
    {
      assert(! "cannot add states to a relabel automaton");
      return 0;
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    template<typename T>
    unsigned 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    add_edge(unsigned from, unsigned to, const T& l)
    {
      assert(! "cannot add edges to a relabel automaton");
      return 0;
    }
#endif

    // these 3 are goodies, BUT only goodies.
    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    del_state(unsigned s)
    { 
      impl().del_state(s); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    del_edge(unsigned e)
    { 
      impl().del_edge(e); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    safe_del_state(unsigned s)
    { 
      impl().safe_del_state(s); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    bool 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    has_state(unsigned s) const
    { 
      return impl().has_state(s); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    bool 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    has_edge(unsigned e) const
    { 
      return impl().has_edge(e); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    template<typename Iter>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    delta_states(Iter out, unsigned from) const
    { 
      impl().delta_states(out, from);  
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    template<typename Iter>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    delta_edges(Iter out, unsigned from) const
    { 
      impl().delta_edges(out, from); 
    }
    
    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    template<typename Iter, typename T>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    delta_states(Iter out, unsigned from, const T& q) const
    { 
      impl().delta_states(out, from, utility::compose1_f_bool(q, lfun_)); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    template<typename Iter, typename T>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    delta_edges(Iter out, unsigned from, const T& q) const
    { 
      impl().delta_edges(out, from, utility::compose1_f_bool(q, lfun_)); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    template<typename Iter>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    rdelta_states(Iter out, unsigned from) const
    { 
      impl().rdelta_states(out, from); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    template<typename Iter>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    rdelta_edges(Iter out, unsigned from) const
    { 
      impl().rdelta_edges(out, from); 
    }
    
    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    template<typename Iter, typename T>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    rdelta_states(Iter out, unsigned from, const T& q) const
    { 
      impl().rdelta_states(out, from, utility::compose1(q, lfun_)); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    template<typename Iter, typename T>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    rdelta_edges(Iter out, unsigned from, const T& q) const
    { 
      impl().rdelta_edges(out, from, utility::compose1(q, lfun_)); 
    }
     
    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    bool 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    is_initial(unsigned s) const
    { 
      return impl().is_initial(s); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    bool 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    is_final(unsigned s) const
    { 
      return impl().is_final(s); 
    }

    // goodies
    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    set_initial(unsigned s)
    { 
      impl().set_final(s); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    unset_initial(unsigned s)
    { 
      impl().unset_final(s); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    set_final(unsigned s)
    { 
      impl().set_initial(s); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    unset_final(unsigned s)
    { 
      impl().unset_initial(s); 
    }

#ifndef NDEBUG
    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    template<typename T>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    set_initial(unsigned s, const T& t)
    { 
      assert(! "cannot set initial values on a relabel automaton");
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    template<typename T>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    unset_initial(unsigned s, const T& t)
    {
      assert(! "cannot unset initial values on a relabel automaton");
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    template<typename T>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    set_final(unsigned s, const T& t)
    { 
      assert(! "cannot set final values on a relabel automaton");
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    template<typename T>
    void 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    unset_final(unsigned s, const T& t)
    {
      assert(! "cannot unset final values on a relabel automaton");
    }
#endif
    
    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    Element<Series, SeriesT>
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    get_initial(unsigned s) const
    { 
      return sfun_(series(), impl().get_final(s)); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    Element<Series, SeriesT>
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    get_final(unsigned s) const
    { 
      return sfun_(series(), impl().get_initial(s)); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    unsigned 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    origin_of(unsigned e) const
    { 
      return impl().origin_of(e); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    unsigned 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    aim_of(unsigned e) const
    { 
      return impl().aim_of(e); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    typename LabelTranslator::result_type
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    label_of(unsigned e) const
    { 
      return lfun_(impl().label_of(e)); 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    Series& 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    series() 
    { 
      return series_; 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    const Series& 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    series() const 
    { 
      return series_; 
    }

    // not for public use:
    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    OtherImpl& 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    impl() 
    { 
      return *impl_; 
    }
    
    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    const OtherImpl& 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    impl() const 
    { 
      return *impl_; 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    utility::ref<OtherImpl>& 
    RelabelImpl< OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    ref() 
    { 
      return impl_ref_; 
    }

    template<typename OtherImpl, typename Kind, typename Series, 
	     typename SeriesT, typename LabelTranslator, typename SerieTranslator>
    const utility::ref<OtherImpl>& 
    RelabelImpl<OtherImpl,  Kind,  Series, 
		 SeriesT,  LabelTranslator,  SerieTranslator>::
    ref() const 
    { 
      return impl_ref_; 
    }

  
  template<typename Auto, typename K, typename S, typename T, typename Lf, typename Sf>
  typename relabel_traits<Auto, K, S, T, Lf, Sf>::relabel_t
  relabel_view(const Auto& a, 
	       K kind, 
	       const S& series, 
	       SELECTOR(T),
	       const Lf& lfun,
	       const Sf& sfun)
  {
    typedef relabel_traits<Auto, K, S, T, Lf, Sf> t;
    
    typename t::relabel_ref_t tref;
    
    tref.reset(new typename t::relabel_impl_t(a.value(), series, lfun, sfun));

    return typename t::relabel_t(a.set(), tref);
  }


}

#endif
