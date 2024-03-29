// krat.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2011 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_HH

# include <list>

# include <vaucanson/algebra/implementation/series/series.hh>
# include <vaucanson/algebra/implementation/series/rat/exp.hh>
# include <vaucanson/algebra/implementation/series/rat/dump_visitor.hh>

namespace vcsn {

  namespace algebra {

    /*------------------.
    | Series compliance |
    `------------------*/

    template<typename Tm, typename Tw>
    struct series_traits<rat::exp<Tm, Tw> >
    {
      typedef Tm	monoid_elt_value_t;
      typedef Tw	semiring_elt_value_t;
      typedef std::list<monoid_elt_value_t> support_t;
    };

    template <class Tm, class Tw, class W, class M>
    struct mute_series_impl<rat::exp<Tm, Tw>, W, M>
    {
      typedef rat::exp<M, W>	ret;
    };

  } // algebra

 /*---------------------------------------------.
 | MetaElement<Series<W, M>, rat::exp<Tm, Tw> > |
 `---------------------------------------------*/
  template<typename W, typename M, typename Tm, typename Tw>
  struct MetaElement<algebra::Series<W, M>, rat::exp<Tm, Tw> >
    : MetaElement<algebra::SeriesBase<algebra::Series<W, M> >,
		  rat::exp<Tm, Tw> >
  {
    static const bool dynamic_value = true;

    void	accept(const rat::ConstNodeVisitor<Tm, Tw>& v) const;
    size_t	depth() const;
  };


  namespace algebra {

    template<typename W, typename M, typename Tm, typename Tw>
    bool op_contains(const algebra::Series<W, M>& s,
		     const rat::exp<Tm, Tw>& m);

    template<typename W, typename M, typename Tm, typename Tw>
    bool op_is_finite_app(const algebra::Series<W, M>& s,
			  const rat::exp<Tm, Tw>& m);

    template <typename W, typename M, typename Tm, typename Tw>
    Tm op_choose_from_supp(const algebra::Series<W, M>& s,
			   const rat::exp<Tm, Tw>& m);

    template<typename W, typename M, typename Tm, typename Tw>
    const rat::exp<Tm, Tw>& identity_value(SELECTOR2(algebra::Series<W, M>),
					   SELECTOR2(rat::exp<Tm, Tw>));

    template<typename W, typename M, typename Tm, typename Tw>
    bool show_identity_value(SELECTOR2(algebra::Series<W, M>),
			     SELECTOR2(rat::exp<Tm, Tw>));


    template<typename W, typename M, typename Tm, typename Tw>
    const rat::exp<Tm, Tw>& zero_value(SELECTOR2(algebra::Series<W, M>),
				       SELECTOR2(rat::exp<Tm, Tw>));


    template<typename W, typename M, typename Tm, typename Tw>
    void op_in_add(const algebra::Series<W, M>& s,
		   rat::exp<Tm, Tw>& dst,
		   const rat::exp<Tm, Tw>& arg);

    template<typename W, typename M, typename Tm, typename Tw>
    rat::exp<Tm, Tw> op_mul(const algebra::Series<W, M>& s,
			    const rat::exp<Tm, Tw>& a,
			    const rat::exp<Tm, Tw>& b);

    template<typename W, typename M, typename Tm, typename Tw>
    void op_in_mul(const algebra::Series<W, M>& s,
		   rat::exp<Tm, Tw>& dst,
		   const rat::exp<Tm, Tw>& arg);

    template<typename W, typename M, typename Tm, typename Tw>
    rat::exp<Tm, Tw> op_mul(const algebra::Series<W, M>& s,
			    const rat::exp<Tm, Tw>& a,
			    const rat::exp<Tm, Tw>& b);


    /*---------------------.
    | foreign constructors |
    `---------------------*/

    template<typename Tm, typename Tw, typename M, typename W>
    rat::exp<Tm, Tw> op_convert(SELECTOR2(algebra::Series<M, W>),
				SELECTOR2(rat::exp<Tm, Tw>),
				const Tm& m_value);

    template<typename Tm, typename Tw, typename M, typename W>
    rat::exp<Tm, Tw> op_convert(SELECTOR2(algebra::Series<M, W>),
				SELECTOR2(rat::exp<Tm, Tw>),
				char m_value);

    template<typename Tm, typename Tw, typename W, typename M, typename oTm>
    rat::exp<Tm, Tw> op_convert(SELECTOR2(algebra::Series<W, M>),
				SELECTOR2(rat::exp<Tm, Tw>),
				SELECTOR(M),
				const oTm& m_value);

    template<typename Tm, typename Tw, typename W, typename M, typename oTw>
    rat::exp<Tm, Tw> op_convert(SELECTOR2(algebra::Series<W, M>),
				SELECTOR2(rat::exp<Tm, Tw>),
				SELECTOR(W),
				const oTw& w_value);

    template<typename W, typename M, typename Tm, typename Tw, typename oTm>
    void op_assign(const algebra::Series<W, M>& s,
		   const M& monoid,
		   rat::exp<Tm, Tw>& dst,
		   const oTm& src);

    template<typename W, typename M, typename Tm, typename Tw, typename oTw>
    void op_assign(const algebra::Series<W, M>& s,
		   const W& semiring,
		   rat::exp<Tm, Tw>& dst,
		   const oTw& src);

    /*-----.
    | star |
    `-----*/

    template<typename W, typename M, typename Tm, typename Tw>
    bool op_starable(const algebra::Series<W, M>& s,
		      const rat::exp<Tm, Tw>& dst);

    template<typename W, typename M, typename Tm, typename Tw>
    void op_in_star(const algebra::Series<W, M>& s,
		    rat::exp<Tm, Tw>& dst);

    template<typename W, typename M, typename Tm, typename Tw>
    rat::exp<Tm, Tw>
    op_star(const algebra::Series<W, M>& s,
	    const rat::exp<Tm, Tw>& src);

  } // algebra

    /*--------------------------------------.
    | foreign addition with monoid elements |
    `--------------------------------------*/

  template<typename M, typename W, typename oTm, typename Tm, typename Tw>
  struct op_add_traits<M, algebra::Series<W, M>, oTm, rat::exp<Tm, Tw> >
  {
    typedef Element<algebra::Series<W, M>, rat::exp<Tm, Tw> > ret_t;
  };

  namespace algebra {

    template<typename W, typename M, typename Tm, typename Tw, typename oTm>
    void op_in_add(const algebra::Series<W, M>& s,
		   const M& monoid,
		   rat::exp<Tm, Tw>& dst,
		   const oTm& src);

    template<typename W, typename M, typename Tm, typename Tw, typename oTm>
    rat::exp<Tm, Tw> op_add(const algebra::Series<W, M>& s,
			    const M& monoid,
			    const rat::exp<Tm, Tw>& a,
			    const oTm& b);

    template<typename M, typename W, typename oTm, typename Tm, typename Tw>
    rat::exp<Tm, Tw> op_add(const M& monoid,
			    const algebra::Series<W, M>& s,
			    const oTm& a,
			    const rat::exp<Tm, Tw>& b);

  }

  /*---------------------------------------.
  | foreign addition with semiring elements |
  `---------------------------------------*/

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  struct op_add_traits<W, algebra::Series<W, M>, oTw, rat::exp<Tm, Tw> >
  {
    typedef Element<algebra::Series<W, M>, rat::exp<Tm, Tw> > ret_t;
  };

  namespace algebra {

    template<typename W, typename M, typename Tm, typename Tw, typename oTw>
    void op_in_add(const algebra::Series<W, M>& s,
		   const W& semiring,
		   rat::exp<Tm, Tw>& dst,
		   const oTw& src);

    template<typename W, typename M, typename Tm, typename Tw, typename oTw>
    rat::exp<Tm, Tw> op_add(const algebra::Series<W, M>& s,
			    const W& semiring,
			    const rat::exp<Tm, Tw>& a,
			    const oTw& b);

    template<typename W, typename M, typename oTw, typename Tm, typename Tw>
    rat::exp<Tm, Tw> op_add(const W& semiring,
			    const algebra::Series<W, M>& s,
			    const oTw& a,
			    const rat::exp<Tm, Tw>& b);

  }

  /*-------------------------------------------.
  | foreign multiplication by semiring elements |
  `-------------------------------------------*/

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  struct op_mul_traits<W, algebra::Series<W, M>, oTw, rat::exp<Tm, Tw> >
  {
    typedef Element<algebra::Series<W, M>, rat::exp<Tm, Tw> > ret_t;
  };

  namespace algebra {

    template<typename W, typename M, typename Tm, typename Tw, typename oTw>
    void op_in_mul(const algebra::Series<W, M>& s,
		   const W& semiring,
		   rat::exp<Tm, Tw>& ret,
		   const oTw& w);

    template<typename W, typename M, typename Tm, typename Tw, typename oTw>
    rat::exp<Tm, Tw> op_mul(const algebra::Series<W, M>& s,
			    const W& semiring,
			    const rat::exp<Tm, Tw>& a,
			    const oTw& w);

    template<typename W, typename M, typename oTw, typename Tm, typename Tw>
    rat::exp<Tm, Tw> op_mul(const W& semiring,
			    const algebra::Series<W, M>& s,
			    const oTw& w,
			    const rat::exp<Tm, Tw>& b);

    /*---------------.
    | Series methods |
    `---------------*/
    template<typename W, typename M, typename Tm, typename Tw, typename oTm>
    Tw op_series_get(const algebra::Series<W, M>& s,
		     const rat::exp<Tm, Tw>& p,
		     const oTm& m);

    template<typename W, typename M, typename Tm,
	     typename Tw, typename oTm, typename oTw>
    void op_series_set(const algebra::Series<W, M>& s,
		       const rat::exp<Tm, Tw>& p,
		       const oTm& m,
		       const oTw& w);

    template <class W, class M, class Tm, class Tw>
    Element<algebra::Series<W,M>, rat::exp<Tm,Tw> >
    op_choose(const algebra::Series<W,M>& s,
	      SELECTOR2(rat::exp<Tm,Tw>));

    template <typename W, typename M, typename Tm, typename Tw, typename St>
    St&
    op_rout(const algebra::Series<W, M>&,
	    St& st,
	    const rat::exp<Tm, Tw>&);

    /*----------.
    | Transpose |
    `----------*/

    template <typename W, typename M, typename Tm, typename Tw>
    void op_in_transpose(const algebra::Series<W, M>& s,
			 rat::exp<Tm, Tw>& dst);


  } // algebra

  template<typename W, typename M, typename Tm, typename Tw>
  struct semiring_traits<algebra::Series<W, M>, rat::exp<Tm, Tw> >
  {
    enum { is_positive = 1 };
  };

} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/algebra/implementation/series/krat.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_HH
