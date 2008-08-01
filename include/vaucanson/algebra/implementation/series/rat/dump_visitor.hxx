// dump_visitor.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DUMP_VISITOR_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DUMP_VISITOR_HXX

# include <vaucanson/algebra/implementation/series/rat/dump_visitor.hh>
# include <vaucanson/algebra/implementation/series/rat/nodes.hh>

# include <vaucanson/misc/escaper.hh>
# include <iostream>

namespace vcsn {

  namespace rat {

    /// Global indexes to the IOS internal extensible array.
    //@{

    /// Print mode.
    inline
    int
    print_mode()
    {
      static const int idx = std::ios::xalloc();
      return idx;
    }

    /// Zero of the series.
    inline
    int
    zero()
    {
      static const int idx = std::ios::xalloc();
      return idx;
    }

    /// Identity of the series.
    inline
    int
    id()
    {
      static const int idx = std::ios::xalloc();
      return idx;
    }

    //@}

    /*------------.
    | DumpVisitor |
    `------------*/

    template <class Word, class Weight>
    class DumpVisitor : public ConstNodeVisitor<Word, Weight>
    {
    public:

      typedef Word			monoid_elt_value_t;
      typedef Weight			semiring_elt_value_t;
      typedef Node<Word, Weight>	node_t;

    public:

      DumpVisitor(std::ostream& ostr = std::cout)
	: ostr_ (ostr)
      {
	if (not ostr_.pword(rat::zero()))
	  ostr_ << setzero ("0");

	if (not ostr_.pword(rat::id()))
	{
	  std::string eps = "";
	  eps += algebra::letter_traits<typename Word::value_type>::default_epsilon();
	  ostr_ << setid(eps);
	}
      }

      virtual
      ~DumpVisitor()
      {
	ostr_.flush();
      }

    protected:

      void
      enclose_if(const bool cond, const node_t* node)
      {
	if (cond)
	  {
	    ostr_ << "(";
	    node->accept(*this);
	    ostr_ << ")";
	  }
	else
	  node->accept(*this);
      }

      enum
	{
	  NODE_LWEIGHT	= Node<Word, Weight>::lweight,
	  NODE_RWEIGHT	= Node<Word, Weight>::rweight,
	  NODE_PROD	= Node<Word, Weight>::prod,
	  NODE_SUM	= Node<Word, Weight>::sum,
	};

      void
      product_print_child(const node_t* child)
      {
	switch(child->what())
	  {
	  case NODE_SUM:
	    // If MODE_SUM is already set, there is no need to enclose the
	    // child, since it will be done in sum().
	    enclose_if(not (ostr_.iword(print_mode()) & MODE_ADD), child);
	    break;
	  default:
	    child->accept(*this);
	    break;
	  }
      }

    public:

      virtual
      void
      product(const node_t* lhs, const node_t* rhs)
      {
	const long verbose = ostr_.iword(print_mode()) & MODE_MUL;

	if (verbose)
	  ostr_ << "(";

	product_print_child(lhs);
	ostr_ << ".";
	product_print_child(rhs);

	if (verbose)
	  ostr_ << ")";
      }

      virtual
      void
      sum(const node_t* lhs, const node_t* rhs)
      {
	const long verbose = ostr_.iword(print_mode()) & MODE_ADD;

	if (verbose)
	  ostr_ << "(";

	lhs->accept(*this);
	ostr_ << "+";
	rhs->accept(*this);

	if (verbose)
	  ostr_ << ")";
      }

      virtual
      void
      star(const node_t* node)
      {
	const long	mode = ostr_.iword(print_mode());
	const unsigned	node_type = node->what();

	switch (node_type)
	  {
	  case NODE_SUM:
	    enclose_if(not (mode & MODE_ADD), node);
	    break;
	  case NODE_PROD:
	    enclose_if(not (mode & MODE_MUL), node);
	    break;
	  case NODE_LWEIGHT:
	    enclose_if(not (mode & MODE_LWEIGHT), node);
	    break;
	  case NODE_RWEIGHT:
	    enclose_if(not (mode & MODE_RWEIGHT), node);
	    break;
	  default:
	    enclose_if(mode & MODE_STAR, node);
	    break;
	  }
	ostr_ << "*";
      }

      virtual
      void
      left_weight(const semiring_elt_value_t& w, const node_t* node)
      {
	const long	mode = ostr_.iword(print_mode());
	const unsigned	node_type = node->what();
	long		verbose;
	bool		enclose_all (false);

	switch (node_type)
	  {
	  case NODE_PROD:
	    verbose = not (mode & MODE_MUL);
	    break;
	  case NODE_SUM:
	    verbose = not (mode & MODE_ADD);
	    break;
	  default:
	    verbose = false;
	    enclose_all = mode & MODE_LWEIGHT;
	    break;
	  }

	if (enclose_all)
	  ostr_ << "(";

	ostr_ << "{" << w << "} ";
	enclose_if(verbose, node);

	if (enclose_all)
	  ostr_ << ")";
      }

      virtual
      void
      right_weight(const semiring_elt_value_t& w, const node_t* node)
      {
	const long	mode = ostr_.iword(print_mode());
	const unsigned	node_type = node->what();
	long		verbose;
	bool		enclose_all (false);

	switch (node_type)
	  {
	  case NODE_PROD:
	    verbose = not (mode & MODE_MUL);
	    break;
	  case NODE_SUM:
	    verbose = not (mode & MODE_ADD);
	    break;
	  default:
	    verbose = false;
	    enclose_all = mode & MODE_LWEIGHT;
	    break;
	  }

	if (enclose_all)
	  ostr_ << "(";

	enclose_if(verbose, node);
	ostr_ << " {" << w << "}";

	if (enclose_all)
	  ostr_ << ")";
      }

      virtual
      void
      constant(const monoid_elt_value_t& m)
      {
	ostr_ << misc::make_escaper(m);
      }

      virtual
      void
      zero()
      {
	ostr_ << *static_cast<const std::string*> (ostr_.pword(rat::zero()));
      }

      virtual
      void
      one()
      {
	ostr_ << *static_cast<const std::string*> (ostr_.pword(id()));
      }

    protected:
      std::ostream&	ostr_;
    };

    /*------------.
    | operator << |
    `------------*/

    template <class Word, class Weight>
    std::ostream&
    operator << (std::ostream& ostr, const exp<Word, Weight>& e)
    {
      DumpVisitor<Word, Weight> v (ostr);
      e.accept(v);
      return ostr;
    }

    /*------.
    | setpm |
    `------*/

    inline
    setpm::setpm(print_mode_t mode) : mode_ (mode)
    {
    }

    inline
    std::ostream&
    setpm::operator () (std::ostream& ostr) const
    {
      ostr.iword(print_mode()) = mode_;
      return ostr;
    }

    /*------.
    | getpm |
    `------*/

    inline
    print_mode_t
    getpm(std::ostream& ostr)
    {
      return print_mode_t (ostr.iword(print_mode()));
    }

    /*--------.
    | setzero |
    `--------*/

    inline
    setzero::setzero(const std::string& zero) : z_ (zero)
    {
    }

    inline
    std::ostream&
    setzero::operator () (std::ostream& ostr) const
    {
      const int idx = zero();

      if (not ostr.pword(idx))
	ostr.register_callback(misc::pword_delete<std::string>, idx);
      else
	delete static_cast<std::string*> (ostr.pword(idx));
      ostr.pword(idx) = new std::string (z_);
      return ostr;
    }

    /*------.
    | setid |
    `------*/

    inline
    setid::setid(const std::string& id) : i_ (id)
    {
    }

    inline
    std::ostream&
    setid::operator () (std::ostream& ostr) const
    {
      const int idx = id();

      if (not ostr.pword(idx))
	ostr.register_callback(misc::pword_delete<std::string>, idx);
      else
	delete static_cast<std::string*> (ostr.pword(idx));
      ostr.pword(idx) = new std::string (i_);
      return ostr;
    }

  } // rat

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DUMP_VISITOR_HXX
