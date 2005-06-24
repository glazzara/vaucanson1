// node.hxx: this file is part of the Vaucanson project.
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

# define PROCESS_NODE(name)						   \
    template <class T>							   \
    void name ## Node<T>::process(xercesc::DOMElement* node, T& aut,	   \
				  typename Node<T>::map_t& m,		   \
				  typename Node<T>::factory_t& f)	   \
    {									   \
      using namespace xercesc;						   \
      for (DOMNode* n = node->getFirstChild(); n; n = n->getNextSibling()) \
	if (n->getNodeType() == DOMNode::ELEMENT_NODE)			   \
	  {								   \
	    DOMElement* elt = static_cast<DOMElement*>(n);		   \
	    Node<T>* node = f.create_object(xml2str(elt->getNodeName()));  \
	    node->process(elt, aut, m, f);				   \
	  }								   \
    }


# define PROCESS_ROOT_NODE(name)					   \
    template <class T>							   \
    void name ## Node<T>::process(xercesc::DOMElement* node, T& aut,	   \
				  typename Node<T>::map_t& m,		   \
				  typename Node<T>::factory_t& f)	   \
    {									   \
      using namespace xercesc;						   \
      bool type_done = false;						   \
      for (DOMNode* n = node->getFirstChild(); n; n = n->getNextSibling()) \
	if (n->getNodeType() == DOMNode::ELEMENT_NODE)			   \
	  {								   \
	    DOMElement* elt = static_cast<DOMElement*>(n);		   \
	    if (! type_done)						   \
	      {								   \
		if (XMLString::compareIString(n->getNodeName(),		   \
					      STR2XML("type")))		   \
		  {							   \
		    typeNode<T>* node = new typeNode<T>;		   \
		    node->process(0, aut, m, f);			   \
		  }							   \
		type_done = true;					   \
	      }								   \
             Node<T>* node = f.create_object(xml2str(elt->getNodeName())); \
	     node->process(elt, aut, m, f);				   \
	  }								   \
    }


# define PROCESS_TYPE_NODE(TempParam, AutType)				      \
    TempParam								      \
    void typeNode<AutType>::process(xercesc::DOMElement* node, AutType& aut,  \
				    typename Node<AutType>::map_t& m,	      \
				    typename Node<AutType>::factory_t& f)     \
    {									      \
      using namespace xercesc;						      \
      bool monoid_done = false, semiring_done = false;			      \
									      \
      if (! node)							      \
	process_type(node, aut, m, f, monoid_done, semiring_done);	      \
      else								      \
	for (DOMNode* n = node->getFirstChild(); n; n = n->getNextSibling())  \
	  if (n->getNodeType() == DOMNode::ELEMENT_NODE)		      \
	    {								      \
	      DOMElement* elt = static_cast<DOMElement*>(n);		      \
	      process_type(elt, aut, m, f, monoid_done, semiring_done);      \
	    }								      \
    }

PROCESS_ROOT_NODE(transducer)
PROCESS_ROOT_NODE(automaton)
PROCESS_TYPE_NODE(TParm, AUTtype)
PROCESS_TYPE_NODE(TParm, TRANStype)
PROCESS_TYPE_NODE(TParmFMP, FMPtype)
PROCESS_NODE(type)
PROCESS_NODE(content)
PROCESS_NODE(states)
PROCESS_NODE(transitions)


    /*-------.
    | <type> |
    `-------*/
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
	  /// FIXME: Remove these const_cast.
	  nd->process(elt, aut,
		      const_cast<typename T::monoid_t&>
		      (aut.structure().series().monoid()), m, f);
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
	    nd->process(elt, aut,
			const_cast<typename T::semiring_t&>
			(aut.structure().series().semiring()), m, f);
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
			  typename Node<T>::factory_t&)
    {
      m[xml2str(node->getAttribute(STR2XML("name")))] = aut.add_state();

      using namespace xercesc;
      for (DOMNode* n = node->getFirstChild(); n; n = n->getNextSibling())
	if (n->getNodeType() == DOMNode::ELEMENT_NODE)
	  {
	    //DOMElement* elt = static_cast<DOMElement*> (n);
	    // Deals with geometry tag.
	  }
    }


    /*-------------.
    | <transition> |
    `-------------*/
    template <class T>
    void
    transitionNode<T>::process(xercesc::DOMElement* node, T& aut,
			       typename Node<T>::map_t& m,
			       typename Node<T>::factory_t&)
    {
      hstate_t src = m[xml2str(node->getAttribute(STR2XML("src")))];
      hstate_t dst = m[xml2str(node->getAttribute(STR2XML("dst")))];
      typename T::series_set_elt_t s = tools::get_series(node, aut);
      aut.add_series_edge(src, dst, s);
    }


    /*----------.
    | <initial> |
    `----------*/
    template <class T>
    void
    initialNode<T>::process(xercesc::DOMElement* node, T& aut,
			    typename Node<T>::map_t& m,
			    typename Node<T>::factory_t&)
    {
      hstate_t state = m[xml2str(node->getAttribute(STR2XML("state")))];
      typename T::series_set_elt_t s = tools::get_series(node, aut);
      aut.set_initial(state, s);
    }


    /*--------.
    | <final> |
    `--------*/
    template <class T>
    void
    finalNode<T>::process(xercesc::DOMElement* node, T& aut,
			  typename Node<T>::map_t& m,
			  typename Node<T>::factory_t&)
    {
      hstate_t state = m[xml2str(node->getAttribute(STR2XML("state")))];
      typename T::series_set_elt_t s = tools::get_series(node, aut);
      aut.set_final(state, s);
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
      using namespace xercesc;
      tools::ensure_semiring_type(node, a, param);

      monoidNode<TRANStype>* nd = new monoidNode<TRANStype>;

      /// FIXME: Remove these const_cast.
      if (! node || ! node->getFirstChild())
	nd->process(0, a, const_cast<typename TRANStype::monoid_t&>
		    (param.monoid()), m, f);
      else
	for (DOMNode* n = node->getFirstChild(); n; n = n->getNextSibling())
	  if (n->getNodeType() == DOMNode::ELEMENT_NODE)
	    nd->process(static_cast<DOMElement*>(n), a,
			const_cast<typename TRANStype::monoid_t&>
			(param.monoid()), m, f);
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

      // Fill monoid with letters.
      if (! node || ! node->getFirstChild())
	for (unsigned int i = 0; i < 256; ++i)
	  param.alphabet().insert(i);
      else
	for (DOMNode* n = node->getFirstChild(); n; n = n->getNextSibling())
	  if (n->getNodeType() == DOMNode::ELEMENT_NODE)
	    {
	      DOMElement* elt = static_cast<DOMElement*>(n);
	      generatorNode<T>* nd = static_cast<generatorNode<T>*>
		(f.create_object(xml2str(elt->getNodeName())));
	      nd->process(elt, aut, param.alphabet(), m, f);
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
			   xml2str(node->getAttribute(STR2XML("value"))));
    }

  } // ! xml

} // !vcsn


# undef PROCESS_NODE
# undef PROCESS_ROOT_NODE
# undef CREATE_TYPE_NODE
# undef CREATE_SPEC_PARAM_NODE
# undef AUTtype
# undef TRANStype
# undef FMPtype
# undef TParm
# undef TParmFMP

#endif // ! VCSN_XML_NODE_HXX
