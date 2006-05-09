// exp.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_EXP_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_EXP_HXX

# include <vaucanson/algebra/implementation/series/rat/exp.hh>

# include <vaucanson/algebra/implementation/series/rat/depth_visitor.hh>
# include <vaucanson/algebra/implementation/series/rat/star_height_visitor.hh>
# include <vaucanson/algebra/implementation/series/rat/length_visitor.hh>
# include <vaucanson/algebra/implementation/series/rat/xml_exp_visitor.hh>

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
    exp<LetterT, WeightT>::exp(const node_t* p)
      : base_(p->clone())
    {}

    template<typename LetterT, typename WeightT>
    exp<LetterT, WeightT>::exp(const exp& other)
      : base_(other.base_->clone())
    {}

    template<typename LetterT, typename WeightT>
    exp<LetterT, WeightT>::~exp()
    {
      delete base_;
    }

    template<typename LetterT, typename WeightT>
    exp<LetterT, WeightT>&
    exp<LetterT, WeightT>::operator = (const exp& other)
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
    exp<LetterT, WeightT>::operator += (const exp& other)
    {
      base_ = new n_sum_t(base_, other.base_->clone());
      return *this;
    }

    template<typename LetterT, typename WeightT>
    exp<LetterT, WeightT>&
    exp<LetterT, WeightT>::operator *= (const exp& other)
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
    exp<LetterT, WeightT>&
    exp<LetterT, WeightT>::swap(exp& other)
    {
      std::swap(base_, other.base_);
      return *this;
    }

    template<typename LetterT, typename WeightT>
    void exp<LetterT, WeightT>::
    accept(ConstNodeVisitor<monoid_elt_value_t, semiring_elt_value_t>& v) const
    {
      base_->accept(v);
    }

    template<typename LetterT, typename WeightT>
    size_t exp<LetterT, WeightT>::depth() const
    {
      DepthVisitor<monoid_elt_value_t, semiring_elt_value_t> v;
      accept(v);
      return v.get();
    }

    template<typename LetterT, typename WeightT>
    size_t exp<LetterT, WeightT>::star_height() const
    {
      StarHeightVisitor<monoid_elt_value_t, semiring_elt_value_t> v;
      accept(v);
      return v.get();
    }

    template<typename LetterT, typename WeightT>
    size_t exp<LetterT, WeightT>::length() const
    {
      LengthVisitor<monoid_elt_value_t, semiring_elt_value_t> v;
      accept(v);
      return v.get();
    }

# if (not defined (VCSN_SANITY_CHECK)) or (defined (VCSN_USE_XML))
    template<typename LetterT, typename WeightT>
    xercesc::DOMElement* exp<LetterT, WeightT>::xml_tree(
      xercesc::DOMDocument* doc, char* node_name) const
    {
      XmlExpVisitor<monoid_elt_value_t, semiring_elt_value_t> v(doc, node_name);
      accept(v);
      return v.get();
    }
# endif

    template<typename LetterT, typename WeightT>
    typename exp<LetterT, WeightT>::node_t* &
    exp<LetterT, WeightT>::base()
    {
      return base_;
    }

    template<typename LetterT, typename WeightT>
    typename exp<LetterT, WeightT>::node_t* const &
    exp<LetterT, WeightT>::base() const
    {
      return base_;
    }

    template<typename LetterT, typename WeightT>
    bool exp<LetterT, WeightT>::operator == (const exp& other) const
    {
      return !(*base_ != *other.base_);
    }

    template<typename LetterT, typename WeightT>
    bool exp<LetterT, WeightT>::operator != (const exp& other) const
    {
      return *base_ != *other.base_;
    }

    template<typename LetterT, typename WeightT>
    bool exp<LetterT, WeightT>::operator < (const exp& other) const
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
    exp<LetterT, WeightT> exp<LetterT, WeightT>::
    constant(const monoid_elt_value_t& l)
    {
      return exp(new n_const_t(l));
    }

    template<typename LetterT, typename WeightT>
    bool exp<LetterT, WeightT>::starable()
    {
      return true;
    }

    template<typename M, typename W>
    const exp<M, W> operator * (const exp<M, W>& lhs,
				const exp<M, W>& rhs)
    {
      exp<M, W> ret(lhs);
      ret *= rhs;
      return ret;
    }

    template<typename M, typename W>
    exp<M, W> operator + (const exp<M, W>& lhs,
			  const exp<M, W>& rhs)
    {
      exp<M, W> ret(lhs);
      ret += rhs;
      return ret;
    }

    template<typename M, typename W>
    exp<M, W> operator * (const W& lhs,
			  const exp<M, W>& rhs)
    {
      exp<M, W> ret(rhs);
      ret.base() = new LeftWeighted<M, W>(lhs, ret.base());
      return ret;
    }

    template<typename M, typename W>
    exp<M, W> operator * (const exp<M, W>& lhs,
			  const W& rhs)
    {
      exp<M, W> ret(lhs);
      ret.base() = new RightWeighted<M, W>(rhs, ret.base());
      return ret;
    }

    // FIXME: this is an evil hack, but without it there is an ambiguity
    // FIXME: in calls to exp * number or number * exp.

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

    template<typename M, typename W>
    void swap(vcsn::rat::exp<M, W>& lhs,
	      vcsn::rat::exp<M, W>& rhs)
    {
      lhs.swap(rhs);
    }

  } // End of namespace rat.

} // End of namespace vcsn.

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_EXP_HXX
