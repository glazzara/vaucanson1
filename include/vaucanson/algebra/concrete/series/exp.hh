// exp.hh
//
//
// $Id$
// VCSN_HEADER

#ifndef RAT_EXP_HH
# define RAT_EXP_HH

// # include <vaucanson/algebra/concept/.hh>
// # include <vaucanson/algebra/transpose.hh>

# include <algorithm>
# include <iostream>

# include <vaucanson/algebra/concrete/series/nodes.hh>
# include <vaucanson/algebra/concrete/series/depth_visitor.hh>
# include <vaucanson/algebra/concrete/series/dump_visitor.hh>
# include <vaucanson/fundamental/element.hh>


namespace vcsn {

  namespace rat {

    template<typename LetterT, typename WeightT>
    class exp
    {
    protected:
      typedef rat::Node<LetterT, WeightT>		node_t;
      typedef rat::Node<LetterT, WeightT>::type		type;
      typedef rat::Zero<LetterT, WeightT>		n_zero_t;
      typedef rat::One<LetterT, WeightT>		n_one_t;
      typedef rat::Sum<LetterT, WeightT>		n_sum_t;
      typedef rat::Product<LetterT, WeightT>		n_prod_t;
      typedef rat::Star<LetterT, WeightT>		n_star_t;
      typedef rat::Constant<LetterT, WeightT>		n_const_t;

    public:
      typedef LetterT letter_t;
      typedef WeightT weight_t;

      exp()
	: base_(new n_zero_t)
      {}
      
      exp(node_t* p)
	: base_(p)
      {}


      exp(const exp& other)
	: base_(other.base_->clone())
      {}

      exp& operator=(const exp& other)
      {
	if (other.base_ != base_)
	  {
	    delete base_;
	    base_ = other.base_->clone();
	  }
	return *this;
      }

      exp& swap(exp& otether)
      {
	std::swap(base_, other.base_);
	return *this;
      }
      
      exp& operator+=(const exp& other)
      {
	base_ = new n_sum_t(base_, other.base_->clone());
	return *this;
      }

      exp& operator*=(const exp& other)
      {
	base_ = new n_prod_t(base_, other.base_->clone());
	return *this;
      }

      exp& star()
      {
	base_ = new n_star_t(base_);
	return *this;
      }

      void accept(ConstNodeVisitor<letter_t, weight_t>& v) const
      {
	base_->accept(v);
      }

      size_t depth() const
      {
	DepthVisitor<letter_t, weight_t> v;
	accept(v);
	return v.get();
      }

      ~exp()
      {
	delete base_;
      }

      node_t* &base() { return base_; }
      node_t* const &base() const { return base_; }

      bool operator==(const exp& other) const
      {
	return !(*base_ != *other.base_);
      }

      bool operator!=(const exp& other) const
      {
	return *base_ != *other.base_;
      }

      bool operator<(const exp& other) const
      {
	return *base_ < *other.base_;
      }

      exp clone() const
      {
	return exp(base_->clone());
      }

      static exp one()
      {
	return exp(new n_one_t);
      }

      static exp zero()
      {
	return exp(new n_zero_t);
      }

      static exp constant(const letter_t& l)
      {
	return exp(new n_const_t(l));
      }

      // compatibility
      static bool stareable() 
      {
	return true;
      }

    protected:
      node_t *base_;
    };

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

  } // algebra

  using namespace rat;

  #define FIXME(Msg) std::cerr << "FIXME: " << Msg << std::endl;
  
  template <class Tm, class Tw>
  bool operator==(const exp<Tm, Tw>& lhs, const exp<Tm, Tw>& rhs)
  { FIXME("not implemented yet."); return true; }

  template <class Tm, class Tw>
  bool operator!=(const exp<Tm, Tw>& lhs, const exp<Tm, Tw>& rhs) 
  { FIXME("not implemented yet."); return true; }

  template <class Tm, class Tw>
  bool operator<(const exp<Tm, Tw>& lhs, const exp<Tm, Tw>& rhs)
  { FIXME("not implemented yet."); return true; }

  template <class Tm, class Tw>
  bool operator>(const exp<Tm, Tw>& lhs, const exp<Tm, Tw>& rhs)
  { FIXME("not implemented yet."); return true; }

  template <class Tm, class Tw>
  bool operator<=(const exp<Tm, Tw>& lhs, const exp<Tm, Tw>& rhs)
  { FIXME("not implemented yet."); return true; }

  template <class Tm, class Tw>
  bool operator>=(const exp<Tm, Tw>& lhs, const exp<Tm, Tw>& rhs)
  { FIXME("not implemented yet."); return true; }


} // vcsn

namespace vcsn {

  template <class Monoid_, class Semiring_>
  class ReverseVisitor : 
    public rat::DefaultMutableNodeVisitor<Monoid_, Semiring_>
  {
  public:
    virtual void product( rat::Node<Monoid_, Semiring_>* lhs,  rat::Node<Monoid_, Semiring_>* rhs)
    {
      lhs->accept(*this);
      rhs->accept(*this);
      std::swap(lhs, rhs);
    }    
  };

//   template <typename M, typename W>
//   struct DefaultTransposeFun<rat::exp<M, W> >
//   {
//     rat::exp<M, W>&
//     operator()(const rat::exp<M, W>& exp)
//     {
//       rat::exp<M, W>*  rexp = new rat::exp<M, W>(exp);
      
//       ReverseVisitor<M,W>  rv;
//       rexp.accept(*this);
//       return *rexp;
//     }
//   };

} // vcsn

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

#endif


