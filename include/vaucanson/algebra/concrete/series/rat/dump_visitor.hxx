// dump_visitor.hxx
//
// $Id$
// VCSN_HEADER
#ifndef RAT_DUMP_VISITOR_HXX
# define RAT_DUMP_VISITOR_HXX

# include <iostream>
# include <vaucanson/algebra/concrete/series/rat/dump_visitor.hh>
# include <vaucanson/algebra/concrete/series/rat/nodes.hh>

namespace vcsn {

  namespace rat {

    template <class M_, class W_>
    DumpVisitor<M_,W_>::DumpVisitor(std::ostream& o,
				    const char *zero = "0",
				    const char *one = "1") 
      : o_(o),
	z_(zero),
	i_(one)
    {}

    template <class M_, class W_>
    void 
    DumpVisitor<M_,W_>::product(const Node<M_, W_>* left_, 
				const Node<M_, W_>* right_)
    { 
      o_ << "(";
      left_->accept(*this);
      o_ << ".";
      right_->accept(*this);
      o_ << ")";
    }

    template <class M_, class W_>
    void 
    DumpVisitor<M_,W_>::sum(const Node<M_, W_>* left_, 
			    const Node<M_, W_>* right_)
    { 
      o_ << "(";
      left_->accept(*this);
      o_ << "+";
      right_->accept(*this);
      o_ << ")";
    }

    template <class M_, class W_>
    void 
    DumpVisitor<M_,W_>::star(const Node<M_, W_>* node)
    { 
      //	  o_ << "(";
      node->accept(*this);
      o_ << "*"; // << ")";
    }

    template <class M_, class W_>
    void 
    DumpVisitor<M_,W_>::left_weight(const W_& w, const Node<M_, W_>* node)
    { 
      o_ << "(" << w << " ";
      node->accept(*this);
      o_ << ")";
    }

    template <class M_, class W_>
    void 
    DumpVisitor<M_,W_>::right_weight(const W_& w, const Node<M_, W_>* node)
    { 
      o_ << "(";
      node->accept(*this);
      o_ << " " << w << ")";
    }

    template <class M_, class W_>
    void 
    DumpVisitor<M_,W_>::constant(const M_& m)
    { 
      o_ << m; 
    }

    template <class M_, class W_>
    void DumpVisitor<M_,W_>::zero()
    { 
      o_ << z_; 
    }

    template <class M_, class W_>
    void DumpVisitor<M_,W_>::one()
    { 
      o_ << i_; 
    }
      
  } // rat

} // vcsn

#endif // RAT_DUMP_VISITOR_HXX
