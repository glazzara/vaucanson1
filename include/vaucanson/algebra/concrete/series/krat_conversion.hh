// krat_conversion.hh
//
//

#ifndef ALGEBRA_KRAT_CONVERSION_HH
# define ALGEBRA_KRAT_CONVERSION_HH

# include <vaucanson/algebra/krat.hh>

namespace vcsn {

  namespace algebra {

    /*------------------.
    | ExpConvertVisitor |
    `------------------*/
    // Description : FIXME
    //
    //

    template<typename Tm, typename Tw, typename oTm, typename oTw,
	     typename Series_>
    class ExpConvertVisitor : public rat::ConstNodeVisitor<oTm, oTw>
    {
    protected:
      typedef rat::Node<oTm, oTw>		node_t;
      typedef rat::exp<Tm, Tw>			exp_t;

      exp_t					exp_;
      const Series_&				series_;

    public:
      ExpConvertVisitor(const Series_& s);
      ~ExpConvertVisitor();
	
      virtual void
      product(const node_t* left_, const node_t* right_);      

      virtual void
      sum(const node_t* left_, const node_t* right_);

      virtual void
      star(const node_t* node_);

      virtual void
      left_weight(const oTw& w, const node_t* node_);

      virtual void
      right_weight(const oTw& w, const node_t* node_);

      virtual void 
      constant(const oTm& m_);

      virtual void 
      one();

      virtual void 
      zero();

      const exp_t& 
      get() const;
    };
      

    template<typename Tm, typename Tw, typename W, typename M, 
	     typename oTm, typename oTw>
    rat::exp<Tm, Tw> 
    convert_exp(SELECTOR2(rat::exp<Tm, Tw>),
		const Series<W, M>& s,
		const rat::exp<oTm, oTw>& arg);

    template<typename W, typename M, typename Tm, typename Tw, 
	     typename oTm, typename oTw>
    Element<Series<W, M>, rat::exp<Tm, Tw> >
    convert_exp(SELECTOR4(Element<Series<W, M>, rat::exp<Tm, Tw> >),
		const Element<Series<W, M>, rat::exp<oTm, oTw> >& arg);
    
  } // algebra

} // vcsn

# include <vaucanson/algebra/krat_conversion.hxx>

#endif // ALGEBRA_KRAT_CONVERSION_HH
 
