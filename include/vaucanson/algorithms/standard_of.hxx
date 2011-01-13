// standard_of.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008, 2009, 2010, 2011
// The Vaucanson Group.
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

	Standard_OfVisitor(automaton_t& a) :
	  automata_set_(a.series()),
          auto_(&a)
	{
        }

	INHERIT_CONSTRUCTORS(this_class, Exp_, Auto_*, Dispatch_);

        // Could not use standard.hh functions because of the storing system.
        // No map needed here.
	MATCH__(Product, lhs, rhs)
	{
          AUTOMATON_TYPES(automaton_t);
	  this->match(lhs);

          hstate_t lhs_i = initial_;

          // Store final states and final values and clear it.
          typedef typename std::list<std::pair<hstate_t, series_set_elt_t> >
            list_fin_st_t;

          list_fin_st_t lhs_tmp;

          for_all_final_states(f, *auto_)
            lhs_tmp.push_back (std::pair<hstate_t, series_set_elt_t>
                                  (*f, auto_->get_final(*f)));
          auto_->clear_final();

	  this->match(rhs);

          // Restore the previously saved data.
          typedef std::list<hstate_t> list_st_t;

          list_st_t lhs_finals;

          for (typename list_fin_st_t::iterator i = lhs_tmp.begin();
               i != lhs_tmp.end();
               ++i)
          {
            auto_->set_final(i->first, i->second);
            lhs_finals.push_back (i->first);
          }

          concat_of_standard_inside(auto_->structure(),
				    *auto_, lhs_finals, initial_);

          initial_ = lhs_i;
          return auto_;
	}
	END

	MATCH__(Sum, lhs, rhs)
	{
          AUTOMATON_TYPES(automaton_t);
          typedef typename std::list<std::pair<hstate_t, series_set_elt_t> >
            list_fin_st_t;

          this->match(lhs);

          // Store lhs initial state.
          hstate_t left_i = initial_;

          // Store final states and final values and clear it.
          list_fin_st_t lhs_tmp;

          for_all_const_final_states(f, *auto_)
            lhs_tmp.push_back (std::pair<hstate_t, series_set_elt_t>
                               (*f, auto_->get_final(*f)));

          auto_->clear_final();

          this->match(rhs);

          // Restore the previously saved data.
          for (typename list_fin_st_t::iterator i = lhs_tmp.begin();
               i != lhs_tmp.end();
               ++i)
            auto_->set_final(i->first, i->second);

          sum_of_standard_inside(auto_->structure(),
				 *auto_, left_i, initial_);

          initial_ = left_i;
	  return auto_;
	}
	END

	MATCH_(Star, node)
	{
          AUTOMATON_TYPES(automaton_t);
	  this->match(node);

	  precondition(auto_->get_final(initial_).starable());

          typedef typename std::list<hstate_t> list_fin_st_t;

          // Store final states and final values and clear it.
          list_fin_st_t tmp;

          for_all_final_states(f, *auto_)
	    if (*f != initial_)
	      tmp.push_back(*f);

	  star_of_standard_inside(auto_->structure(),
				  *auto_, initial_, tmp);
	  return auto_;
	}
	END

	MATCH__(LeftWeight, w, node)
	{
	  const semiring_t&	semiring = automata_set_.series().semiring();
	  const semiring_elt_t	weight (semiring, w);
	  const series_set_elt_t ws(auto_->series(), weight);
	  this->match(node);

	  left_ext_mult_of_standard_inside(auto_->structure(),
					   *auto_, initial_, ws);
          return auto_;
	}
	END

	MATCH__(RightWeight, node, w)
	{
	  const semiring_t&	semiring = automata_set_.series().semiring();
	  const semiring_elt_t	weight (semiring, w);
	  this->match(node);

	  for (typename automaton_t::final_iterator
		 f, next = auto_->final().begin();
	       next != auto_->final().end();)
	  {
	    // We need to store the next iterator before using the
	    // current one to avoid an invalid iterator after having
	    // called set_final.  Indeed, set_final() can delete the
	    // iterator if its second parameter is the zero of the
	    // series.
	    f = next;
	    next++;
	    auto_->set_final(*f, auto_->get_final(*f) * weight);
	  }

	  return auto_;
	}
	END

	MATCH_(Constant, m)
	{
	  initial_ = auto_->add_state();
	  hstate_t last = initial_;
	  hstate_t new_f = initial_;

	  for (typename monoid_elt_value_t::const_iterator i = m.begin();
	       i != m.end(); ++i)
	  {
	    new_f = auto_->add_state();
	    auto_->add_letter_transition(last, new_f, *i);
	    last = new_f;
	  }
	  auto_->set_initial(initial_);
	  auto_->set_final(new_f);

	  return auto_;
	}
	END

	MATCH(Zero)
	{
	  initial_ = auto_->add_state();
	  auto_->set_initial(initial_);
	  return auto_;
	}
	END

	MATCH(One)
	{
	  initial_ = auto_->add_state();
	  auto_->set_initial(initial_);
	  auto_->set_final(initial_);
	  return auto_;
	}
        END

      private:
	automata_set_t automata_set_;
        // The automata used for construction
        hstate_t initial_;
        automaton_ptr_t auto_;

        typedef
        class
        {
          public:
            inline hstate_t operator[] (hstate_t a)
            {
              return a;
            }
        } ident_t;

        ident_t identity_;
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
      m(output);

    m.match(kexp);
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
