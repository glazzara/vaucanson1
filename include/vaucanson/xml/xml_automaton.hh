#ifndef VCSN_XML_XML_AUTOMATON_HH
# define VCSN_XML_XML_AUTOMATON_HH

# include <vaucanson/misc/support.hh>
# include <vaucanson/xml/infos.hh>
# include <vaucanson/xml/xml_value.hh>

# include <xercesc/dom/DOM.hpp>

/** @addtogroup xml XML tools for Vaucanson *//** @{ */
/**
 * @file xml_automaton.hh
 * @brief XML automaton implementation.
 * @author Valentin David <valentin@lrde.epita.fr>
 */

namespace vcsn
{
  namespace xml
  {
    using namespace xercesc;

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

  }

  namespace algebra {
    template <>
    struct series_traits<vcsn::xml::XmlValue>
    {
      typedef xml::XmlValue monoid_value_t;
      typedef xml::XmlValue semiring_elt_value_t;
      typedef utility::Support<xml::XmlValue> support_t;
    };
  }

  template <>
  struct automaton_traits<xml::XmlAutomaton>
  {
    typedef xml::XmlValue      			     series_value_t;
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

}

/** @} */

# include <vaucanson/xml/xml_automaton.hxx>

#endif // VCSN_AUTOMATA_CONCRETE_XML_AUTOMATON_HH
