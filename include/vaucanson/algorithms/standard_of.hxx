// standard_of.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_STANDARD_OF_HXX
# define VCSN_ALGORITHMS_STANDARD_OF_HXX

# include <vaucanson/algorithms/standard_of.hh>

# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>
# include <vaucanson/algorithms/standard.hh>

# include <vaucanson/misc/usual_macros.hh>

namespace vcsn {

  namespace algebra {

    /*-------------------.
    | Standard_OfVisitor |
    `-------------------*/
    template <class Exp_,
	      class Auto_,
	      class Dispatch_>
    class Standard_OfVisitor :
	public algebra::KRatExpMatcher<
      Standard_OfVisitor<Exp_, Auto_, Dispatch_>,
      Exp_,
      Auto_*,
      Dispatch_
      >
    {
      public :
	typedef Auto_*					automaton_ptr_t;
	typedef Auto_					automaton_t;
	typedef typename automaton_t::set_t		automata_set_t;

	typedef typename automaton_t::series_set_t	series_set_t;
	typedef typename automaton_t::monoid_t		monoid_t;
	typedef typename automaton_t::semiring_t	semiring_t;

	typedef typename automaton_t::series_set_elt_t	series_set_elt_t;
	typedef typename automaton_t::monoid_elt_t	monoid_elt_t;
	typedef typename automaton_t::semiring_elt_t	semiring_elt_t;

	typedef typename automaton_t::hstate_t		hstate_t;
	typedef typename automaton_t::htransition_t	htransition_t;

	typedef typename Exp_::monoid_elt_value_t	monoid_elt_value_t;
	typedef typename Exp_::semiring_elt_value_t	semiring_elt_value_t;

	typedef Standard_OfVisitor<Exp_, Auto_, Dispatch_>	this_class;
	typedef algebra::KRatExpMatcher<this_class, Exp_, Auto_*, Dispatch_>
	parent_class;
	typedef typename parent_class::return_type	return_type;

      public :

	Standard_OfVisitor(const series_set_t& series) :
	  automata_set_(series)
	{}

	INHERIT_CONSTRUCTORS(this_class, Exp_, Auto_*, Dispatch_);

	MATCH__(Product, lhs, rhs)
	{
	  automaton_ptr_t tmp_	= match(rhs);
	  automaton_ptr_t auto_ = match(lhs);
	  concat_of_standard_here(*auto_, *tmp_);
	  delete (tmp_);
	  return auto_;
	}
	END

	MATCH__(Sum, lhs, rhs)
	{
	  automaton_ptr_t tmp_	= match(rhs);
	  automaton_ptr_t auto_ = match(lhs);
	  union_of_standard_here(*auto_, *tmp_);
	  delete (tmp_);
	  return auto_;
	}
	END

	MATCH_(Star, node)
	{
	  automaton_ptr_t stared = match(node);
	  star_of_standard_here(*stared);
	  return stared;
	}
	END

	MATCH__(LeftWeight, w, node)
	{
	  const semiring_t&	semiring = automata_set_.series().semiring();
	  const semiring_elt_t	weight (semiring, w);
	  automaton_ptr_t	auto_ = match(node);

	  for (typename automaton_t::initial_iterator i = auto_->initial().begin();
	       i != auto_->initial().end();
	       ++i)
	  {
            std::list<htransition_t>	e;
            for (typename automaton_t::delta_iterator j(auto_->value(), *i);
                 ! j.done();
                 j.next())
              e.push_back(*j);
            for (typename std::list<htransition_t>::const_iterator j = e.begin();
                 j != e.end();
                 ++j)
	    {
	      // FIXME: The following code is only correct when labels are
	      // FIXME: series. We should add meta code to make the code
	      // FIXME: fail at runtime when this function is called
	      // FIXME: with label as letters. However, we cannot afford
	      // FIXME: an error at compile time, because the rest
	      // FIXME: of this matcher is valid for Boolean automata when
	      // FIXME: labels are letter.
	      typedef typename automaton_t::label_t	label_t;
	      typedef Element<series_set_t, label_t>	label_elt_t;

	      label_elt_t label (automata_set_.series(), auto_->label_of(*j));
	      label  = weight * label;

	      hstate_t dst = auto_->dst_of(*j);
	      auto_->del_transition(*j);

	      if (label != zero_as<label_t>::of(automata_set_.series()))
		auto_->add_transition(*i, dst, label.value());
	    }
	    auto_->set_final(*i, weight * auto_->get_final(*i));
	  }
	  return auto_;
	}
	END

	MATCH__(RightWeight, node, w)
	{
	  const semiring_t&	semiring = automata_set_.series().semiring();
	  const semiring_elt_t	weight (semiring, w);
	  automaton_ptr_t	auto_ = match(node);

	  for (typename automaton_t::final_iterator f, next = auto_->final().begin();
	       next != auto_->final().end();)
	  {
	    //We need to store the next iterator before using the current one
	    //to avoid an invalid iterator after having called set_final.
	    //Indeed, set_final can delete the iterator if its second parameter
	    //is the zero of the serie.
	    f = next;
	    next++;
	    auto_->set_final(*f, auto_->get_final(*f) * weight);
	  }
	  return auto_;
	}
	END

	MATCH_(Constant, m)
	{
	  automaton_ptr_t auto_ = new automaton_t(automata_set_);
	  hstate_t new_i = auto_->add_state();
	  hstate_t last = new_i;
	  hstate_t new_f = new_i;
	  for (typename monoid_elt_value_t::const_iterator i = m.begin();
	       i != m.end(); ++i)
	  {
	    new_f = auto_->add_state();
	    auto_->add_letter_transition(last, new_f, *i);
	    last = new_f;
	  }
	  auto_->set_initial(new_i);
	  auto_->set_final(new_f);
	  return auto_;
	}
	END

	MATCH(Zero)
	{
	  automaton_ptr_t auto_ = new automaton_t(automata_set_);
	  hstate_t s = auto_->add_state();
	  auto_->set_initial(s);
	  return auto_;
	}
	END

	MATCH(One)
	{
	  automaton_ptr_t auto_ = new automaton_t(automata_set_);
	  hstate_t new_i = auto_->add_state();
	  auto_->set_initial(new_i);
	  auto_->set_final(new_i);
	  return auto_;
	}
      END

      private:
	automata_set_t automata_set_;
    };

  }

  template <typename A,
	    typename Output,
	    typename Exp>
  void
  do_standard_of(const AutomataBase<A>&,
		 Output& output,
		 const Exp& kexp)
  {
    algebra::Standard_OfVisitor<Exp, Output, algebra::DispatchFunction<Exp> >
      m(output.structure().series());
    Output* res = m.match(kexp);
    output = *res;
    delete res;
  }

  template<typename A,
	   typename T,
	   typename Exp>
  void
  standard_of(Element<A, T>& out,
	      const Exp& kexp)
  {
    do_standard_of(out.structure(), out, kexp);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_STANDARD_OF_HXX
