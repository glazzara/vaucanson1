// automaton_impl.hh
//
// $Id$
// VCSN_HEADER
#ifndef AUTOMATA_AUTOMATON_IMPL_HH
#define AUTOMATA_AUTOMATON_IMPL_HH

#include <vaucanson/fundamental/slots.hh>
#include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn
{
  template<typename Kind,
	   typename Series /* the Series algebraic structure type */,
	   typename SeriesT /* the data type for series values in initial/final */,
	   class Backend /* the class doing all the dirty work */, 
	   typename Tag /* the tag type for the automaton */,
	   template <class, class> class Container /* the container used for storing initial/final */>
  class AutomatonImpl
  {
  protected:
    typedef Container<unsigned, SeriesT> map_t;
  public:

    typedef Kind adapter_kind_t;
    typedef Tag tag_t;
    typedef Series series_t;
    typedef SeriesT series_value_t;

    typedef typename Backend::label_t label_t;

    typedef typename Backend::states_t states_t;
    typedef typename Backend::edges_t edges_t;

    AutomatonImpl();
    AutomatonImpl(const AutomatonImpl& other);

//     template<typename K_, typename T_, typename B_, typename Tg_, template<class,class> class C_>
//     AutomatonImpl(const AutomatonImpl<K_, Series, T_, B_, Tg_, C_>& other)
//       : series_(other.series())
//     {
//       // FIXME: insert copy code here 
//     }
    
    // there is no operator= in this class, because copy is handled
    // through utility::ref<>.

    typename automaton_traits<Backend>::states_ret_t
    states() const;

    typename automaton_traits<Backend>::edges_ret_t
    edges() const;

    typename automaton_traits<Backend>::initial_ret_t
    initial() const;

    typename automaton_traits<Backend>::final_ret_t
    final() const;


    Tag& tag();
    const Tag& tag() const;

    
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

    void clear_initial();

    template<typename T>
    void set_initial(unsigned s, const Element<series_t, T>& v);

    void set_final(unsigned s);


    void unset_final(unsigned s);

    void clear_final();

    template<typename T>
    void set_final(unsigned s, const Element<series_t, T>& v);

    Element<series_t, series_value_t>
    get_initial(unsigned s) const;

    Element<series_t, series_value_t>
    get_final(unsigned s) const;

    unsigned origin_of(unsigned e) const;

    unsigned aim_of(unsigned e) const;

    typename automaton_traits<Backend>::label_ret_t
    label_of(unsigned e) const;

    Series& series();
    const Series& series() const;

    // this is not for public use:
    Backend& impl();
    const Backend& impl() const;

  protected:
    Backend impl_;
    Tag tag_;
    Series series_;
    map_t initial_;
    map_t final_;
  };

  template<typename K, typename S, typename T, typename B, typename Tg, template<class,class>class C>
  struct automaton_traits<AutomatonImpl<K, S, T, B, Tg, C> >
  {
    typedef K adapter_kind_t;
    typedef S series_t;
    typedef T series_value_t;
    typedef Tg tag_t;
    typedef typename B::label_t label_t;
    typedef typename B::states_t states_t;
    typedef typename B::edges_t edges_t;
    typedef typename B::initial_t initial_t;
    typedef typename B::final_t final_t;

    typedef typename states_t::const_iterator state_iterator;
    typedef typename edges_t::const_iterator edge_iterator;

    typedef typename automaton_traits<B>::states_ret_t states_ret_t;
    typedef typename automaton_traits<B>::edges_ret_t edges_ret_t;
    typedef typename automaton_traits<B>::initial_ret_t initial_ret_t;
    typedef typename automaton_traits<B>::final_ret_t final_ret_t;
    typedef typename automaton_traits<B>::label_ret_t label_ret_t;
  };


}

# include <vaucanson/automata/concept/automaton_impl.hxx>

#endif
