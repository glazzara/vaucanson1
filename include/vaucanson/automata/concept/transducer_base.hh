// transducer_base.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey
// and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_BASE_HH
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_BASE_HH

# include <iterator>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/internal/traits.hh>
# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*! \addtogroup automata */  /* @{ */
  /*! \addtogroup concept  */  /* @{ */

  /*---------------------.
  | TransducerBase<Self> |
  `----------------------*/
  //! The most general concept of transducer. 
  /*! It denotes the set of transducer with multiplicity over a fixed
    semiring and a fixed free couple of monoid. 
    Note that this class is abstract
    in the hierarchy.
  */
  template <typename Self>
  struct TransducerBase
    : AutomataBase<Self>
  {
  public:
    //! The type of the series set associated with the automaton.
    typedef typename traits::virtual_types<Self>::series_t  series_t;

  protected:
    //! The default constructor is protected since it is an abstract class.
    TransducerBase();

    //! The copy constructor is protected since it is an abstract class.
    TransducerBase(const TransducerBase& other);
  };

  // traits for transducer implementation.
  template <typename T>
  struct transducer_traits
  {
     typedef traits::undefined_type input_monoid_elt_value_t;
     typedef traits::undefined_type output_monoid_elt_value_tt;
     typedef traits::undefined_type output_weight_value_tt;
  };

  template <typename T>
  struct extension_traits
  {
    typedef traits::undefined_type ret;
  };

  /*-------------------------------------.
  | MetaElement<TransducerBase<Self>, T> |
  `-------------------------------------*/
  //! Services of every element of the transducer set. 
  /*! MetaElement<TransducerBase<Self>, T> defines the interface of
    every transducer that is the result of the interaction of a
    structural element (TransducerBase<Self>) and an implementation T.
    
   */

  template <typename Self, typename T>
  struct MetaElement<TransducerBase<Self>, T>
    : MetaElement<AutomataBase<Self>, T>
  {
    /*! type of the interface of an automaton. */
    typedef MetaElement<TransducerBase<Self>, T>	      self_t;

    /*! type of the mother class. */
    typedef MetaElement<AutomataBase<Self>, T>		      mother_t;

    /*! type of the output. */
    typedef typename mother_t::weight_t output_serie_t;

    /*! type of the output monoid element implementation. */
    typedef typename automaton_traits<T>::weight_value_t weight_value_t;
    typedef typename series_traits<weight_value_t>::monoid_value_t 
						output_monoid_elt_value_t;

    /*! type of the output monoid. */
    typedef typename weights_t::monoid_t	output_monoid_t;

    /*! type of the output monoid element. */
    typedef Element<output_monoid_t, output_monoid_elt_value_t>
						output_monoid_elt_t;

    typedef typename output_monoid_t::letter_t output_letter_t;

    /*! type of the input monoid element implementation. */
    typedef typename mother_t::monoid_elt_value_t input_monoid_elt_value_t;

    /*! type of the input monoid. */
    typedef typename mother_t::monoid_t		input_monoid_t;

    /* type of the input monoid element. */
    typedef Element<input_monoid_t, input_monoid_elt_value_t> 
						input_monoid_elt_t;

    typedef typename input_monoid_t::letter_t input_letter_t;

    /*! type of the output weight implementation. */
    typedef typename series_traits<weight_value_t>::weight_value_t
    output_weight_value_t;
    
    /*! type of the output weights. */
    typedef typename weights_t::weights_t	output_weights_t;

    /*! type of the output weight. */
    typedef Element<output_weights_t, output_weight_value_t>
    output_weight_t;

    /*! return the input of an edge */
    input_monoid_elt_t input_of(hedge_t) const;

    /*! return the output of an edge */
    output_serie_t output_of(hedge_t) const;

    /*! add an edge specified as an input word, an output word and
      a weight linked to it. */
    hedge_t add_io_edge(hstate_t, hstate_t, input_monoid_elt_t, 
			output_monoid_elt_t, 
			output_weight_t = output_weight_t());

    /*! add an edge specified using an input letter, an output letter and
      a weight linked to it. */
    hedge_t add_io_edge(hstate_t, hstate_t, input_letter_t, output_letter_t,
			output_weight_t = output_weight_t());

    /*! add an only-output edge (epsilon as input). */
    hedge_t add_o_edge(hstate_t, hstate_t, output_letter_t, 
		       output_weight_t = output_weight_t());

    /*! add an only-input edge (epsilon as output). */
    hedge_t add_i_edge(hstate_t, hstate_t, input_letter_t, 
		       output_weight_t = output_weight_t());

  protected:
    MetaElement();
    MetaElement(const MetaElement& other);
  };


  /*! @} @} */

} // vcsn

# include <vaucanson/automata/concept/transducer_base.hxx>

#endif // VCSN_AUTOMATA_CONCEPT_TRANSDUCER_BASE_HH
