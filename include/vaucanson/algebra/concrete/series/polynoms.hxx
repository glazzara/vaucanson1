// polynoms.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_POLYNOMS_HXX
# define VCSN_ALGEBRA_CONCRETE_SERIES_POLYNOMS_HXX

# include <vaucanson/algebra/concrete/series/polynoms.hh>
# include <vaucanson/algebra/concept/freemonoid_base.hh>
# include <vaucanson/misc/contract.hh>

namespace vcsn {

  namespace algebra {

    /*----------------.
      | polynom<Tm, Tw> |
      `----------------*/
    
    template<typename Tm, typename Tw>
    template<typename M, typename W>
    inline
    polynom<Tm, Tw>::polynom(SELECTOR(M), SELECTOR(W))
    {
      map_.insert(std::make_pair(identity_value(SELECT(M), SELECT(Tm)),
				 identity_value(SELECT(W), SELECT(Tw))));
    }
    
    template<typename Tm, typename Tw>
    inline
    polynom<Tm, Tw>::polynom(const polynom& other) : map_(other.map_) 
    {}
    
    template<typename Tm, typename Tw>
    inline
    polynom<Tm, Tw>::polynom() : map_() 
    {}
    
    template<typename Tm, typename Tw>
    inline
    size_t 
    polynom<Tm, Tw>::size() const
    { 
      return map_.size(); 
    }
    
    template<typename Tm, typename Tw>
    inline
    bool polynom<Tm, Tw>::empty() const
    { 
      return map_.empty(); 
    }
    
    template<typename Tm, typename Tw>
    inline
    typename polynom<Tm, Tw>::iterator 
    polynom<Tm, Tw>::begin() 
    { 
      return map_.begin(); 
    }
    
    template<typename Tm, typename Tw>    
    inline
    typename polynom<Tm, Tw>::const_iterator 
    polynom<Tm, Tw>::begin() const 
    { 
      return map_.begin(); 
    }
    
    template<typename Tm, typename Tw>
    inline
    typename polynom<Tm, Tw>::iterator 
    polynom<Tm, Tw>::end() 
    { 
      return map_.end(); 
    }
    
    template<typename Tm, typename Tw>    
    inline
    typename polynom<Tm, Tw>::const_iterator 
    polynom<Tm, Tw>::end() const 
    { 
      return map_.end(); 
    }
    
    template<typename Tm, typename Tw>    
    inline
    typename polynom<Tm, Tw>::iterator 
    polynom<Tm, Tw>::find(const Tm& m) 
    { 
      return map_.find(m); 
    }
    
    template<typename Tm, typename Tw>
    inline
    typename polynom<Tm, Tw>::const_iterator 
    polynom<Tm, Tw>::find(const Tm& m) const
    { 
      return map_.find(m); 
    }

    template<typename Tm, typename Tw>    
    template<typename W>
    inline
    Tw& polynom<Tm, Tw>::make_get(SELECTOR(W), const Tm& m)
    {
      std::pair<iterator, bool> i = 
	map_.insert(std::make_pair(m, zero_value(SELECT(W), SELECT(Tw))));
      return i.first->second;
    }
    
    template<typename Tm, typename Tw>    
    template<typename W>
    inline
    Tw polynom<Tm, Tw>::get(SELECTOR(W), const Tm& m) const
    {
      const_iterator i;            
      if ((i = map_.find(m)) == map_.end())
	return zero_value(SELECT(W), SELECT(Tw));
      return i->second;
    }
    
    template<typename Tm, typename Tw>    
    inline
    void polynom<Tm, Tw>::insert(const Tm& m, const Tw& w)
    { 
      map_.insert(std::make_pair(m, w)); 
    }
    
    template<typename Tm, typename Tw>    
    template<typename W>
    inline
    void polynom<Tm, Tw>::add(const W& semiring, const Tm& m, const Tw& w)
    {
      Tw& o = make_get(SELECT(W), m);
      op_in_add(semiring, o, w);
    }
    
    template<typename Tm, typename Tw>        
    inline
    void polynom<Tm, Tw>::erase(iterator i)
    { 
      map_.erase(i); 
    }
    
    template<typename Tm, typename Tw>    
    inline
    void polynom<Tm, Tw>::clear() 
    { 
      map_.clear(); 
    }
    
    template<typename Tm, typename Tw>        
    inline
    void polynom<Tm, Tw>::swap(polynom<Tm, Tw>& other)
    { 
      map_.swap(other.map_); 
    }

    template<typename Tm, typename Tw>        
    inline
    const std::map<Tm, Tw>&
    polynom<Tm, Tw>::as_map() const
    { 
      return map_;
    }

    template <class Series, class Tm, class Tw>
    inline
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


    template <class Tm, class Tw>
    inline
    bool operator==(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs)
    {
      return lhs.as_map() == rhs.as_map();
    }
  
    template <class Tm, class Tw>
    inline
    bool operator!=(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs)
    {
      return !(lhs == rhs);
    }
  
  
    template <class Tm, class Tw>
    inline
    bool operator<(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs)
    {
      return lhs.as_map() < rhs.as_map();
    }

    template <class Tm, class Tw>
    inline
    bool operator>(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs)
    {
      return lhs.as_map() > rhs.as_map();
    }

    template <class Tm, class Tw>
    inline
    bool operator<=(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs)
    {
      return lhs.as_map() <= rhs.as_map();
    }

    template <class Tm, class Tw>
    inline
    bool operator>=(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs)
    {
      return lhs.as_map() >= rhs.as_map();
    }


  } // algebra

 
  /*-------------------.
    | External functions |
    `-------------------*/

  template<typename W, typename M, typename Tm, typename Tw>
  inline
  bool op_contains(const algebra::Series<W, M>& s, const algebra::polynom<Tm, Tw>& m)
  { 
    for (typename algebra::polynom<Tm, Tw>::const_iterator i = m.begin();
	 i != m.end();
	 ++i)
      if (!s.monoid().contains(i->first) || !s.semiring().contains(i->second))
	return false;
    return true; 
  }

  template<typename W, typename M, typename Tm, typename Tw>
  inline
  bool op_is_finite_app(const algebra::Series<W, M>& s, const algebra::polynom<Tm, Tw>& m)
  { 
    return true; 
  }

  template<typename W, typename M, typename Tm, typename Tw>
  inline
  typename algebra::series_traits<algebra::polynom<Tm, Tw> >::support_t
  op_support(const algebra::Series<W, M>&, const algebra::polynom<Tm, Tw>& m)
  { 
    return typename algebra::series_traits<algebra::polynom<Tm, Tw> >::support_t(m.as_map());
  }

  template<typename W, typename M, typename Tm, typename Tw>
  inline
  const algebra::polynom<Tm, Tw>& identity_value(SELECTOR2(algebra::Series<W, M>), 
						 SELECTOR2(algebra::polynom<Tm, Tw>))
  {
    static const algebra::polynom<Tm, Tw> instance = 
      algebra::polynom<Tm, Tw>(SELECT(M), SELECT(W));
    return instance;
  }

  template<typename W, typename M, typename Tm, typename Tw>
  inline
  const algebra::polynom<Tm, Tw>& zero_value(SELECTOR2(algebra::Series<W, M>), 
					     SELECTOR2(algebra::polynom<Tm, Tw>))
  {
    static const algebra::polynom<Tm, Tw> instance;
    return instance;
  }

  template<typename W, typename M, typename Tm, typename Tw>
  inline
  void op_in_add(const algebra::Series<W, M>& s, 
		 algebra::polynom<Tm, Tw>& dst,
		 const algebra::polynom<Tm, Tw>& arg)
  {
    typename algebra::polynom<Tm, Tw>::iterator p;
    Tw zero = zero_value(SELECT(W), SELECT(Tw));
    Tw w;

    for (typename algebra::polynom<Tm, Tw>::const_iterator i = arg.begin();
	 i != arg.end();
	 ++i)
      if (i->second != zero)
	{
	  p = dst.find(i->first);
	  if (p != dst.end())
	    {
	      w = i->second;
	      op_in_add(s.semiring(), w, p->second);
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
  inline
  algebra::polynom<Tm, Tw> op_add(const algebra::Series<W, M>& s,
				  const algebra::polynom<Tm, Tw>& a,
				  const algebra::polynom<Tm, Tw>& b)
  {
    algebra::polynom<Tm, Tw> ret(a);
    op_in_add(s, ret, b);
    return ret;
  }

  /*-----------------.
    | cauchy's product |
    `-----------------*/
  template<typename W, typename M, typename Tm, typename Tw>
  inline
  algebra::polynom<Tm, Tw> op_mul(const algebra::Series<W, M>& s,
				  const algebra::polynom<Tm, Tw>& a,
				  const algebra::polynom<Tm, Tw>& b)
  {
    algebra::polynom<Tm, Tw> ret;
    for (typename algebra::polynom<Tm, Tw>::const_iterator i = a.begin();
	 i != a.end();
	 ++i)
      for (typename algebra::polynom<Tm, Tw>::const_iterator j = b.begin();
	   j != b.end();
	   ++j)
	{
	  Tw w = op_mul(s.semiring(), i->second, j->second);
	  if (w != zero_value(SELECT(W), SELECT(Tw)))
	    ret.add(s.semiring(),
		    op_mul(s.monoid(), i->first, j->first),
		    w);
	}
    return ret;
  }
    
  template<typename W, typename M, typename Tm, typename Tw>
  inline
  void op_in_mul(const algebra::Series<W, M>& s, 
		 algebra::polynom<Tm, Tw>& dst,
		 const algebra::polynom<Tm, Tw>& arg)
  {
    op_assign(s, dst, op_mul(s, dst, arg));
  }

  /*---------------------.
    | foreign constructors |
    `---------------------*/
  template<typename Tm, typename Tw, typename W, typename M, typename oTm>
  inline
  algebra::polynom<Tm, Tw> op_convert(SELECTOR2(algebra::Series<W, M>),
				      SELECTOR2(algebra::polynom<Tm, Tw>),
				      SELECTOR(algebra::MonoidBase<M>),
				      const oTm& m_value)
  {
    algebra::polynom<Tm, Tw> ret;
    ret.insert(op_convert(SELECT(M), SELECT(Tm), m_value),
	       identity_value(SELECT(W), SELECT(Tw)));
    return ret;
  }

  template<typename Tm, typename Tw, typename W, typename M, typename oTw>
  inline
  algebra::polynom<Tm, Tw> op_convert(SELECTOR2(algebra::Series<W, M>),
				      SELECTOR2(algebra::polynom<Tm, Tw>),
				      SELECTOR(algebra::SemiringBase<W>),
				      const oTw& w_value)
  {
    algebra::polynom<Tm, Tw> ret;
    if (w_value != zero_value(SELECT(W), SELECT(oTw)))
      ret.insert(identity_value(SELECT(M), SELECT(Tm)),
		 op_convert(SELECT(W), SELECT(Tw), w_value));
    return ret;
  }
    
  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  inline
  void op_assign(const algebra::Series<W, M>&,
		 const algebra::MonoidBase<M>&,
		 algebra::polynom<Tm, Tw>& dst,
		 const oTm& src)
  {
    dst.clear();
    dst.insert(op_convert(SELECT(M), SELECT(Tm), src),
	       identity_value(SELECT(W), SELECT(Tw)));
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  inline
  void op_assign(const algebra::Series<W, M>& s,
		 const algebra::SemiringBase<W>&,
		 algebra::polynom<Tm, Tw>& dst,
		 const oTw& src)
  {
    dst.clear();
    if (src != zero_value(SELECT(W), SELECT(oTw)))
      dst.insert(identity_value(SELECT(M), SELECT(Tm)),
		 op_convert(SELECT(W), SELECT(Tw), src));
  }

  /*--------------------------------------.
    | foreign addition with monoid elements |
    `--------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  inline
  void op_in_add(const algebra::Series<W, M>& s,
		 const algebra::MonoidBase<M>& monoid,
		 algebra::polynom<Tm, Tw>& dst,
		 const oTm& src)
  { 
    precondition(& s.monoid() == & monoid);
    dst.add(s.semiring(), 
	    op_convert(SELECT(M), SELECT(Tm), src),
	    identity_value(SELECT(W), SELECT(Tw)));
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  inline
  algebra::polynom<Tm, Tw> op_add(const algebra::Series<W, M>& s,
				  const algebra::MonoidBase<M>& monoid,
				  const algebra::polynom<Tm, Tw>& a,
				  const oTm& b)
  { 
    algebra::polynom<Tm, Tw> ret(a);
    op_in_add(s, monoid, ret, b);
    return ret;
  }

  template<typename M, typename W, typename oTm, typename Tm, typename Tw>
  inline
  algebra::polynom<Tm, Tw> op_add(const algebra::MonoidBase<M>& monoid,
				  const algebra::Series<W, M>& s,
				  const oTm& a,
				  const algebra::polynom<Tm, Tw>& b)
  { 
    algebra::polynom<Tm, Tw> ret(b);
    op_in_add(s, monoid, ret, a);
    return ret;
  }

  /*---------------------------------------.
    | foreign addition with semiring elements |
    `---------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  inline
  void op_in_add(const algebra::Series<W, M>& s,
		 const algebra::SemiringBase<W>& semiring,
		 algebra::polynom<Tm, Tw>& dst,
		 const oTw& src)
  { 
    precondition(& s.semiring() == & semiring);
    if (src != zero_value(SELECT(W), SELECT(oTw)))
      dst.add(s.semiring(), 
	      identity_value(SELECT(M), SELECT(Tm)),
	      op_convert(SELECT(W), SELECT(Tw), src));
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  inline
  algebra::polynom<Tm, Tw> op_add(const algebra::Series<W, M>& s,
				  const algebra::SemiringBase<W>& semiring,
				  const algebra::polynom<Tm, Tw>& a,
				  const oTw& b)
  { 
    algebra::polynom<Tm, Tw> ret(a);
    op_in_add(s, semiring, ret, b);
    return ret;
  }

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  inline
  algebra::polynom<Tm, Tw> op_add(const algebra::SemiringBase<W>& semiring,
				  const algebra::Series<W, M>& s,
				  const oTw& a,
				  const algebra::polynom<Tm, Tw>& b)
  { 
    algebra::polynom<Tm, Tw> ret(b);
    op_in_add(s, semiring, ret, a);
    return ret;
  }

  /*-------------------------------------------.
    | foreign multiplication by semiring elements |
    `-------------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  inline
  void op_in_mul(const algebra::Series<W, M>& s,
		 const algebra::SemiringBase<W>& semiring,
		 algebra::polynom<Tm, Tw>& dst,
		 const oTw& src)
  { 
    precondition(& s.semiring() == & semiring);

    typename algebra::polynom<Tm, Tw>::iterator p;
    for (typename algebra::polynom<Tm, Tw>::iterator i = dst.begin();
	 i != dst.end();
	 )
      {
	p = i++;
	op_in_mul(s.semiring(), p->second, src);
	if (p->second == zero_value(SELECT(W), SELECT(Tw)))
	  dst.erase(p);
      }
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  inline
  algebra::polynom<Tm, Tw> op_mul(const algebra::Series<W, M>& s,
				  const algebra::SemiringBase<W>& semiring,
				  const algebra::polynom<Tm, Tw>& a,
				  const oTw& b)
  { 
    algebra::polynom<Tm, Tw> ret(a);
    op_in_mul(s, semiring, ret, b);
    return ret;
  }

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  inline
  algebra::polynom<Tm, Tw> op_mul(const algebra::SemiringBase<W>& semiring,
				  const algebra::Series<W, M>& s,
				  const oTw& a,
				  const algebra::polynom<Tm, Tw>& b)
  { 
    precondition(& s.semiring() == & semiring);

    algebra::polynom<Tm, Tw> ret(b);

    typename algebra::polynom<Tm, Tw>::iterator p;
    for (typename algebra::polynom<Tm, Tw>::iterator i = ret.begin();
	 i != ret.end();)
      {
	p = i++;
	p->second = op_mul(s.semiring(), a, p->second);
	if (p->second == zero_value(SELECT(W), SELECT(Tw)))
	  ret.erase(p);
      }
    return ret;
  }

  /*-------------.
    | input-output |
    `-------------*/

  template<typename W, typename M, typename St, typename Tm, typename Tw>
  inline
  St& op_rout(const algebra::Series<W, M>& s, St& st, const algebra::polynom<Tm, Tw>& p)
  {
      
    typename algebra::polynom<Tm, Tw>::const_iterator i = p.begin();
    while(i != p.end())
      {
	if (i != p.begin())
	  st << "+";
	if (i->second != identity_value(SELECT(W), SELECT(Tw)) ||
	    i->first == identity_value(SELECT(M), SELECT(Tm)))
	  op_rout(s.semiring(), st, i->second);
	if (i->first != identity_value(SELECT(M), SELECT(Tm)))
	  {
	    if (i->second != identity_value(SELECT(W), SELECT(Tw)))
	      st << ".";
	    op_rout(s.monoid(), st, i->first);
	  }
	++i;
      }
    if (i == p.begin()) /* case zero */
      op_rout(s.semiring(), st, zero_value(SELECT(W), SELECT(Tw)));
    return st;
  }

  /*---------------.
    | specialization |
    `---------------*/

  /*------------------------------.
    | fundamental series operations |
    `------------------------------*/

    
  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  inline
  Tw op_series_get(const algebra::Series<W, M>&, 
		   const algebra::polynom<Tm, Tw>& p,
		   const oTm& m)
  { 
    return p.get(SELECT(W), op_convert(SELECT(M), SELECT(Tm), m)); 
  }

  template <typename W, typename M, 
	    typename Tm, typename Tw, 
	    typename oTm, typename oTw>
  inline
  void op_series_set(const algebra::Series<W, M>&,
		     algebra::polynom<Tm, Tw>& p,
		     const oTm& m,
		     const oTw& w)
  {
    typename utility::static_if
      <utility::static_eq<Tm, oTm>::value, const Tm&, Tm>::t
      new_m = op_convert(SELECT(M), SELECT(Tm), m);
    typename utility::static_if
      <utility::static_eq<Tw, oTw>::value, const Tw&, Tw>::t
      new_w = op_convert(SELECT(W), SELECT(Tw), w);

    typename algebra::polynom<Tm, Tw>::iterator i = p.find(new_m);
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
  inline
  Tm op_choose_from_supp(const algebra::Series<W, M>&, 
			 const algebra::polynom<Tm, Tw>& p)
  {
    typedef typename algebra::polynom<Tm, Tw>::const_iterator const_iterator;

    if (p.size() == 0)
      return Tm();

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
  inline
  Element<algebra::Series<W,M>, algebra::polynom<Tm,Tw> > 
  op_choose(const algebra::Series<W,M>& s, 
	    SELECTOR2(algebra::polynom<Tm,Tw>))
  {
    algebra::polynom<Tm, Tw> p;
    // FIXME: add global constants to define this !
    unsigned nb_monome = rand() * 10 / RAND_MAX;
    for (unsigned i = 0; i < nb_monome; ++i)
      p[s.monoid().choose()] = s.semiring().choose();
    return Element<algebra::Series<W,M>, algebra::polynom<Tm,Tw> >(s, p);
  }

  /*----------.
    | transpose |
    `----------*/
  template <typename W, typename M, typename Tm, typename Tw>
  inline
  void  op_in_transpose(const algebra::Series<W, M>& s, algebra::polynom<Tm, Tw>& t)
  {
    typedef typename algebra::polynom<Tm, Tw>::const_iterator const_iterator;
    algebra::polynom<Tm, Tw>	new_t(t);

    t.clear();
    for (const_iterator i = new_t.begin(); i != new_t.end(); ++i)
      {
	Element<M, Tm> w(s.monoid(), i->first);
	t.insert(mirror(w).value(), (*i).second);
      }
  }

} // vcsn

namespace std {

  template <class Tm, class Tw>
  inline
  std::ostream& operator<<(std::ostream& out, const vcsn::algebra::polynom<Tm, Tw>& p)
  {
    typename vcsn::algebra::polynom<Tm, Tw>::const_iterator i = p.begin();
    while(i != p.end())
      {
	if (i != p.begin())
	  out << "+";
	out << i->second << "." << i->first;
	++i;
      }
    if (i == p.begin()) /* case zero */
      out << "0";
    return out;
  }

} // std

#endif // VCSN_ALGEBRA_CONCRETE_SERIES_POLYNOMS_HXX
