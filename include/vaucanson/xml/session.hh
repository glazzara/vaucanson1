// session.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
#ifndef VCSN_XML_SESSION_HH
# define VCSN_XML_SESSION_HH

# include <xercesc/util/PlatformUtils.hpp>
# include <xercesc/dom/DOM.hpp>

# include <list>

# include <vaucanson/xml/dynamic.hh>
# include <vaucanson/xml/error_handler.hh>

# include <vaucanson/automata/concept/automata_base.hh>

/** @addtogroup xml *//** @{ */
/**
 * @file session.hh
 *
 * XML sessions tools.
 *
 * @author Valentin David <valentin@lrde.epita.fr>
 */
/** @} */

namespace vcsn
{

  namespace xml
  {

    using xercesc::DOMDocument;
    using xercesc::DOMBuilder;

    /** @addtogroup xml *//** @{ */

    /// Session handler.
    class XmlSession
    {
    public:
      DOMDocument*		doc_;
      myDOMErrorHandler*	err_;
      DOMBuilder*		parser_;
      std::list<DOMElement*>	roots_;
    public:
      /// Default constructor.
      XmlSession();
      ~XmlSession();

      //      template <typename T>
      /// Pop operator.
      void operator << (const xml_automaton_t&);
      /// Queue operator.
      void operator >> (xml_automaton_t&);
    protected:
      // States must be unique in each session.
      // Keep tracks of the session states.
      std::set<std::string>			states;
      // Keep track of the renamings.
      std::map<std::string, std::string>	states_map;
    };

    /// Read operator.
    std::ostream&
    operator << (std::ostream&, const XmlSession&);

    /// Write operator.
    std::istream&
    operator >> (std::istream&, XmlSession&);

    template<typename S, typename T>
    XmlSession&
    op_rout(const AutomataBase<S>&,
	    XmlSession&,
	    const T&);


    template <class S, class T>
    XmlSession&
    op_rin(AutomataBase<S>& structure,
	   XmlSession& st,
	   T& v);

    /** @} */

  } // End of namespace xml.

} // End of namespace vcsn.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/session.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_XML_SESSION_HH
