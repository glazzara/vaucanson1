// xml_automaton.hh: this file is part of the Vaucanson project.
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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_XML_XML_AUTOMATON_HH
# define VCSN_XML_XML_AUTOMATON_HH

# include <vaucanson/xml/types.hh>

# include <vaucanson/misc/support.hh>
# include <vaucanson/xml/infos.hh>
# include <vaucanson/xml/xml_value.hh>

# include <xercesc/dom/DOM.hpp>

/** @addtogroup xml *//** @{ */
/**
 * @file xml_automaton.hh
 *
 * XML automaton implementation.
 *
 * @author Valentin David <valentin@lrde.epita.fr>
 */
/** @} */

namespace vcsn
{

  namespace xml
  {

    using xercesc::DOMDocument;
    using xercesc::DOMElement;
    using xercesc::DOMNode;

    /** @addtogroup xml *//** @{ */

    /// Xml automaton implementation
    class XmlAutomaton
    {
    public:
      typedef xml_value_t	    label_t;
      typedef XmlAutomaton	    self_t;

    public:
      /// Default constructor.
      XmlAutomaton();


      /// Read constructor.
      XmlAutomaton(DOMElement* elt);

      bool			operator == (const XmlAutomaton& rhs) const;

      hstate_t			add_state(hstate_t i = 0);
      hstate_t			add_state(const std::string&);
      hstate_t		        add_state(hstate_t, const std::string&);
      void			del_state(hstate_t);


      // for internal only
      DOMElement*		add_state_elt(hstate_t);
      DOMElement*		add_state_elt(hstate_t, const std::string&);

      bool			has_state(hstate_t) const;

      hedge_t			add_edge(hstate_t, hstate_t, const label_t&);
      void			del_edge(hedge_t);

      bool			has_edge(hedge_t) const;

      hstate_t			origin_of(hedge_t) const;
      hstate_t		    	aim_of(hedge_t) const;
      label_t		    	label_of(hedge_t) const;

      DOMElement*		set_initial(hstate_t,
					    const xml_value_t&,
					    const xml_value_t&);
      xml_value_t		get_initial(hstate_t, const xml_value_t&);
      void			clear_initial();

      DOMElement*		set_final(hstate_t,
					  const xml_value_t&,
					  const xml_value_t&);
      xml_value_t		get_final(hstate_t, const xml_value_t&);
      void			clear_final();
      void			update(hedge_t, label_t);

      const DOMDocument*	doc() const;
      DOMDocument*		doc();

      const DOMElement*		root() const;
      DOMElement*		root();

      const DOMElement*		structure() const;
      DOMElement*		structure();

      const DOMElement*		states() const;
      DOMElement*		states();

      const DOMElement*		edges() const;
      DOMElement*		edges();

      const DOMElement*		initials() const;
      DOMElement*		initials();

      const DOMElement*		finals() const;
      DOMElement*		finals();


    protected:
      DOMDocument*	doc_;

      DOMElement*	root_;
      DOMElement*	structure_;
      DOMElement*	states_;
      DOMElement*	edges_;
      DOMElement*	initials_;
      DOMElement*	finals_;

      // FIXME: Put these protected:
    public:
      std::map<hedge_t, DOMElement*>  edges_nodes_;
      std::map<std::string, hstate_t> sname2num_;
      std::map<hstate_t,std::string>  snum2name_;
    };

    /** @} */

  } // End of namespace xml.

} // End of namespace vcsn.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/xml_automaton.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_XML_XML_AUTOMATON_HH
