#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_TO_POLYNOM_HH
# define VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_TO_POLYNOM_HH

# include <vaucanson/algebra/concrete/series/krat.hh>
# include <vaucanson/algebra/concrete/series/rat/nodes.hh>
# include <vaucanson/algebra/concrete/series/polynoms.hh>

// At this moment, it does not convert everything, the expression must be in
// disjonctive form.

namespace vcsn {

  namespace algebra {

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    class Krat2Polynom : public rat::ConstNodeVisitor<Tm, Ts>
    {
    protected:
      typedef rat::Node<Tm, Ts> node_t;

      polynom<Tm, Ts>	_p;
      bool		error;

      std::pair<Element<Sm, Tm>, Element<Ss, Ts> >
      explore_product(const node_t* n);

    public:
      Krat2Polynom() : _p(), error(false) {}

      bool
      has_error();

      polynom<Tm, Ts>
      get_polynom();

      virtual void
      product(const node_t* left_, const node_t* right_);

      virtual void
      sum(const node_t* left_, const node_t* right_);

      virtual void
      star(const node_t* node_);

      virtual void
      left_weight(const Ts& w, const node_t* node_);

      virtual void
      right_weight(const Ts& w, const node_t* node_);

      virtual void
      constant(const Tm& m_);

      virtual void
      one();

      virtual void
      zero();
    };

    class Unconvertible {};

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    Element<Series<Ss, Sm>, polynom<Tm, Ts> >
    krat_to_polynom(const Element<Series<Ss, Sm>, rat::exp<Tm, Ts> >&);
  }
}

# include <vaucanson/xml/krat_to_polynom.hxx>

#endif //VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_TO_POLYNOM_HH
