// krat_conversion.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_CONVERSION_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_CONVERSION_HXX

# include <vaucanson/algebra/implementation/series/krat_conversion.hh>

namespace vcsn {

  namespace algebra {

    /*------------------.
    | ExpConvertVisitor |
    `------------------*/

    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
    ExpConvertVisitor<Tm, Tw, oTm, oTw, Series_>::ExpConvertVisitor(const Series_& s)
      : exp_(), series_(s)
    {}


    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
    ExpConvertVisitor<Tm, Tw, oTm, oTw, Series_>::~ExpConvertVisitor()
    {}

    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
     void
    ExpConvertVisitor<Tm, Tw, oTm, oTw, Series_>::product(const node_t* left_,
						 const node_t* right_)
    {
      right_->accept(*this);
      exp_t tmp = exp_;
      left_->accept(*this);
      op_in_mul(series_, exp_, tmp);
    }

    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
     void
    ExpConvertVisitor<Tm, Tw, oTm, oTw, Series_>::sum(const node_t* left_,
					     const node_t* right_)
    {
      right_->accept(*this);
      exp_t tmp = exp_;
      left_->accept(*this);
      op_in_add(series_, exp_, tmp);
    }

    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
     void
    ExpConvertVisitor<Tm, Tw, oTm, oTw, Series_>::star(const node_t* node_)
    {
      node_->accept(*this);
      op_in_star(series_, exp_);
    }

    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
     void
    ExpConvertVisitor<Tm, Tw, oTm, oTw, Series_>::left_weight(const oTw& w,
							      const node_t* node_)
    {
      node_->accept(*this);
      exp_ = op_mul(series_.semiring(), series_,
		    op_convert(SELECT(typename Series_::semiring_t),
			       SELECT(Tw),
			       w),
		    exp_);
    }

    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
     void
    ExpConvertVisitor<Tm, Tw, oTm, oTw, Series_>::right_weight(const oTw& w,
							       const node_t*
								 node_)
    {
      node_->accept(*this);
      op_in_mul(series_, series_.semiring(), exp_,
		op_convert(SELECT(typename Series_::semiring_t),
			   SELECT(Tw),
			   w));
    }

    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
     void
    ExpConvertVisitor<Tm, Tw, oTm, oTw, Series_>::constant(const oTm& m_)
    {
      Tm m = op_convert(SELECT(typename Series_::monoid_t),
			SELECT(Tm),
			m_);
      if (m == identity_value(SELECT(typename Series_::monoid_t),
			      SELECT(Tm)))
	exp_ = exp_t::one();
      else
	exp_ = exp_t::constant(m);
    }

    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
     void
    ExpConvertVisitor<Tm, Tw, oTm, oTw, Series_>::one()
    {
      exp_ = exp_t::one();
    }

    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
     void
    ExpConvertVisitor<Tm, Tw, oTm, oTw, Series_>::zero()
    {
      exp_ = exp_t::zero();
    }

    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
    const typename ExpConvertVisitor<Tm,Tw,oTm,oTw,Series_>::exp_t&
    ExpConvertVisitor<Tm, Tw, oTm, oTw, Series_>::get() const
    {
      return exp_;
    }

    template<typename Tm, typename Tw, typename W, typename M,
	     typename oTm, typename oTw>
    rat::exp<Tm, Tw>
    convert_exp(SELECTOR2(rat::exp<Tm, Tw>),
		const Series<W, M>& s,
		const rat::exp<oTm, oTw>& arg)
    {
      ExpConvertVisitor<Tm, Tw, oTm, oTw, Series<W, M> > v(s);
      arg.accept(v);
      return v.get();
    }

    template<typename W, typename M, typename Tm, typename Tw,
	     typename oTm, typename oTw>
    Element<Series<W, M>, rat::exp<Tm, Tw> >
    convert_exp(SELECTOR4(Element<Series<W, M>, rat::exp<Tm, Tw> >),
		const Element<Series<W, M>, rat::exp<oTm, oTw> >& arg)
    {
      return Element<Series<W, M>, rat::exp<Tm, Tw> >
	(arg.structure(),
	 convert_exp(SELECT2(rat::exp<Tm, Tw>),
		     arg.structure(),
		     arg.value()));
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_CONVERSION_HXX
