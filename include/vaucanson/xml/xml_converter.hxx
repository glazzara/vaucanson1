// xml_converter.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_XML_XML_CONVERTER_HXX
# define VCSN_XML_XML_CONVERTER_HXX

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
    template <class OStream>
    void xml_converter<Auto>::save(const Auto& aut, OStream& os)
    {
      create_document(aut);
      tools::print_document(root_, os);
    }

    template <class Auto>
    void xml_converter<Auto>::create_document(const Auto& aut)
    {
      typedef typename Auto::state_iterator state_iterator;
      typedef typename Auto::edge_iterator edge_iterator;
      typedef typename Auto::initial_iterator initial_iterator;
      typedef typename Auto::final_iterator final_iterator;
      using namespace xercesc;

      std::map<hstate_t, std::string> state2str;
      const char* root_name = chooser_.choose_start_tag();
      DOMElement* node;

      // Document creation.
      impl_ = DOMImplementationRegistry::getDOMImplementation(STR2XML("LS"));
      doc_ = impl_->createDocument(STR2XML
				  ("http://vaucanson.lrde.epita.fr"),
				  STR2XML(root_name), 0);
      root_ = doc_->getDocumentElement();

      // Create type tag.
      chooser_.create_type_tag(aut, doc_, root_);

      DOMElement* content = doc_->createElement(STR2XML("content"));
      root_->appendChild(content);

      // Create states.
      node = doc_->createElement(STR2XML("states"));
      content->appendChild(node);
      for_each_state(s, aut)
	 state2str[*s] = create_state(*s, aut, node);

      // Create transitions.
      node = doc_->createElement(STR2XML("transitions"));
      content->appendChild(node);
      for_each_edge(e, aut)
	create_transition(*e, aut, node, state2str);

      // Create initial transitions.
      for_each_initial_state(i, aut)
	create_initial(*i, aut, node, state2str);

      // Create final transitions.
      for_each_final_state(f, aut)
	create_final(*f, aut, node, state2str);
    }


    // Create a state in the XML document.
    template <class Auto>
    std::string xml_converter<Auto>::create_state(hstate_t s,
						  const Auto& aut,
						  xercesc::DOMElement* root)
    {
      std::ostringstream os;
      os << "s" << s;
      xercesc::DOMElement* node = doc_->createElement(STR2XML("state"));
      root->appendChild(node);
      node->setAttribute(STR2XML("name"), STR2XML(os.str().c_str()));
      add_xml_geometry(aut.geometry().states(), s, node);

      return os.str();
    }


    // Create a transition in the XML document.
    template <class Auto>
    void
    xml_converter<Auto>::create_transition(hedge_t e,
					   const Auto& aut,
					   xercesc::DOMElement* root,
					   std::map<hstate_t, std::string>&
					   state2str)
    {
      xercesc::DOMElement* node = doc_->createElement(STR2XML("transition"));
      root->appendChild(node);
      node->setAttribute(STR2XML("src"),
			 STR2XML(state2str[aut.origin_of(e)].c_str()));
      node->setAttribute(STR2XML("dst"),
			 STR2XML(state2str[aut.aim_of(e)].c_str()));
      chooser_.create_label(e, aut, node);
      add_xml_drawing(aut.geometry().edges(), e, node);
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
      xercesc::DOMElement* node = doc_->createElement(STR2XML("initial"));
      root->appendChild(node);
      node->setAttribute(STR2XML("state"),
			 STR2XML(state2str[s].c_str()));
      chooser_.create_initial_label(s, aut, node);
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
      xercesc::DOMElement* node = doc_->createElement(STR2XML("final"));
      root->appendChild(node);
      node->setAttribute(STR2XML("state"),
			 STR2XML(state2str[s].c_str()));
      chooser_.create_final_label(s, aut, node);
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
	  xercesc::DOMElement* nd = doc_->createElement(STR2XML("geometry"));
	  root->appendChild(nd);
	  nd->setAttribute(STR2XML("x"),
			   STR2XML(osx.str().c_str()));
	  osy << iter->second.second;
	  nd->setAttribute(STR2XML("y"),
			   STR2XML(osy.str().c_str()));
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
	  xercesc::DOMElement* nd = doc_->createElement(STR2XML("drawing"));
	  root->appendChild(nd);
	  nd->setAttribute(STR2XML("labelPositionX"),
			   STR2XML(osx.str().c_str()));
	  osy << iter->second.second;
	  nd->setAttribute(STR2XML("labelPositionY"),
			   STR2XML(osy.str().c_str()));
	}
    }


    /**
     * @brief Load automaton from stream.
     *
     * This method uses the Factory Method design pattern. The factory has to
     * be registered with the macro register_all_factory(f, Auto) (where f is
     * the factory, and Auto the template parameter.
     *
     * @param Auto	Type of the automaton.
     * @param IStream	Type of the input stream.
     *
     * @arg a		Automaton to save.
     * @arg in		Input stream.
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
