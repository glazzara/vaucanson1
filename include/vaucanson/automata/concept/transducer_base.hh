// transducer_base.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_BASE_HH
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_BASE_HH

# include <iterator>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/design_pattern/predecls.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {

  /** @addtogroup automata */  /** @{ */
  /** @addtogroup concept  */  /** @{ */

  /*---------------------.
  | TransducerBase<Self> |
  `----------------------*/
  /// The most general concept of transducer. 
  /** It denotes the set of transducer with multiplicity over a fixed
    semiring and a fixed free couple of monoid. 
    Note that this class is abstract
    in the hierarchy.
  */
  template <typename Self>
  struct TransducerBase
    : AutomataBase<Self>
  {
  public:
    /// The type of the series set associated with the automaton.
    typedef typename virtual_types<Self>::series_t  series_t;

  protected:
    /// The default constructor is protected since it is an abstract class.
    TransducerBase();

    /// The copy constructor is protected since it is an abstract class.
    TransducerBase(const TransducerBase& other);
  };

  // traits for transducer implementation.
  template <typename T>
  struct transducer_traits
  {
    typedef undefined_type input_monoid_elt_value_t;
    typedef undefined_type output_monoid_elt_value_t;
  };

  template <typename T>
  struct extension_traits
  {
    typedef undefined_type ret;
  };

  template <class S, class T>
  struct projection_traits
  {
    typedef undefined_type	ret;
  };

  template <class T>
  struct output_projection_traits
  {
    typedef undefined_type	ret;
  };

  /*-------------------------------------.
  | MetaElement<TransducerBase<Self>, T> |
  `-------------------------------------*/
  /// Services of every element of the transducer set. 
  /** MetaElement<TransducerBase<Self>, T> defines the interface of
    every transducer that is the result of the interaction of a
    structural element (TransducerBase<Self>) and an implementation T.
    
   */

  template <typename Self, typename T>
  struct MetaElement<TransducerBase<Self>, T>
    : MetaElement<AutomataBase<Self>, T>
  {
    /** type of the interface of an automaton. */
    typedef MetaElement<AutomataBase<Self>, T>		      automaton_t;

    /** type the series set from which is build the automaton. */
    INHERIT_TYPEDEF_(automaton_t, series_t);

    /** type of the implementation of series that holds the automaton. */
    INHERIT_TYPEDEF_(automaton_t, series_value_t);

    /** type of the element of the set of series that holds the automaton. */
    INHERIT_TYPEDEF_(automaton_t, series_elt_t);

    INHERIT_TYPEDEF_(automaton_t, series_elt_t);

    /** type of the free monoid. */
    INHERIT_TYPEDEF_(automaton_t, monoid_t);

    /** type of the free monoid element. */
    INHERIT_TYPEDEF_(automaton_t, monoid_elt_t);

    /** type of the implementation of a word. */
    INHERIT_TYPEDEF_(automaton_t, monoid_elt_value_t);

    /** type of the letter. */
    INHERIT_TYPEDEF_(automaton_t, letter_t);

    /** type of the semiring set. */
    INHERIT_TYPEDEF_(automaton_t, semiring_t);

    /** type of the free monoid element. */
    INHERIT_TYPEDEF_(automaton_t, semiring_elt_t);

    /** type of the implementation of a semiring_elt. */
    INHERIT_TYPEDEF_(automaton_t, semiring_elt_value_t);

    /** type of additional information that is aggregated to the automaton. */
    INHERIT_TYPEDEF_(automaton_t, tag_t);

    /** type of the label of the automaton implementation. */
    INHERIT_TYPEDEF_(automaton_t, label_t);

    /** type of the states container. */
    INHERIT_TYPEDEF_(automaton_t, states_t);

    /** type of the iterator over the states set. */
    INHERIT_TYPEDEF_(automaton_t, state_iterator);

    /** type of the edges set. */
    INHERIT_TYPEDEF_(automaton_t, edges_t);

    /** type of the iterator over the edges. */
    INHERIT_TYPEDEF_(automaton_t, edge_iterator);

    /** type of the initial application. */
    INHERIT_TYPEDEF_(automaton_t, initial_t);

    /** type of the initial application support. */
    INHERIT_TYPEDEF_(automaton_t, initial_support_t);

    /** type of the iterator of the initial application support. */
    INHERIT_TYPEDEF_(automaton_t, initial_iterator);

    /** type of the final application. */
    INHERIT_TYPEDEF_(automaton_t, final_t);

    /** type of the iterator of the final application support. */
    INHERIT_TYPEDEF_(automaton_t, final_iterator);

    /** type of the interface of an automaton. */
    typedef MetaElement<TransducerBase<Self>, T>	      self_t;

    /** type of the mother class. */
    typedef MetaElement<AutomataBase<Self>, T>		      mother_t;

    /** type of the output. */
    typedef typename mother_t::semiring_elt_t output_series_elt_t;

    /** type of the output monoid element implementation. */
    typedef typename automaton_traits<T>::semiring_elt_value_t semiring_elt_value_t;
    typedef typename algebra::series_traits<semiring_elt_value_t>::monoid_elt_value_t 
						output_monoid_elt_value_t;

    /** type of the output monoid. */
    typedef typename semiring_t::monoid_t	output_monoid_t;

    /** type of the output monoid element. */
    typedef Element<output_monoid_t, output_monoid_elt_value_t>
						output_monoid_elt_t;

    typedef typename output_monoid_t::letter_t output_letter_t;

    /** type of the input monoid element implementation. */
    typedef typename mother_t::monoid_elt_value_t input_monoid_elt_value_t;

    /** type of the input monoid. */
    typedef typename mother_t::monoid_t		input_monoid_t;

    /* type of the input monoid element. */
    typedef Element<input_monoid_t, input_monoid_elt_value_t> 
						input_monoid_elt_t;

    typedef typename input_monoid_t::letter_t input_letter_t;

    /** type of the output weight implementation. */
    typedef typename algebra::series_traits<semiring_elt_value_t>::semiring_elt_value_t
    output_semiring_elt_value_t;
    
    /** type of the output semiring. */
    typedef typename semiring_t::semiring_t	output_semiring_t;

    /** type of the output weight. */
    typedef Element<output_semiring_t, output_semiring_elt_value_t>
    output_semiring_elt_t;

    /** return the input of an edge */
    input_monoid_elt_t input_of(hedge_t) const;

    /** return the output of an edge */
    output_series_elt_t output_of(hedge_t) const;

    /** add an edge specified as an input word, an output word and
      a weight linked to it. */
    hedge_t add_io_edge(hstate_t, hstate_t, input_monoid_elt_t, 
			output_monoid_elt_t, 
			output_semiring_elt_t = output_semiring_elt_t());

    /** add an edge specified using an input letter, an output letter and
      a weight linked to it. */
    hedge_t add_io_edge(hstate_t, hstate_t, input_letter_t, output_letter_t,
			output_semiring_elt_t = output_semiring_elt_t());

    /** add an only-output edge (epsilon as input). */
    hedge_t add_o_edge(hstate_t, hstate_t, output_letter_t, 
		       output_semiring_elt_t = output_semiring_elt_t());

    /** add an only-input edge (epsilon as output). */
    hedge_t add_i_edge(hstate_t, hstate_t, input_letter_t, 
		       output_semiring_elt_t = output_semiring_elt_t());

  protected:
    MetaElement();
    MetaElement(const MetaElement& other);
  };


  /** @} @} */

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/automata/concept/transducer_base.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_AUTOMATA_CONCEPT_TRANSDUCER_BASE_HH
