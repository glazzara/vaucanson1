// krat_conversion.hxx
//
//

#ifndef ALGEBRA_KRAT_CONVERSION_HXX
# define ALGEBRA_KRAT_CONVERSION_HXX

# include <vaucanson/algebra/krat_conversion.hh>


namespace vcsn {

  namespace algebra {

    /*------------------.
    | ExpConvertVisitor |
    `------------------*/

    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
    ExpConvertVisitor<Tm, Tw, oTm, oTw>::ExpConvertVisitor(const Series_& s)
      : exp_(), series_(s)
    {}
    
    
    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
    ExpConvertVisitor<Tm, Tw, oTm, oTw>::~ExpConvertVisitor()
    {}
    
    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
    virtual void
    ExpConvertVisitor<Tm, Tw, oTm, oTw>::product(const node_t* left_, 
						 const node_t* right_)
    {
      right_->accept(*this);
      exp_t tmp = exp_;
      left_->accept(*this);
      op_in_mul(series_, exp_, tmp);
    }
    
    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
    virtual void
    ExpConvertVisitor<Tm, Tw, oTm, oTw>::sum(const node_t* left_, 
					     const node_t* right_)
    {
      right_->accept(*this);
      exp_t tmp = exp_;
      left_->accept(*this);
      op_in_add(series_, exp_, tmp);
    }
    
    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
    virtual void
    ExpConvertVisitor<Tm, Tw, oTm, oTw>::star(const node_t* node_)
    {
      node_->accept(*this);
      op_in_star(series_, exp_);
    }
    
    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
    virtual void
    ExpConvertVisitor<Tm, Tw, oTm, oTw>::left_weight(const oTw& w, 
						     const node_t* node_)
    {
      node_->accept(*this);
      exp_ = op_mul(series_.weights(), series_, 
		    op_convert(SELECT(Tw),
			       SELECT(typename Series_::weights_t),
			       w),
		    exp_);
    }
    
    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
    virtual void
    ExpConvertVisitor<Tm, Tw, oTm, oTw>::right_weight(const oTw& w, 
						      const node_t* node_)
    {
      node_->accept(*this);
      op_in_mul(series_, series_.weights(), exp_, 
		op_convert(SELECT(Tw), 
			   SELECT(typename Series_::weights_t),
			   w));
    }
    
    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
    virtual void 
    ExpConvertVisitor<Tm, Tw, oTm, oTw>::constant(const oTm& m_)
    {
      Tm m = op_convert(SELECT(Tm),
			SELECT(typename Series_::monoid_t),
			m_);
      if (m == identity_value(SELECT(typename Series_::monoid_t),
			      SELECT(Tm)))
	exp_ = exp_t::one();
      else
	exp_ = exp_t::constant(m);
    }
    
    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
    virtual void 
    ExpConvertVisitor<Tm, Tw, oTm, oTw>::one()
    {
      exp_ = exp_t::one();
    }
    
    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
    virtual void 
    ExpConvertVisitor<Tm, Tw, oTm, oTw>::zero()
    {
      exp_ = exp_t::zero();
    }
    
    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
    const exp_t& 
    ExpConvertVisitor<Tm, Tw, oTm, oTw>::get() const
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
	(arg.set(),
	 convert_exp(SELECT2(rat::exp<Tm, Tw>),
		     arg.set(),
		     arg.value()));
    }

  } // algebra

} // vcsn

#endif // ALGEBRA_KRAT_CONVERSION_HXX
