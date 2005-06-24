// partial_rat_exp.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_HXX
# define VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_HXX

# include <vaucanson/algorithms/internal/partial_rat_exp.hh>

namespace vcsn
{
  /*-----------------.
  | PartialExp class |
  `-----------------*/

  template <typename Series, typename T>
  PartialExp<Series, T>::PartialExp(const exp_t &e):
    rat_exp_(&e),
    semiring_elt_list_(),
    node_list_()
  {
    semiring_elt_list_.push_back(rat_exp_->structure().semiring().identity(
      SELECT(typename semiring_elt_t::value_t)));
  }

  template <typename Series, typename T>
  PartialExp<Series, T>::PartialExp(const PartialExp &other):
    rat_exp_(other.rat_exp_),
    semiring_elt_list_(other.semiring_elt_list_),
    node_list_(other.node_list_)
  { }

  template <typename Series, typename T>
  PartialExp<Series, T>::PartialExp(const exp_t &e, const semiring_elt_t& w):
    rat_exp_(&e),
    semiring_elt_list_(),
    node_list_()
  {
    semiring_elt_list_.push_back(w);
  }

  template <typename Series, typename T>
  PartialExp<Series, T>&
  PartialExp<Series, T>::insert(const node_t *v)
  {
    node_list_.push_back(v);
    semiring_elt_list_.push_back(rat_exp_->structure().semiring().identity(
      SELECT(typename semiring_elt_t::value_t)));
    return *this;
  }

  template <typename Series, typename T>
  typename PartialExp<Series, T>::semiring_elt_list_t&
  PartialExp<Series, T>::weights()
  {
    return semiring_elt_list_;
  }

  template <typename Series, typename T>
  const typename PartialExp<Series, T>::semiring_elt_list_t&
  PartialExp<Series, T>::weights() const
  {
    return semiring_elt_list_;
  }

  template <typename Series, typename T>
  const typename PartialExp<Series, T>::node_list_t&
  PartialExp<Series, T>::nodes() const
  {
    return node_list_;
  }

  template <typename Series, typename T>
  typename PartialExp<Series, T>::node_list_t&
  PartialExp<Series, T>::nodes()
  {
    return node_list_;
  }

  template <typename Series, typename T>
  PartialExp<Series, T>&
  PartialExp<Series, T>::operator<<=(const semiring_elt_t& w)
  {
    semiring_elt_list_.back() *= w;
    return *this;
  }

  template <typename Series, typename T>
  PartialExp<Series, T>&
  PartialExp<Series, T>::operator>>=(const semiring_elt_t& w)
  {
    semiring_elt_list_.front() = w * semiring_elt_list_.front();
    return *this;
  }

  template <typename Series, typename T>
  const Series&
  PartialExp<Series, T>::exp_structure() const
  {
    return rat_exp_->structure();
  }

  template <typename Series, typename T>
  const T&
  PartialExp<Series, T>::exp_value() const
  {
    return rat_exp_->value();
  }

  template <typename Series, typename T>
  const typename PartialExp<Series, T>::exp_t&
  PartialExp<Series, T>::exp() const
  {
    return *rat_exp_;
  }

  /*--------------------.
  | PartialExp iterator |
  `--------------------*/

  template <typename Series, typename T>
  template <bool IsConst>
  PartialExp<Series, T>::internal_iterator<IsConst>::internal_iterator(
    const semiring_elts_iterator_t& sit, const nodes_iterator_t& nit ):
      semiring_elts_iterator_(sit),
      nodes_iterator_(nit),
      on_node_ (false)
  {}

  template <typename Series, typename T>
  template <bool IsConst>
  PartialExp<Series, T>::internal_iterator<IsConst>&
  PartialExp<Series, T>::internal_iterator<IsConst>::operator++()
  {
    if (on_node_)
      ++nodes_iterator_;
    else
      ++semiring_elts_iterator_;
    on_node_ = not on_node_;
    return *this;
  }

  template <typename Series, typename T>
  template <bool IsConst>
  PartialExp<Series, T>::internal_iterator<IsConst>
  PartialExp<Series, T>::internal_iterator<IsConst>::operator++(int)
  {
    internal_iterator old = *this;

    if (on_node_)
      ++nodes_iterator_;
    else
      ++semiring_elts_iterator_;
    on_node_ = not on_node_;
    return old;
  }

  template <typename Series, typename T>
  template <bool IsConst>
  typename PartialExp<Series, T>::template internal_iterator<IsConst>::
  semiring_elt_ref_t
  PartialExp<Series, T>::internal_iterator<IsConst>::semiring_elt() const
  {
    assertion(!on_node_);
    return *semiring_elts_iterator_;
  }

  template <typename Series, typename T>
  template <bool IsConst>
  typename PartialExp<Series, T>::template internal_iterator<IsConst>::
  node_ref_t
  PartialExp<Series, T>::internal_iterator<IsConst>::node() const
  {
    assertion(on_node_);
    return *nodes_iterator_;
  }

  template <typename Series, typename T>
  template <bool IsConst>
  bool
  PartialExp<Series, T>::internal_iterator<IsConst>::on_node() const
  {
    return on_node_;
  }

  template <typename Series, typename T>
  template <bool IsConst>
  bool
  PartialExp<Series, T>::internal_iterator<IsConst>::operator!=(const internal_iterator& other)
  {
    return nodes_iterator_ != other.nodes_iterator_ or
      semiring_elts_iterator_ != other.semiring_elts_iterator_;
  }

  template <typename Series, typename T>
  template <bool IsConst>
  bool
  PartialExp<Series, T>::internal_iterator<IsConst>::operator==(const internal_iterator& other)
  {
    return nodes_iterator_ == other.nodes_iterator_ and
      semiring_elts_iterator_ == other.semiring_elts_iterator_;
  }

  template <typename Series, typename T>
  typename PartialExp<Series, T>::iterator
  PartialExp<Series, T>::begin()
  {
    return iterator(semiring_elt_list_.begin(), node_list_.begin());
  }

  template <typename Series, typename T>
  typename PartialExp<Series, T>::const_iterator
  PartialExp<Series, T>::begin() const
  {
    return const_iterator(semiring_elt_list_.begin(), node_list_.begin());
  }

  template <typename Series, typename T>
  typename PartialExp<Series, T>::iterator
  PartialExp<Series, T>::end()
  {
    return iterator(semiring_elt_list_.end(), node_list_.end());
  }

  template <typename Series, typename T>
  typename PartialExp<Series, T>::const_iterator
  PartialExp<Series, T>::end() const
  {
    return const_iterator(semiring_elt_list_.end(), node_list_.end());
  }

  /*---------------------.
  | PartialExp functions |
  `---------------------*/

  template <typename S, typename T>
  std::ostream& operator<< (std::ostream& o, const PartialExp<S, T>& e)
  {
    typename PartialExp<S, T>::const_iterator i = e.begin();

    o << '[' << i.semiring_elt();

    for (i++; i != e.end(); ++i)
    {
      if (i.on_node())
	o << '|' << typename PartialExp<S, T>::series_set_elt_value_t(i.node());
      else
	o << '|' << i.semiring_elt();
    }
    return o << ']';
  }

  template <typename S, typename T, typename M, typename W>
  void prat_exp_list(PartialExp<S, T>&		pexp,
		     const rat::Node<M, W>*	node)
  {
    if (node->what() == rat::Node<M, W>::prod)
    {
      const rat::Product<M, W>* p =
	dynamic_cast<const rat::Product<M, W>*>(node);
      prat_exp_list(pexp, p->left_);
      prat_exp_list(pexp, p->right_);
    }
    else
      pexp.insert(node);
  }

  template <typename S, typename T, typename M, typename W>
  PartialExp<S, T> prat_exp_convert(const Element<S, T>& exp,
				    const rat::Node<M, W>* node)
  {
    typedef typename PartialExp<S, T>::semiring_elt_t	semiring_elt_t;
    semiring_elt_t	lw = exp.structure().semiring().identity(
      SELECT(typename semiring_elt_t::value_t));
    semiring_elt_t	rw = exp.structure().semiring().identity(
      SELECT(typename semiring_elt_t::value_t));

    while (node->what() == rat::Node<M, W>::lweight or
	   node->what() == rat::Node<M, W>::rweight)
      if (node->what() == rat::Node<M, W>::lweight)
      {
	const rat::LeftWeighted<M, W>* p =
	  dynamic_cast<const rat::LeftWeighted<M, W>*>(node);
	lw = p->weight_ * lw;
	node = p->child_;
      }
      else
      {
	const rat::RightWeighted<M, W>* p =
	  dynamic_cast<const rat::RightWeighted<M, W>*>(node);
	rw *= p->weight_;
	node = p->child_;
      }
    PartialExp<S, T>	res(exp);
    prat_exp_list(res, node);
    res >>= lw;
    res <<= rw;
    return res;
  }

  template <typename S, typename T>
  PartialExp<S, T> prat_exp_convert(const Element<S, T>& exp)
  {
    return prat_exp_convert(exp, exp.value().base());
  }

  template <typename S, typename T>
  std::list<PartialExp<S, T> > prat_exp_convert(const std::list<Element<S, T> >& listexp)
  {
    std::list<PartialExp<S, T> > res;
    for (typename std::list<Element<S, T> >::const_iterator it =
	   listexp.begin(); it != listexp.end(); ++it)
      res.push_back(prat_exp_convert(*it, it->value().base()));
    return res;
  }

  template <typename S, typename T>
  bool operator< (const PartialExp<S, T>& e1, const PartialExp<S, T>& e2)
  {
    typedef
    typename PartialExp<S, T>::series_set_elt_value_t	series_set_elt_value_t;
    typename PartialExp<S, T>::const_iterator i1 = e1.begin();
    typename PartialExp<S, T>::const_iterator i2 = e2.begin();

    if (i1.semiring_elt() != i2.semiring_elt())
      return (i1.semiring_elt() < i2.semiring_elt());

    for (i1++, i2++; i1 != e1.end() and i2 != e2.end(); )
    {
      if (series_set_elt_value_t(i1.node()) != series_set_elt_value_t(i2.node()))
	break;
      ++i1;
      ++i2;
      if (i1.semiring_elt() != i2.semiring_elt())
	break;
      ++i1;
      ++i2;
    }
    if (i1 == e1.end() || i2 == e2.end())
      return (i1 == e1.end() && i2 != e2.end());
    else if (i1.on_node())
      return series_set_elt_value_t(i1.node()) < series_set_elt_value_t(i2.node());
    else
      return i1.semiring_elt() < i2.semiring_elt();
  }

  template <typename S, typename T>
  bool operator== (const PartialExp<S, T>& e1, const PartialExp<S, T>& e2)
  {
    typedef
    typename PartialExp<S, T>::series_set_elt_value_t	series_set_elt_value_t;
    typename PartialExp<S, T>::const_iterator i1 = e1.begin();
    typename PartialExp<S, T>::const_iterator i2 = e2.begin();

    if (i1.semiring_elt() != i2.semiring_elt())
      return false;

    for (i1++, i2++; i1 != e1.end() and i2 != e2.end(); )
    {
      if (series_set_elt_value_t(i1.node()) != series_set_elt_value_t(i2.node()))
	break;
      ++i1;
      ++i2;
      if (i1.semiring_elt() != i2.semiring_elt())
	break;
      ++i1;
      ++i2;
    }
    return (i1 == e1.end() && i2 == e2.end());
  }

  template <typename S, typename T>
  bool unweighted_inf(const PartialExp<S, T>& e1, const PartialExp<S, T>& e2)
  {
    typedef
    typename PartialExp<S, T>::series_set_elt_value_t	series_set_elt_value_t;
    typename PartialExp<S, T>::const_iterator i1 = e1.begin();
    typename PartialExp<S, T>::const_iterator i2 = e2.begin();

    for (i1++, i2++; i1 != e1.end() and i2 != e2.end(); )
    {
      if (series_set_elt_value_t(i1.node()) != series_set_elt_value_t(i2.node()))
	break;
      ++i1;
      ++i2;
      if (i1.semiring_elt() != i2.semiring_elt())
	break;
      ++i1;
      ++i2;
    }
    if (i1 == e1.end() || i2 == e2.end())
      return (i1 == e1.end() && i2 != e2.end());
    else if (i1.on_node())
      return series_set_elt_value_t(i1.node()) < series_set_elt_value_t(i2.node());
    else
      return i1.semiring_elt() < i2.semiring_elt();
  }

  template <typename S, typename T>
  bool unweighted_eq(const PartialExp<S, T>& e1, const PartialExp<S, T>& e2)
  {
    typedef
    typename PartialExp<S, T>::series_set_elt_value_t	series_set_elt_value_t;
    typename PartialExp<S, T>::const_iterator i1 = e1.begin();
    typename PartialExp<S, T>::const_iterator i2 = e2.begin();

    for (i1++, i2++; i1 != e1.end() and i2 != e2.end(); )
    {
      if (series_set_elt_value_t(i1.node()) != series_set_elt_value_t(i2.node()))
	break;
      ++i1;
      ++i2;
      if (i1.semiring_elt() != i2.semiring_elt())
	break;
      ++i1;
      ++i2;
    }
    return (i1 == e1.end() && i2 == e2.end());
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_HXX
