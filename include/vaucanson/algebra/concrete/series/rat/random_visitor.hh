// random_visitor.hh
//
// $Id$
// VCSN_HEADER
#ifndef RAT_RANDOM_VISITOR_HH
# define RAT_RANDOM_VISITOR_HH

# include <algorithm>
# include <vaucanson/algebra/concrete/series/rat/nodes.hh>

namespace vcsn {

  namespace rat {

    template<typename M_, typename W_>
    class RandomVisitor : public ConstNodeVisitor<M_, W_>
    {
    public:
      static const unsigned nb_star_max_default /* = 5 */;

      RandomVisitor(unsigned nb_star_max);
      RandomVisitor();

      virtual void 
      product(const Node<M_, W_>* left_, const Node<M_, W_>* right_);
      virtual void 
      sum(const Node<M_, W_>* left_, const Node<M_, W_>* right_);

      virtual void 
      star(const Node<M_, W_>* node);

      virtual void left_weight(const W_&, const Node<M_, W_>*);
      virtual void right_weight(const W_&, const Node<M_, W_>*);

      virtual void 
      constant(const M_& m);
      virtual void zero();
      virtual void one();

      M_ get() const;

    protected:
      M_		w_;
      bool		not_empty;
      unsigned		nb_star_max_;
    };

  } // rat

} // vcsn

# include <vaucanson/algebra/concrete/series/rat/random_visitor.hxx>

#endif // RAT_RANDOM_VISITOR_HH
