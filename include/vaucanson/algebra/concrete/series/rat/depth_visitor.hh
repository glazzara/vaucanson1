// depth_visitor.hh
//
// $Id$
// VCSN_HEADER
#ifndef RAT_DEPTH_VISITOR_HH
# define RAT_DEPTH_VISITOR_HH

# include <algorithm>
# include <vaucanson/algebra/concrete/series/rat/nodes.hh>

namespace vcsn {

  namespace rat {

    template<typename M_, typename W_>
    class DepthVisitor : public ConstNodeVisitor<M_, W_>
    {
    protected:
      void 
      sum_or_product(const Node<M_, W_>* left_, const Node<M_, W_>* right_);
      void 
      weight_or_star(const Node<M_, W_>* node);

    public:
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

      size_t get() const;

    protected:
      size_t		d;
    };

  } // rat

} // vcsn

# include <vaucanson/algebra/concrete/series/rat/depth_visitor.hxx>

#endif // RAT_DEPTH_VISITOR_HH
