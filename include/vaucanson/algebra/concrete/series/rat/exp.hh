// exp.hh
//
// $Id$
// VCSN_HEADER
#ifndef ALGEBRA_CONCRETE_SERIES_EXP_HH
# define ALGEBRA_CONCRETE_SERIES_EXP_HH

# include <algorithm>
# include <iostream>

# include <vaucanson/algebra/concept/algebra_base.hh>
# include <vaucanson/algebra/transpose.hh>
# include <vaucanson/algebra/concrete/series/rat/nodes.hh>
# include <vaucanson/algebra/concrete/series/rat/depth_visitor.hh>
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

      exp();
      exp(node_t* p);
      exp(const exp& other);
      exp& operator=(const exp& other);
      exp& swap(exp& otether);
      exp& operator+=(const exp& other);
      exp& operator*=(const exp& other);
      exp& star();
      void accept(ConstNodeVisitor<letter_t, weight_t>& v) const;
      size_t depth() const;
      ~exp();
      node_t* &base();
      node_t* const &base() const;
      bool operator==(const exp& other) const;
      bool operator!=(const exp& other) const;
      bool operator<(const exp& other) const;
      exp clone() const;
      static exp one();
      static exp zero();
      static exp constant(const letter_t& l);
      // compatibility
      static bool stareable();

    protected:
      node_t *base_;
    };

    template<typename M, typename W>
    exp<M, W> operator*(const exp<M, W>& lhs,
			const exp<M, W>& rhs);

    template<typename M, typename W>
    exp<M, W> operator+(const exp<M, W>& lhs,
			const exp<M, W>& rhs);

    template<typename M, typename W>
    exp<M, W> operator*(const W& lhs,
			const exp<M, W>& rhs);

    template<typename M, typename W>
    exp<M, W> operator*(const exp<M, W>& lhs,
			const W& rhs);

    // FIXME: this is an evil hack, but without it there is an ambiguity
    // in calls to exp * number or num * exp
    // FIXME: high level fixme !

    template<typename M, typename S, typename T>
    exp<M, Element<S, T> > 
    operator*(const Element<S, T>& lhs,
	      const exp<M, Element<S, T> >& rhs);

    template<typename M, typename S, typename T>
    exp<M, Element<S, T> > 
    operator*(const exp<M, Element<S, T> >& lhs,
	      const Element<S, T>& rhs);

  } // rat

} // vcsn


namespace vcsn {

  template <class Monoid_, class Semiring_>
  class ReverseVisitor : 
    public rat::DefaultMutableNodeVisitor<Monoid_, Semiring_>
  {
  public:
    virtual void 
    product(rat::Node<Monoid_, Semiring_>* lhs,  
	    rat::Node<Monoid_, Semiring_>* rhs);
  };

  template <typename M, typename W>
  struct DefaultTransposeFun<rat::exp<M, W> >
  {
    rat::exp<M, W>&
    operator()(const rat::exp<M, W>& exp);
  };

} // vcsn


#include <vaucanson/rat/dump_visitor.hh>

namespace std
{
  template<typename M_, typename W_>
  std::ostream& operator<<(std::ostream& o, const vcsn::rat::exp<M_, W_>& exp);
  
  template<typename M, typename W>
  void swap(vcsn::rat::exp<M, W>& lhs, 
	    vcsn::rat::exp<M, W>& rhs);

} // std

# include <vaucanson/algebra/series/concrete/rat/exp.hxx>

#endif // ALGEBRA_CONCRETE_SERIES_EXP_HH


