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

    using namespace xercesc;

    /** @addtogroup xml *//** @{ */

    /// Xml automaton implementation
    class XmlAutomaton
    {
    public:
      typedef XmlValue		    label_t;
      typedef XmlAutomaton	    self_t;

      //protected:
      //TODO: Accessors against public attribute.
    public:
      DOMDocument*		      doc_;
      bool			      handled_doc_;
      DOMElement*		      root_;
      DOMElement*		      type_;
      DOMElement*		      structure_;
      DOMElement*	       	      semiring_node_;
      DOMElement*	       	      monoid_node_;
      DOMElement*	       	      states_node_;
      DOMElement*	       	      initials_node_;
      DOMElement*	       	      finals_node_;
      DOMElement*             	      edges_node_;
      std::map<hedge_t, DOMElement*>  edges_nodes_;
      std::map<std::string, hstate_t> sname2num_;
      std::map<hstate_t,std::string>  snum2name_;

    public:
      /// Default constructor.
      XmlAutomaton();
      /**
       * @brief Read constructor.
       * @param elt XML automaton root element.
       */
      XmlAutomaton(DOMElement* elt);
      ~XmlAutomaton();

      void			    serialize(std::ostream&) const;

      hstate_t			    add_state();
      void			    del_state(hstate_t);

      hstate_t			    add_state(hstate_t);
      hstate_t			    add_state(const std::string&);
      hstate_t		            add_state(hstate_t, const std::string&);

      // for internal only
      xercesc::DOMElement*	    add_state_elt(hstate_t);
      xercesc::DOMElement*          add_state_elt(hstate_t,
						  const std::string&);

      bool			    has_state(hstate_t) const;
      hedge_t			    add_edge(hstate_t, hstate_t,
					     const label_t&);
      void			    del_edge(hedge_t);
      bool			    has_edge(hedge_t) const;

      hstate_t			    origin_of(hedge_t) const;
      hstate_t		    	    aim_of(hedge_t) const;
      label_t		    	    label_of(hedge_t) const;
      xercesc::DOMElement*	    set_initial(hstate_t, const XmlValue&,
						const XmlValue&);
      XmlValue			    get_initial(hstate_t,
						const XmlValue&);
      void			    clear_initial();
      xercesc::DOMElement*	    set_final(hstate_t, const XmlValue&,
					      const XmlValue&);
      XmlValue			    get_final(hstate_t,
					      const XmlValue&);
      void			    clear_final();
      void			    update(hedge_t, label_t);
    };

    /** @} */

  } // End of namespace xml.

  namespace algebra {

    /** @addtogroup xml *//** @{ */

    template <>
    struct series_traits<vcsn::xml::XmlValue>
    {
      typedef xml::XmlValue monoid_elt_value_t;
      typedef xml::XmlValue semiring_elt_value_t;
      typedef utility::Support<xml::XmlValue> support_t;
    };

    /** @} */

  } // End of namespace algebra.

  /** @addtogroup xml *//** @{ */

  template <>
  struct automaton_traits<xml::XmlAutomaton>
  {
    typedef xml::XmlValue      			     series_set_elt_value_t;
    typedef xml::XmlValue	       		     word_value_t;
    typedef xml::XmlValue      			     monoid_elt_value_t;
    typedef xml::XmlValue      			     semiring_elt_value_t;
    typedef xml::XmlValue			     letter_t;
    typedef xml::XmlValue      			     label_t;
    typedef xml::XmlInfosTag      		     tag_t;
    typedef std::map<hstate_t, xml::XmlValue>  	     states_t;
    typedef std::map<hstate_t, xml::XmlValue>::iterator
						     state_iterator;
    typedef std::map<hedge_t, xml::XmlValue>	     edges_t;
    typedef std::map<hedge_t, xml::XmlValue>::iterator
						     edge_iterator;
    typedef std::map<hstate_t, xml::XmlValue> 	     initial_t;
    typedef std::map<hstate_t, xml::XmlValue>        final_t;
    typedef utility::Support<initial_t>		     initial_support_t;
    typedef utility::Support<final_t>    	     final_support_t;
    typedef initial_support_t::iterator		     initial_iterator;
    typedef final_support_t::iterator  	             final_iterator;
    typedef xml::XmlValue			     edge_value_t;
    typedef xml::XmlValue			     state_value_t;
    typedef std::vector<xml::XmlValue>		     state_data_t;
    typedef std::vector<xml::XmlValue> 		     edge_data_t;
  };

  /** @} */

} // End of namespace vcsn.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/xml_automaton.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_XML_XML_AUTOMATON_HH
