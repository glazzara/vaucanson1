// standard_of.hxx: this file is part of the Vaucanson project.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGORITHMS_STANDARD_OF_HXX
# define VCSN_ALGORITHMS_STANDARD_OF_HXX

# include <vaucanson/algorithms/standard_of.hh>

# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>
# include <vaucanson/algorithms/standard.hh>

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
    typedef typename automaton_t::set_t			automata_set_t;

    typedef typename automaton_t::series_set_t		series_set_t;
    typedef typename automaton_t::monoid_t		monoid_t;
    typedef typename automaton_t::semiring_t		semiring_t;

    typedef typename automaton_t::series_set_elt_t	series_set_elt_t;
    typedef typename automaton_t::monoid_elt_t		monoid_elt_t;
    typedef typename automaton_t::semiring_elt_t	semiring_elt_t;

    typedef typename Exp_::monoid_elt_value_t		monoid_elt_value_t;
    typedef typename Exp_::semiring_elt_value_t		semiring_elt_value_t;

    typedef Standard_OfVisitor<Exp_, Auto_, Dispatch_>	this_class;
    typedef algebra::KRatExpMatcher<this_class, Exp_, Auto_*, Dispatch_>
							parent_class;
    typedef typename parent_class::return_type          return_type;

  public :

    Standard_OfVisitor(const series_set_t& series) :
      automata_set_(series)
    {}

    INHERIT_CONSTRUCTORS(this_class, Exp_, Auto_*, Dispatch_);

    MATCH__(Product, lhs, rhs)
    {
      automaton_ptr_t tmp_  = match(rhs);
      automaton_ptr_t auto_ = match(lhs);
      concat_of_standard_here(*auto_, *tmp_);
      delete (tmp_);
      return auto_;
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      automaton_ptr_t tmp_  = match(rhs);
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
      const semiring_t&		semiring = automata_set_.series().semiring();
      const semiring_elt_t	weight (semiring, w);
      automaton_ptr_t		auto_ = match(node);

      for (typename automaton_t::initial_iterator i = auto_->initial().begin();
	   i != auto_->initial().end();
	   ++i)
	{
	  std::list<hedge_t>	e;
	  auto_->deltac(e, *i, delta_kind::edges());
	  for (typename std::list<hedge_t>::const_iterator j = e.begin();
	       j != e.end();
	       ++j)
	    {
	      // FIXME: The following code is only correct when labels are
	      // FIXME: series. We should add meta code to make the code
	      // FIXME: fail at runtime when this function is called
	      // FIXME: with label as letters. However, we cannot afford
	      // FIXME: doing an error at compile time, because the rest
	      // FIXME: of this matcher is valid on Boolean automata with
	      // FIXME: label as letter.
	      typedef typename automaton_t::label_t	label_t;
	      typedef Element<series_set_t, label_t>	label_elt_t;

	      label_elt_t label (automata_set_.series(), auto_->label_of(*j));
	      label  = weight * label;

	      hstate_t				aim = auto_->aim_of(*j);
	      auto_->del_edge(*j);

	      if (label != zero_as<label_t>::of(automata_set_.series()))
		auto_->add_edge(*i, aim, label.value());
	    }
	  auto_->set_final(*i, weight * auto_->get_final(*i));
	}
      return auto_;
    }
    END

    MATCH__(RightWeight, node, w)
    {
      const semiring_t&		semiring = automata_set_.series().semiring();
      const semiring_elt_t	weight (semiring, w);
      automaton_ptr_t		auto_ = match(node);

      for (typename automaton_t::final_iterator i = auto_->final().begin();
	   i != auto_->final().end();
	   ++i)
	auto_->set_final(*i, auto_->get_final(*i) * weight);
      return auto_;
    }
    END

    MATCH_(Constant, m)
    {
      automaton_ptr_t auto_ = new automaton_t(automata_set_);
      hstate_t new_i = auto_->add_state();
      hstate_t last = new_i;
      hstate_t new_f;
      for (typename monoid_elt_value_t::const_iterator i = m.begin();
	   i != m.end(); ++i)
	{
	  new_f = auto_->add_state();
	  auto_->add_letter_edge(last, new_f, *i);
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
    output = *m.match(kexp);
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

  template <typename A, typename T, typename Exp>
  Element<A, T>
  standard_of(const Exp& e)
  {
    A automata_structure(e.structure());
    Element<A, T> out(automata_structure);
    standard_of(out, e);
    return out;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_STANDARD_OF_HXX
