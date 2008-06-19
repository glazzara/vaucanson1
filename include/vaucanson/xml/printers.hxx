// printers.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2007 The Vaucanson Group.
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

#ifndef VCSN_XML_PRINTERS_HXX
# define VCSN_XML_PRINTERS_HXX

# include <fstream>

# include <vaucanson/xml/xml_xerces_stream.hh>
# include <vaucanson/xml/strings.hh>
# include <vaucanson/xml/tools.hh>
# include <vaucanson/xml/builders.hh>

namespace vcsn
{
  namespace xml
  {
    /*
     * Printer class.
     */

    Printer::Printer ()
    {
    };

    Printer::~Printer ()
    {
    }

    /*
     * AutPrinter class.
     */
    template <typename Auto>
    AutPrinter<Auto>::AutPrinter (const Auto& aut, const std::string& name)
      : aut_(aut), name_(name)
    {
    }

    template <typename Auto>
    AutPrinter<Auto>::~AutPrinter ()
    {
    }

    template <typename Auto>
    void
    AutPrinter<Auto>::print (std::ostream& out)
    {
      typedef typename Auto::state_iterator state_iterator;
      typedef typename Auto::transition_iterator transition_iterator;
      typedef typename Auto::initial_iterator initial_iterator;
      typedef typename Auto::final_iterator final_iterator;
      using namespace xercesc;

      state2str_.clear();

      // Document creation.
      impl_ = DOMImplementationRegistry::getDOMImplementation(transcode("LS"));
      doc_ = impl_->createDocument(transcode(VCSN_XMLNS),
				   transcode("fsmxml"), 0);
      root_ = doc_->getDocumentElement();

      tools::set_attribute(root_, "version", "1.0"); // FIXME should be... a macro?

      DOMElement* automaton = tools::create_element(doc_, "automaton");
      root_->appendChild(automaton);
      tools::set_attribute(automaton, "name", aut_.geometry().name());

      DOMElement* valueType = tools::create_element(doc_, "valueType");
      automaton->appendChild(valueType);
      builders::create_semiring_node(aut_, doc_, valueType);
      builders::create_monoid_node(aut_, doc_, valueType);

      DOMElement* content = tools::create_element(doc_, "automatonStruct");
      automaton->appendChild(content);

      // Create states.
      DOMElement* node = tools::create_element(doc_, "states");
      content->appendChild(node);
      for_all_states(s, aut_)
	state2str_[*s] = create_state(*s, node);

      // Create transitions.
      node = tools::create_element(doc_, "transitions");
      content->appendChild(node);
      for_all_transitions(e, aut_)
	create_transition(*e, node);

      // Create initial transitions.
      for_all_initial_states(i, aut_)
	create_initial(*i, node);

      // Create final transitions.
      for_all_final_states(f, aut_)
	create_final(*f, node);

      // Print it!

      XMLXercesStream<std::ostream>* target = new XMLXercesStream<std::ostream>(out);
      DOMWriter* writer = impl_->createDOMWriter();

      if (writer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true))
	writer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true);
      writer->writeNode(target, *root_);
      writer->release();
      out << std::endl;
      delete doc_;
      delete target;
    }

    template <class Auto>
    void
    AutPrinter<Auto>::create_geometry(hstate_t& key,
			xercesc::DOMElement* root)
    {
      typedef typename Auto::geometry_t::states_geometry_map_t gmap_t;
      typename gmap_t::const_iterator iter;
      gmap_t map = aut_.geometry().states();
      if ((iter = map.find(key)) != map.end())
      {
	std::ostringstream osx, osy;
	osx << iter->second.first;
	xercesc::DOMElement* nd = tools::create_element(doc_, "geometricData");
	root->appendChild(nd);
	tools::set_attribute(nd, "x", osx.str());
	osy << iter->second.second;
	tools::set_attribute(nd, "y", osy.str());
      }
    }

    template <class Auto>
    std::string
    AutPrinter<Auto>::create_state(hstate_t s,
				   xercesc::DOMElement* root)
    {
      xercesc::DOMElement* node = tools::create_element(doc_, "state");
      root->appendChild(node);
      std::ostringstream os;
      os << "s" << s;
      tools::set_attribute(node, "id", os.str());
      this->create_geometry(s, node);
      return os.str();
    }

    template <class Auto>
    void
    AutPrinter<Auto>::create_transition(htransition_t e,
					xercesc::DOMElement* root)
    {
      xercesc::DOMElement* node = tools::create_element(doc_, "transition");
      root->appendChild(node);
      tools::set_attribute(node, "src", state2str_[aut_.src_of(e)]);
      tools::set_attribute(node, "target", state2str_[aut_.dst_of(e)]);
      builders::create_regexp_node(aut_.series_of(e), doc_, node);
    }
    template <class Auto>
    void
    AutPrinter<Auto>::create_initial(hstate_t s,
				     xercesc::DOMElement* root)
    {
      xercesc::DOMElement* node = tools::create_element(doc_, "initial");
      root->appendChild(node);
      tools::set_attribute(node, "state", state2str_[s]);
      typename Auto::series_set_elt_t tmp = aut_.get_initial(s);
      if (tmp != algebra::identity_as<typename Auto::series_set_elt_t::value_t>::of(aut_.structure().series()).value())
	builders::create_regexp_node(tmp, doc_, node);
    }
    template <class Auto>
    void
    AutPrinter<Auto>::create_final(hstate_t s,
				     xercesc::DOMElement* root)
    {
      xercesc::DOMElement* node = tools::create_element(doc_, "final");
      root->appendChild(node);
      tools::set_attribute(node, "state", state2str_[s]);
      typename Auto::series_set_elt_t tmp = aut_.get_final(s);
      if (tmp != algebra::identity_as<typename Auto::series_set_elt_t::value_t>::of(aut_.structure().series()).value())
	builders::create_regexp_node(tmp, doc_, node);
    }
  } // !xml
} // !vcsn

#endif // !VCSN_XML_PRINTERS_HXX
