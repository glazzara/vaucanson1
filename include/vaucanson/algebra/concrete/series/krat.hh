/*******************************
 * <vaucanson/algebra/krat.hh> *
 *******************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef ALGEBRA_KRAT_HH
# define ALGEBRA_KRAT_HH

# include <vaucanson/algebra/concrete/series/series.hh>
# include <vaucanson/rat/exp.hh>
# include <utility>

namespace vcsn
{
  namespace algebra
  {

    /*------------------.
    | Series compliance |
    `------------------*/

    template<typename W, typename M, typename Tm, typename Tw>
    struct series_traits<Series<W, M>, rat::exp<Tm, Tw> >
    {
      typedef Tm	monoid_value_t;
      typedef Tw	weights_value_t;
    };

  } //algebra

    /*---------------------------------------------.
    | MetaElement<Series<W, M>, rat::exp<Tm, Tw> > |
    `---------------------------------------------*/

    template<typename W, typename M, typename Tm, typename Tw>
    struct MetaElement<Series<W, M>, rat::exp<Tm, Tw> >
      : MetaElement<SeriesBase<Series<W, M> >, rat::exp<Tm, Tw> >
    {
      static const bool dynamic_values = true;
      
      void	accept(const rat::ConstNodeVisitor<Tm, Tw>& v) const;
      size_t	depth() const;
    };

  namespace algebra
  {   
    
    
    template<typename W, typename M, typename Tm, typename Tw>
    bool op_contains(const Series<W, M>& s, const rat::exp<Tm, Tw>& m);

    template<typename W, typename M, typename Tm, typename Tw>
    bool op_is_finite_app(const Series<W, M>& s, const rat::exp<Tm, Tw>& m);

    template<typename W, typename M, typename Tm, typename Tw>
    const rat::exp<Tm, Tw>& identity_value(SELECTOR2(Series<W, M>), 
					   SELECTOR2(rat::exp<Tm, Tw>));

    template<typename W, typename M, typename Tm, typename Tw>
    const rat::exp<Tm, Tw>& zero_value(SELECTOR2(Series<W, M>), 
				       SELECTOR2(rat::exp<Tm, Tw>));


    template<typename W, typename M, typename Tm, typename Tw>
    void op_in_add(const Series<W, M>& s, 
		   rat::exp<Tm, Tw>& dst,
		   const rat::exp<Tm, Tw>& arg);
    
    template<typename W, typename M, typename Tm, typename Tw>
    bool krat_simplify_left_is_k(const Series<W, M>& s,
				 rat::exp<Tm, Tw>& dst,
				 const rat::exp<Tm, Tw>& other, 
				 rat::LeftWeighted<Tm, Tw>* left, 
				 typename rat::Node<Tm, Tw>::type other_type);

    template<typename W, typename M, typename Tm, typename Tw>
    bool krat_simplify_left_is_ka(const Series<W, M>& s,
				  rat::exp<Tm, Tw>& dst,
				  const rat::exp<Tm, Tw>& other, 
				  rat::LeftWeighted<Tm, Tw>* left, 
				  typename rat::Node<Tm, Tw>::type other_type);
    
    template<typename W, typename M, typename Tm, typename Tw>
    bool krat_simplify_left_is_kany(const Series<W, M>& s,
				    rat::exp<Tm, Tw>& dst,
				    const rat::exp<Tm, Tw>& other, 
				    rat::LeftWeighted<Tm, Tw>* left, 
				    typename rat::Node<Tm, Tw>::type 
				    other_type);
    
    template<typename W, typename M, typename Tm, typename Tw>
    bool krat_simplify_left_is_lweight(const Series<W, M>& s,
				       rat::exp<Tm, Tw>& dst,
				       const rat::exp<Tm, Tw>& other, 
				       rat::LeftWeighted<Tm, Tw>* left, 
				       typename rat::Node<Tm, Tw>::type 
				       other_type);
 
    template<typename W, typename M, typename Tm, typename Tw>
    bool krat_simplify_left_is_anyk(const Series<W, M>& s,
				    rat::exp<Tm, Tw>& dst,
				    const rat::exp<Tm, Tw>& other, 
				    rat::RightWeighted<Tm, Tw>* left, 
				    typename rat::Node<Tm, Tw>::type 
				    other_type);

    template<typename Tm, typename Tw>
    bool krat_simplify_left_is_const( rat::exp<Tm, Tw>& dst,
				      const rat::exp<Tm, Tw>& other, 
				      typename 
				      rat::Node<Tm, Tw>::type other_type);
    
    template<typename W, typename M, typename Tm, typename Tw>
    void op_in_mul(const Series<W, M>& s, 
		   rat::exp<Tm, Tw>& dst,
		   const rat::exp<Tm, Tw>& arg);

    template<typename W, typename M, typename Tm, typename Tw>
    rat::exp<Tm, Tw> op_mul(const Series<W, M>& s,
			    const rat::exp<Tm, Tw>& a,
			    const rat::exp<Tm, Tw>& b);


    /*---------------------.
      | foreign constructors |
      `---------------------*/
    template<typename Tm, typename Tw, typename W, typename M, typename oTm>
    rat::exp<Tm, Tw> op_convert(SELECTOR2(rat::exp<Tm, Tw>),
				SELECTOR2(Series<W, M>),
				SELECTOR(M),
				const oTm& m_value);

    template<typename Tm, typename Tw, typename W, typename M, typename oTw>
    rat::exp<Tm, Tw> op_convert(SELECTOR2(rat::exp<Tm, Tw>),
				SELECTOR2(Series<W, M>),
				SELECTOR(W),
				const oTw& w_value);
    
    template<typename W, typename M, typename Tm, typename Tw, typename oTm>
    void op_assign(const Series<W, M>& s,
		   const M& monoid,
		   rat::exp<Tm, Tw>& dst,
		   const oTm& src);

    template<typename W, typename M, typename Tm, typename Tw, typename oTw>
    void op_assign(const Series<W, M>& s,
		   const W& weights,
		   rat::exp<Tm, Tw>& dst,
		   const oTw& src);

    /*-----.
      | star |
      `-----*/

    template<typename W, typename M, typename Tm, typename Tw>
    bool op_stareable(const Series<W, M>& s,
		      const rat::exp<Tm, Tw>& dst);

    template<typename W, typename M, typename Tm, typename Tw>
    void op_in_star(const Series<W, M>& s,
		    rat::exp<Tm, Tw>& dst);

    template<typename W, typename M, typename Tm, typename Tw>
    rat::exp<Tm, Tw> 
    op_star(const Series<W, M>& s,
	    const rat::exp<Tm, Tw>& src);

  }  //algebra

    /*--------------------------------------.
      | foreign addition with monoid elements |
      `--------------------------------------*/

    template<typename M, typename W, typename oTm, typename Tm, typename Tw>
    struct op_add_traits<M, Series<W, M>, oTm, rat::exp<Tm, Tw> >
    {
      typedef Element<Series<W, M>, rat::exp<Tm, Tw> > ret_t;
    };

  namespace algebra
  {
    
    template<typename W, typename M, typename Tm, typename Tw, typename oTm>
    void op_in_add(const Series<W, M>& s,
		   const M& monoid,
		   rat::exp<Tm, Tw>& dst,
		   const oTm& src);

    template<typename W, typename M, typename Tm, typename Tw, typename oTm>
    rat::exp<Tm, Tw> op_add(const Series<W, M>& s,
			    const M& monoid,
			    const rat::exp<Tm, Tw>& a,
			    const oTm& b);

    template<typename M, typename W, typename oTm, typename Tm, typename Tw>
    rat::exp<Tm, Tw> op_add(const M& monoid,
			    const Series<W, M>& s,
			    const oTm& a,
			    const rat::exp<Tm, Tw>& b);

    /*---------------------------------------.
      | foreign addition with weights elements |
      `---------------------------------------*/

  }  // algebra



  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  struct op_add_traits<W, Series<W, M>, oTw, rat::exp<Tm, Tw> >
  {
    typedef Element<Series<W, M>, rat::exp<Tm, Tw> > ret_t;
  };
  
  namespace algebra 
  {
    template<typename W, typename M, typename Tm, typename Tw, typename oTw>
    void op_in_add(const Series<W, M>& s,
		   const W& weights,
		   rat::exp<Tm, Tw>& dst,
		   const oTw& src);

    template<typename W, typename M, typename Tm, typename Tw, typename oTw>
    rat::exp<Tm, Tw> op_add(const Series<W, M>& s,
			    const W& weights,
			    const rat::exp<Tm, Tw>& a,
			    const oTw& b);

    template<typename W, typename M, typename oTw, typename Tm, typename Tw>
    rat::exp<Tm, Tw> op_add(const W& weights,
			    const Series<W, M>& s,
			    const oTw& a,
			    const rat::exp<Tm, Tw>& b);

  } // algebra

    /*-------------------------------------------.
      | foreign multiplication by weights elements |
      `-------------------------------------------*/

    template<typename W, typename M, typename oTw, typename Tm, typename Tw>
    struct op_mul_traits<W, Series<W, M>, oTw, rat::exp<Tm, Tw> >
    {
      typedef Element<Series<W, M>, rat::exp<Tm, Tw> > ret_t;
    };

  namespace algebra 
  {
    
    template<typename W, typename M, typename Tm, typename Tw, typename oTw>
    void op_in_mul(const Series<W, M>& s,
		   const W& weights,
		   rat::exp<Tm, Tw>& ret,
		   const oTw& w);

    template<typename W, typename M, typename Tm, typename Tw, typename oTw>
    rat::exp<Tm, Tw> op_mul(const Series<W, M>& s,
			    const W& weights,
			    const rat::exp<Tm, Tw>& a,
			    const oTw& w);

    template<typename W, typename M, typename oTw, typename Tm, typename Tw>
    rat::exp<Tm, Tw> op_mul(const W& weights,
			    const Series<W, M>& s,
			    const oTw& w,
			    const rat::exp<Tm, Tw>& b);

    /*---------------.
    | Series methods |
    `---------------*/
    template<typename W, typename M, typename Tm, typename Tw, typename oTm>
    Tw op_series_get(const Series<W, M>& s, 
		     const rat::exp<Tm, Tw>& p,
		     const oTm& m);


  } // algebra
} // vcsn

# include <vaucanson/algebra/concrete/series/krat.hxx>

#endif // ALGEBRA_KRAT_HH

