// algebra/polynoms.hxx
//
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef ALGEBRA_POLYNOMS_HXX
# define ALGEBRA_POLYNOMS_HXX

# include <vaucanson/algebra/concrete/series/polynoms.hh>
# include <vaucanson/algebra/concept/freemonoid_base.hh>

namespace vcsn {

  namespace algebra {

    /*----------------.
      | polynom<Tm, Tw> |
      `----------------*/

    template<typename Tm, typename Tw>
    template<typename M, typename W>
    polynom<Tm, Tw>::polynom(SELECTOR(M), SELECTOR(W))
    {
      map_.insert(std::make_pair(identity_value(SELECT(M), SELECT(Tm)),
				 identity_value(SELECT(W), SELECT(Tw))));
    }
    
    template<typename Tm, typename Tw>
    polynom<Tm, Tw>::polynom(const polynom& other) : map_(other.map_) 
    {}
    
    template<typename Tm, typename Tw>
    polynom<Tm, Tw>::polynom() : map_() 
    {}
    
    template<typename Tm, typename Tw>
    size_t 
    polynom<Tm, Tw>::size() const
    { 
      return map_.size(); 
    }
    
    template<typename Tm, typename Tw>
    bool polynom<Tm, Tw>::empty() const
    { 
      return map_.empty(); 
    }
    
    template<typename Tm, typename Tw>
    typename polynom<Tm, Tw>::iterator 
    polynom<Tm, Tw>::begin() 
    { 
      return map_.begin(); 
    }
    
    template<typename Tm, typename Tw>    
    typename polynom<Tm, Tw>::const_iterator 
    polynom<Tm, Tw>::begin() const 
    { 
      return map_.begin(); 
    }
    
    template<typename Tm, typename Tw>
    typename polynom<Tm, Tw>::iterator 
    polynom<Tm, Tw>::end() 
    { 
      return map_.end(); 
    }
    
    template<typename Tm, typename Tw>    
    typename polynom<Tm, Tw>::const_iterator 
    polynom<Tm, Tw>::end() const 
    { 
      return map_.end(); 
    }
    
    template<typename Tm, typename Tw>
    typename polynom<Tm, Tw>::iterator 
    polynom<Tm, Tw>::find(const Tm& m) 
    { 
      return map_.find(m); 
    }
    
    template<typename Tm, typename Tw>
    typename polynom<Tm, Tw>::const_iterator 
    polynom<Tm, Tw>::find(const Tm& m) const
    { 
      return map_.find(m); 
    }

    template<typename Tm, typename Tw>    
    template<typename W>
    Tw& polynom<Tm, Tw>::make_get(SELECTOR(W), const Tm& m)
    {
      std::pair<iterator, bool> i = 
	map_.insert(std::make_pair(m, zero_value(SELECT(W), SELECT(Tw))));
      return i.first->second;
    }
    
    template<typename Tm, typename Tw>    
    template<typename W>
    Tw polynom<Tm, Tw>::get(SELECTOR(W), const Tm& m) const
    {
      const_iterator i;
            
      if ((i = map_.find(m)) == map_.end())
	return zero_value(SELECT(W), SELECT(Tw));
      return i->second;
    }
    
    template<typename Tm, typename Tw>    
    void polynom<Tm, Tw>::insert(const Tm& m, const Tw& w)
    { 
      map_.insert(std::make_pair(m, w)); 
    }
    
    template<typename Tm, typename Tw>    
    template<typename W>
    void polynom<Tm, Tw>::add(const W& weights, const Tm& m, const Tw& w)
    {
      Tw& o = make_get(SELECT(W), m);
      op_in_add(weights, o, w);
    }
    
    template<typename Tm, typename Tw>        
    void polynom<Tm, Tw>::erase(iterator i)
    { 
      map_.erase(i); 
    }
    
    template<typename Tm, typename Tw>    
    void polynom<Tm, Tw>::clear() 
    { 
      map_.clear(); 
    }
    
    template<typename Tm, typename Tw>        
    void polynom<Tm, Tw>::swap(polynom<Tm, Tw>& other)
    { 
      map_.swap(other.map_); 
    }

    template<typename Tm, typename Tw>        
    const std::map<Tm, Tw>&
    polynom<Tm, Tw>::as_map() const
    { 
      return map_;
    }

    template <class Series, class Tm, class Tw>
    polynom<Tm,Tw>
    DefaultTransposeFun<Series, polynom<Tm,Tw> >::
    operator()(const Series& s,const polynom<Tm,Tw>& t) const
    {
      typedef typename polynom<Tm, Tw>::const_iterator const_iterator;
      typedef typename Series::monoid_elt_t	       monoid_elt_t;
      polynom<Tm, Tw>	new_t;

      for (const_iterator i = t.begin(); i != t.end(); ++i)
	new_t[mirror(monoid_elt_t((*i).first))] = (*i).second;
      return new_t;
    }

  } // algebra

} // vcsn

namespace std {

  using namespace vcsn;
  using namespace algebra;

  template <class Tm, class Tw>
  bool operator==(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs)
  {
    return lhs.as_map() == rhs.as_map();
  }

  template <class Tm, class Tw>
  bool operator!=(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs)
  {
    return !(lhs == rhs);
  }


  template <class Tm, class Tw>
  bool operator<(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs)
  {
    return lhs.as_map() < rhs.as_map();
  }

  template <class Tm, class Tw>
  bool operator>(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs)
  {
    return lhs.as_map() > rhs.as_map();
  }

  template <class Tm, class Tw>
  bool operator<=(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs)
  {
    return lhs.as_map() <= rhs.as_map();
  }

  template <class Tm, class Tw>
  bool operator>=(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs)
  {
    return lhs.as_map() >= rhs.as_map();
  }

} // std

namespace vcsn {
 
  /*-------------------.
    | External functions |
    `-------------------*/

  template<typename W, typename M, typename Tm, typename Tw>
  bool op_contains(const Series<W, M>& s, const polynom<Tm, Tw>& m)
  { 
    for (typename polynom<Tm, Tw>::const_iterator i = m.begin();
	 i != m.end();
	 ++i)
      if (!s.monoid().contains(i->first) || !s.weights().contains(i->second))
	return false;
    return true; 
  }

  template<typename W, typename M, typename Tm, typename Tw>
  bool op_is_finite_app(const Series<W, M>& s, const polynom<Tm, Tw>& m)
  { 
    return true; 
  }

  template<typename W, typename M, typename Tm, typename Tw>
  const polynom<Tm, Tw>& identity_value(SELECTOR2(Series<W, M>), 
					SELECTOR2(polynom<Tm, Tw>))
  {
    static const polynom<Tm, Tw> instance = 
      polynom<Tm, Tw>(SELECT(M), SELECT(W));
    return instance;
  }

  template<typename W, typename M, typename Tm, typename Tw>
  const polynom<Tm, Tw>& zero_value(SELECTOR2(Series<W, M>), 
				    SELECTOR2(polynom<Tm, Tw>))
  {
    static const polynom<Tm, Tw> instance;
    return instance;
  }

  template<typename W, typename M, typename Tm, typename Tw>
  void op_in_add(const Series<W, M>& s, 
		 polynom<Tm, Tw>& dst,
		 const polynom<Tm, Tw>& arg)
  {
    typename polynom<Tm, Tw>::iterator p;
    Tw zero = zero_value(SELECT(W), SELECT(Tw));
    Tw w;

    for (typename polynom<Tm, Tw>::const_iterator i = arg.begin();
	 i != arg.end();
	 ++i)
      if (i->second != zero)
	{
	  p = dst.find(i->first);
	  if (p != dst.end())
	    {
	      w = i->second;
	      op_in_add(s.weights(), w, p->second);
	      if (w == zero_value(SELECT(W), SELECT(Tw)))
		dst.erase(p);
	      else
		p->second = w;
	    }
	  else
	    dst.insert(i->first, i->second);
	}
  }

  template<typename W, typename M, typename Tm, typename Tw>
  polynom<Tm, Tw> op_add(const Series<W, M>& s,
			 const polynom<Tm, Tw>& a,
			 const polynom<Tm, Tw>& b)
  {
    polynom<Tm, Tw> ret(a);
    op_in_add(s, ret, b);
    return ret;
  }

  /*-----------------.
    | cauchy's product |
    `-----------------*/
  template<typename W, typename M, typename Tm, typename Tw>
  polynom<Tm, Tw> op_mul(const Series<W, M>& s,
			 const polynom<Tm, Tw>& a,
			 const polynom<Tm, Tw>& b)
  {
    polynom<Tm, Tw> ret;
    for (typename polynom<Tm, Tw>::const_iterator i = a.begin();
	 i != a.end();
	 ++i)
      for (typename polynom<Tm, Tw>::const_iterator j = b.begin();
	   j != b.end();
	   ++j)
	{
	  Tw w = op_mul(s.weights(), i->second, j->second);
	  if (w != zero_value(SELECT(W), SELECT(Tw)))
	    ret.add(s.weights(),
		    op_mul(s.monoid(), i->first, j->first),
		    w);
	}
    return ret;
  }
    
  template<typename W, typename M, typename Tm, typename Tw>
  void op_in_mul(const Series<W, M>& s, 
		 polynom<Tm, Tw>& dst,
		 const polynom<Tm, Tw>& arg)
  {
    op_assign(s, dst, op_mul(s, dst, arg));
  }

  /*---------------------.
    | foreign constructors |
    `---------------------*/
  template<typename Tm, typename Tw, typename W, typename M, typename oTm>
  polynom<Tm, Tw> op_convert(SELECTOR2(polynom<Tm, Tw>),
			     SELECTOR2(Series<W, M>),
			     SELECTOR(M),
			     const oTm& m_value)
  {
    polynom<Tm, Tw> ret;
    ret.insert(op_convert(SELECT(Tm), SELECT(M), m_value),
	       identity_value(SELECT(W), SELECT(Tw)));
    return ret;
  }

  template<typename Tm, typename Tw, typename W, typename M, typename oTw>
  polynom<Tm, Tw> op_convert(SELECTOR2(polynom<Tm, Tw>),
			     SELECTOR2(Series<W, M>),
			     SELECTOR(W),
			     const oTw& w_value)
  {
    polynom<Tm, Tw> ret;
    if (w_value != zero_value(SELECT(W), SELECT(oTw)))
      ret.insert(identity_value(SELECT(M), SELECT(Tm)),
		 op_convert(SELECT(Tw), SELECT(W), w_value));
    return ret;
  }
    
  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  void op_assign(const Series<W, M>& s,
		 const M& monoid,
		 polynom<Tm, Tw>& dst,
		 const oTm& src)
  {
    dst.clear();
    dst.insert(op_convert(SELECT(Tm), SELECT(M), src),
	       identity_value(SELECT(W), SELECT(Tw)));
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  void op_assign(const Series<W, M>& s,
		 const W& weights,
		 polynom<Tm, Tw>& dst,
		 const oTw& src)
  {
    dst.clear();
    if (src != zero_value(SELECT(W), SELECT(oTw)))
      dst.insert(identity_value(SELECT(M), SELECT(Tm)),
		 op_convert(SELECT(Tw), SELECT(W), src));
  }

  /*--------------------------------------.
    | foreign addition with monoid elements |
    `--------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  void op_in_add(const Series<W, M>& s,
		 const M& monoid,
		 polynom<Tm, Tw>& dst,
		 const oTm& src)
  { 
    // assert(s.monoid() == monoid);
    dst.add(s.weights(), 
	    op_convert(SELECT(Tm), SELECT(M), src),
	    identity_value(SELECT(W), SELECT(Tw)));
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  polynom<Tm, Tw> op_add(const Series<W, M>& s,
			 const M& monoid,
			 const polynom<Tm, Tw>& a,
			 const oTm& b)
  { 
    polynom<Tm, Tw> ret(a);
    op_in_add(s, monoid, ret, b);
    return ret;
  }

  template<typename M, typename W, typename oTm, typename Tm, typename Tw>
  polynom<Tm, Tw> op_add(const M& monoid,
			 const Series<W, M>& s,
			 const oTm& a,
			 const polynom<Tm, Tw>& b)
  { 
    polynom<Tm, Tw> ret(b);
    op_in_add(s, monoid, ret, a);
    return ret;
  }

  /*---------------------------------------.
    | foreign addition with weights elements |
    `---------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  void op_in_add(const Series<W, M>& s,
		 const W& weights,
		 polynom<Tm, Tw>& dst,
		 const oTw& src)
  { 
    // assert(s.weights() == weights);
    if (src != zero_value(SELECT(W), SELECT(oTw)))
      dst.add(s.weights(), 
	      identity_value(SELECT(M), SELECT(Tm)),
	      op_convert(SELECT(Tw), SELECT(W), src));
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  polynom<Tm, Tw> op_add(const Series<W, M>& s,
			 const W& weights,
			 const polynom<Tm, Tw>& a,
			 const oTw& b)
  { 
    polynom<Tm, Tw> ret(a);
    op_in_add(s, weights, ret, b);
    return ret;
  }

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  polynom<Tm, Tw> op_add(const W& weights,
			 const Series<W, M>& s,
			 const oTw& a,
			 const polynom<Tm, Tw>& b)
  { 
    polynom<Tm, Tw> ret(b);
    op_in_add(s, weights, ret, a);
    return ret;
  }

  /*-------------------------------------------.
    | foreign multiplication by weights elements |
    `-------------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  void op_in_mul(const Series<W, M>& s,
		 const W&,
		 polynom<Tm, Tw>& dst,
		 const oTw& src)
  { 
    // assert(s.weights() == weights);

    typename polynom<Tm, Tw>::iterator p;
    for (typename polynom<Tm, Tw>::iterator i = dst.begin();
	 i != dst.end();
	 )
      {
	p = i++;
	op_in_mul(s.weights(), p->second, src);
	if (p->second == zero_value(SELECT(W), SELECT(Tw)))
	  dst.erase(p);
      }
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  polynom<Tm, Tw> op_mul(const Series<W, M>& s,
			 const W& weights,
			 const polynom<Tm, Tw>& a,
			 const oTw& b)
  { 
    polynom<Tm, Tw> ret(a);
    op_in_mul(s, weights, ret, b);
    return ret;
  }

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  polynom<Tm, Tw> op_mul(const W&,
			 const Series<W, M>& s,
			 const oTw& a,
			 const polynom<Tm, Tw>& b)
  { 
    // assert(s.weights() == weights);

    polynom<Tm, Tw> ret(b);

    typename polynom<Tm, Tw>::iterator p;
    for (typename polynom<Tm, Tw>::iterator i = ret.begin();
	 i != ret.end();
	 i = p)
      {
	p = i++;
	p->second = op_mul(s.weights(), a, p->second);
	if (p->second == zero_value(SELECT(W), SELECT(Tw)))
	  ret.erase(p);
      }
    return ret;
  }

  /*-------------.
  | input-output |
  `-------------*/

  template<typename W, typename M, typename St, typename Tm, typename Tw>
  St& op_rout(const Series<W, M>& s, St& st, const polynom<Tm, Tw>& p)
  {
      
    typename polynom<Tm, Tw>::const_iterator i = p.begin();
    while(i != p.end())
      {
	if (i != p.begin())
	  st << "+";
	if (i->second != identity_value(SELECT(W), SELECT(Tw)) ||
	    i->first == identity_value(SELECT(M), SELECT(Tm)))
	  op_rout(s.weights(), st, i->second);
	if (i->first != identity_value(SELECT(M), SELECT(Tm)))
	  {
	    if (i->second != identity_value(SELECT(W), SELECT(Tw)))
	      st << ".";
	    op_rout(s.monoid(), st, i->first);
	  }
	++i;
      }
    if (i == p.begin()) /* case zero */
      op_rout(s.weights(), st, zero_value(SELECT(W), SELECT(Tw)));
    return st;
  }

  /*---------------.
    | specialization |
    `---------------*/

  /*------------------------------.
    | fundamental series operations |
    `------------------------------*/

    
  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  Tw op_series_get(const Series<W, M>&, 
		   const polynom<Tm, Tw>& p,
		   const oTm& m)
  { 
    return p.get(SELECT(W), op_convert(SELECT(Tm), SELECT(M), m)); 
  }

  template <typename W, typename M, 
	    typename Tm, typename Tw, 
	    typename oTm, typename oTw>
  void op_series_set(const Series<W, M>&,
		     polynom<Tm, Tw>& p,
		     const oTm& m,
		     const oTw& w)
  {
    typename utility::static_if
      <utility::static_eq<Tm, oTm>::value, const Tm&, Tm>::t
      new_m = op_convert(SELECT(Tm), SELECT(M), m);
    typename utility::static_if
      <utility::static_eq<Tw, oTw>::value, const Tw&, Tw>::t
      new_w = op_convert(SELECT(Tw), SELECT(W), w);

    typename polynom<Tm, Tw>::iterator i = p.find(new_m);
    if (new_w == zero_value(SELECT(W), SELECT(Tw)))
      { 
	if (i != p.end())
	  p.erase(i);
      }
    else
      if (i == p.end())
	p.insert(new_m, new_w);
      else
	i->second = new_w;
  }


  template <class W, class M, class Tm, class Tw>
  Tm op_choose_from_supp(const Series<W, M>& s, 
			 const polynom<Tm, Tw>& p)
  {
    typedef typename polynom<Tm, Tw>::const_iterator const_iterator;

    if (p.size() == 0)
      return Tw();

    unsigned       index = rand() * p.size() / RAND_MAX;
    const_iterator i = p.begin();
    while ((index > 0) && (i != p.end()))
      {
	--index;
	++i;
      }
    return (*i).first;
  }


  template <class W, class M, class Tm, class Tw>
  Element<Series<W,M>, polynom<Tm,Tw> > 
  op_choose(const Series<W,M>& s, 
	    SELECTOR2(polynom<Tm,Tw>))
  {
    polynom<Tm, Tw> p;
    // FIXME: add global constants to define this !
    unsigned nb_monome = rand() * 10 / RAND_MAX;
    for (unsigned i = 0; i < nb_monome; ++i)
      p[s.monoid().choose()] = s.weights().choose();
    return Element<Series<W,M>, polynom<Tm,Tw> >(s, p);
  }

  /*----------.
  | transpose |
  `----------*/
  template <typename W, typename M, typename Tm, typename Tw>
  void  op_in_transpose(const Series<W, M>& s, polynom<Tm, Tw>& t)
  {
    typedef typename polynom<Tm, Tw>::const_iterator const_iterator;
    polynom<Tm, Tw>	new_t(t);

    t.clear();
    for (const_iterator i = new_t.begin(); i != new_t.end(); ++i)
      {
	Element<M, Tm> w(s.monoid(), i->first);
	t.insert(mirror(w).value(), (*i).second);
      }
  }

} // vcsn



#endif // ALGEBRA_POLYNOMS_HH

