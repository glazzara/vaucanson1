// xml_automaton.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_XML_AUTOMATON_HXX
# define VCSN_XML_XML_AUTOMATON_HXX

# include <xercesc/framework/MemBufFormatTarget.hpp>
# include <xercesc/framework/Wrapper4InputSource.hpp>

# include <vaucanson/xml/xml_automaton.hh>

// FIXME: That is huge!
# include <vaucanson/boolean_automaton.hh>
# include <vaucanson/z_automaton.hh>
# include <vaucanson/r_automaton.hh>
# include <vaucanson/z_max_plus_automaton.hh>
# include <vaucanson/z_min_plus_automaton.hh>


# include <vaucanson/xml/error_handler.hh>
# include <vaucanson/xml/strings.hh>
# include <vaucanson/xml/ios.hh>

namespace vcsn
{

  namespace xml
  {

# define NEW_ATTR(X)				\
  template <typename I>				\
  struct attr_##X;

# define NEW_ATTR_VALUE(X,Y,V)			\
  template <>					\
  struct attr_##X < Y > {			\
    static const XMLCh* getstr()		\
    {						\
      return V;					\
    }						\
  };

    NEW_ATTR(semiring)
    NEW_ATTR_VALUE(semiring, algebra::NumericalSemiring, str_numerical)
    NEW_ATTR_VALUE(semiring, algebra::TropicalSemiring<algebra::TropicalMax>,
		   str_tropicalMax)
    NEW_ATTR_VALUE(semiring, algebra::TropicalSemiring<algebra::TropicalMin>,
		   str_tropicalMin)

    NEW_ATTR(semiring_impl)
    NEW_ATTR_VALUE(semiring_impl, bool, str_B)
    NEW_ATTR_VALUE(semiring_impl, int, str_Z)
    NEW_ATTR_VALUE(semiring_impl, float, str_R)

    NEW_ATTR(monoid)
    NEW_ATTR_VALUE(monoid, algebra::char_letter::Words, str_letters)
    NEW_ATTR_VALUE(monoid, algebra::char_pair::Words, str_pairs)
    NEW_ATTR_VALUE(monoid, algebra::weighted_letter::Words, str_weighted)
    NEW_ATTR_VALUE(monoid, algebra::int_letter::Words, str_integers)

    NEW_ATTR(monoid_impl)
    NEW_ATTR_VALUE(monoid_impl, algebra::char_letter::WordValue, str_free)
    NEW_ATTR_VALUE(monoid_impl, algebra::char_pair::WordValue, str_free)
    NEW_ATTR_VALUE(monoid_impl, algebra::weighted_letter::WordValue, str_free)
    NEW_ATTR_VALUE(monoid_impl, algebra::int_letter::WordValue, str_free)

    inline
    XmlAutomaton::XmlAutomaton()
    {
      DOMImplementation* impl =
	xercesc::DOMImplementationRegistry::getDOMImplementation(str_LS);

      DOMDocumentType* doctype =
	impl->createDocumentType(str_automaton, 0, str_vaucanson_pdtd);

      doc_ =
	impl->createDocument(str_http_c_s_swww_plrde_pepita_pfr_svaucanson,
			     str_automaton, doctype);

      root_		= doc_->getDocumentElement();
      structure_	= doc_->createElement(str_content);
      states_		= doc_->createElement(str_states);
      edges_		= doc_->createElement(str_transitions);
      initials_		= doc_->createElement(str_initials);
      finals_		= doc_->createElement(str_finals);


      structure_->appendChild(states_);
      structure_->appendChild(edges_);
      structure_->appendChild(initials_);
      structure_->appendChild(finals_);

      root_->appendChild(structure_);
    }

    inline
    XmlAutomaton::XmlAutomaton(DOMElement* root)
      : doc_ (root->getOwnerDocument()), root_ (root)
    {
      DOMNode* i = root->getFirstChild();

      structure_	= 0;
      states_		= 0;
      edges_		= 0;
      initials_		= 0;
      finals_		= 0;

      while (i)
	{
	  if (not XMLString::compareIString(i->getNodeName(), str_content))
	    {
	      structure_ = static_cast<DOMElement*> (i);

	      DOMNode* child = i->getFirstChild();
	      while (child)
		{
		  if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		    {
		      DOMElement* elt = static_cast<DOMElement*>(child);
		      if (not XMLString::compareIString(elt->getNodeName(),
							str_transitions))
			edges_ = elt;
		      else if (not XMLString::
			       compareIString(elt->getNodeName(), str_states))
			states_ = elt;
		      else if (not XMLString::
			       compareIString(elt->getNodeName(),
					      str_initials))
			initials_ = elt;
		      else if (not XMLString::
			       compareIString(elt->getNodeName(), str_finals))
			finals_ = elt;
		    }
		  child = child->getNextSibling();
		}
	    }
	  i = i ->getNextSibling();
	}

      if (not structure_)
	{
	  structure_ = doc_->createElement(str_content);
	  root_->appendChild(structure_);
	}
      if (not states_)
	{
	  states_ = doc_->createElement(str_states);
	  structure_->insertBefore(states_, edges_);
	}
      if (not edges_)
	{
	  edges_ = doc_->createElement(str_transitions);
	  structure_->insertBefore(edges_, finals_);
	}
      if (not initials_)
	{
	  initials_ = doc_->createElement(str_initials);
	  structure_->insertBefore(initials_, finals_);
	}
      if (not finals_)
	{
	  finals_ = doc_->createElement(str_finals);
	  structure_->appendChild(finals_);
	}

      DOMNode* child = states_->getFirstChild();
      unsigned j = 0;
      while (child)
	{
	  if (child->getNodeType() == DOMNode::ELEMENT_NODE and
	      not XMLString::compareIString(child->getNodeName(), str_state))
	    {
	      DOMElement* elt = static_cast<DOMElement*> (child);
	      if (elt->hasAttribute(str_name))
		{
		  std::string name = xml2str(elt->getAttribute(str_name));
		  hstate_t state (j++);
		  sname2num_[name] = state;
		  snum2name_[state] = name;
		}
	    }
	  child = child->getNextSibling();
	}

      child = edges_->getFirstChild();
      j = 0;
      while (child)
	{
	  if (child->getNodeType() == DOMNode::ELEMENT_NODE and
	      not XMLString::compareIString(child->getNodeName(), str_transition))
	    {
	      DOMElement* elt = static_cast<DOMElement*> (child);
	      hedge_t edge (j++);
	      edges_nodes_[edge] = elt;
	    }
	  child = child->getNextSibling();
	}
    }

    inline
    bool
    XmlAutomaton::operator == (const XmlAutomaton& rhs) const
    {
      return doc_ == rhs.doc_;
    }

    inline
    hstate_t
    XmlAutomaton::add_state(hstate_t i)
    {
      std::ostringstream s;
      s << "s" << i;

      while (sname2num_.find(s.str()) != sname2num_.end() or
	     snum2name_.find(i) != snum2name_.end())
	{
	  s.str("");
	  s << "s" << (i = i + 1);
	}

      return add_state(i, s.str());
    }


    inline
    hstate_t
    XmlAutomaton::add_state(const std::string& name)
    {
      unsigned i (0);

      while (snum2name_.find(i) != snum2name_.end())
	++i;

      return add_state(i, name);
    }

    inline
    hstate_t
    XmlAutomaton::add_state(hstate_t i, const std::string& str)
    {
      DOMElement* state = doc_->createElement(str_state);
      states_->appendChild(state);
      snum2name_[i] = str;
      sname2num_[str] = i;
      XMLCh* name = XMLString::transcode(str.c_str());
      state->setAttribute(str_name, name);
      XMLString::release(&name);

      return i;
    }

    inline
    void
    XmlAutomaton::del_state(hstate_t state)
    {
      assertion(has_state(state));
      if (not has_state(state))
	return ;

      std::string statename = snum2name_[state];

      DOMNode* i = states_->getFirstChild();
      while (i)
	{
	  if (i->getNodeType() == DOMNode::ELEMENT_NODE)
	    {
	      DOMElement* elt = static_cast<DOMElement*> (i);
	      if (xml2str(elt->getAttribute(str_name)) == statename)
		{
		  states_->removeChild(i);
		  snum2name_.erase(state);
		  sname2num_.erase(statename);
		  return ;
		}
	    }
	  i = i->getNextSibling();
	}
    }

    inline
    xercesc::DOMElement*
    XmlAutomaton::add_state_elt(hstate_t i)
    {
      std::ostringstream s;
      s << "s" << i;
      return add_state_elt(i, s.str());
    }

    inline
    xercesc::DOMElement*
    XmlAutomaton::add_state_elt(hstate_t i, const std::string& str)
    {
      DOMElement* state = doc_->createElement(str_state);
      states_->appendChild(state);
      snum2name_[i] = str;
      sname2num_[str] = i;
      XMLCh* name = XMLString::transcode(str.c_str());
      state->setAttribute(str_name, name);
      XMLString::release(&name);

      return state;
    }

    inline
    bool
    XmlAutomaton::has_state(hstate_t state) const
    {
      return snum2name_.find(state) != snum2name_.end();
    }

    inline
    hedge_t
    XmlAutomaton::add_edge(hstate_t source,
			   hstate_t destination,
			   const label_t& label)
    {
      precondition(has_state(source) and has_state(destination));

      DOMElement* edge = doc_->createElement(str_transition);
      edges_->appendChild(edge);
      XMLCh* lbl = XMLString::transcode(label.value().c_str());
      edge->setAttribute(str_label, lbl);
      XMLString::release(&lbl);

      lbl = XMLString::transcode(snum2name_[source].c_str());
      edge->setAttribute(str_src, lbl);
      XMLString::release(&lbl);
      lbl = XMLString::transcode(snum2name_[destination].c_str());
      edge->setAttribute(str_dst, lbl);
      XMLString::release(&lbl);

      unsigned n = 0;
      while (has_edge(hedge_t(n)))
	n++;
      edges_nodes_[hedge_t(n)] = edge;
      return n;
    }

    inline
    void
    XmlAutomaton::del_edge(hedge_t n)
    {
      precondition(has_edge(n));

      edges_->removeChild(edges_nodes_[n]);
      edges_nodes_.erase(n);
    }

    inline
    bool
    XmlAutomaton::has_edge(hedge_t edge) const
    {
      return edges_nodes_.find(edge) != edges_nodes_.end();
    }

    inline
    hstate_t
    XmlAutomaton::origin_of(hedge_t edge) const
    {
      precondition(has_edge(edge));

      return sname2num_.find(xml2str(edges_nodes_.find(edge)->second
				     ->getAttribute(str_dst)))->second;
    }

    inline
    hstate_t
    XmlAutomaton::aim_of(hedge_t edge) const
    {
      precondition(has_edge(edge));

      return sname2num_.find(xml2str(edges_nodes_.find(edge)->second
				     ->getAttribute(str_src)))->second;
    }

    inline
    xml_value_t
    XmlAutomaton::label_of(hedge_t edge) const
    {
      precondition(has_edge(edge));

      return xml2str(edges_nodes_.find(edge)->second->getAttribute(str_label));
    }

    inline
    xercesc::DOMElement*
    XmlAutomaton::set_initial(hstate_t state,
			      const xml_value_t& v,
			      const xml_value_t& z)
    {
      precondition(has_state(state));

      std::string statename = snum2name_[state];
      DOMNode* i = initials_->getFirstChild();
      DOMElement* init = 0;
      while (i)
	{
	  if (i->getNodeType() == DOMNode::ELEMENT_NODE)
	    {
	      DOMElement* elt = static_cast<DOMElement*>(i);
	      const XMLCh* l = elt->getAttribute(str_state);
	      if (xml2str(l) == statename)
		{
		  init = elt;
		  break ;
		}
	    }
	  i = i->getNextSibling();
	}
      if (z == v)
	{
	  if (init)
	    {
	      initials_->removeChild(init);
	      init->release();
	    }
	  return 0;
	}
      else
	{
	  if (not init)
	    {
	      init = doc_->createElement(str_initial);
	      initials_->appendChild(init);
	      XMLCh* n = XMLString::transcode(statename.c_str());
	      init->setAttribute(str_state, n);
	      XMLString::release(&n);
	    }
	  XMLCh* lbl = XMLString::transcode(v.value().c_str());
	  init->setAttribute(str_label, lbl);
	  XMLString::release(&lbl);
	  return init;
	}
    }

    inline
    xml_value_t
    XmlAutomaton::get_initial(hstate_t state,
			      const xml_value_t& z)
    {
      precondition(has_state(state));

      std::string statename = snum2name_[state];
      DOMNode* i = initials_->getFirstChild();
      while (i)
	{
	  if (i->getNodeType() == DOMNode::ELEMENT_NODE)
	    {
	      DOMElement* elt = static_cast<DOMElement*>(i);
	      const XMLCh* l = elt->getAttribute(str_state);
	      if (xml2str(l) == statename)
		{
		  if (elt->getAttribute(str_label))
		    {
		      const XMLCh* label = elt->getAttribute(str_label);
		      if (elt->hasAttribute(str_weight))
			{
			  const XMLCh* weight = elt->getAttribute(str_weight);
			  return "(" + xml2str(weight) +
			    " " + xml2str(label) + ")";
			}
		      else
			return xml2str(label);
		    }
		}
	    }
	  i = i->getNextSibling();
	}
      return z;
    }

    inline
    void
    XmlAutomaton::clear_initial()
    {
      DOMNode* i = initials_->getFirstChild();
      DOMNode* next;

      while (i)
	{
	  next = i->getNextSibling();
	  initials_->removeChild(i);
	  i = next;
	}
    }

    inline
    xercesc::DOMElement*
    XmlAutomaton::set_final(hstate_t state,
			    const xml_value_t& v,
			    const xml_value_t& z)
    {
      precondition(has_state(state));

      std::string statename = snum2name_[state];
      DOMNode* i = finals_->getFirstChild();
      DOMElement* final = 0;
      while (i)
	{
	  if (i->getNodeType() == DOMNode::ELEMENT_NODE)
	    {
	      DOMElement* elt = static_cast<DOMElement*>(i);
	      const XMLCh* l = elt->getAttribute(str_state);
	      if (xml2str(l) == statename)
		{
		  final = elt;
		  break ;
		}
	    }
	  i = i->getNextSibling();
	}
      if (z == v)
	{
	  if (final)
	    {
	      finals_->removeChild(final);
	      final->release();
	    }
	  return 0;
	}
      else
	{
	  if (not final)
	    {
	      final = doc_->createElement(str_final);
	      finals_->appendChild(final);
	      XMLCh* n = XMLString::transcode(statename.c_str());
	      final->setAttribute(str_state, n);
	      XMLString::release(&n);
	    }
	  XMLCh* lbl = XMLString::transcode(v.value().c_str());
	  final->setAttribute(str_label, lbl);
	  XMLString::release(&lbl);
	  return final;
	}
    }

    inline
    xml_value_t
    XmlAutomaton::get_final(hstate_t state,
			    const xml_value_t& z)
    {
      precondition(has_state(state));

      std::string statename = snum2name_[state];
      DOMNode* i = finals_->getFirstChild();
      while (i)
	{
	  if (i->getNodeType() == DOMNode::ELEMENT_NODE)
	    {
	      DOMElement* elt = static_cast<DOMElement*>(i);
	      const XMLCh* l = elt->getAttribute(str_state);
	      if (xml2str(l) == statename)
		{
		  if (elt->hasAttribute(str_label))
		    {
		      const XMLCh* label = elt->getAttribute(str_label);
		      if (elt->hasAttribute(str_weight))
			{
			  const XMLCh* weight = elt->getAttribute(str_weight);
			  return "(" + xml2str(weight) +
			    " " + xml2str(label) + ")";
			}
		      else
			return xml2str(label);
		    }
		}
	    }
	  i = i->getNextSibling();
	}
      return z;
    }

    inline
    void
    XmlAutomaton::clear_final()
    {
      DOMNode* i = initials_->getFirstChild();
      DOMNode* next;

      while (i)
	{
	  next = i->getNextSibling();
	  finals_->removeChild(i);
	  i = next;
	}
    }

    inline
    void
    XmlAutomaton::update(hedge_t edge, label_t label)
    {
      precondition(has_edge(edge));

      XMLCh* lbl = XMLString::transcode(label.value().c_str());
      if (edges_nodes_[edge]->hasAttribute(str_weight))
	edges_nodes_[edge]->removeAttribute(str_weight);
      edges_nodes_[edge]->setAttribute(str_label, lbl);
      XMLString::release(&lbl);
    }

    inline
    DOMDocument*
    XmlAutomaton::doc()
    {
      return doc_;
    }

    inline
    const DOMDocument*
    XmlAutomaton::doc() const
    {
      return doc_;
    }

# define XML_AUTOMATON_DEFINE_ACCESSOR(Name, Const)	\
    inline						\
    Const DOMElement*					\
    XmlAutomaton:: Name () Const			\
    {							\
      return Name ## _;					\
    }
# define XML_AUTOMATON_DEFINE_BOTH_ACCESSORS(Name)	\
    XML_AUTOMATON_DEFINE_ACCESSOR(Name, )		\
    XML_AUTOMATON_DEFINE_ACCESSOR(Name, const)

    XML_AUTOMATON_DEFINE_BOTH_ACCESSORS(root)
    XML_AUTOMATON_DEFINE_BOTH_ACCESSORS(structure)
    XML_AUTOMATON_DEFINE_BOTH_ACCESSORS(states)
    XML_AUTOMATON_DEFINE_BOTH_ACCESSORS(initials)
    XML_AUTOMATON_DEFINE_BOTH_ACCESSORS(finals)
    XML_AUTOMATON_DEFINE_BOTH_ACCESSORS(edges)

# undef XML_AUTOMATON_DEFINE_BOTH_ACCESSORS
# undef XML_AUTOMATON_DEFINE_ACCESSOR

  } // End of namespace xml.

} // End of namespace vcsn.

#endif // ! VCSN_XML_XML_AUTOMATON_HXX
