// nodes.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_NODES_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_NODES_HXX

# include <vaucanson/algebra/implementation/series/rat/nodes.hh>

namespace vcsn {

  namespace rat {

    template<class M_, class W_>
    void
    DefaultMutableNodeVisitor<M_,W_>::product(Node<M_, W_>* lhs,
					      Node<M_, W_>* rhs)
    {
      lhs->accept(*this);
      rhs->accept(*this);
    }

    template<class M_, class W_>
    void DefaultMutableNodeVisitor<M_,W_>::sum(Node<M_, W_>* lhs,
					       Node<M_, W_>* rhs)
    {
      lhs->accept(*this);
      rhs->accept(*this);
    }

    template<class M_, class W_>
    void DefaultMutableNodeVisitor<M_,W_>::star(Node<M_, W_>* n)
    {
      n->accept(*this);
    }

    template<class M_, class W_>
    void DefaultMutableNodeVisitor<M_,W_>::left_weight(W_&,
						       Node<M_, W_>* n)
    {
      n->accept(*this);
    }

    template<class M_, class W_>
    void DefaultMutableNodeVisitor<M_,W_>::right_weight(W_&,
							Node<M_, W_>*n)
    {
      n->accept(*this);
    }

    template<class M_, class W_>
    void DefaultMutableNodeVisitor<M_,W_>::constant( M_&)
    {}

    template<class M_, class W_>
    void DefaultMutableNodeVisitor<M_,W_>::zero()
    {}

    template<class M_, class W_>
    void DefaultMutableNodeVisitor<M_,W_>::one()
    {}

    /*-----.
    | Node |
    `-----*/

    // Defined methods
    template<typename M_, typename W_>
    Node<M_,W_>::~Node()
    {
      delete constant_term_;
    }

    template<typename M_, typename W_>
    W_* &		Node<M_,W_>::c()
    {
      return constant_term_;
    }

    template<typename M_, typename W_>  W_ const * &
    Node<M_,W_>::c() const
    {
      return constant_term_;
    }

    template<typename M_, typename W_>
    Node<M_,W_>::Node()
      : constant_term_(0)
    {}

    /*-----.
    | Zero |
    `-----*/
    template <class M_, class W_>
    Zero<M_,W_>::Zero()
    {}

    template <class M_, class W_>
    typename Node<M_, W_>::type
    Zero<M_,W_>::what() const
    {
      return Node<M_, W_>::zero;
    }

    template <class M_, class W_>
    Node<M_, W_>*
    Zero<M_,W_>::clone() const
    {
      Node<M_, W_>* p = new Zero<M_, W_>;
      if (this->constant_term_)
	p->constant_term_ = new W_ (*(this->constant_term_));
      return p;
    }

    template <class M_, class W_>
    void
    Zero<M_,W_>::accept(ConstNodeVisitor<M_, W_>& v) const
    {
      v.zero();
    }

    template <class M_, class W_>
    bool
    Zero<M_,W_>::operator!=(const Node<M_, W_>& other) const
    {
      return (dynamic_cast<const Zero<M_, W_>*>(&other) == 0);
    }

    template <class M_, class W_>
    bool
    Zero<M_,W_>::operator<(const Node<M_, W_>& other) const
    {
      return what() < other.what();
    }

    template <class M_, class W_>

    Zero<M_,W_>::~Zero()
    {}

    /*----.
    | One |
    `----*/

    template<typename M_, typename W_>
    One<M_,W_>::One()
    {}

    template<typename M_, typename W_>
    typename Node<M_, W_>::type
    One<M_,W_>::what() const
    {
      return Node<M_, W_>::one;
    }

    template<typename M_, typename W_>
    Node<M_, W_>*
    One<M_,W_>::clone() const
    {
      Node<M_, W_>* p = new One<M_, W_>;
      if (this->constant_term_)
	p->constant_term_ = new W_ (*(this->constant_term_));
      return p;
    }

    template<typename M_, typename W_>
    void
    One<M_,W_>::accept(ConstNodeVisitor<M_, W_>& v) const
    {
      v.one();
    }

    template<typename M_, typename W_>
    bool
    One<M_,W_>::operator!=(const Node<M_, W_>& other) const
    {
      return (dynamic_cast<const One<M_, W_>*>(&other) == 0);
    }

    template<typename M_, typename W_>
    bool
    One<M_,W_>::operator<(const Node<M_, W_>& other) const
    {
      return what() < other.what();
    }

    template<typename M_, typename W_>

    One<M_,W_>::~One()
    {}

    /*---------.
    | Constant |
    `---------*/

    template<typename M_, typename W_>
    Constant<M_,W_>::Constant(const M_ &v) : value_(v)
    {}

    template<typename M_, typename W_>
    typename Node<M_, W_>::type
    Constant<M_,W_>::what() const
    {
      return Node<M_, W_>::constant;
    }

    template<typename M_, typename W_>
    Node<M_, W_>*
    Constant<M_,W_>::clone() const
    {
      Node<M_, W_>* p = new Constant<M_, W_>(value_);
      if (this->constant_term_)
	p->constant_term_ = new W_ (*(this->constant_term_));
      return p;
    }

    template<typename M_, typename W_>
    void
    Constant<M_,W_>::accept(ConstNodeVisitor<M_, W_>& v) const
    {
      v.constant(value_);
    }

    template<typename M_, typename W_>
    bool
    Constant<M_,W_>::operator!=(const Node<M_, W_>& other) const
    {
      const Constant<M_, W_>* otherp =
	dynamic_cast<const Constant<M_, W_>*>(&other);
      if(!otherp)
	return true;
      return (value_ != otherp->value_);
    }

    template<typename M_, typename W_>
    bool
    Constant<M_,W_>::operator<(const Node<M_, W_>& other) const
    {
      const Constant<M_, W_>* otherp =
	dynamic_cast<const Constant<M_, W_>*>(&other);
      if (otherp)
	return value_ < otherp->value_;
      else
	return what() < other.what();
    }

    template<typename M_, typename W_>

    Constant<M_,W_>::~Constant()
    {};

    /*-------------.
    | LeftWeighted |
    `-------------*/
    template<typename M_, typename W_>
    LeftWeighted<M_,W_>::LeftWeighted(const W_& w, const Node<M_, W_>& c)
      : weight_(w), child_(c.clone())
    {}

    template<typename M_, typename W_>
    LeftWeighted<M_,W_>::LeftWeighted(const W_& w, Node<M_, W_>* c)
      : weight_(w), child_(c)
    {}

    template<typename M_, typename W_>
    LeftWeighted<M_,W_>::LeftWeighted(const W_& w)
      : weight_(w),
	child_(new One<M_, W_>)
    {}

    template<typename M_, typename W_>
    typename Node<M_, W_>::type
    LeftWeighted<M_,W_>::what() const
    {
      return Node<M_, W_>::lweight;
    }

    template<typename M_, typename W_>
    Node<M_, W_>*
    LeftWeighted<M_,W_>::clone() const
    {
      Node<M_, W_>* p = new LeftWeighted<M_, W_>(weight_, *child_);
      if (this->constant_term_)
	p->constant_term_ = new W_ (*(this->constant_term_));
      return p;
    }

    template<typename M_, typename W_>
    void
    LeftWeighted<M_,W_>::accept(ConstNodeVisitor<M_, W_>& v) const
    {
      v.left_weight(weight_, child_);
    }

    template<typename M_, typename W_>
    bool
    LeftWeighted<M_,W_>::operator!=(const Node<M_, W_>& other) const
    {
      const LeftWeighted<M_, W_>* otherp =
	dynamic_cast<const LeftWeighted<M_, W_>*>(&other);
      if(!otherp || (weight_ != otherp->weight_))
	return true;
      return (*child_ != *otherp->child_);
    }

    template<typename M_, typename W_>
    bool
    LeftWeighted<M_,W_>::operator<(const Node<M_, W_>& other) const
    {
      const LeftWeighted<M_, W_>* otherp =
	dynamic_cast<const LeftWeighted<M_, W_>*>(&other);
      if (otherp)
      {
	if (weight_ == otherp->weight_)
	  return *child_ < *otherp->child_;
	else
	  return weight_ < otherp->weight_;
      }
      else
	return what() < other.what();
    }

    template<typename M_, typename W_>

    LeftWeighted<M_,W_>::~LeftWeighted()
    {
      delete child_;
    }

    /*--------------.
    | RightWeighted |
    `--------------*/
    template<typename M_, typename W_>
    RightWeighted<M_,W_>::RightWeighted(const W_& w, const Node<M_, W_>& c)
      : weight_(w), child_(c.clone())
    {}

    template<typename M_, typename W_>
    RightWeighted<M_,W_>::RightWeighted(const W_& w, Node<M_, W_>* c)
      : weight_(w), child_(c)
    {}

    template<typename M_, typename W_>
    RightWeighted<M_,W_>::RightWeighted(const W_& w)
      : weight_(w),
	child_(new One<M_, W_>)
    {}

    template<typename M_, typename W_>
    typename Node<M_, W_>::type
    RightWeighted<M_,W_>::what() const
    {
      return Node<M_, W_>::rweight;
    }

    template<typename M_, typename W_>
    Node<M_, W_>*
    RightWeighted<M_,W_>::clone() const
    {
      Node<M_, W_>* p = new RightWeighted<M_, W_>(weight_, *child_);
      if (this->constant_term_)
	p->constant_term_ = new W_(*(this->constant_term_));
      return p;
    }

    template<typename M_, typename W_>
    void
    RightWeighted<M_,W_>::accept(ConstNodeVisitor<M_, W_>& v) const
    {
      v.right_weight(weight_, child_);
    }

    template<typename M_, typename W_>
    bool
    RightWeighted<M_,W_>::operator!=(const Node<M_, W_>& other) const
    {
      const RightWeighted<M_, W_>* otherp =
	dynamic_cast<const RightWeighted<M_, W_>*>(&other);
      if(!otherp || (weight_ != otherp->weight_))
	return true;
      return (*child_ != *otherp->child_);
    }

    template<typename M_, typename W_>
    bool
    RightWeighted<M_,W_>::operator<(const Node<M_, W_>& other) const
    {
      const RightWeighted<M_, W_>* otherp =
	dynamic_cast<const RightWeighted<M_, W_>*>(&other);
      if (otherp)
      {
	if (weight_ == otherp->weight_)
	  return *child_ < *otherp->child_;
	else
	  return weight_ < otherp->weight_;
      }
      else
	return what() < other.what();
    }

    template<typename M_, typename W_>

    RightWeighted<M_,W_>::~RightWeighted()
    {
      delete child_;
    }

    /*-----.
    | Star |
    `-----*/
    template <class M_,class W_>
    Star<M_,W_>::Star(const Node<M_, W_>& other)
      : child_(other.clone())
    {}

    template <class M_,class W_>
    Star<M_,W_>::Star(Node<M_, W_>* other)
      : child_(other)
    {}

    template <class M_,class W_>
    typename Node<M_, W_>::type
    Star<M_,W_>::what() const
    {
      return Node<M_, W_>::star;
    }

    template <class M_,class W_>
    Node<M_, W_>*
    Star<M_,W_>::clone() const
    {
      Node<M_, W_>* p = new Star<M_, W_>(*child_);
      if (this->constant_term_)
	p->constant_term_ = new W_(*(this->constant_term_));
      return p;
    }

    template <class M_,class W_>
    void
    Star<M_,W_>::accept(ConstNodeVisitor<M_, W_>& v) const
    {
      v.star(child_);
    }

    template <class M_,class W_>
    bool
    Star<M_,W_>::operator!=(const Node<M_, W_>& other) const
    {
      const Star<M_, W_>* otherp =
	dynamic_cast<const Star<M_, W_>*>(&other);
      if(!otherp)
	return true;
      return (*child_ != *otherp->child_);
    }

    template <class M_,class W_>
    bool
    Star<M_,W_>::operator<(const Node<M_, W_>& other) const
    {
      const Star<M_, W_>* otherp =
	dynamic_cast<const Star<M_, W_>*>(&other);
      if (otherp)
      	return *child_ < *otherp->child_;
      else
	return what() < other.what();
    }

    template <class M_,class W_>

    Star<M_,W_>::~Star()
    {
      delete child_;
    }

    /*--------.
    | Product |
    `--------*/
    template <class M_,class W_>
    Product<M_,W_>::Product(const Node<M_, W_>& left,
			    const Node<M_, W_>& right)
      : left_(left.clone()), right_(right.clone())
    {}

    template <class M_,class W_>
    Product<M_,W_>::Product(Node<M_, W_>* left, Node<M_, W_>* right)
      : left_(left), right_(right)
    {}

    template <class M_,class W_>
    typename Node<M_, W_>::type
    Product<M_,W_>::what() const
    {
      return Node<M_, W_>::prod;
    }

    template <class M_,class W_>
    Node<M_, W_>*
    Product<M_,W_>::clone() const
    {
      Node<M_, W_>* p = new Product<M_, W_>(*left_, *right_);
      if (this->constant_term_)
	p->constant_term_ = new W_(*(this->constant_term_));
      return p;
    }

    template <class M_,class W_>
    void
    Product<M_,W_>::accept(ConstNodeVisitor<M_, W_>& v) const
    {
      return v.product(left_, right_);
    }

    template <class M_,class W_>
    bool
    Product<M_,W_>::operator!=(const Node<M_, W_>& other) const
    {
      const Product<M_, W_>* otherp =
	dynamic_cast<const Product<M_, W_>*>(&other);
      if(!otherp || (*left_ != *otherp->left_))
	return true;
      return (*right_ != *otherp->right_);
    }

    template <class M_,class W_>
    bool
    Product<M_,W_>::operator<(const Node<M_, W_>& other) const
    {
      const Product<M_, W_>* otherp =
	dynamic_cast<const Product<M_, W_>*>(&other);
      if (otherp)
      {
	if (*left_ != *otherp->left_)
	  return *left_ < *otherp->left_;
	else
	  return *right_ < *otherp->right_;
      }
      else
	return what() < other.what();
    }

    template <class M_,class W_>

    Product<M_,W_>::~Product()
    {
      delete right_;
      delete left_;
    }

    /*----.
    | Sum |
    `----*/
    template<typename M_, typename W_>
    Sum<M_,W_>::Sum(const Node<M_, W_>& left, const Node<M_, W_>& right)
      : left_(left.clone()), right_(right.clone())
    {}

    template<typename M_, typename W_>
    Sum<M_,W_>::Sum(Node<M_, W_>* left, Node<M_, W_>* right)
      : left_(left), right_(right)
    {}

    template<typename M_, typename W_>
    void
    Sum<M_,W_>::accept(ConstNodeVisitor<M_, W_>& v) const
    {
      return v.sum(left_, right_);
    }

    template<typename M_, typename W_>
    typename Node<M_, W_>::type
    Sum<M_,W_>::what() const
    {
      return Node<M_, W_>::sum;
    }

    template<typename M_, typename W_>
    Node<M_, W_>*
    Sum<M_,W_>::clone() const
    {
      Node<M_, W_>* p = new Sum<M_, W_>(*left_, *right_);
      if (this->constant_term_)
	p->constant_term_ = new W_(*(this->constant_term_));
      return p;
    }

    template<typename M_, typename W_>
    bool
    Sum<M_,W_>::operator!=(const Node<M_, W_>& other) const
    {
      const Sum<M_, W_>* otherp =
	dynamic_cast<const Sum<M_, W_>*>(&other);
      if(!otherp)
	return true;
      // X + Y and Y + X are NOT equal
      // Indeed : if   b + X < a + c   and   a + c = c + a
      // then   b + X > a + c   !
      return (*left_ != *otherp->left_) || (*right_ != *otherp->right_);
    }

    template<typename M_, typename W_>
    bool
    Sum<M_,W_>::operator<(const Node<M_, W_>& other) const
    {
      const Sum<M_, W_>* otherp =
	dynamic_cast<const Sum<M_, W_>*>(&other);
      if (otherp)
      {
	if (*left_ != *otherp->left_)
	  return *left_ < *otherp->left_;
	else
	  return *right_ < *otherp->right_;
      }
      else
	return what() < other.what();
    }

    template<typename M_, typename W_>

    Sum<M_,W_>::~Sum()
    {
      delete right_;
      delete left_;
    }

  } // End of namespace rat.

} // End of namespace vcsn.

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_NODES_HXX
