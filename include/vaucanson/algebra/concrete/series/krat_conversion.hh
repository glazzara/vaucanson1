// krat_conversion.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef ALGEBRA_KRAT_CONVERSION_HH
# define ALGEBRA_KRAT_CONVERSION_HH

# include <vaucanson/algebra/concrete/series/krat.hh>

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

# include <vaucanson/algebra/krat_conversion.hxx>

#endif // ALGEBRA_KRAT_CONVERSION_HH
 
