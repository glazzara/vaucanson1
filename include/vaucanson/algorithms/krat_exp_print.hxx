// krat_exp_print.hxx: this file is part of the Vaucanson project.
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
//

#ifndef VCSN_ALGORITHMS_KRAT_EXP_PRINT_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_PRINT_HXX

# include <vaucanson/algorithms/krat_exp_print.hh>

# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/implementation/series/rat/exp.hh>

# include <string>

namespace vcsn {

  enum node_types {
    NODE_CONSTANT,
    NODE_LWEIGHT,
    NODE_RWEIGHT,
    NODE_ONE,
    NODE_PROD,
    NODE_STAR,
    NODE_SUM,
    NODE_ZERO
  };

  /*-------------.
  | PrintVisitor |
  `-------------*/

  template <class Word, class Weight>
  class PrintVisitor :
    public rat::ConstNodeVisitor<Word, Weight>
  {
  public:
    typedef Word			monoid_elt_value_t;
    typedef Weight			semiring_elt_value_t;
    typedef rat::Node<Word, Weight>	node_t;
    typedef print_modes			print_mode_t;

  public:

    PrintVisitor(std::ostream&		ostr = std::cout,
		 const print_mode_t	pm = MODE_NONE,
		 const std::string&	zero = "0",
		 const std::string&	one = "1")
      : ostr_ (ostr),
	print_mode_ (pm),
	z_ (zero),
	i_ (one)
    {
    }

    virtual
    ~PrintVisitor()
    {
      ostr_.flush();
    }

    // PRODUCT
    virtual
    void
    product(const node_t* lhs, const node_t* rhs)
    {
      unsigned node_type_lhs = lhs->what();
      unsigned node_type_rhs = rhs->what();
      switch(node_type_lhs)
	{
	case NODE_SUM:
	  ostr_ << "(";
	  lhs->accept(*this);
	  ostr_ << ")";
	  break;
	case NODE_PROD:
	  if (print_mode_ == MODE_NONE or print_mode_ == MODE_ADD)
	    lhs->accept(*this);
	  else
	    {
	      ostr_ << "(";
	      lhs->accept(*this);
	      ostr_ << ")";
	    }
	  break;
	default:
	  lhs->accept(*this);
	  break;
	}

      ostr_ << ".";

      switch(node_type_rhs)
	{
	case NODE_SUM:
	  ostr_ << "(";
	  rhs->accept(*this);
	  ostr_ << ")";
	  break;
	case NODE_PROD:
	  if (print_mode_ == MODE_NONE or print_mode_ == MODE_ADD)
	    rhs->accept(*this);
	  else
	    {
	      ostr_ << "(";
	      rhs->accept(*this);
	      ostr_ << ")";
	    }
	  break;
	default:
	  rhs->accept(*this);
	  break;
	}
    }

    // SUM
    virtual
    void
    sum(const node_t* lhs, const node_t* rhs)
    {
      unsigned node_type_lhs = lhs->what();
      unsigned node_type_rhs = rhs->what();
      if (node_type_lhs != NODE_SUM or
	  print_mode_ == MODE_NONE or
	  print_mode_ == MODE_MUL)
	lhs->accept(*this);
      else
	{
	  ostr_ << "(";
	  lhs->accept(*this);
	  ostr_ << ")";
	}

      ostr_ << " + ";

      if (node_type_rhs != NODE_SUM or
	  print_mode_ == MODE_NONE or
	  print_mode_ == MODE_MUL)
	rhs->accept(*this);
      else
	{
	  ostr_ << "(";
	  rhs->accept(*this);
	  ostr_ << ")";
	}
    }

    virtual
    void
    star(const node_t* node)
    {
      ostr_ << "(";
      node->accept(*this);
      ostr_ << ")*";
    }

    virtual
    void
    left_weight(const semiring_elt_value_t& w, const node_t* node)
    {
      ostr_ << w;
      node->accept(*this);
    }

    virtual
    void
    right_weight(const semiring_elt_value_t& w, const node_t* node)
    {
      node->accept(*this);
      ostr_ << w;
    }

    virtual
    void
    constant(const monoid_elt_value_t& m)
    {
      ostr_ << m;
    }

    virtual
    void
    zero()
    {
      ostr_ << z_;
    }

    virtual
    void
    one()
    {
      ostr_ << i_;
    }

  private :
    std::ostream&	ostr_;
    const print_mode_t	print_mode_;
    const std::string	z_;
    const std::string	i_;
  };

  template <class S, class T, class Word, class Weight>
  std::ostream&
  do_krat_exp_print(const algebra::SeriesBase<S>&,
		    const rat::exp<Word, Weight>& value,
		    const Element<S, T>&,
		    std::ostream& ostr,
		    const print_modes mode = MODE_NONE)
  {
    PrintVisitor<Word, Weight> v (ostr, mode);
    value.accept(v);
    return ostr;
  }

  template<class S, class T>
  std::ostream&
  krat_exp_print(const Element<S, T>& kexp,
		 std::ostream& ostr,
		 const print_modes mode)
  {
    return do_krat_exp_print(kexp.structure(), kexp.value(), kexp, ostr, mode);
  }

} // End of namespace vcsn.

#endif // VCSN_ALGORITHMS_KRAT_EXP_PRINT_HXX
