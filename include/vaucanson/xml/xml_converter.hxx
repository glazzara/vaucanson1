// xml_converter.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_XML_XML_CONVERTER_HXX
# define VCSN_XML_XML_CONVERTER_HXX

# include <vaucanson/xml/tools.hh>

/**
   * @file xml_converter.hxx
   *
   * XML conversion class. Used to convert stream containing XML to automaton,
   * and vice et versa.
   *
   * @see vcsn::xml::xml_chooser, vcsn::xml::Node, vcsn::Factory
   *
   * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
   */


namespace vcsn
{
  namespace xml
  {

    template <class Auto>
    xml_converter<Auto>::xml_converter (bool use_label_node) 
	: impl_(0), doc_(0), root_(0), use_label_node_(use_label_node) 
    {}

    template <class Auto>
    template <class OStream>
    void xml_converter<Auto>::save(const Auto& aut, OStream& os,
				   const std::string& name)
    {
      create_document(aut, name);
      tools::print_document(root_, os);
    }

    template <class Auto>
    void xml_converter<Auto>::create_document(const Auto& aut,
					      const std::string& name)
    {
      typedef typename Auto::state_iterator state_iterator;
      typedef typename Auto::transition_iterator transition_iterator;
      typedef typename Auto::initial_iterator initial_iterator;
      typedef typename Auto::final_iterator final_iterator;
      using namespace xercesc;

      std::map<hstate_t, std::string> state2str;
      const char* root_name = chooser_.choose_start_tag();
      const char* xml_namespace = "http://vaucanson.lrde.epita.fr";
      DOMElement* node;

      // Document creation.
      impl_ = DOMImplementationRegistry::getDOMImplementation(transcode("LS"));
      doc_ = impl_->createDocument(transcode(xml_namespace),
				   transcode(root_name), 0);
      root_ = doc_->getDocumentElement();

      tools::xset_attribute(root_, "name", aut.geometry().name());
      tools::xset_attribute(root_, "name", name);

      // Create type tag.
      chooser_.create_type_tag(aut, doc_, root_);

      DOMElement* content = doc_->createElement(transcode("content"));
      root_->appendChild(content);

      // Create states.
      node = doc_->createElement(transcode("states"));
      content->appendChild(node);
      for_all_states(s, aut)
	state2str[*s] = create_state(*s, aut, node);

      // Create transitions.
      node = doc_->createElement(transcode("transitions"));
      content->appendChild(node);
      for_all_transitions(e, aut)
	create_transition(*e, aut, node, state2str);

      // Create initial transitions.
      for_all_initial_states(i, aut)
	create_initial(*i, aut, node, state2str);

      // Create final transitions.
      for_all_final_states(f, aut)
	create_final(*f, aut, node, state2str);
    }


    template <class Auto>
    xercesc::DOMElement*  
    xml_converter<Auto>::root_get() 
    {
      return root_; 
    }

    // Create a state in the XML document.
    template <class Auto>
    std::string xml_converter<Auto>::create_state(hstate_t s,
						  const Auto& aut,
						  xercesc::DOMElement* root)
    {
      std::ostringstream os;
      os << "s" << s;
      xercesc::DOMElement* node = doc_->createElement(transcode("state"));
      root->appendChild(node);
      tools::set_attribute(node, "name", os.str());
      add_xml_geometry(aut.geometry().states(), s, node);

      return os.str();
    }


    // Create a transition in the XML document.
    template <class Auto>
    void
    xml_converter<Auto>::create_transition(htransition_t e,
					   const Auto& aut,
					   xercesc::DOMElement* root,
					   std::map<hstate_t, std::string>&
					   state2str)
    {
      xercesc::DOMElement* node = doc_->createElement(transcode("transition"));
      root->appendChild(node);
      tools::set_attribute(node, "src", state2str[aut.src_of(e)]);
      tools::set_attribute(node, "dst", state2str[aut.dst_of(e)]);
      chooser_.create_label(doc_, e, aut, node, use_label_node_);
      add_xml_drawing(aut.geometry().transitions(), e, node);
    }


    // Create an initial state in the XML document.
    template <class Auto>
    void
    xml_converter<Auto>::create_initial(hstate_t s,
					const Auto& aut,
					xercesc::DOMElement* root,
					std::map<hstate_t, std::string>&
					state2str)
    {
      xercesc::DOMElement* node = doc_->createElement(transcode("initial"));
      root->appendChild(node);
      tools::set_attribute(node, "state", state2str[s]);
      chooser_.create_initial_label(doc_, s, aut, node, use_label_node_);
      add_xml_drawing(aut.geometry().initials(), s, node);
    }


    // Create a final state in the XML document.
    template <class Auto>
    void
    xml_converter<Auto>::create_final(hstate_t s,
				      const Auto& aut,
				      xercesc::DOMElement* root,
				      std::map<hstate_t, std::string>&
				      state2str)
    {
      xercesc::DOMElement* node = doc_->createElement(transcode("final"));
      root->appendChild(node);
      tools::set_attribute(node, "state", state2str[s]);
      chooser_.create_final_label(doc_, s, aut, node, use_label_node_);
      add_xml_drawing(aut.geometry().finals(), s, node);
    }


    // Add geometry informations in the XML document.
    template <class Auto>
    template <class Map, class Key>
    void xml_converter<Auto>::add_xml_geometry(Map& map,
					       Key& key,
					       xercesc::DOMElement* root)
    {
      typename Map::const_iterator iter;
      if ((iter = map.find(key)) != map.end())
      {
	std::ostringstream osx, osy;
	osx << iter->second.first;
	xercesc::DOMElement* nd = doc_->createElement(transcode("geometry"));
	root->appendChild(nd);
	tools::set_attribute(nd, "x", osx.str());
	osy << iter->second.second;
	tools::set_attribute(nd, "y", osy.str());
      }
    }


    // Add drawing informations in the XML document.
    template <class Auto>
    template <class Map, class Key>
    void xml_converter<Auto>::add_xml_drawing(Map& map,
					      Key& key,
					      xercesc::DOMElement* root)
    {
      typename Map::const_iterator iter;
      if ((iter = map.find(key)) != map.end())
      {
	std::ostringstream osx, osy;
	osx << iter->second.first;
	xercesc::DOMElement* nd = doc_->createElement(transcode("drawing"));
	root->appendChild(nd);
	tools::set_attribute(nd, "labelPositionX", osx.str());
	osy << iter->second.second;
	tools::set_attribute(nd, "labelPositionY", osy.str());
      }
    }


    /**
       * @brief Load automaton from stream.
       *
       * This method uses the Factory Method design pattern. The factory has to
       * be registered with the macro register_all_factory(f, Auto) (where f is
       * the factory, and Auto the template parameter.
       *
       * @arg \c Auto	  Type of the automaton.
       * @arg \c IStream  Type of the input stream.
       *
       * @param a	Automaton to save.
       * @param in	Input stream.
       */
    template <class Auto>
    template <class IStream>
    void xml_converter<Auto>::load(Auto& aut,
				   IStream& in)
    {
      root_ = xerces_parser::stream_parser(in);

      typedef Node<Auto> node_t;
      Factory<node_t, std::string> f;
      register_all_factory(f, Auto);
      typename node_t::map_t str2state;

      node_t* node = factory_create(f, xml2str(root_->getNodeName()));
      node->process(root_, aut, str2state, f);
    }


  } // !xml

} // !vcsn


#endif // ! VCSN_XML_XML_CONVERTER_HXX
