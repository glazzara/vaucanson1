// algebra/polynoms.hh
//
// $Id$
// VCSN_HEADER

#ifndef ALGEBRA_POLYNOMS_HH
# define ALGEBRA_POLYNOMS_HH

# include <map>
# include <utility>

# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/algebra/concrete/series/series.hh>
# include <vaucanson/algebra/concrete/series/transpose.hh>

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

    template<typename W, typename M, typename Tm, typename Tw>
    struct series_traits<Series<W, M>, polynom<Tm, Tw> >
    {
      typedef Tm monoid_value_t;
      typedef Tw weights_value_t;
    };

    template <class Series, class Tm, class Tw>
    struct DefaultTransposeFun<Series, polynom<Tm,Tw> >
    {
      polynom<Tm,Tw>
      operator()(const Series& s, const polynom<Tm,Tw>& l) const;
    };
    

  } // algebra
  

  using namespace algebra;

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

  template<typename W, typename M, typename Tm, typename Tw>
  bool op_contains(const Series<W, M>& s, const polynom<Tm, Tw>& m);
  
  template<typename W, typename M, typename Tm, typename Tw>
  bool op_is_finite_app(const Series<W, M>& s, const polynom<Tm, Tw>& m);
  
  template<typename W, typename M, typename Tm, typename Tw>
  const polynom<Tm, Tw>& identity_value(SELECTOR2(Series<W, M>), 
					SELECTOR2(polynom<Tm, Tw>));
  
  template<typename W, typename M, typename Tm, typename Tw>
  const polynom<Tm, Tw>& zero_value(SELECTOR2(Series<W, M>), 
				    SELECTOR2(polynom<Tm, Tw>));
  
  template<typename W, typename M, typename Tm, typename Tw>
  void op_in_add(const Series<W, M>& s, 
		 polynom<Tm, Tw>& dst,
		 const polynom<Tm, Tw>& arg);
  
  template<typename W, typename M, typename Tm, typename Tw>
  polynom<Tm, Tw> op_add(const Series<W, M>& s,
			 const polynom<Tm, Tw>& a,
			 const polynom<Tm, Tw>& b);
  
  /*-----------------.
  | cauchy's product |
  `-----------------*/
  template<typename W, typename M, typename Tm, typename Tw>
  polynom<Tm, Tw> op_mul(const Series<W, M>& s,
			 const polynom<Tm, Tw>& a,
			 const polynom<Tm, Tw>& b);
    
  template<typename W, typename M, typename Tm, typename Tw>
  void op_in_mul(const Series<W, M>& s, 
		 polynom<Tm, Tw>& dst,
		 const polynom<Tm, Tw>& arg);

  /*---------------------.
  | foreign constructors |
  `---------------------*/
  template<typename Tm, typename Tw, typename W, typename M, typename oTm>
  polynom<Tm, Tw> op_convert(SELECTOR2(polynom<Tm, Tw>),
			     SELECTOR2(Series<W, M>),
			     SELECTOR(M),
			     const oTm& m_value);

  template<typename Tm, typename Tw, typename W, typename M, typename oTw>
  polynom<Tm, Tw> op_convert(SELECTOR2(polynom<Tm, Tw>),
			     SELECTOR2(Series<W, M>),
			     SELECTOR(W),
			     const oTw& w_value);
    
  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  void op_assign(const Series<W, M>& s,
		 const M& monoid,
		 polynom<Tm, Tw>& dst,
		 const oTm& src);

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  void op_assign(const Series<W, M>& s,
		 const W& weights,
		 polynom<Tm, Tw>& dst,
		 const oTw& src);

  /*--------------------------------------.
  | foreign addition with monoid elements |
  `--------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  void op_in_add(const Series<W, M>& s,
		 const M& monoid,
		 polynom<Tm, Tw>& dst,
		 const oTm& src);

  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  polynom<Tm, Tw> op_add(const Series<W, M>& s,
			 const M& monoid,
			 const polynom<Tm, Tw>& a,
			 const oTm& b);


  template<typename M, typename W, typename oTm, typename Tm, typename Tw>
  struct op_add_traits<M, Series<W, M>, oTm, polynom<Tm, Tw> >
  {
    typedef Element<Series<W, M>, polynom<Tm, Tw> > ret_t;
  };
  
  template<typename M, typename W, typename oTm, typename Tm, typename Tw>
  polynom<Tm, Tw> op_add(const M& monoid,
			 const Series<W, M>& s,
			 const oTm& a,
			 const polynom<Tm, Tw>& b);

  /*---------------------------------------.
  | foreign addition with weights elements |
  `---------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  void op_in_add(const Series<W, M>& s,
		 const W& weights,
		 polynom<Tm, Tw>& dst,
		 const oTw& src);

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  polynom<Tm, Tw> op_add(const Series<W, M>& s,
			 const W& weights,
			 const polynom<Tm, Tw>& a,
			 const oTw& b);

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  struct op_add_traits<W, Series<W, M>, oTw, polynom<Tm, Tw> >
  {
    typedef Element<Series<W, M>, polynom<Tm, Tw> > ret_t;
  };
  
  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  polynom<Tm, Tw> op_add(const W& weights,
			 const Series<W, M>& s,
			 const oTw& a,
			 const polynom<Tm, Tw>& b);

  /*-------------------------------------------.
  | foreign multiplication by weights elements |
  `-------------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  void op_in_mul(const Series<W, M>& s,
		 const W& weights,
		 polynom<Tm, Tw>& dst,
		 const oTw& src);

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  polynom<Tm, Tw> op_mul(const Series<W, M>& s,
			 const W& weights,
			 const polynom<Tm, Tw>& a,
			 const oTw& b);

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  struct op_mul_traits<W, Series<W, M>, oTw, polynom<Tm, Tw> >
  {
    typedef Element<Series<W, M>, polynom<Tm, Tw> > ret_t;
  };

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  polynom<Tm, Tw> op_mul(const W& weights,
			 const Series<W, M>& s,
			 const oTw& a,
			 const polynom<Tm, Tw>& b);

  /*----------.
  | transpose |
  `----------*/
  template <typename W, typename M, typename Tm, typename Tw>
  void  op_in_transpose(Series<W, M>& s, polynom<Tm, Tw>& t);

  /*-------------.
  | input-output |
  `-------------*/

  template<typename W, typename M, typename St, typename Tm, typename Tw>
  St& op_rout(const Series<W, M>& s, St& st, const polynom<Tm, Tw>& p);

  /*---------------.
  | specialization |
  `---------------*/

  template<typename W, typename M, typename Tm, typename Tw>
  struct MetaElement<Series<W, M>, polynom<Tm, Tw> >
    : public MetaElement<SeriesBase<Series<W, M> >, polynom<Tm, Tw> >
  {
    static const bool dynamic_values = true;
  };

  /*------------------------------.
  | fundamental series operations |
  `------------------------------*/

  template <class W, class M, class Tm, class Tw>
  Tm op_choose_from_supp(const Series<W, M>& s, 
			 const polynom<Tm, Tw>& p);
    
  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  Tw op_series_get(const Series<W, M>& s, 
		   const polynom<Tm, Tw>& p,
		   const oTm& m);

  template<typename W, typename M, 
	   typename Tm, typename Tw, 
	   typename oTm, typename oTw>
  void op_series_set(const Series<W, M>& s,
		     polynom<Tm, Tw>& p,
		     const oTm& m,
		     const oTw& w);

  template <class W, class M, class Tm, class Tw>
  Element<Series<W,M>, polynom<Tm,Tw> > 
  op_choose(const Series<W,M>& s, 
	    SELECTOR2(polynom<Tm,Tw>));


} // vcsn

# include <vaucanson/algebra/concrete/series/polynoms.hxx>

#endif // ALGEBRA_POLYNOMS_HH

