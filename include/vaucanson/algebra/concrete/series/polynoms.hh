// algebra/polynoms.hh
//
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey
// and Regis-Gianas.
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

#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_POLYNOMS_HH
# define VCSN_ALGEBRA_CONCRETE_SERIES_POLYNOMS_HH

# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/algebra/concrete/series/series.hh>
# include <vaucanson/algebra/concrete/series/transpose.hh>
# include <vaucanson/misc/support.hh>

# include <map>
# include <utility>

namespace vcsn {

  namespace algebra  {

    /*----------------.
      | polynom<Tm, Tw> |
      `----------------*/

    template<typename Tm, typename Tw>
    class polynom
    {
    public:
      typedef typename std::map<Tm, Tw>::const_iterator const_iterator;
      typedef typename std::map<Tm, Tw>::iterator	iterator;

      template<typename M, typename W>
      polynom(SELECTOR(M), SELECTOR(W));
      polynom(const polynom& other);
      polynom();

      size_t		size() const;
      bool		empty() const;

      iterator		begin();      
      const_iterator	begin() const;
      
      iterator		end();     
      const_iterator	end() const;

      iterator		find(const Tm& m); 
      const_iterator	find(const Tm& m) const;

      template<typename W>
      Tw&		make_get(SELECTOR(W), const Tm& m);
      template<typename W>
      Tw		get(SELECTOR(W), const Tm& m) const;

      void		insert(const Tm& m, const Tw& w);

      template<typename W>
      void		add(const W& weights, const Tm& m, const Tw& w);
      void		erase(iterator i);
      void		clear();
      void		swap(polynom<Tm, Tw>& other);

      const std::map<Tm, Tw>&
      as_map() const;

    protected:
      std::map<Tm, Tw> map_;
    };

    template<typename Tm, typename Tw>
    struct series_traits<polynom<Tm, Tw> >
    {
      typedef Tm monoid_value_t;
      typedef Tw weight_value_t;
      typedef utility::Support<std::map<Tm, Tw> > support_t;
    };

    template <class Tm, class Tw, class W, class M>
    struct mute_serie_impl<polynom<Tm, Tw>, W, M>
    {
      typedef polynom<M, W>	ret;
    };

    template <class Series, class Tm, class Tw>
    struct DefaultTransposeFun<Series, polynom<Tm,Tw> >
    {
      polynom<Tm,Tw>
      operator()(const Series& s, const polynom<Tm,Tw>& l) const;
    };

    template <class Tm, class Tw>
    bool operator==(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs); 

    template <class Tm, class Tw>
    bool operator!=(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs); 

    template <class Tm, class Tw>
    bool operator<(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs);   

    template <class Tm, class Tw>
    bool operator>(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs);   

    template <class Tm, class Tw>
    bool operator<=(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs);   

    template <class Tm, class Tw>
    bool operator>=(const polynom<Tm, Tw>& lhs, const polynom<Tm, Tw>& rhs);   

    
  } // algebra

  template<typename W, typename M, typename Tm, typename Tw>
  bool op_contains(const algebra::Series<W, M>& s, const algebra::polynom<Tm, Tw>& m);
  
  template<typename W, typename M, typename Tm, typename Tw>
  bool op_is_finite_app(const algebra::Series<W, M>& s, const algebra::polynom<Tm, Tw>& m);
  
  template<typename W, typename M, typename Tm, typename Tw>
  const algebra::polynom<Tm, Tw>& identity_value(SELECTOR2(algebra::Series<W, M>), 
						 SELECTOR2(algebra::polynom<Tm, Tw>));
  
  template<typename W, typename M, typename Tm, typename Tw>
  const algebra::polynom<Tm, Tw>& zero_value(SELECTOR2(algebra::Series<W, M>), 
					     SELECTOR2(algebra::polynom<Tm, Tw>));
  
  template<typename W, typename M, typename Tm, typename Tw>
  void op_in_add(const algebra::Series<W, M>& s, 
		 algebra::polynom<Tm, Tw>& dst,
		 const algebra::polynom<Tm, Tw>& arg);
  
  template<typename W, typename M, typename Tm, typename Tw>
  algebra::polynom<Tm, Tw> op_add(const algebra::Series<W, M>& s,
				  const algebra::polynom<Tm, Tw>& a,
				  const algebra::polynom<Tm, Tw>& b);
  
  /*-----------------.
    | cauchy's product |
    `-----------------*/
  template<typename W, typename M, typename Tm, typename Tw>
  algebra::polynom<Tm, Tw> op_mul(const algebra::Series<W, M>& s,
				  const algebra::polynom<Tm, Tw>& a,
				  const algebra::polynom<Tm, Tw>& b);
    
  template<typename W, typename M, typename Tm, typename Tw>
  void op_in_mul(const algebra::Series<W, M>& s, 
		 algebra::polynom<Tm, Tw>& dst,
		 const algebra::polynom<Tm, Tw>& arg);

  /*---------------------.
    | foreign constructors |
    `---------------------*/
  template<typename Tm, typename Tw, typename W, typename M, typename oTm>
  algebra::polynom<Tm, Tw> op_convert(SELECTOR2(algebra::polynom<Tm, Tw>),
				      SELECTOR2(algebra::Series<W, M>),
				      SELECTOR(M),
				      const oTm& m_value);

  template<typename Tm, typename Tw, typename W, typename M, typename oTw>
  algebra::polynom<Tm, Tw> op_convert(SELECTOR2(algebra::polynom<Tm, Tw>),
				      SELECTOR2(algebra::Series<W, M>),
				      SELECTOR(W),
				      const oTw& w_value);
    
  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  void op_assign(const algebra::Series<W, M>& s,
		 const M& monoid,
		 algebra::polynom<Tm, Tw>& dst,
		 const oTm& src);

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  void op_assign(const algebra::Series<W, M>& s,
		 const W& weights,
		 algebra::polynom<Tm, Tw>& dst,
		 const oTw& src);

  /*--------------------------------------.
    | foreign addition with monoid elements |
    `--------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  void op_in_add(const algebra::Series<W, M>& s,
		 const M& monoid,
		 algebra::polynom<Tm, Tw>& dst,
		 const oTm& src);

  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  algebra::polynom<Tm, Tw> op_add(const algebra::Series<W, M>& s,
				  const M& monoid,
				  const algebra::polynom<Tm, Tw>& a,
				  const oTm& b);


  template<typename M, typename W, typename oTm, typename Tm, typename Tw>
  struct op_add_traits<M, algebra::Series<W, M>, oTm, algebra::polynom<Tm, Tw> >
  {
    typedef Element<algebra::Series<W, M>, algebra::polynom<Tm, Tw> > ret_t;
  };
  
  template<typename M, typename W, typename oTm, typename Tm, typename Tw>
  algebra::polynom<Tm, Tw> op_add(const M& monoid,
				  const algebra::Series<W, M>& s,
				  const oTm& a,
				  const algebra::polynom<Tm, Tw>& b);

  /*---------------------------------------.
    | foreign addition with weights elements |
    `---------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  void op_in_add(const algebra::Series<W, M>& s,
		 const W& weights,
		 algebra::polynom<Tm, Tw>& dst,
		 const oTw& src);

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  algebra::polynom<Tm, Tw> op_add(const algebra::Series<W, M>& s,
				  const W& weights,
				  const algebra::polynom<Tm, Tw>& a,
				  const oTw& b);

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  struct op_add_traits<W, algebra::Series<W, M>, oTw, algebra::polynom<Tm, Tw> >
  {
    typedef Element<algebra::Series<W, M>, algebra::polynom<Tm, Tw> > ret_t;
  };
  
  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  algebra::polynom<Tm, Tw> op_add(const W& weights,
				  const algebra::Series<W, M>& s,
				  const oTw& a,
				  const algebra::polynom<Tm, Tw>& b);

  /*-------------------------------------------.
    | foreign multiplication by weights elements |
    `-------------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  void op_in_mul(const algebra::Series<W, M>& s,
		 const W& weights,
		 algebra::polynom<Tm, Tw>& dst,
		 const oTw& src);

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  algebra::polynom<Tm, Tw> op_mul(const algebra::Series<W, M>& s,
				  const W& weights,
				  const algebra::polynom<Tm, Tw>& a,
				  const oTw& b);

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  struct op_mul_traits<W, algebra::Series<W, M>, oTw, algebra::polynom<Tm, Tw> >
  {
    typedef Element<algebra::Series<W, M>, algebra::polynom<Tm, Tw> > ret_t;
  };

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  algebra::polynom<Tm, Tw> op_mul(const W& weights,
				  const algebra::Series<W, M>& s,
				  const oTw& a,
				  const algebra::polynom<Tm, Tw>& b);

  /*----------.
    | transpose |
    `----------*/
  template <typename W, typename M, typename Tm, typename Tw>
  void  op_in_transpose(const algebra::Series<W, M>& s, algebra::polynom<Tm, Tw>& t);

  /*-------------.
    | input-output |
    `-------------*/

  template<typename W, typename M, typename St, typename Tm, typename Tw>
  St& op_rout(const algebra::Series<W, M>& s, St& st, const algebra::polynom<Tm, Tw>& p);

  /*---------------.
    | specialization |
    `---------------*/

  template<typename W, typename M, typename Tm, typename Tw>
  struct MetaElement<algebra::Series<W, M>, algebra::polynom<Tm, Tw> >
    : public MetaElement<algebra::SeriesBase<algebra::Series<W, M> >, algebra::polynom<Tm, Tw> >
  {
    static const bool dynamic_values = true;
  };

  /*------------------------------.
    | fundamental series operations |
    `------------------------------*/
    
  template <class W, class M, class Tm, class Tw>
  Tm op_choose_from_supp(const algebra::Series<W, M>& s, 
			 const algebra::polynom<Tm, Tw>& p);
  
  template<typename W, typename M, typename Tm, typename Tw>
  typename algebra::series_traits<algebra::polynom<Tm, Tw> >::support_t
  op_support(const algebra::Series<W, M>& s, const algebra::polynom<Tm, Tw>& m);

  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  Tw op_series_get(const algebra::Series<W, M>& s, 
		   const algebra::polynom<Tm, Tw>& p,
		   const oTm& m);
  
  template<typename W, typename M, 
	   typename Tm, typename Tw, 
	   typename oTm, typename oTw>
  void op_series_set(const algebra::Series<W, M>& s,
		     algebra::polynom<Tm, Tw>& p,
		     const oTm& m,
		     const oTw& w);
  
  template <class W, class M, class Tm, class Tw>
  Element<algebra::Series<W,M>, algebra::polynom<Tm,Tw> > 
  op_choose(const algebra::Series<W,M>& s, 
	    SELECTOR2(algebra::polynom<Tm,Tw>));

} // vcsn

namespace std {

  template <class Tm, class Tw>
  std::ostream& operator<<(std::ostream& out, 
			   const vcsn::algebra::polynom<Tm, Tw>& p);

} // std


# include <vaucanson/algebra/concrete/series/polynoms.hxx>

#endif // VCSN_ALGEBRA_ALGEBRA::POLYNOMS_HH

