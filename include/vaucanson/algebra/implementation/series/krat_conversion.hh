// krat_conversion.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_CONVERSION_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_CONVERSION_HH

# include <vaucanson/algebra/implementation/series/krat.hh>

namespace vcsn {

  namespace algebra {

    /*------------------.
    | ExpConvertVisitor |
    `------------------*/
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


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algebra/implementation/series/krat_conversion.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_CONVERSION_HH
