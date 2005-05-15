// xml_chooser.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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

#ifndef VCSN_XML_XML_CHOOSER_HH
# define VCSN_XML_XML_CHOOSER_HH

/**
 * @file xml_chooser.hh
 *
 * XML specialized class, providing methods to create <type> tag and to
 * create labels in the XML document.
 *
 * @see vcsn::xml::xml_converter, vcsn::xml::Node
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */
# include <string>
# include <sstream>
# include <xercesc/dom/DOM.hpp>

# include <vaucanson/xml/tools.hh>
# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/boolean_automaton.hh>
# include <vaucanson/z_automaton.hh>
# include <vaucanson/z_max_plus_automaton.hh>
# include <vaucanson/z_min_plus_automaton.hh>
# include <vaucanson/r_automaton.hh>
# include <vaucanson/fmp_transducer.hh>
# include <vaucanson/boolean_transducer.hh>


namespace vcsn
{
  namespace xml
  {
    /**
     * @brief Chooser base class. All specialization should inherit from it.
     *
     * @param S		Automaton structure type.
     * @param T		Automaton implementation type.
     *
     */
    template <class S, class T>
    struct xml_chooser_base
    {
      const char* choose_start_tag();
      void create_type_tag(const Element<S, T>&, xercesc::DOMDocument*,
			   xercesc::DOMElement*);
      void create_label(hedge_t, const Element<S, T>&, xercesc::DOMElement*);
      void create_initial_label(hstate_t, const Element<S, T>&,
				xercesc::DOMElement*);
      void create_final_label(hstate_t, const Element<S, T>&,
			      xercesc::DOMElement*);
    };

    /**
     * @brief Default Chooser class.
     *
     * @param S		Automaton structure type.
     * @param T		Automaton implementation type.
     *
     */
    template <class S, class T>
    struct xml_chooser : xml_chooser_base<S, T>
    {};

    /**
     * @brief Chooser specialization for automata.
     *
     * @param S		Automaton structure type.
     * @param T		Automaton implementation type.
     *
     */
    template <class S, class T>
    struct xml_chooser<Automata<S>, T> : xml_chooser_base<Automata<S>, T>
    {};

    /**
     * @brief Chooser specialization for transducers on P(B*).
     *
     * @param S		Automaton structure type.
     * @param T		Automaton implementation type.
     *
     */
    template <class S, class T>
    struct xml_chooser<Transducer<S>, T> : xml_chooser_base<Transducer<S>, T>
    {
      const char* choose_start_tag();
      void create_type_tag(const Element<Transducer<S>, T>&,
			   xercesc::DOMDocument*, xercesc::DOMElement*);
    };

    /**
     * @brief Chooser specialization for FMP transducers.
     *
     * @param S		Automaton semiring type.
     * @param T		Automaton implementation type.
     * @param M1	Automaton first monoid type.
     * @param M2	Automaton second monoid type.
     *
     */
# define TParmFMP						\
      template <class S, class T, class M1, class M2>
# define FMPtype							   \
      Automata<								   \
      vcsn::algebra::Series<S, vcsn::algebra::FreeMonoidProduct<M1, M2> >  \
      >, T

    TParmFMP
    struct xml_chooser<FMPtype> : xml_chooser_base<FMPtype>
    {
      const char* choose_start_tag();
      void create_type_tag(const Element<FMPtype>&, xercesc::DOMDocument*,
			   xercesc::DOMElement*);
    };


  } // !xml

} // !vcsn



# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/xml_chooser.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // VCSN_XML_XML_CHOOSER_HH

