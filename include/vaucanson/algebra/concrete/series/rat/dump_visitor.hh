// dump_visitor.hh
//
// $Id$
// VCSN_HEADER
#ifndef RAT_DUMP_VISITOR_HH
# define RAT_DUMP_VISITOR_HH

# include <iostream>
# include <vaucanson/rat/nodes.hh>

namespace vcsn {

  namespace rat {

    template<typename M_, typename W_>
    class DumpVisitor : public ConstNodeVisitor<M_, W_>
    {
    public:
      DumpVisitor(std::ostream& o,
		  const char *zero = "0",
		  const char *one = "1");

      virtual void 
      product(const Node<M_, W_>* left_, const Node<M_, W_>* right_);

      virtual void 
      sum(const Node<M_, W_>* left_, const Node<M_, W_>* right_);

      virtual void 
      star(const Node<M_, W_>* node);

      virtual void 
      left_weight(const W_& w, const Node<M_, W_>* node);

      virtual void 
      right_weight(const W_& w, const Node<M_, W_>* node);

      virtual void 
      constant(const M_& m);

      virtual void zero();

      virtual void one();

    protected:
      std::ostream& o_;
      const char *z_;
      const char *i_;
    };
      
  } // rat

} // vcsn

# include <vaucanson/algebra/concrete/series/rat/dump_visitor.hh>

#endif // RAT_DUMP_VISITOR_HH
