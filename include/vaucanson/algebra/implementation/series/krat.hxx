// krat.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_HXX

# include <utility>
# include <vaucanson/algebra/implementation/series/series.hh>
# include <vaucanson/algebra/implementation/series/rat/exp.hh>
# include <vaucanson/algebra/implementation/series/rat/random_visitor.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <vaucanson/algebra/implementation/series/krat_exp_is_finite_app.hxx>
# include <vaucanson/algebra/implementation/series/krat_exp_support.hxx>
# include <vaucanson/algebra/implementation/series/krat_exp_transpose.hxx>

# include <vaucanson/algorithms/eval.hh>
# include <vaucanson/algorithms/standard_of.hh>

# include <vaucanson/algebra/implementation/series/polynoms.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/implementation/boost_graph.hh>

# include <vaucanson/misc/contract.hh>


namespace vcsn {

  /**
   * @bug
   * FIXME
   * Operators in krat.hxx are of the form:
   * <pre>
   *    template<typename S, typename M ...>
   *      ... op(Series<S>& series, M& monoid, ...)
   * </pre>
   * and should be instead:
   * <pre>
   *    template<typename S, typename M ...>
   *      ... op(Series<S>& series, Monoid<M>& monoid, ...)
   * </pre>
   */


  template<typename W, typename M, typename Tm, typename Tw>
  bool op_contains(const algebra::Series<W, M>&, const rat::exp<Tm, Tw>&)
  {
    pure_service_call ("default version of op_contains(Series<W,M>, exp<Tm,Tw>)");
    return true;
  }

  template<typename W, typename M, typename Tm, typename Tw>
  bool op_is_finite_app(const algebra::Series<W, M>&,
			const rat::exp<Tm, Tw>& m)
  {
    vcsn::IsFiniteAppMatcher<algebra::Series<W, M>,
      vcsn::rat::exp<Tm, Tw>,
      algebra::DispatchFunction<vcsn::rat::exp<Tm, Tw> > > matcher;
    return matcher.match(m);
  }

  template<typename W, typename M, typename Tm, typename Tw>
  typename algebra::series_traits<rat::exp<Tm, Tw> >::support_t
  op_support(const algebra::Series<W, M>& s, const rat::exp<Tm, Tw>& m)
  {
    vcsn::SupportMatcher<algebra::Series<W, M>, rat::exp<Tm, Tw>,
      algebra::DispatchFunction<rat::exp<Tm, Tw> > > matcher(s);
    matcher.match(m);
    return matcher.get();
  }

  template <typename W, typename M, typename Tm, typename Tw>
  Tm op_choose_from_supp(const algebra::Series<W, M>&,
			 const rat::exp<Tm, Tw>& m)
  {
    rat::RandomVisitor<Tm, Tw> v;
    m.accept(v);
    return v.get();
  }

  template<typename W, typename M, typename Tm, typename Tw>
  const rat::exp<Tm, Tw>& identity_value(SELECTOR2(algebra::Series<W, M>),
					 SELECTOR2(rat::exp<Tm, Tw>))
  {
    static const rat::exp<Tm, Tw> instance = rat::exp<Tm, Tw>::one();
    return instance;
  }

  template<typename W, typename M, typename Tm, typename Tw>
  const rat::exp<Tm, Tw>& zero_value(SELECTOR2(algebra::Series<W, M>),
				     SELECTOR2(rat::exp<Tm, Tw>))
  {
    static const rat::exp<Tm, Tw> instance = rat::exp<Tm, Tw>::zero();
    return instance;
  }

  template <typename W, typename M, typename Tm, typename Tw>
  void op_in_transpose(const algebra::Series<W, M>& s,
		       rat::exp<Tm, Tw>& exp)
  {
    Element<algebra::Series<W, M>,
      rat::exp<Tm, Tw> > elt(s, exp);

    vcsn::algebra::KRatExpTranspose<
      algebra::Series<W, M>,
      rat::exp<Tm, Tw>,
      algebra::DispatchFunction<vcsn::rat::exp<Tm, Tw> >
      > matcher(elt);

    elt = matcher.match(exp);
    exp = elt.value();
  }


  template<typename W, typename M, typename Tm, typename Tw>
  void op_in_add(const algebra::Series<W, M>&,
		 rat::exp<Tm, Tw>& dst,
		 const rat::exp<Tm, Tw>& arg)
  {
    // case any + 0
    if (arg.base()->what() == rat::Node<Tm, Tw>::zero)
      return ;

    // case 0 + any
    if (dst.base()->what() == rat::Node<Tm, Tw>::zero)
      {
	delete dst.base();
	dst.base() = arg.base()->clone();
	return;
      }

    dst.base() = new rat::Sum<Tm, Tw>(dst.base(), arg.base()->clone());
  }

  template<typename W, typename M, typename Tm, typename Tw>
  rat::exp<Tm, Tw> op_add(const algebra::Series<W, M>& s,
			  const rat::exp<Tm, Tw>& a,
			  const rat::exp<Tm, Tw>& b)
  {
    rat::exp<Tm, Tw> ret(a);
    op_in_add(s, ret, b);
    return ret;
  }

  template<typename W, typename M, typename Tm, typename Tw>
  void op_in_mul(const algebra::Series<W, M>& s,
		 rat::exp<Tm, Tw>& dst,
		 const rat::exp<Tm, Tw>& arg)
  {
    typedef rat::Node<Tm, Tw>			node_t;
    typedef typename  rat::Node<Tm, Tw>::type	type;
    typedef rat::One<Tm, Tw>			n_one_t;
    typedef rat::Constant<Tm, Tw>		n_const_t;
    typedef rat::Zero<Tm, Tw>			n_zero_t;
    typedef rat::Star<Tm, Tw>			n_star_t;
    typedef rat::LeftWeighted<Tm, Tw>		n_lweight_t;
    typedef rat::RightWeighted<Tm, Tw>		n_rweight_t;
    typedef rat::Sum<Tm, Tw>			n_sum_t;
    typedef rat::Product<Tm, Tw>		n_prod_t;

    type this_type = dst.base()->what();
    type arg_type  = arg.base()->what();

    // case 0 * E -> 0
    if (this_type == node_t::zero)
      return;

    // case E * 0 -> 0
    if (arg_type == node_t::zero)
      {
	delete dst.base();
	dst.base() = new n_zero_t;
	return;
      }

    // case 1 * E -> E
    if (this_type == node_t::one)
      {
	delete dst.base();
	dst.base() = arg.base()->clone();
	return;
      }

    // case E * 1 -> E
    if (arg_type == node_t::one)
      {
	return;
      }

    // case E * (k' 1) -> E k'
    if (arg_type == node_t::lweight)
    {
      n_lweight_t *p = dynamic_cast<n_lweight_t*>(arg.base());
      if (p->child_->what() == node_t::one)
      {
	op_in_mul(s, s.semiring(), dst, p->weight_);
        return;
      }
    }

    /// @bug FIXME: Add the following transformation in a separated function.
    /*
    // case (k E) * E' -> k (E * E')
    // it manages case (k 1) * E' -> k E'
    if (this_type == node_t::lweight)
    {
      n_lweight_t *p = dynamic_cast<n_lweight_t*>(dst.base());
      if (p->child_->what() == node_t::one)
	// case (k 1) * E' -> k E'
	dst = op_mul(s.semiring(), s, p->weight_, arg);
      else
	// case (k E) * E' -> k (E * E')
	p->child_ = new n_prod_t(p->child_, arg.base()->clone());
      return;
    }

    // case E * (E' k') -> (E * E') k'
    if (arg_type == node_t::rweight)
    {
      n_rweight_t *p = dynamic_cast<n_rweight_t*>(arg.base());
      dst.base() = new n_rweight_t(p->weight_,
	new n_prod_t(dst.base(), p->child_->clone()));
      return;
    }
    */

    // case (k 1) * E' -> k E'
    if (this_type == node_t::lweight)
    {
      n_lweight_t *p = dynamic_cast<n_lweight_t*>(dst.base());
      if (p->child_->what() == node_t::one)
      {
	dst = op_mul(s.semiring(), s, p->weight_, arg);
        return;
      }
    }

    // general case
    dst.base() = new n_prod_t(dst.base(), arg.base()->clone());
    return;
  }

  template<typename W, typename M, typename Tm, typename Tw>
  rat::exp<Tm, Tw> op_mul(const algebra::Series<W, M>& s,
			  const rat::exp<Tm, Tw>& a,
			  const rat::exp<Tm, Tw>& b)
  {
    rat::exp<Tm, Tw> ret(a);
    op_in_mul(s, ret, b);
    return ret;
  }


  /*---------------------.
    | foreign constructors |
    `---------------------*/

  template<typename Tm, typename Tw, typename M, typename W>
  rat::exp<Tm, Tw> op_convert(SELECTOR2(algebra::Series<M, W>),
			      SELECTOR2(rat::exp<Tm, Tw>),
			      const Tm& m_value)
  {
    return new rat::Constant<Tm, Tw>(m_value);
  }

  template<typename Tm, typename Tw, typename M, typename W>
  rat::exp<Tm, Tw> op_convert(SELECTOR2(algebra::Series<M, W>),
			      SELECTOR2(rat::exp<Tm, Tw>),
			      char m_value)
  {
    const char str[] = {m_value, '\0'};
    return new rat::Constant<Tm, Tw>(str);
  }

  template<typename Tm, typename Tw, typename W, typename M, typename oTm>
  rat::exp<Tm, Tw> op_convert(SELECTOR2(algebra::Series<W, M>) s,
			      SELECTOR2(rat::exp<Tm, Tw>),
			      SELECTOR(M),
			      const oTm& m_value)
  {
    // FIXME: this is completely broken. It should break up m_value
    // into letters.
    if (m_value == identity_value(SELECT(M), SELECT(oTm)))
      return rat::exp<Tm, Tw>::one();
    return rat::exp<Tm, Tw>::constant(op_convert(s.monoid(), SELECT(Tm),
    						 m_value));
  }

  template<typename Tm, typename Tw, typename W, typename M, typename oTw>
  rat::exp<Tm, Tw> op_convert(SELECTOR2(algebra::Series<W, M>),
			      SELECTOR2(rat::exp<Tm, Tw>),
			      SELECTOR(W),
			      const oTw& w_value)
  {
    if (w_value == identity_value(SELECT(W), SELECT(oTw)))
      return rat::exp<Tm, Tw>::one();
    if (w_value == zero_value(SELECT(W), SELECT(oTw)))
      return rat::exp<Tm, Tw>::zero();
    rat::exp<Tm, Tw> ret = rat::exp<Tm, Tw>::one();
    ret.base() = new rat::LeftWeighted<Tm, Tw>
      (op_convert(SELECT(W), SELECT(Tw),
		  w_value), ret.base());
    return ret;
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  void op_assign(const algebra::Series<W, M>&,
		 const M&,
		 rat::exp<Tm, Tw>& dst,
		 const oTm& src)
  {
    // FIXME: this is completely broken also.

    if (src == identity_value(SELECT(M), SELECT(oTm)))
      dst = rat::exp<Tm, Tw>::one();
    else
      dst = rat::exp<Tm, Tw>::constant(src);
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  void op_assign(const algebra::Series<W, M>&,
		 const W& semiring,
		 rat::exp<Tm, Tw>& dst,
		 const oTw& src)
  {
    dst = op_convert
      (SELECT2(algebra::Series<W, M>), SELECT2(rat::exp<Tm, Tw>), SELECT(W), src);
  }

  /*-----.
    | star |
    `-----*/

  template<typename W, typename M, typename Tm, typename Tw>
  bool op_starable(const algebra::Series<W, M>&,
		    const rat::exp<Tm, Tw>&)
  {
    return true;
  }

  template<typename W, typename M, typename Tm, typename Tw>
  void op_in_star(const algebra::Series<W, M>&,
		  rat::exp<Tm, Tw>& dst)
  {
    if (dst.base()->what() == rat::Node<Tm, Tw>::zero)
      dst = rat::exp<Tm, Tw>::one();
    else
      dst.base() = new rat::Star<Tm, Tw>(dst.base());
  }

  template<typename W, typename M, typename Tm, typename Tw>
  rat::exp<Tm, Tw>
  op_star(const algebra::Series<W, M>&,
	  const rat::exp<Tm, Tw>& src)
  {
    if (src.base()->what() == rat::Node<Tm, Tw>::zero)
      return rat::exp<Tm, Tw>::one();
    rat::exp<Tm, Tw> ret(src);
    ret.base() = new rat::Star<Tm, Tw>(ret.base());
    return ret;
  }


  /*--------------------------------------.
    | foreign addition with monoid elements |
    `--------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  void op_in_add(const algebra::Series<W, M>& s,
		 const M& monoid,
		 rat::exp<Tm, Tw>& dst,
		 const oTm& src)
  {
    op_in_add(s, dst, op_convert(SELECT2(algebra::Series<W, M>),
				 SELECT2(rat::exp<Tm, Tw>),
				 SELECT(M),
				 src));
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  rat::exp<Tm, Tw> op_add(const algebra::Series<W, M>& s,
			  const M& monoid,
			  const rat::exp<Tm, Tw>& a,
			  const oTm& b)
  {
    rat::exp<Tm, Tw> ret(a);
    op_in_add(s, monoid, ret, b);
    return ret;
  }

  template<typename M, typename W, typename oTm, typename Tm, typename Tw>
  rat::exp<Tm, Tw> op_add(const M& monoid,
			  const algebra::Series<W, M>& s,
			  const oTm& a,
			  const rat::exp<Tm, Tw>& b)
  {
    rat::exp<Tm, Tw> ret(b);
    op_in_add(s, monoid, ret, a);
    return ret;
  }

  /*---------------------------------------.
    | foreign addition with semiring elements |
    `---------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  void op_in_add(const algebra::Series<W, M>& s,
		 const W& semiring,
		 rat::exp<Tm, Tw>& dst,
		 const oTw& src)
  {
    precondition(& s.semiring() == & semiring);
    op_in_add(s, dst, op_convert(SELECT2(algebra::Series<W, M>),
				 SELECT2(rat::exp<Tm, Tw>),
				 SELECT(W),
				 src));
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  rat::exp<Tm, Tw> op_add(const algebra::Series<W, M>& s,
			  const W& semiring,
			  const rat::exp<Tm, Tw>& a,
			  const oTw& b)
  {
    rat::exp<Tm, Tw> ret(a);
    op_in_add(s, semiring, ret, b);
    return ret;
  }

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  rat::exp<Tm, Tw> op_add(const W& semiring,
			  const algebra::Series<W, M>& s,
			  const oTw& a,
			  const rat::exp<Tm, Tw>& b)
  {
    rat::exp<Tm, Tw> ret(b);
    op_in_add(s, semiring, ret, a);
    return ret;
  }

  /*-------------------------------------------.
    | foreign multiplication by semiring elements |
    `-------------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  void op_in_mul(const algebra::Series<W, M>& s,
		 const W& semiring,
		 rat::exp<Tm, Tw>& ret,
		 const oTw& w)
  {
    precondition(& s.semiring() == & semiring);
    (void) s; (void) semiring;

    typedef rat::Node<Tm, Tw>				node_t;
    typedef typename rat::Node<Tm, Tw>::type		type;
    typedef rat::One<Tm, Tw>				n_one_t;
    typedef rat::Constant<Tm, Tw>			n_const_t;
    typedef rat::Zero<Tm, Tw>				n_zero_t;
    typedef rat::Star<Tm, Tw>				n_star_t;
    typedef rat::LeftWeighted<Tm, Tw>			n_lweight_t;
    typedef rat::RightWeighted<Tm, Tw>			n_rweight_t;
    typedef rat::Sum<Tm, Tw>				n_sum_t;
    typedef rat::Product<Tm, Tw>			n_prod_t;

    type this_type = ret.base()->what();

    // case 0 * k -> 0
    if (this_type == node_t::zero)
      return;

    // case E * 1 -> E
    if (w == identity_value(SELECT(W), SELECT(oTw)))
      return;

    // case E * 0 -> 0
    if (w == zero_value(SELECT(W), SELECT(oTw)))
      {
	delete ret.base();
	ret.base() = new n_zero_t;
	return;
      }

    // case 1 * k -> k * 1
    if (this_type == node_t::one)
      {
	ret.base() = new n_lweight_t
	  (op_convert(SELECT(W), SELECT(Tw), w), ret.base());
	return;
      }

    /// @bug FIXME: Add the following transformation in a separated function.
    /*
    // case (k' 1) * k -> [k' k] 1
    if (this_type == node_t::lweight)
      {
	n_lweight_t* p = dynamic_cast<n_lweight_t*>(ret.base());
	type child_type = p->child_->what();

	if (child_type == node_t::one)
	  {
	    op_in_mul
	      (s.semiring(), p->weight_, op_convert(SELECT(W), SELECT(Tw), w));
	    return;
	  }
      }

    // case (k' E) * k -> general case

    // case (E k') * k -> E [k' k]
    if (this_type == node_t::rweight)
      {
	op_in_mul(s.semiring(),
		  dynamic_cast<n_rweight_t* >(ret.base())
		  ->weight_, op_convert(SELECT(W), SELECT(Tw), w));
	return;
      }
    */

    // general case
    ret.base() =
      new n_rweight_t(op_convert(SELECT(W), SELECT(Tw), w), ret.base());
    return;
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  rat::exp<Tm, Tw> op_mul(const algebra::Series<W, M>& s,
			  const W& semiring,
			  const rat::exp<Tm, Tw>& a,
			  const oTw& w)
  {
    rat::exp<Tm, Tw> ret(a);
    op_in_mul(s, semiring, ret, w);
    return ret;
  }

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  rat::exp<Tm, Tw> op_mul(const W& semiring,
			  const algebra::Series<W, M>& s,
			  const oTw& w,
			  const rat::exp<Tm, Tw>& b)
  {
    precondition(& s.semiring() == & semiring);
    (void) s; (void) semiring;

    typedef rat::Node<Tm, Tw>				node_t;
    typedef typename rat::Node<Tm, Tw>::type		type;
    typedef rat::One<Tm, Tw>				n_one_t;
    typedef rat::Constant<Tm, Tw>			n_const_t;
    typedef rat::Zero<Tm, Tw>				n_zero_t;
    typedef rat::Star<Tm, Tw>				n_star_t;
    typedef rat::LeftWeighted<Tm, Tw>			n_lweight_t;
    typedef rat::RightWeighted<Tm, Tw>			n_rweight_t;
    typedef rat::Sum<Tm, Tw>				n_sum_t;
    typedef rat::Product<Tm, Tw>			n_prod_t;

    rat::exp<Tm, Tw> ret(b);

    type this_type = ret.base()->what();

    // case k * 0 -> 0
    if (this_type == node_t::zero)
      return ret;

    // case k * 1 -> general case

    // case 0 * E -> 0
    if (w == zero_value(SELECT(W), SELECT(oTw)))
      { return rat::exp<Tm, Tw>::zero(); }

    // case 1 * E -> E
    if (w == identity_value(SELECT(W), SELECT(oTw)))
      return ret;

    /// @bug FIXME: Add the following transformation in a separated function.
    /*
    // case k * (k' E) -> [k k'] E
    if (this_type == node_t::lweight)
      {
	n_lweight_t* p = dynamic_cast<n_lweight_t*>(ret.base());
	p->weight_ = op_mul
	  (s.semiring(), op_convert(SELECT(W), SELECT(Tw), w), p->weight_);
	return ret;
      }

    // case k * (E k') -> (k E) k'
    if (this_type == node_t::rweight)
      {
	n_rweight_t* p = dynamic_cast<n_rweight_t*>(ret.base());
	p->child_ =
	  new n_lweight_t(op_convert(SELECT(W), SELECT(Tw), w), p->child_);
	return ret;
      }
    */

    // general case
    ret.base() = new n_lweight_t(w, ret.base());
    return ret;
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  Tw op_series_get(const algebra::Series<W, M>& s,
		   const rat::exp<Tm, Tw>& p,
		   const oTm& m)
  {
    typedef typename algebra::Series<W,M>		series_set_t;
    typedef typename algebra::polynom<Tm, Tw>		series_set_elt_value_t;
    typedef typename rat::exp<Tm, Tw>			exp_t;
    typedef Graph
      <
      labels_are_series,
      Tm,
      Tw,
      series_set_elt_value_t,
      Tm,
      NoTag,
      NoTag
      >
      automaton_impl_t;
    typedef Element<Automata<series_set_t>, automaton_impl_t>	automaton_t;

    typename automaton_t::set_t	automata (s);
    automaton_t			a (automata);
    standard_of(a, p);
    return eval(a, m).value();
  }

  template<typename W, typename M, typename Tm, typename Tw,
	   typename oTm, typename oTw>
  void op_series_set(const algebra::Series<W, M>& s,
		     rat::exp<Tm, Tw>& p,
		     const oTm& m,
		     const oTw& w)
  {
    if ((m == algebra::identity_as<oTm>::of(s.monoid())) &&
	(w == algebra::identity_as<oTw>::of(s.semiring())) &&
	(p == algebra::zero_as<rat::exp<Tm, Tw> >::of(s)))
      {
	p = algebra::identity_as<rat::exp<Tm, Tw> >::of(s).value();
	return ;
      }

    rat::exp<Tm, Tw> ret =
      rat::exp<Tm, Tw>::constant(op_convert(s.monoid(),
					    SELECT(Tm),
					    m));
    op_in_add(s, p, op_mul(s.semiring(), s, w, ret));
  }

  /*----------------------------------------------------------.
    | MetaElement<algebra::SeriesBase<algebra::Series<W, M> >, rat::exp<Tm, Tw> > |
    `----------------------------------------------------------*/

  template <typename W, typename M, typename Tm, typename Tw>
  void
  MetaElement<algebra::Series<W, M>, rat::exp<Tm, Tw> >::accept
  (const rat::ConstNodeVisitor<Tm, Tw>& v) const
  {
    this->value().accept(v);
  }

  template <typename W, typename M, typename Tm, typename Tw>
  size_t
  MetaElement<algebra::Series<W, M>, rat::exp<Tm, Tw> >::depth() const
  {
    return this->value().depth();
  }

  template <class W, class M, class Tm, class Tw>
  Element<algebra::Series<W,M>, rat::exp<Tm,Tw> >
  op_choose(const algebra::Series<W,M>& s,
	    SELECTOR2(rat::exp<Tm,Tw>))
  {
    Element<algebra::Series<W,M>, rat::exp<Tm, Tw> > e(s);
    // FIXME : add global constants to do this !
    unsigned nb = RAND___(10);
    while (nb != 0)
      {
	--nb;
	unsigned t = RAND___(3);
	switch (t)
	  {
	    // star
	  case 0 :
	    {
	      e = e.star();
	      continue;
	    }
	    // plus
	  case 1 :
	    {
	      Element<algebra::Series<W,M>, rat::exp<Tm,Tw> >
		ep(s, s.monoid().choose(SELECT(Tm)));
	      ep = ep * s.semiring().choose(SELECT(Tw));
	      unsigned t = RAND___(2);
	      if (t < 1)
		e = e + ep;
	      else
		e = ep + e;
	      continue;
	    }
	    // mult
	  case 2 :
	    {
	      Element<algebra::Series<W,M>, rat::exp<Tm,Tw> >
		ep(s, s.monoid().choose(SELECT(Tm)));
	      ep = ep * s.semiring().choose(SELECT(Tw));
	      unsigned t = RAND___(2);
	      if (t < 1)
		e = e * ep;
	      else
		e = ep * e;
	      continue;
	    }
	  }
      }
    return Element<algebra::Series<W,M>, rat::exp<Tm,Tw> >(s, e);
  }

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_HXX
