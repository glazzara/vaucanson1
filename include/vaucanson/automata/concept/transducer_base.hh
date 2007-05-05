// transducer_base.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_BASE_HH
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_BASE_HH

# include <iterator>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/design_pattern/predecls.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>

namespace vcsn {

  /** @addtogroup automata */  /** @{ */
  /** @addtogroup concept  */  /** @{ */

  /*---------------------.
  | TransducerBase<Self> |
  `----------------------*/
  /** The most general concept of transducer.
   *
   * It denotes the set of transducer with multiplicity over a fixed
   * semiring and a fixed free couple of monoid.
   * Note that this class is abstract in the hierarchy.
   */
  template <typename Self>
  struct TransducerBase
    : AutomataBase<Self>
  {
    public:
      /// The type of the series set associated with the automaton.
      typedef typename virtual_types<Self>::series_set_t  series_set_t;

    protected:
      /// The default constructor is protected since it is an abstract class.
      TransducerBase();

      /// The copy constructor is protected since it is an abstract class.
      TransducerBase(const TransducerBase& other);
  };

  /// Traits for transducer implementation.
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

  /*-----------------------------------.
  | virtual_types<AutomataBase<Self> > |
  `-----------------------------------*/
  template <class S>
  struct virtual_types<TransducerBase<S> >
    : virtual_types<AutomataBase<S> >
  { };

  /*------------------------------------.
  | dynamic_traits<AutomataBase<Self> > |
  `------------------------------------*/
  template <class S>
  struct dynamic_traits<TransducerBase<S> >
    : dynamic_traits<AutomataBase<S> >
  { };

  /*-------------------------------------.
  | MetaElement<TransducerBase<Self>, T> |
  `-------------------------------------*/
  /** Services of every element of the transducer set.
   *
   * MetaElement<TransducerBase<Self>, T> defines the interface of
   * every transducer that is the result of the interaction of a
   * structural element (TransducerBase<Self>) and an implementation T.
   */

  template <typename Self, typename T>
  struct MetaElement<TransducerBase<Self>, T>
    : MetaElement<AutomataBase<Self>, T>
  {
      /// Type of the interface of an automaton.
      typedef MetaElement<TransducerBase<Self>, T> self_t;

      /// Type of the super class.
      typedef MetaElement<AutomataBase<Self>, T> super_t;

      /// Type of the interface of an automaton.
      typedef MetaElement<AutomataBase<Self>, T> automaton_t;

      /// Type the series set from which is build the automaton.
      IMPORT_TYPEDEF_(automaton_t, series_set_t);

      /// Type of the implementation of series that holds the automaton.
      IMPORT_TYPEDEF_(automaton_t, series_set_elt_value_t);

      /// Type of the element of the set of series that holds the automaton.
      IMPORT_TYPEDEF_(automaton_t, series_set_elt_t);

      /// Type of the free monoid.
      IMPORT_TYPEDEF_(automaton_t, monoid_t);

      /// Type of the free monoid element.
      IMPORT_TYPEDEF_(automaton_t, monoid_elt_t);

      /// Type of the implementation of a word.
      IMPORT_TYPEDEF_(automaton_t, monoid_elt_value_t);

      /// Type of the letter.
      IMPORT_TYPEDEF_(automaton_t, letter_t);

      /// Type of the semiring set.
      IMPORT_TYPEDEF_(automaton_t, semiring_t);

      /// Type of the free monoid element.
      IMPORT_TYPEDEF_(automaton_t, semiring_elt_t);

      /// Type of the implementation of a semiring_elt.
      IMPORT_TYPEDEF_(automaton_t, semiring_elt_value_t);

      /// Type of additional information that is aggregated to the automaton.
      IMPORT_TYPEDEF_(automaton_t, tag_t);

      /// Type of the label of the automaton implementation.
      IMPORT_TYPEDEF_(automaton_t, label_t);

      /// Type of the states container.
      IMPORT_TYPEDEF_(automaton_t, states_t);

      /// Type of the iterator over the states set.
      IMPORT_TYPEDEF_(automaton_t, state_iterator);

      /// Type of the transitions set.
      IMPORT_TYPEDEF_(automaton_t, transitions_t);

      /// Type of the iterator over the transitions.
      IMPORT_TYPEDEF_(automaton_t, transition_iterator);

      /// Type of the initial application support.
      IMPORT_TYPEDEF_(automaton_t, initial_support_t);

      /// Type of the iterator of the initial application support.
      IMPORT_TYPEDEF_(automaton_t, initial_iterator);

      /// Type of the final application support.
      IMPORT_TYPEDEF_(automaton_t, final_support_t);

      /// Type of the iterator of the final application support.
      IMPORT_TYPEDEF_(automaton_t, final_iterator);

      /// Type of the output.
      typedef typename super_t::semiring_elt_t output_series_set_elt_t;

      typedef typename algebra::series_traits<semiring_elt_value_t>::monoid_elt_value_t
      output_monoid_elt_value_t;

      /// Type of the output monoid.
      typedef typename semiring_t::monoid_t	output_monoid_t;

      /// Type of the output monoid element.
      typedef Element<output_monoid_t, output_monoid_elt_value_t>
      output_monoid_elt_t;

      typedef typename output_monoid_t::letter_t output_letter_t;

      /// Type of the input monoid element implementation.
      typedef typename super_t::monoid_elt_value_t input_monoid_elt_value_t;

      /// Type of the input monoid.
      typedef typename super_t::monoid_t		input_monoid_t;

      /// Type of the input monoid element.
      typedef Element<input_monoid_t, input_monoid_elt_value_t>
      input_monoid_elt_t;

      typedef typename input_monoid_t::letter_t input_letter_t;

      /// Type of the output weight implementation.
      typedef typename algebra::series_traits<semiring_elt_value_t>::semiring_elt_value_t
      output_semiring_elt_value_t;

      /// Type of the output semiring.
      typedef typename semiring_t::semiring_t	output_semiring_t;

      /// Type of the output weight.
      typedef Element<output_semiring_t, output_semiring_elt_value_t>
      output_semiring_elt_t;

      /// Return the input of a transition
      input_monoid_elt_t input_of(typename automaton_traits<T>::htransition_t) const;

      /// Return the output of a transition
      output_series_set_elt_t output_of(typename automaton_traits<T>::htransition_t) const;

      /** Add a transition specified as an input word value and
       * output word value. */
      typename automaton_traits<T>::htransition_t
      add_io_transition(typename automaton_traits<T>::hstate_t, typename automaton_traits<T>::hstate_t,
			input_monoid_elt_value_t,
			output_monoid_elt_value_t,
			output_semiring_elt_t = output_semiring_elt_t());

      /** Add a transition specified using an input letter, an output letter and
       * a weight linked to it. */
      typename automaton_traits<T>::htransition_t
      add_io_transition(typename automaton_traits<T>::hstate_t, typename automaton_traits<T>::hstate_t, input_letter_t, output_letter_t,
			output_semiring_elt_t = output_semiring_elt_t());

      /// Add an only-output transition (epsilon as input).
      typename automaton_traits<T>::htransition_t
      add_o_transition(typename automaton_traits<T>::hstate_t, typename automaton_traits<T>::hstate_t, output_letter_t,
		       output_semiring_elt_t = output_semiring_elt_t());

      /// Add an only-input transition (epsilon as output).
      typename automaton_traits<T>::htransition_t
      add_i_transition(typename automaton_traits<T>::hstate_t, typename automaton_traits<T>::hstate_t, input_letter_t,
		       output_semiring_elt_t = output_semiring_elt_t());

      /// Set a weight on the final transition, specifying an output_monoid value.
      void set_o_final(typename automaton_traits<T>::hstate_t, output_monoid_elt_value_t);

      /** Set a weight on the initial transition, specifying an output_monoid
       value. */
      void set_o_initial(typename automaton_traits<T>::hstate_t, output_monoid_elt_value_t);

    protected:
      MetaElement();
      MetaElement(const MetaElement& other);
  };


  /** @} */
  /** @} */

} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/automata/concept/transducer_base.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_CONCEPT_TRANSDUCER_BASE_HH
