#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_TO_POLYNOM_HXX
# define VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_TO_POLYNOM_HXX

# include <vaucanson/xml/krat_to_polynom.hh>

namespace vcsn {

  namespace algebra {

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    inline
    bool
    Krat2Polynom<Sm, Ss, Tm, Ts>::has_error()
    {
      return error;
    }

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    inline
    polynom<Tm, Ts>
    Krat2Polynom<Sm, Ss, Tm, Ts>::get_polynom()
    {
      return _p;
    }

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    inline
    std::pair<Element<Sm, Tm>, Element<Ss, Ts> >
    Krat2Polynom<Sm, Ss, Tm, Ts>::explore_product(const node_t* n)
    {
      using namespace rat;

      Element<Ss, Ts> weight;
      Element<Sm, Tm> label;

      if (const LeftWeighted<Tm, Ts>* left =
	  dynamic_cast<const LeftWeighted<Tm, Ts>*>(n)) {
	weight = left->weight_;
	if (const Constant<Tm, Ts>* c =
	    dynamic_cast<const Constant<Tm, Ts>*>(left->child_))
	  label = c->value_;
	else if (dynamic_cast<const One<Tm, Ts>*>(left->child_))
	  ;
	else if (!(dynamic_cast<const Zero<Tm, Ts>*>(left->child_))) {
	  error = true;
	  return std::pair<Element<Sm, Tm>, Element<Ss, Ts> >();
	}
      }
      else if (const RightWeighted<Tm, Ts>* right =
	       dynamic_cast<const RightWeighted<Tm, Ts>*>(n)) {
	weight = right->weight_;
	if (const Constant<Tm, Ts>* c =
	    dynamic_cast<const Constant<Tm, Ts>*>(right->child_)) {
	  label *= c->value_;
	}
	else if (dynamic_cast<const One<Tm, Ts>*>(right->child_))
	  ;
	else if (dynamic_cast<const Zero<Tm, Ts>*>(right->child_)) {
	  error = true;
	  return std::pair<Element<Sm, Tm>, Element<Ss, Ts> >();
	}
      }
      else if (const Constant<Tm, Ts>* c =
	       dynamic_cast<const Constant<Tm, Ts>*>(n)) {
	label = c->value_;
	weight = identity_value(SELECT(Ss), SELECT(Ts));
      }
      else if (dynamic_cast<const One<Tm, Ts>*>(n)) {
	weight = identity_value(SELECT(Ss), SELECT(Ts));
      }
      else if (const Product<Tm, Ts>* p =
	       dynamic_cast<const Product<Tm, Ts>*>(n)) {
	std::pair<Element<Sm, Tm>, Element<Ss, Ts> >
	  left = explore_product(p->left_);
	std::pair<Element<Sm, Tm>, Element<Ss, Ts> >
	  right = explore_product(p->right_);
	label = left.first * right.first;
	weight = left.second * right.second;
      }
      else if (!(dynamic_cast<const Zero<Tm, Ts>*>(n))) {
	error = true;
	return std::pair<Element<Sm, Tm>, Element<Ss, Ts> >();
      }

      return std::pair<Element<Sm, Tm>, Element<Ss, Ts> >(label, weight);
    }

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    inline
    void
    Krat2Polynom<Sm, Ss, Tm, Ts>::product(const node_t* left_,
					  const node_t* right_)
    {
      std::pair<Element<Sm, Tm>, Element<Ss, Ts> >
	left = explore_product(left_);
      if (error)
	return ;
      std::pair<Element<Sm, Tm>, Element<Ss, Ts> >
	right = explore_product(right_);
      Element<Sm, Tm> label = left.first * right.first;
      Element<Ss, Ts> weight = left.second * right.second;
      _p.insert(label.value(), weight.value());
    }

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    inline
    void
    Krat2Polynom<Sm, Ss, Tm, Ts>::sum(const node_t* left_,
				      const node_t* right_)
    {
      left_->accept(*this);
      if (!error)
	right_->accept(*this);
    }

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    inline
    void
    Krat2Polynom<Sm, Ss, Tm, Ts>::star(const node_t*)
    {
      error = true;
    }

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    inline
    void
    Krat2Polynom<Sm, Ss, Tm, Ts>::left_weight(const Ts& w, const node_t* node_)
    {
      using namespace rat;

      Element<Sm, Tm> label;
      Element<Ss, Ts> weight;
      if (const Constant<Tm, Ts>* c =
	  dynamic_cast<const Constant<Tm, Ts>*>(node_)) {
	label = c->value_;
	weight = w;
      }
      else if (dynamic_cast<const One<Tm, Ts>*>(node_))
	weight = w;
      else if (!(dynamic_cast<const Zero<Tm, Ts>*>(node_))) {
	error = true;
	return ;
      }
      _p.insert(label.value(), weight.value());
    }

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    inline
    void
    Krat2Polynom<Sm, Ss, Tm, Ts>::right_weight(const Ts& w,
					       const node_t* node_)
    {
      using namespace rat;

      Element<Sm, Tm> label;
      Element<Ss, Ts> weight;
      if (const Constant<Tm, Ts>* c =
	  dynamic_cast<const Constant<Tm, Ts>*>(node_)) {
	label = c->value_;
	weight = w;
      }
      else if (dynamic_cast<const One<Tm, Ts>*>(node_))
	weight = w;
      else if (!(dynamic_cast<const Zero<Tm, Ts>*>(node_))) {
	error = true;
	return ;
      }
      _p.insert(label.value(), weight.value());
    }

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    inline
    void
    Krat2Polynom<Sm, Ss, Tm, Ts>::constant(const Tm& m_)
    {
      _p.insert(m_, identity_value(SELECT(Ss), SELECT(Ts)));
    }

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    inline
    void
    Krat2Polynom<Sm, Ss, Tm, Ts>::one()
    {
      _p.insert(identity_value(SELECT(Sm), SELECT(Tm)),
		identity_value(SELECT(Ss), SELECT(Ts)));
    }

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    inline
    void
    Krat2Polynom<Sm, Ss, Tm, Ts>::zero()
    {
      _p.insert(identity_value(SELECT(Sm), SELECT(Tm)),
		zero_value(SELECT(Ss), SELECT(Ts)));
    }

    template <typename Sm, typename Ss, typename Tm, typename Ts>
    inline
    Element<Series<Ss, Sm>, polynom<Tm, Ts> >
    krat_to_polynom(const Element<Series<Ss, Sm>, rat::exp<Tm, Ts> >& exp)
    {
      Krat2Polynom<Sm, Ss, Tm, Ts> visitor;

      exp.value().accept(visitor);
      if (visitor.has_error())
	throw Unconvertible();

      Element<Series<Ss, Sm>, polynom<Tm, Ts> > ret(exp.set());
      ret = visitor.get_polynom();
      return ret;
    }
  }
}

#endif // VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_TO_POLYNOM_HXX