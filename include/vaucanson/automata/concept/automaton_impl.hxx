/******************************************
 * <vaucanson/automata/automaton_impl.hxx> *
 ******************************************/

/* this file is part of the Vaucanson project */
#ifndef AUTOMATA_AUTOMATON_IMPL_HXX
#define AUTOMATA_AUTOMATON_IMPL_HXX

#include <vaucanson/fundamental/slots.hh>
#include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn
{
 


  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  AutomatonImpl() {}

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  AutomatonImpl(const AutomatonImpl& other) 
    : impl_(other.impl_),
      tag_(other.tag_),
      series_(other.series_),
      initial_(other.initial_),
      final_(other.final_)
  {}


  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  typename automaton_traits<Backend>::states_ret_t
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  states() const
  { return auto_op_states(series(), impl_); }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  typename automaton_traits<Backend>::edges_ret_t
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  edges() const
  { return auto_op_edges(series(), impl_); }
    
  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  typename automaton_traits<Backend>::initial_ret_t
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  initial() const
  { return auto_op_initial(series(), impl_); }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  typename automaton_traits<Backend>::final_ret_t
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  final() const
  { return auto_op_final(series(), impl_); }

    
  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  Tag&
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  tag() { return tag_; }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  const Tag& 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  tag() const { return tag_; }
   
  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  unsigned 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  add_state()
  { return auto_op_add_state(series(), impl_); }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  unsigned 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  add_edge(unsigned from, unsigned to, const label_t& label)
  { return auto_op_add_edge(series(), impl_, from, to, label); }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  del_state(unsigned s)
  { 
    initial_.erase(s);
    final_.erase(s);
    auto_op_del_state(series(), impl_, s); 
  }
    
  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  del_edge(unsigned e)
  { 
    auto_op_del_edge(series(), impl_, e); 
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  safe_del_state(unsigned s)
  { 
    initial_.erase(s);
    final_.erase(s);
    auto_op_safe_del_state(series(), impl_, s); 
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  bool 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  has_state(unsigned s) const
  { 
    return auto_op_has_state(series(), impl_, s); 
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  bool 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  has_edge(unsigned e) const
  { 
    return auto_op_has_edge(series(), impl_, e); 
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  template<typename Iter>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  delta_states(Iter out, unsigned from) const
  { 
    auto_op_delta_states(series(), impl_, out, from); 
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  template<typename Iter>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  delta_edges(Iter out, unsigned from) const
  { 
    auto_op_delta_edges(series(), impl_, out, from); 
  }
    
  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  template<typename Iter, typename T>
  void
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  delta_states(Iter out, unsigned from, const T& q) const
  { 
    auto_op_delta_states(series(), impl_, out, from, q); 
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  template<typename Iter, typename T>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  delta_edges(Iter out, unsigned from, const T& q) const
  { 
    auto_op_delta_edges(series(), impl_, out, from, q); 
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  template<typename Iter>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  rdelta_states(Iter out, unsigned from) const
  { 
    auto_op_rdelta_states(series(), impl_, out, from); 
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  template<typename Iter>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  rdelta_edges(Iter out, unsigned from) const
  { 
    auto_op_rdelta_edges(series(), impl_, out, from); 
  }
    
  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  template<typename Iter, typename T>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  rdelta_states(Iter out, unsigned from, const T& q) const
  { 
    auto_op_rdelta_states(series(), impl_, out, from, q); 
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  template<typename Iter, typename T>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  rdelta_edges(Iter out, unsigned from, const T& q) const
  { 
    auto_op_rdelta_edges(series(), impl_, out, from, q); 
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  bool
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  is_initial(unsigned s) const
  { 
    return initial().find(s) != initial().end(); 
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  bool 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  is_final(unsigned s) const
  { 
    return final().find(s) != final().end(); 
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  set_initial(unsigned s)
  {
    auto_op_set_initial(series(), impl_, s);
    initial_[s] = identity_value(SELECT(series_t), SELECT(series_value_t));
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  unset_initial(unsigned s)
  {
    auto_op_clear_initial(series(), impl_, s);
    initial_.erase(s);
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  clear_initial()
  {
    for (typename map_t::const_iterator i = initial_.begin();
	 i != initial_.end();
	 ++i)
      auto_op_clear_initial(series(), impl_, i->first);
    initial_.clear();
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  template<typename T>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  set_initial(unsigned s, const Element<series_t, T>& v)
  {
    if (v == zero_value(SELECT(series_t), SELECT(series_value_t)))
      {
	initial_.erase(s);
	auto_op_clear_initial(series(), impl_, s);
      }
    else
      {
	auto_op_set_initial(series(), impl_, s);
	initial_[s] = op_convert(SELECT(series_value_t), SELECT(series_t), v.value());
      }
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  set_final(unsigned s)
  {
    auto_op_set_final(series(), impl_, s);
    final_[s] = identity_value(SELECT(series_t), SELECT(series_value_t));
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  unset_final(unsigned s)
  {
    auto_op_clear_final(series(), impl_, s);
    final_.erase(s);
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  clear_final()
  {
    for (typename map_t::const_iterator i = final_.begin();
	 i != final_.end();
	 ++i)
      auto_op_clear_final(series(), impl_, i->first);
    final_.clear();
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  template<typename T>
  void 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  set_final(unsigned s, const Element<series_t, T>& v)
  {
    if (v == zero_value(SELECT(series_t), SELECT(series_value_t)))
      {
	final_.erase(s);
	auto_op_clear_final(series(), impl_, s);
      }
    else
      {
	auto_op_set_final(series(), impl_, s);
	final_[s] = op_convert(SELECT(series_value_t), SELECT(series_t), v.value());
      }
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  Element<Series, SeriesT>
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::    
  get_initial(unsigned s) const
  {
    typename map_t::const_iterator i;
    if ((i = initial_.find(s)) == initial_.end())
      return Element<series_t, series_value_t>
	(series(), zero_value(SELECT(series_t), SELECT(series_value_t)));

    return Element<series_t, series_value_t>(series(), i->second);
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  Element<Series, SeriesT>
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  get_final(unsigned s) const
  {
    typename map_t::const_iterator i;
    if ((i = final_.find(s)) == final_.end())
      return Element<series_t, series_value_t>
	(series(), zero_value(SELECT(series_t), SELECT(series_value_t)));

    return Element<series_t, series_value_t>(series(), i->second);
  }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  unsigned 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  origin_of(unsigned e) const
  { return edges().find(e).origin(); }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  unsigned 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  aim_of(unsigned e) const
  { return edges().find(e).aim(); }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  typename automaton_traits<Backend>::label_ret_t
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::    
  label_of(unsigned e) const
  { return edges().find(e).label(); }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  Series& 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  series()
  { return series_; }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  const Series& 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  series() const { return series_; }

  // this is not for public use:
  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  Backend& 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  impl() { return impl_; }

  template<typename Kind, typename Series, typename SeriesT,
	   class Backend, typename Tag,
	   template <class, class> class Container>
  const Backend& 
  AutomatonImpl<Kind, Series, SeriesT, Backend, Tag, Container>::
  impl() const 
  { return impl_; }


}  //vcsn

#endif
