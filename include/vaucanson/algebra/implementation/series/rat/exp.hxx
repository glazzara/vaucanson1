// exp.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_EXP_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_EXP_HXX

# include <vaucanson/algebra/implementation/series/rat/exp.hh>

# include <vaucanson/algebra/implementation/series/rat/depth_visitor.hh>

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
    exp<LetterT, WeightT>::swap(exp& otether)
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
