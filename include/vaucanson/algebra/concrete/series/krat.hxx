// krat.hxx
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

#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_HXX
# define VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_HXX

# include <utility>
# include <vaucanson/algebra/concrete/series/series.hh>
# include <vaucanson/algebra/concrete/series/rat/exp.hh>
# include <vaucanson/algebra/concrete/series/rat/random_visitor.hh>
# include <vaucanson/tools/usual.hh>

namespace vcsn {

  template<typename W, typename M, typename Tm, typename Tw>
  inline
  bool op_contains(const Series<W, M>& s, const rat::exp<Tm, Tw>& m)
  { 
    assert(! "op_contains for Element<Series<W,M>, exp<Tm,Tw> > not defined.");
    return true; 
  }

  template<typename W, typename M, typename Tm, typename Tw>
  inline
  bool op_is_finite_app(const Series<W, M>& s, const rat::exp<Tm, Tw>& m)
  { 
    return false; 
  }

  template <typename W, typename M, typename Tm, typename Tw>
  Tm op_choose_from_supp(const Series<W, M>& s, const rat::exp<Tm, Tw>& m)
  {
    rat::RandomVisitor<Tm, Tw> v;
    m.accept(v);
    return v.get();
  }

  template<typename W, typename M, typename Tm, typename Tw>
  const rat::exp<Tm, Tw>& identity_value(SELECTOR2(Series<W, M>), 
					 SELECTOR2(rat::exp<Tm, Tw>))
  {
    static const rat::exp<Tm, Tw> instance = rat::exp<Tm, Tw>::one();
    return instance;
  }

  template<typename W, typename M, typename Tm, typename Tw>
  const rat::exp<Tm, Tw>& zero_value(SELECTOR2(Series<W, M>), 
				     SELECTOR2(rat::exp<Tm, Tw>))
  {
    static const rat::exp<Tm, Tw> instance = rat::exp<Tm, Tw>::zero();
    return instance;
  }

  template <typename W, typename M, typename Tm, typename Tw>
  inline
  void op_in_tranpose(const Series<W, M>& s, 
		      rat::exp<Tm, Tw>& dst)
  {
    typedef rat::Product<Tm, Tw>	n_prod_t;
    typedef rat::Node<Tm, Tw>		node_t;

    n_prod_t* node = dynamic_cast<n_prod_t*>(arg.base());
    if (node != 0)
      {
	node_t* tmp = node->right_;
	node->right_ = node->left_;
	node->left_ = tmp;
      }
  }

  template<typename W, typename M, typename Tm, typename Tw>
  inline
  void op_in_add(const Series<W, M>&, 
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
  inline
  rat::exp<Tm, Tw> op_add(const Series<W, M>& s,
			  const rat::exp<Tm, Tw>& a,
			  const rat::exp<Tm, Tw>& b)
  {
    rat::exp<Tm, Tw> ret(a);
    op_in_add(s, ret, b);
    return ret;
  }
    
  template<typename W, typename M, typename Tm, typename Tw>
  inline
  bool krat_simplify_left_is_k(const Series<W, M>& s,
			       rat::exp<Tm, Tw>& dst,
			       const rat::exp<Tm, Tw>& other, 
			       rat::LeftWeighted<Tm, Tw>* left, 
			       typename rat::Node<Tm, Tw>::type other_type)
  {
    typedef rat::Node<Tm, Tw>			node_t;
    typedef rat::LeftWeighted<Tm, Tw>		n_lweight_t;
    typedef rat::RightWeighted<Tm, Tw>	n_rweight_t;
    switch (other_type)
      {
      case node_t::lweight:
	{    // case (k 1) * (k' E') -> ([k k'] E')
	  const n_lweight_t* right =
	    dynamic_cast<const n_lweight_t*>(other.base());
	    
	  op_in_mul(s.weights(), left->weight_, right->weight_); 
	  // ([k k'] 1) * (k' E')
	  delete left->child_;			// ([k k'] %) * (k' E')
	  left->child_ = right->child_->clone();	// ([k k'] E')
	    
	  return true; 
	}
	  
      case node_t::rweight:
	{   // case (k 1) * (E' k') -> ((k E) k')
	  const n_rweight_t* right =
	    dynamic_cast<const n_rweight_t*>(other.base());
	    
	  delete left->child_;			   // (k %) * (E' k')
	  left->child_ = right->child_->clone();       // (k E') * (E' k')
	  dst.base() = new n_rweight_t(right->weight_, dst.base()); 
	  // ((k E') k')
	    
	  return true;
	}
	 
      // FIXME: reduce (k 1) * Const -> (k Const)
 
      default: break;
	  
      }
      
    return false; // no simplification occured
  }

  template<typename W, typename M, typename Tm, typename Tw>
  inline
  bool krat_simplify_left_is_ka(const Series<W, M>& s,
				rat::exp<Tm, Tw>&,
				const rat::exp<Tm, Tw>& other, 
				rat::LeftWeighted<Tm, Tw>* left, 
				typename rat::Node<Tm, Tw>::type other_type)
  {
    typedef rat::Node<Tm, Tw>		node_t;
    typedef rat::LeftWeighted<Tm, Tw>	n_lweight_t;
      
    const n_lweight_t* right;
      
    if (other_type == node_t::lweight &&
	(right = dynamic_cast<const n_lweight_t* >(other.base()))
	->what() == node_t::one)
      {
	// case (k a) * (k' 1) -> ([k k'] a)
	op_in_mul(s.weights(), left->weight_, right->weight_); 
	return true;
      }
    return false; // could not simplify
  }
    
  template<typename W, typename M, typename Tm, typename Tw>
  inline
  bool krat_simplify_left_is_kany(const Series<W, M>& s,
				  rat::exp<Tm, Tw>&,
				  const rat::exp<Tm, Tw>& other, 
				  rat::LeftWeighted<Tm, Tw>* left, 
				  typename 
				  rat::Node<Tm, Tw>::type other_type)
  {
    typedef rat::Node<Tm, Tw>		node_t;
    typedef rat::LeftWeighted<Tm, Tw>	n_lweight_t;
    const n_lweight_t* right;

    if (other_type == node_t::lweight &&
	(right = dynamic_cast<const n_lweight_t* >(other.base()))
	->what() == node_t::one)
      {
	// case (k E') * (k' 1) -> ([k k'] E')
	op_in_mul(s.weights(), left->weight_, right->weight_); 
	return true;
      }
    return false; // could not simplify
  }
    
  template<typename W, typename M, typename Tm, typename Tw>
  inline
  bool krat_simplify_left_is_lweight(const Series<W, M>& s,
				     rat::exp<Tm, Tw>& dst,
				     const rat::exp<Tm, Tw>& other, 
				     rat::LeftWeighted<Tm, Tw>* left, 
				     typename 
				     rat::Node<Tm, Tw>::type other_type)
  {
    typename rat::Node<Tm, Tw>::type left_child_type = left->child_->what();
      
    switch(left_child_type)
      {
      case rat::Node<Tm, Tw>::one:
	return krat_simplify_left_is_k(s, dst, other, left, other_type);
      case rat::Node<Tm, Tw>::constant:
	return krat_simplify_left_is_ka(s, dst, other, left, other_type);
      default:
	return krat_simplify_left_is_kany(s, dst, other, left, other_type);
      }
  }
    
  template<typename W, typename M, typename Tm, typename Tw>
  inline
  bool krat_simplify_left_is_anyk(const Series<W, M>& s,
				  rat::exp<Tm, Tw>& dst,
				  const rat::exp<Tm, Tw>& other, 
				  rat::RightWeighted<Tm, Tw>* left, 
				  typename 
				  rat::Node<Tm, Tw>::type other_type)
  {
    typedef rat::Node<Tm, Tw>		node_t;
    typedef rat::LeftWeighted<Tm, Tw>	n_lweight_t;
    typedef rat::RightWeighted<Tm, Tw>	n_rweight_t;
    typedef rat::Product<Tm, Tw>	n_prod_t;

    if (other_type == node_t::lweight)
      {
	const n_lweight_t *right = 
	  dynamic_cast<const n_lweight_t *>(other.base());
	  
	if (right->child_->what() == node_t::one) // case E k * k' 1
	  {
	    // case (E k) * (k' 1) -> (E [k k'])
	    op_in_mul(s.weights(), left->weight_, right->weight_); 
	    return true; 
	  }
	  
	// case (E k) * (k' E') -> (E * (k k' E'))
	  
	n_lweight_t *new_right = // (k k' E')
	  new n_lweight_t(op_mul(s.weights(), left->weight_, right->weight_),
			  *right->child_->clone());
	  
	dst.base() = left->child_;		// (E k) -> E
	left->child_ = 0;
	delete left;    // delete (% k)
	  
	dst.base() = new n_prod_t(dst.base(), new_right); 
	// build E * ([k k'] E')
	return true;
      }
    return false;
  }

  template<typename Tm, typename Tw>
  inline
  bool krat_simplify_left_is_const( rat::exp<Tm, Tw>& dst,
				    const rat::exp<Tm, Tw>& other, 
				    typename 
				    rat::Node<Tm, Tw>::type other_type)
  {
    typedef rat::Node<Tm, Tw>			node_t;
    typedef rat::LeftWeighted<Tm, Tw>		n_lweight_t;
    typedef rat::RightWeighted<Tm, Tw>	n_rweight_t;
      
    const n_lweight_t *right;
      
    if (other_type == node_t::lweight &&
	(right = dynamic_cast<const n_lweight_t*>(other.base()))
	->child_->what() == node_t::one)
      {
	// case a * (k 1) -> (k a)
	dst.base() = new n_lweight_t(right->weight_, dst.base()); 
	return true; 
      }
    return false;
  }

    
  template<typename W, typename M, typename Tm, typename Tw>
  inline
  void op_in_mul(const Series<W, M>& s, 
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
    typedef rat::RightWeighted<Tm, Tw>	n_rweight_t;
    typedef rat::Sum<Tm, Tw>			n_sum_t;
    typedef rat::Product<Tm, Tw>		n_prod_t;
      
    type this_type = dst.base()->what();
    type arg_type  = arg.base()->what();

    // case 0 * E
    if (this_type == node_t::zero)
      return; 

    // case E * 0
    if (arg_type == node_t::zero)
      { 
	delete dst.base(); 
	dst.base() = new n_zero_t; 
	return; 
      }
      
    // case 1 * E
    if (this_type == node_t::one)
      { 
	delete dst.base(); 
	dst.base() = arg.base()->clone(); 
	return; 
      }
      
    // case E * 1
    if (arg_type == node_t::one)
      {
	return; 
      }

    switch (this_type)
      { 
      case node_t::lweight:	// case (k E) * E'
	{
	  n_lweight_t* left = dynamic_cast<n_lweight_t*>(dst.base());

	  if (krat_simplify_left_is_lweight(s, dst, arg, left, arg_type))
	    return;
	  break;
	}
	    
      case node_t::rweight: // case (E k) * E'
	{
	  n_rweight_t *left = dynamic_cast<n_rweight_t*>(dst.base());
	      
	  if (krat_simplify_left_is_anyk(s, dst, arg, left, arg_type))
	    return;
	  break;
	} 

      case node_t::constant: // case a * E'
	{
	  if (krat_simplify_left_is_const(dst, arg, arg_type))
	    return;

	  break;
	}

      default: break;
      } 

    // general case
    dst.base() = new n_prod_t(dst.base(), arg.base()->clone());
    return;
  }

  template<typename W, typename M, typename Tm, typename Tw>
  inline
  rat::exp<Tm, Tw> op_mul(const Series<W, M>& s,
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

  template<typename Tm, typename Tw, typename M, typename W, typename S>
  inline
  rat::exp<Tm, Tw> op_convert(SELECTOR2(rat::exp<Tm, Tw>), 
			      SELECTOR2(Series<M, W>),
			      const std::basic_string<S>& m_value)
  { 
    return new rat::Constant<Tm, Tw>(m_value); 
  }
  
  template<typename Tm, typename Tw, typename M, typename W>
  inline
  rat::exp<Tm, Tw> op_convert(SELECTOR2(rat::exp<Tm, Tw>), 
			      SELECTOR2(Series<M, W>),
			      char m_value)
  { 
    const char str[] = {m_value, '\0'};
    return new rat::Constant<Tm, Tw>(str); 
  }
  
  template<typename Tm, typename Tw, typename W, typename M, typename oTm>
  inline
  rat::exp<Tm, Tw> op_convert(SELECTOR2(rat::exp<Tm, Tw>),
			      SELECTOR2(Series<W, M>),
			      SELECTOR(M),
			      const oTm& m_value)
  {
    // FIXME: this is completely broken. It should break up m_value
    // into letters.
    if (m_value == identity_value(SELECT(M), SELECT(oTm)))
      return rat::exp<Tm, Tw>::one();
    return rat::exp<Tm, Tw>::constant(op_convert(SELECT(Tm), SELECT(M), 
    						 m_value));
  }

  template<typename Tm, typename Tw, typename W, typename M, typename oTw>
  rat::exp<Tm, Tw> op_convert(SELECTOR2(rat::exp<Tm, Tw>),
			      SELECTOR2(Series<W, M>),
			      SELECTOR(W),
			      const oTw& w_value)
  {
    if (w_value == identity_value(SELECT(W), SELECT(oTw)))
      return rat::exp<Tm, Tw>::one();
    if (w_value == zero_value(SELECT(W), SELECT(oTw)))
      return rat::exp<Tm, Tw>::zero();
    rat::exp<Tm, Tw> ret = rat::exp<Tm, Tw>::one();
    ret.base() = new rat::LeftWeighted<Tm, Tw>
      (op_convert(SELECT(Tw), SELECT(W), 
		  w_value), ret.base());
    return ret;
  }
    
  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  inline
  void op_assign(const Series<W, M>&,
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
  inline
  void op_assign(const Series<W, M>& s,
		 const W& weights,
		 rat::exp<Tm, Tw>& dst,
		 const oTw& src)
  {
    dst = op_convert
      (SELECT2(rat::exp<Tm, Tw>), SELECT2(Series<W, M>), SELECT(W), src);
  }

  /*-----.
    | star |
    `-----*/

  template<typename W, typename M, typename Tm, typename Tw>
  inline
  bool op_stareable(const Series<W, M>& s,
		    const rat::exp<Tm, Tw>& dst)
  { 
    return true; 
  }

  template<typename W, typename M, typename Tm, typename Tw>
  inline
  void op_in_star(const Series<W, M>&,
		  rat::exp<Tm, Tw>& dst)
  { 
    if (dst.base()->what() == rat::Node<Tm, Tw>::zero)
      dst = rat::exp<Tm, Tw>::one();
    else
      dst.base() = new rat::Star<Tm, Tw>(dst.base());
  }

  template<typename W, typename M, typename Tm, typename Tw>
  inline
  rat::exp<Tm, Tw> 
  op_star(const Series<W, M>& s,
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
  inline
  void op_in_add(const Series<W, M>& s,
		 const M& monoid,
		 rat::exp<Tm, Tw>& dst,
		 const oTm& src)
  { 
    op_in_add(s, dst, op_convert(SELECT2(rat::exp<Tm, Tw>), 
				 SELECT2(Series<W, M>),
				 SELECT(M),
				 src));
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  inline
  rat::exp<Tm, Tw> op_add(const Series<W, M>& s,
			  const M& monoid,
			  const rat::exp<Tm, Tw>& a,
			  const oTm& b)
  { 
    rat::exp<Tm, Tw> ret(a);
    op_in_add(s, monoid, ret, b);
    return ret;
  }

  template<typename M, typename W, typename oTm, typename Tm, typename Tw>
  inline
  rat::exp<Tm, Tw> op_add(const M& monoid,
			  const Series<W, M>& s,
			  const oTm& a,
			  const rat::exp<Tm, Tw>& b)
  { 
    rat::exp<Tm, Tw> ret(b);
    op_in_add(s, monoid, ret, a);
    return ret;
  }

  /*---------------------------------------.
    | foreign addition with weights elements |
    `---------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  inline
  void op_in_add(const Series<W, M>& s,
		 const W& weights,
		 rat::exp<Tm, Tw>& dst,
		 const oTw& src)
  { 
    // assert(s.weights() == weights);
    op_in_add(s, dst, op_convert(SELECT2(rat::exp<Tm, Tw>), 
				 SELECT2(Series<W, M>),
				 SELECT(W),
				 src));
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  inline
  rat::exp<Tm, Tw> op_add(const Series<W, M>& s,
			  const W& weights,
			  const rat::exp<Tm, Tw>& a,
			  const oTw& b)
  { 
    rat::exp<Tm, Tw> ret(a);
    op_in_add(s, weights, ret, b);
    return ret;
  }

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  inline
  rat::exp<Tm, Tw> op_add(const W& weights,
			  const Series<W, M>& s,
			  const oTw& a,
			  const rat::exp<Tm, Tw>& b)
  { 
    rat::exp<Tm, Tw> ret(b);
    op_in_add(s, weights, ret, a);
    return ret;
  }

  /*-------------------------------------------.
    | foreign multiplication by weights elements |
    `-------------------------------------------*/

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  inline
  void op_in_mul(const Series<W, M>& s,
		 const W&,
		 rat::exp<Tm, Tw>& ret,
		 const oTw& w)
  { 
    // assert(s.weights() == weights);
    typedef rat::Node<Tm, Tw>				node_t;
    typedef typename rat::Node<Tm, Tw>::type		type;
    typedef rat::One<Tm, Tw>				n_one_t;
    typedef rat::Constant<Tm, Tw>			n_const_t;
    typedef rat::Zero<Tm, Tw>				n_zero_t;
    typedef rat::Star<Tm, Tw>				n_star_t;
    typedef rat::LeftWeighted<Tm, Tw>			n_lweight_t;
    typedef rat::RightWeighted<Tm, Tw>		n_rweight_t;
    typedef rat::Sum<Tm, Tw>				n_sum_t;
    typedef rat::Product<Tm, Tw>			n_prod_t;

    type this_type = ret.base()->what();
      
    // case 0 * k
    if (this_type == node_t::zero)
      return;

    // case E * 1
    if (w == identity_value(SELECT(W), SELECT(oTw)))
      return;

    // case E * 0
    if (w == zero_value(SELECT(W), SELECT(oTw)))
      { 
	delete ret.base(); 
	ret.base() = new n_zero_t; 
	return; 
      }

    // case 1 * k or a * k
    if (this_type == node_t::one || this_type == node_t::constant)
      { 
	ret.base() = new n_lweight_t
	  (op_convert(SELECT(Tw), SELECT(W), w), ret.base()); 
	return; 
      }

    // case k' E * k
    if (this_type == node_t::lweight)
      {
	n_lweight_t* p
	  = dynamic_cast<n_lweight_t*>(ret.base());
	type child_type = p->child_->what();

	// case k'1 *k -> k'k 1 and k'a k -> k'k a
	if (child_type == node_t::one || child_type == node_t::constant)
	  { 
	    op_in_mul
	      (s.weights(), p->weight_, op_convert(SELECT(Tw), SELECT(W), w)); 
	    return; 
	  }
      }
    else if (this_type == node_t::rweight)
      {
	op_in_mul(s.weights(),
		  dynamic_cast<n_rweight_t* >(ret.base())
		  ->weight_, op_convert(SELECT(Tw), SELECT(W), w));
	return;
      }

    // general case
    ret.base() = 
      new n_rweight_t(op_convert(SELECT(Tw), SELECT(W), w), ret.base()); 
    return; 
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTw>
  inline
  rat::exp<Tm, Tw> op_mul(const Series<W, M>& s,
			  const W& weights,
			  const rat::exp<Tm, Tw>& a,
			  const oTw& w)
  { 
    rat::exp<Tm, Tw> ret(a);
    op_in_mul(s, weights, ret, w);
    return ret;
  }

  template<typename W, typename M, typename oTw, typename Tm, typename Tw>
  inline
  rat::exp<Tm, Tw> op_mul(const W&,
			  const Series<W, M>& s,
			  const oTw& w,
			  const rat::exp<Tm, Tw>& b)
  { 
    // assert(s.weights() == weights);

    typedef rat::Node<Tm, Tw>				node_t;
    typedef typename rat::Node<Tm, Tw>::type		type;
    typedef rat::One<Tm, Tw>				n_one_t;
    typedef rat::Constant<Tm, Tw>			n_const_t;
    typedef rat::Zero<Tm, Tw>				n_zero_t;
    typedef rat::Star<Tm, Tw>				n_star_t;
    typedef rat::LeftWeighted<Tm, Tw>			n_lweight_t;
    typedef rat::RightWeighted<Tm, Tw>		n_rweight_t;
    typedef rat::Sum<Tm, Tw>				n_sum_t;
    typedef rat::Product<Tm, Tw>			n_prod_t;

    rat::exp<Tm, Tw> ret(b);

    type this_type = ret.base()->what();

    // case k * 0
    if (this_type == node_t::zero)
      return ret;

    // case 0 * E
    if (w == zero_value(SELECT(W), SELECT(oTw)))
      { return rat::exp<Tm, Tw>::zero(); }

    // case 1 * E
    if (w == identity_value(SELECT(W), SELECT(oTw)))
      return ret;

    // case k * k' E -> [k k'] E
    if (this_type == node_t::lweight)
      {
	n_lweight_t* p
	  = dynamic_cast<n_lweight_t*>(ret.base());
	p->weight_ = op_mul
	  (s.weights(), op_convert(SELECT(Tw), SELECT(W), w), p->weight_);
	return ret;
      }

    // case k * E k' -> (k E) k'
    if (this_type == node_t::rweight)
      {
	n_rweight_t* p
	  = dynamic_cast<n_rweight_t*>(ret.base());
	p->child_ = 
	  new n_lweight_t(op_convert(SELECT(Tw), SELECT(W), w), p->child_);
	return ret;
      }

    // general case
    ret.base() = new n_lweight_t(w, ret.base());
    return ret; 

  }

#define FIXME(Msg) std::cerr << "FIXME: " << Msg << std::endl;

  template<typename W, typename M, typename Tm, typename Tw, typename oTm>
  inline
  Tw op_series_get(const Series<W, M>& s, 
		   const rat::exp<Tm, Tw>& p,
		   const oTm& m)
  { 
    // FIXME : doing a get on a krat could be implemented by computed 
    //         a thompson/glushkov automaton and compute resulting series 
    //         of m.
    FIXME("not implemented yet.");
    return zero_value(SELECT(W), SELECT(Tw));
  }

  template<typename W, typename M, typename Tm, typename Tw, typename oTm, typename oTw>
  inline
  void op_series_set(const Series<W, M>& s, 
		     const rat::exp<Tm, Tw>& p,
		     const oTm& m,
		     const oTw& w)
  { 
    // FIXME : doing a get on a krat could be implemented by computed 
    //         a thompson/glushkov automaton and compute resulting series 
    //         of m.
    FIXME("not implemented yet.");
  }

  /*----------------------------------------------------------.
    | MetaElement<SeriesBase<Series<W, M> >, rat::exp<Tm, Tw> > |
    `----------------------------------------------------------*/
      
  template <typename W, typename M, typename Tm, typename Tw>
  inline
  void 
  MetaElement<Series<W, M>, rat::exp<Tm, Tw> >::accept
  (const rat::ConstNodeVisitor<Tm, Tw>& v) const
  {
    value().accept(v);
  }
    
  template <typename W, typename M, typename Tm, typename Tw>
  inline
  size_t 
  MetaElement<Series<W, M>, rat::exp<Tm, Tw> >::depth() const
  {
    return value().depth();
  }

  template <class W, class M, class Tm, class Tw>
  Element<Series<W,M>, rat::exp<Tm,Tw> > 
  op_choose(const Series<W,M>& s, 
	    SELECTOR2(rat::exp<Tm,Tw>))
  {
    Element<Series<W,M>, rat::exp<Tm, Tw> > e(s);
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
	      Element<Series<W,M>, rat::exp<Tm,Tw> > ep = 
		s.monoid().choose(SELECT(Tm));
	      ep = ep * s.weights().choose(SELECT(Tw));
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
	      Element<Series<W,M>, rat::exp<Tm,Tw> > ep = 
		s.monoid().choose(SELECT(Tm));
	      ep = ep * s.weights().choose(SELECT(Tw));
	      unsigned t = RAND___(2);
	      if (t < 1)
		e = e * ep;
	      else
		e = ep * e;
	      continue;
	    }
	  }
      }
    return Element<Series<W,M>, rat::exp<Tm,Tw> >(s, e);
  }

} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_HXX

