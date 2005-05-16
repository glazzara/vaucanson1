// tools.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_TOOLS_TOOLS_HH
# define VCSN_XML_TOOLS_TOOLS_HH

/**
 * @file tools.hh
 *
 * Some useful utility functions.
 *
 *
 * @see vcsn::xml::xml_converter, vcsn::xml::Node
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */
# include <xercesc/dom/DOM.hpp>
# include <xercesc/framework/MemBufFormatTarget.hpp>
# include <xercesc/util/XMLString.hpp>
# include <xercesc/util/PlatformUtils.hpp>

# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/tools/usual_macros.hh>
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
    namespace tools
    {
      template <class S>
      const char* get_monoid_type(const S&);

      template <class S>
      const char* get_semiring_operations(const S&);

      template <class S, class T>
      const char* get_semiring_set(const S&, const T&);

      template <class S, class T, class U>
      void add_label(xercesc::DOMElement*, const Element<S, T>&, const U&);

      template <class M>
      xercesc::DOMElement* create_monoid(const M& monoid,
					 xercesc::DOMDocument* doc,
					 xercesc::DOMElement* elt);
      template <class A>
      void create_alphabet(const A& alphabet, xercesc::DOMDocument* doc,
			   xercesc::DOMElement* root);
      template <class A, class S>
      xercesc::DOMElement* create_semiring(const A& aut,
					   const S& semiring,
					   xercesc::DOMDocument* doc,
					   xercesc::DOMElement* elt);

      template <class T>
      typename T::series_set_elt_t get_series(xercesc::DOMElement*, T&);

      template <class U, class V>
      void insert_letter(Element<vcsn::algebra::AlphabetSet<U>, V>&,
			 const std::string&);

      template <class U>
      void ensure_monoid_type(const xercesc::DOMElement*, const U&);

      template <class T, class U>
      void ensure_semiring_type(const xercesc::DOMElement*, const T&,
				const U&);

      template <class OStream>
      void print_document(const xercesc::DOMElement*, OStream&);

    } // ! tools

  } // ! xml

} // ! vcsn

# define TParm					\
    template <class S, class T>
# define TParmFMP					\
      template <class S, class T, class M1, class M2>
# define AUTtype				\
    Element<Automata<S>, T>
# define TRANStype				\
    Element<Transducer<S>, T>
# define FMPtype      							  \
    Element<								  \
      Automata<								  \
      vcsn::algebra::Series<S, vcsn::algebra::FreeMonoidProduct<M1, M2> > \
      >, T								  \
    >


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/tools.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_XML_TOOLS_TOOLS_HH
