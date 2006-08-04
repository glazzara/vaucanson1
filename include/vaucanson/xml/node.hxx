// node.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_NODE_HXX
# define VCSN_XML_NODE_HXX

/**
 * @file node.hxx
 *
 * Node class for Factory Method, used in xml::xml_converter::save()
 *
 *
 * @see xml::xml_converter, vcsn::Factory
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */


namespace vcsn
{
  namespace xml
  {

    template <class T>
    Node<T>::~Node()
    {
    }

# define PROCESS_NODE(name)						\
    template <class T>							\
    void name ## Node<T>::process(xercesc::DOMElement* node, T& aut,	\
				  typename Node<T>::map_t& m,		\
				  typename Node<T>::factory_t& f)	\
    {									\
      using namespace xercesc;						\
      for (DOMNode* n = node->getFirstChild(); n; n = n->getNextSibling()) \
	if (n->getNodeType() == DOMNode::ELEMENT_NODE)			\
	{								\
	  DOMElement* elt = static_cast<DOMElement*>(n);		\
	  Node<T>* node = f.create_object(xml2str(elt->getNodeName()));	\
	  node->process(elt, aut, m, f);				\
	}								\
    }

    PROCESS_NODE(content)
    PROCESS_NODE(labelType)
    PROCESS_NODE(states)
    PROCESS_NODE(transitions)

# undef PROCESS_NODE

# define PROCESS_ROOT_NODE(node_name)					\
    template <class T>							\
    void								\
    node_name ## Node<T>::process(xercesc::DOMElement* node, T& aut,	\
				  typename Node<T>::map_t& m,		\
				  typename Node<T>::factory_t& f)	\
    {									\
      using namespace xercesc;						\
      bool type_done = false;						\
      if (node->hasAttribute(transcode("name")))				\
	aut.geometry().name() = xml2str(node->getAttribute(transcode("name"))); \
      for (DOMNode* n = node->getFirstChild(); n; n = n->getNextSibling()) \
	if (n->getNodeType() == DOMNode::ELEMENT_NODE)			\
	{								\
	  DOMElement* elt = static_cast<DOMElement*>(n);		\
	  if (! type_done)						\
	  {								\
	    if (XMLString::compareIString(n->getNodeName(),		\
					  transcode("labelType")))	\
	    {								\
	      labelTypeNode<T>* node = new labelTypeNode<T>;		\
	      node->process(0, aut, m, f);				\
	    }								\
	    type_done = true;						\
	  }								\
	  Node<T>* node = f.create_object(xml2str(elt->getNodeName())); \
	  node->process(elt, aut, m, f);				\
	}								\
    }

    PROCESS_ROOT_NODE(automaton)
    PROCESS_ROOT_NODE(transducer)

# undef PROCESS_ROOT_NODE

# define PROCESS_TYPE_NODE(TempParam, AutType)				\
    TempParam								\
    void 								\
    labelTypeNode<AutType >::process(xercesc::DOMElement* node,		\
				     AutType& aut,			\
				     typename Node<AutType >::map_t& m, \
				     typename Node<AutType >::factory_t& f) \
    {									\
      using namespace xercesc;						\
      bool monoid_done = false, semiring_done = false;			\
									\
      if (! node)							\
	process_type(node, aut, m, f, monoid_done, semiring_done);	\
      else								\
	for (DOMNode* n = node->getFirstChild(); n; n = n->getNextSibling()) \
	  if (n->getNodeType() == DOMNode::ELEMENT_NODE)		\
	  {								\
	    DOMElement* elt = static_cast<DOMElement*>(n);		\
	    process_type(elt, aut, m, f, monoid_done, semiring_done);	\
	  }								\
    }

    PROCESS_TYPE_NODE(TParm,    AUTtype)
    PROCESS_TYPE_NODE(TParm,    TRANStype)
    PROCESS_TYPE_NODE(TParmFMP, FMPtype)

# undef PROCESS_TYPE_NODE


    /*------------.
    | <labelType> |
    `------------*/
    template <class T>
    void process_type(xercesc::DOMElement* node, T& aut,
		      typename Node<T>::map_t& m,
		      typename Node<T>::factory_t& f,
		      bool& monoid_done,
		      bool& semiring_done)
    {
      std::string arg;
      xercesc::DOMElement* elt;
      if (! monoid_done)
      {
	std::string monoid("monoid");
	if (node && xml2str(node->getNodeName()) == monoid)
	  elt = node;
	else
	  elt = 0;
	monoidNode<T>* nd = new monoidNode<T>;
	typename T::monoid_t::alphabet_t at;
	typename T::monoid_t md(at);
	nd->process(elt, aut, md, m, f);
	typename T::series_set_t
	  series(aut.structure().series().semiring(), md);
	aut.attach(series);
	monoid_done = true;
      }
      else
	if (! semiring_done)
	{
	  std::string semiring("semiring");
	  if (node && xml2str(node->getNodeName()) == semiring)
	    elt = node;
	  else
	    elt = 0;
	  semiringNode<T>* nd = new semiringNode<T>;
	  typename T::semiring_t sg;
	  nd->process(elt, aut, sg, m, f);
	  typename T::series_set_t
	    series(sg, aut.structure().series().monoid());
	  aut.attach(series);
	  semiring_done = true;
	}
    }


    TParm
    void process_type(xercesc::DOMElement* node, TRANStype& aut,
		      typename Node<TRANStype>::map_t& m,
		      typename Node<TRANStype>::factory_t& f,
		      bool& monoid_done,
		      bool& semiring_done)
    {
      std::string arg;
      xercesc::DOMElement* elt;
      if (! monoid_done)
      {
	std::string monoid("monoid");
	if (node && xml2str(node->getNodeName()) == monoid)
	  elt = node;
	else
	  elt = 0;
	monoidNode<TRANStype>* nd = new monoidNode<TRANStype>;
	typename TRANStype::monoid_t::alphabet_t at;
	typename TRANStype::monoid_t md(at);
	nd->process(elt, aut, md, m, f);
	typename TRANStype::series_set_t
	  series(aut.structure().series().semiring(), md);
	aut.attach(series);
	monoid_done = true;
      }
      else
	if (! semiring_done)
	{
	  std::string semiring("semiring");
	  if (node && xml2str(node->getNodeName()) == semiring)
	    elt = node;
	  else
	    elt = 0;
	  semiringNode<TRANStype>* nd = new semiringNode<TRANStype>;
	  typename TRANStype::semiring_t::monoid_t::alphabet_t at;
	  typename TRANStype::semiring_t::monoid_t md(at);
	  typename TRANStype::semiring_t::semiring_t ssg;
	  typename TRANStype::semiring_t sg(ssg, md);
	  nd->process(elt, aut, sg, m, f);
	  typename TRANStype::series_set_t
	    series(sg, aut.structure().series().monoid());
	  aut.attach(series);
	  semiring_done = true;
	}
    }


    TParmFMP
    void process_type(xercesc::DOMElement* node, FMPtype& aut,
		      typename Node<FMPtype>::map_t& m,
		      typename Node<FMPtype>::factory_t& f,
		      bool& monoid_done,
		      bool& semiring_done)
    {
      std::string arg;
      xercesc::DOMElement* elt;
      if (! monoid_done)
      {
	std::string monoid("monoid");
	if (node && xml2str(node->getNodeName()) == monoid)
	  elt = node;
	else
	  elt = 0;
	monoidNode<FMPtype>* nd = new monoidNode<FMPtype>;
	typename FMPtype::monoid_t::first_monoid_t::alphabet_t at1;
	typename FMPtype::monoid_t::second_monoid_t::alphabet_t at2;
	typename FMPtype::monoid_t::first_monoid_t md1(at1);
	typename FMPtype::monoid_t::second_monoid_t md2(at2);
	typename FMPtype::monoid_t md(md1, md2);
	nd->process(elt, aut, md, m, f);
	typename FMPtype::series_set_t
	  series(aut.structure().series().semiring(), md);
	aut.attach(series);
	monoid_done = true;
      }
      else
	if (! semiring_done)
	{
	  std::string semiring("semiring");
	  if (node && xml2str(node->getNodeName()) == semiring)
	    elt = node;
	  else
	    elt = 0;
	  semiringNode<FMPtype>* nd = new semiringNode<FMPtype>;
	  typename FMPtype::semiring_t sg;
	  nd->process(elt, aut, sg, m, f);
	  typename FMPtype::series_set_t
	    series(sg, aut.structure().series().monoid());
	  aut.attach(series);
	  semiring_done = true;
	}
    }


    /*--------.
    | <state> |
    `--------*/
    template <class T>
    void
    stateNode<T>::process(xercesc::DOMElement* node, T& aut,
			  typename Node<T>::map_t& m,
			  typename Node<T>::factory_t& f)
    {
      hstate_t state = aut.add_state();
      m[xml2str(node->getAttribute(transcode("name")))] = state;
      typename Node<T>::map_state_pair_t p(aut.geometry().states(), state);
      handle_geometry(node, aut, p, m, f);
    }


    /*-------------.
    | <transition> |
    `-------------*/
    template <class T>
    void
    transitionNode<T>::process(xercesc::DOMElement* node, T& aut,
			       typename Node<T>::map_t& m,
			       typename Node<T>::factory_t& f)
    {
      hstate_t src = m[xml2str(node->getAttribute(transcode("src")))];
      hstate_t dst = m[xml2str(node->getAttribute(transcode("dst")))];
      typename T::series_set_elt_t s = tools::get_series(node, aut);
      htransition_t e = aut.add_series_transition(src, dst, s);
      typename Node<T>::map_transition_pair_t p(aut.geometry().transitions(), e);
      handle_geometry(node, aut, p, m, f);
    }


    /*----------.
    | <initial> |
    `----------*/
    template <class T>
    void
    initialNode<T>::process(xercesc::DOMElement* node, T& aut,
			    typename Node<T>::map_t& m,
			    typename Node<T>::factory_t& f)
    {
      hstate_t state = m[xml2str(node->getAttribute(transcode("state")))];
      typename T::series_set_elt_t s = tools::get_series(node, aut);
      aut.set_initial(state, s);
      typename Node<T>::map_state_pair_t p(aut.geometry().initials(), state);
      handle_geometry(node, aut, p, m, f);
    }


    /*--------.
    | <final> |
    `--------*/
    template <class T>
    void
    finalNode<T>::process(xercesc::DOMElement* node, T& aut,
			  typename Node<T>::map_t& m,
			  typename Node<T>::factory_t& f)
    {
      hstate_t state = m[xml2str(node->getAttribute(transcode("state")))];
      typename T::series_set_elt_t s = tools::get_series(node, aut);
      aut.set_final(state, s);
      typename Node<T>::map_state_pair_t p(aut.geometry().finals(), state);
      handle_geometry(node, aut, p, m, f);
    }


    /*-----------.
    | <semiring> |
    `-----------*/
    template <class T>
    template <class U>
    void
    semiringNode<T>::process(xercesc::DOMElement* node, T& a,
			     U& param,
			     typename Node<T>::map_t&,
			     typename Node<T>::factory_t&)
    {
      tools::ensure_semiring_type(node, a, param);
    }


    TParm
    template <class U>
    void
    semiringNode<TRANStype>::process(xercesc::DOMElement* node, TRANStype& a,
				     U& param,
				     typename Node<TRANStype>::map_t& m,
				     typename Node<TRANStype>::factory_t& f)
    {
      process_semiring(node, a, param, m, f);
    }


    TParm
    void
    process_semiring(xercesc::DOMElement* node, TRANStype& a,
		     typename TRANStype::semiring_t::semiring_t& param,
		     typename Node<TRANStype>::map_t&,
		     typename Node<TRANStype>::factory_t&)
    {
      tools::ensure_semiring_type(node, a, param);
    }

    TParm
    void
    process_semiring(xercesc::DOMElement* node, TRANStype& a,
		     typename TRANStype::semiring_t& param,
		     typename Node<TRANStype>::map_t& m,
		     typename Node<TRANStype>::factory_t& f)
    {
      using namespace xercesc;
      tools::ensure_semiring_type(node, a, param);

      monoidNode<TRANStype>* nd = new monoidNode<TRANStype>;

      /// FIXME: Remove these const_cast.
      if (! node || ! node->getFirstChild())
	nd->process(0, a, const_cast<typename TRANStype::semiring_t::monoid_t&>
		    (param.monoid()), m, f);
      else
	for (DOMNode* n = node->getFirstChild(); n; n = n->getNextSibling())
	  if (n->getNodeType() == DOMNode::ELEMENT_NODE)
	  {
	    if (! XMLString::compareIString(n->getNodeName(),
					    transcode("monoid")))
	      nd->process(static_cast<DOMElement*>(n), a,
			  const_cast
			  <typename TRANStype::semiring_t::monoid_t&>
			  (param.monoid()), m, f);
	    else
	    {
	      semiringNode<TRANStype>* sg = new semiringNode<TRANStype>;
	      sg->process(static_cast<DOMElement*>(n), a,
			  const_cast
			  <typename TRANStype::semiring_t::semiring_t&>
			  (param.semiring()), m, f);
	    }
	  }
    }


    /*---------.
    | <monoid> |
    `---------*/
    // This is only called when param is a free monoid.
    template <class T, class U>
    void process_monoid(xercesc::DOMElement* node, T& aut,
			U& param,
			typename Node<T>::map_t& m,
			typename Node<T>::factory_t& f)
    {
      using namespace xercesc;

      tools::ensure_monoid_type(node, param);

      // Default case, if there is no label tag.
      // Here, implicitAlphabet range case is the default.
      if (! node)
      {
	for (unsigned int i = 'a'; i <= 'z'; ++i)
	  param.alphabet().insert(i);
	for (unsigned int i = 'A'; i <= 'Z'; ++i)
	  param.alphabet().insert(i);
      }
      else
	for (DOMNode* n = node->getFirstChild(); n; n = n->getNextSibling())
	  if (n->getNodeType() == DOMNode::ELEMENT_NODE)
	  {
	    DOMElement* elt = static_cast<DOMElement*>(n);

	    // Fill the alphabet if a range attribute exists.
	    if (elt->hasAttribute(transcode("range")))
	    {
	      if (xml2str(elt->getAttribute(transcode("range"))) == "implicitAlphabet")
	      {
		for (unsigned int i = 'a'; i <= 'z'; ++i)
		  param.alphabet().insert(i);
		for (unsigned int i = 'A'; i <= 'Z'; ++i)
		  param.alphabet().insert(i);
	      }
	      if (xml2str(elt->getAttribute(transcode("range"))) == "digits")
		for (unsigned int i = '0'; i <= '9'; ++i)
		  param.alphabet().insert(i);
	      if (xml2str(elt->getAttribute(transcode("range"))) == "ascii")
		for (unsigned char c = 0; c <= 127; ++c)
		  param.alphabet().insert(c);
	    }
	    // Else, add single letters.
	    else
	    {
	      generatorNode<T>* nd = static_cast<generatorNode<T>*>
		(f.create_object(xml2str(elt->getNodeName())));
	      nd->process(elt, aut, param.alphabet(), m, f);
	    }
	  }
    }

    template <class T>
    template <class U>
    void
    monoidNode<T>::process(xercesc::DOMElement* node, T& aut,
			   U& param,
			   typename Node<T>::map_t& m,
			   typename Node<T>::factory_t& f)
    {
      process_monoid(node, aut, param, m, f);
    }


    template <class T>
    template <class U>
    void
    freemonoidNode<T>::process(xercesc::DOMElement* node, T& aut,
			       U& param,
			       typename Node<T>::map_t& m,
			       typename Node<T>::factory_t& f)
    {
      process_monoid(node, aut, param, m, f);
    }


    TParmFMP
    template <class U>
    void
    monoidNode<FMPtype>::process(xercesc::DOMElement* node, FMPtype& aut,
				 U& param,
				 typename Node<FMPtype>::map_t& m,
				 typename Node<FMPtype>::factory_t& f)
    {
      using namespace xercesc;
      bool first = true;

      tools::ensure_monoid_type(node, param);

      if (! node || ! node->getFirstChild())
      {
	freemonoidNode<FMPtype>* nd_first = new freemonoidNode<FMPtype>;
	freemonoidNode<FMPtype>* nd_snd = new freemonoidNode<FMPtype>;
	nd_first->process(0, aut, param.first_monoid(), m, f);
	nd_snd->process(0, aut, param.second_monoid(), m, f);
      }
      else
	for (DOMNode* n = node->getFirstChild(); n; n = n->getNextSibling())
	  if (n->getNodeType() == DOMNode::ELEMENT_NODE)
	  {
	    DOMElement* elt = static_cast<DOMElement*>(n);
	    freemonoidNode<FMPtype>* nd = new freemonoidNode<FMPtype>;
	    if (first)
	    {
	      nd->process(elt, aut, param.first_monoid(), m, f);
	      first = false;
	    }
	    else
	      nd->process(elt, aut, param.second_monoid(), m, f);
	  }
    }


    /*------------.
    | <generator> |
    `------------*/
    template <class T>
    template <class U>
    void
    generatorNode<T>::process(xercesc::DOMElement* node, T&,
			      U& param,
			      typename Node<T>::map_t&,
			      typename Node<T>::factory_t&)
    {
      tools::insert_letter(param,
			   xml2str(node->getAttribute(transcode("value"))));
    }


    /*-----------.
    | <geometry> |
    `-----------*/
    template <class T>
    template <class U>
    void
    geometryNode<T>::process(xercesc::DOMElement* node, T&,
			     U& param,
			     typename Node<T>::map_t&,
			     typename Node<T>::factory_t&)
    {
      double x, y;
      if (node->hasAttribute(transcode("x")) && node->hasAttribute(transcode("y")))
      {
	std::istringstream xstr(xml2str(node->getAttribute(transcode("x"))));
	std::istringstream ystr(xml2str(node->getAttribute(transcode("y"))));
	xstr >> x;
	ystr >> y;
	param.first[param.second] = std::make_pair(x, y);
      }
      /// FIXME: handle attribute "direction".
    }


    /*----------.
    | <drawing> |
    `----------*/
    template <class T>
    template <class U>
    void
    drawingNode<T>::process(xercesc::DOMElement* node, T&,
			    U& param,
			    typename Node<T>::map_t&,
			    typename Node<T>::factory_t&)
    {
      double x, y;
      if (node->hasAttribute(transcode("labelPositionX")) &&
	  node->hasAttribute(transcode("labelPositionY")))
      {
	std::istringstream
	  xstr(xml2str(node->getAttribute(transcode("labelPositionX"))));
	std::istringstream
	  ystr(xml2str(node->getAttribute(transcode("labelPositionY"))));
	xstr >> x;
	ystr >> y;
	param.first[param.second] = std::make_pair(x, y);
      }
    }


    template <class T, class U>
    void
    handle_geometry(xercesc::DOMElement* node, T& aut,
		    U& param,
		    typename Node<T>::map_t& m,
		    typename Node<T>::factory_t& f)
    {
      std::string geometry("geometry");
      std::string drawing("drawing");

      using namespace xercesc;
      for (DOMNode* n = node->getFirstChild(); n; n = n->getNextSibling())
	if (n->getNodeType() == DOMNode::ELEMENT_NODE)
	{
	  if (xml2str(n->getNodeName()) == geometry)
	  {
	    geometryNode<T>* nd = new geometryNode<T>;
	    nd->process(static_cast<DOMElement*>(n), aut, param, m, f);
	  }
	  else if (xml2str(n->getNodeName()) == drawing)
	  {
	    drawingNode<T>* nd = new drawingNode<T>;
	    nd->process(static_cast<DOMElement*>(n), aut, param, m, f);
	  }
	}
    }


  } // ! xml

} // !vcsn

#endif // ! VCSN_XML_NODE_HXX
