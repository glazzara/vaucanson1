// exp.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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

#ifndef ALGEBRA_CONCRETE_SERIES_EXP_HXX
# define ALGEBRA_CONCRETE_SERIES_EXP_HXX

# include <algorithm>
# include <iostream>

# include <vaucanson/algebra/concrete/series/rat/exp.hh>
# include <vaucanson/algebra/concrete/series/transpose.hh>
# include <vaucanson/algebra/concrete/series/rat/nodes.hh>
# include <vaucanson/algebra/concrete/series/rat/depth_visitor.hh>
# include <vaucanson/fundamental/element.hh>

namespace vcsn {

  namespace rat {

    template<typename LetterT, typename WeightT>
    exp<LetterT, WeightT>::exp()
      : base_(new n_zero_t)
    {}
    
    template<typename LetterT, typename WeightT>
    exp<LetterT, WeightT>::exp(node_t* p)
      : base_(p)
    {}

    template<typename LetterT, typename WeightT>
    exp<LetterT, WeightT>::exp(const exp& other)
      : base_(other.base_->clone())
    {}
    
    template<typename LetterT, typename WeightT>
    exp<LetterT, WeightT>& 
    exp<LetterT, WeightT>::operator=(const exp& other)
    {
      if (other.base_ != base_)
	{
	  delete base_;
	  base_ = other.base_->clone();
	}
      return *this;
    }

    template<typename LetterT, typename WeightT>
    exp<LetterT, WeightT>& 
    exp<LetterT, WeightT>::swap(exp& otether)
    {
      std::swap(base_, other.base_);
      return *this;
    }

    template<typename LetterT, typename WeightT>  
    exp<LetterT, WeightT>& 
    exp<LetterT, WeightT>::operator+=(const exp& other)
    {
      base_ = new n_sum_t(base_, other.base_->clone());
      return *this;
    }

    template<typename LetterT, typename WeightT>
    exp<LetterT, WeightT>& 
    exp<LetterT, WeightT>::operator*=(const exp& other)
    {
      base_ = new n_prod_t(base_, other.base_->clone());
      return *this;
    }

    template<typename LetterT, typename WeightT>
    exp<LetterT, WeightT>& exp<LetterT, WeightT>::star()
    {
      base_ = new n_star_t(base_);
      return *this;
    }

    template<typename LetterT, typename WeightT>
    void exp<LetterT, WeightT>::accept(ConstNodeVisitor<letter_t, weight_t>& v) const
    {
      base_->accept(v);
    }

    template<typename LetterT, typename WeightT>
    size_t exp<LetterT, WeightT>::depth() const
    {
      DepthVisitor<letter_t, weight_t> v;
      accept(v);
      return v.get();
    }
    
    template<typename LetterT, typename WeightT>   exp<LetterT, WeightT>::~exp()
    {
      delete base_;
    }
    
    template<typename LetterT, typename WeightT>
    typename exp<LetterT, WeightT>::node_t* &
    exp<LetterT, WeightT>::base() 
    { 
      return base_; 
    }

    template<typename LetterT, typename WeightT>
    typename exp<LetterT, WeightT>::node_t* const &
    exp<LetterT, WeightT>::base() const { return base_; }

    template<typename LetterT, typename WeightT>
    bool exp<LetterT, WeightT>::operator==(const exp& other) const
    {
      return !(*base_ != *other.base_);
    }

    template<typename LetterT, typename WeightT>
    bool exp<LetterT, WeightT>::operator!=(const exp& other) const
    {
      return *base_ != *other.base_;
    }

    template<typename LetterT, typename WeightT>
    bool exp<LetterT, WeightT>::operator<(const exp& other) const
    {
      return *base_ < *other.base_;
    }

    template<typename LetterT, typename WeightT>
    exp<LetterT, WeightT>
    exp<LetterT, WeightT>::clone() const
    {
      return exp(base_->clone());
    }

    template<typename LetterT, typename WeightT>
    exp<LetterT, WeightT>
    exp<LetterT, WeightT>::one()
    {
      return exp(new n_one_t);
    }
    
    template<typename LetterT, typename WeightT>
    exp<LetterT, WeightT> exp<LetterT, WeightT>::zero()
    {
      return exp(new n_zero_t);
    }

    template<typename LetterT, typename WeightT>
    exp<LetterT, WeightT> exp<LetterT, WeightT>::constant(const letter_t& l)
    {
      return exp(new n_const_t(l));
    }
    
    // compatibility
    template<typename LetterT, typename WeightT>
    bool exp<LetterT, WeightT>::stareable() 
    {
      return true;
    }

    template<typename M, typename W>
    exp<M, W> operator*(const exp<M, W>& lhs,
			const exp<M, W>& rhs)
    {
      exp<M, W> ret(lhs);
      ret *= rhs;
      return ret;
    }

    template<typename M, typename W>
    exp<M, W> operator+(const exp<M, W>& lhs,
			const exp<M, W>& rhs)
    {
      exp<M, W> ret(lhs);
      ret += rhs;
      return ret;
    }

    template<typename M, typename W>
    exp<M, W> operator*(const W& lhs,
			const exp<M, W>& rhs)
    {
      exp<M, W> ret(rhs);
      ret.base() = new LeftWeighted<M, W>(lhs, ret.base());
      return ret;
    }

    template<typename M, typename W>
    exp<M, W> operator*(const exp<M, W>& lhs,
			const W& rhs)
    {
      exp<M, W> ret(lhs);
      ret.base() = new RightWeighted<M, W>(rhs, ret.base());
      return ret;
    }

    // FIXME: this is an evil hack, but without it there is an ambiguity
    // in calls to exp * number or num * exp

    template<typename M, typename S, typename T>
    exp<M, Element<S, T> > 
    operator*(const Element<S, T>& lhs,
	      const exp<M, Element<S, T> >& rhs)
    {
      exp<M, Element<S, T> > ret(rhs);
      ret.base() 
	= new LeftWeighted<M, Element<S, T> >(lhs, ret.base());
      return ret;
    }

    template<typename M, typename S, typename T>
    exp<M, Element<S, T> > 
    operator*(const exp<M, Element<S, T> >& lhs,
	      const Element<S, T>& rhs)
    {
      exp<M, Element<S, T> > ret(lhs);
      ret.base() 
	= new RightWeighted<M, Element<S, T> >(rhs, ret.base());
      return ret;
    }

  } // rat

} // vcsn

namespace vcsn {

  template <class Monoid_, class Semiring_>
  void 
  ReverseVisitor<Monoid_,Semiring_>::
  product(rat::Node<Monoid_, Semiring_>* lhs,  
	  rat::Node<Monoid_, Semiring_>* rhs)
  {
    lhs->accept(*this);
    rhs->accept(*this);
    std::swap(lhs, rhs);
  }


  template <typename S, typename M, typename W>
  rat::exp<M, W>&
  DefaultTransposeFun<S, rat::exp<M,W> >::
  operator()(const S&, const rat::exp<M, W>& exp)
  {
    rat::exp<M, W>*  rexp = new rat::exp<M, W>(exp);
    
    ReverseVisitor<M,W>  rv;
    rexp.accept(*this);
    return *rexp;
  }

} // vcsn


#include <vaucanson/algebra/concrete/series/rat/dump_visitor.hh>

namespace std
{
  template<typename M_, typename W_>
  std::ostream& operator<<(std::ostream& o, const vcsn::rat::exp<M_, W_>& exp)
  { 
    vcsn::rat::DumpVisitor<M_, W_> v(o);
    exp.accept(v);
    return o;
  }
  
  template<typename M, typename W>
  void swap(vcsn::rat::exp<M, W>& lhs, 
	    vcsn::rat::exp<M, W>& rhs)
  {
    lhs.swap(rhs);
  }

}

#endif // ALGEBRA_CONCRETE_SERIES_EXP_HXX


