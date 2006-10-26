// xml_exp_visitor.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_XML_EXP_VISITOR_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_XML_EXP_VISITOR_HXX

# include <vaucanson/algebra/implementation/series/rat/xml_exp_visitor.hh>

# include <algorithm>
# include <sstream>
# include <vaucanson/xml/strings.hh>

namespace vcsn {

  namespace rat {

    using xml::transcode;

    template<typename M_, typename W_>
    XmlExpVisitor<M_,W_>::XmlExpVisitor(xercesc::DOMDocument* doc, const char* node_name) :
      doc_(doc),
      label_(doc_->createElement(transcode(node_name))),
      current_(label_)
    {}


    template<typename M_, typename W_>
    void
    XmlExpVisitor<M_,W_>::sum_or_product(const Node<M_, W_>* left_,
					 const Node<M_, W_>* right_)
    {
      left_->accept(*this);
      right_->accept(*this);
    }

    template<typename M_, typename W_>
    void
    XmlExpVisitor<M_, W_>::weight_or_star(const Node<M_, W_>* node)
    {
      node->accept(*this);
    }

    template<typename M_, typename W_>
    void
    XmlExpVisitor<M_, W_>::product(const Node<M_, W_>* left_,
				   const Node<M_, W_>* right_)
    {
      xercesc::DOMElement* tmp = current_;
      current_ = doc_->createElement(transcode("product"));
      sum_or_product(left_, right_);
      tmp->appendChild(current_);
      current_ = tmp;
    }

    template<typename M_, typename W_>
    void
    XmlExpVisitor<M_, W_>::sum(const Node<M_, W_>* left_,
			       const Node<M_, W_>* right_)
    {
      xercesc::DOMElement* tmp = current_;
      current_ = doc_->createElement(transcode("sum"));
      sum_or_product(left_, right_);
      tmp->appendChild(current_);
      current_ = tmp;
    }

    template<typename M_, typename W_>
    void
    XmlExpVisitor<M_, W_>::star(const Node<M_, W_>* node)
    {
      xercesc::DOMElement* tmp = current_;
      current_ = doc_->createElement(transcode("star"));
      weight_or_star(node);
      tmp->appendChild(current_);
      current_ = tmp;
    }

    template<typename M_, typename W_>
    void
    XmlExpVisitor<M_, W_>::left_weight(const W_& w, const Node<M_, W_>* node)
    {
      std::stringstream ss;
      ss << w;
      weight_ = ss.str();
      weight_or_star(node);
    }

    template<typename M_, typename W_>
    void
    XmlExpVisitor<M_, W_>::right_weight(const W_& w, const Node<M_, W_>* node)
    {
      std::stringstream ss;
      ss << w;
      weight_or_star(node);
    }

    template<typename M_, typename W_>
    void
    XmlExpVisitor<M_, W_>::constant(const M_& m)
    {
      std::stringstream ss;
      ss << m;
      xercesc::DOMElement* word = doc_->createElement(transcode("word"));
      word->setAttribute(transcode("value"), transcode(ss.str()));
      if (weight_.size())
      {
	word->setAttribute(transcode("weight"), transcode(weight_));
	weight_ = "";
      }
      current_->appendChild(word);
    }

    template<typename M_, typename W_>
    void XmlExpVisitor<M_, W_>::zero()
    {
      xercesc::DOMElement* zero = doc_->createElement(transcode("zero"));
      current_->appendChild(zero);
    }

    template<typename M_, typename W_>
    void XmlExpVisitor<M_, W_>::one()
    {
      xercesc::DOMElement* identity = doc_->createElement(transcode("identity"));
      current_->appendChild(identity);
      if (weight_.size())
      {
	identity->setAttribute(transcode("weight"), transcode(weight_));
	weight_ = "";
      }
    }

    template<typename M_, typename W_>
    xercesc::DOMElement*
    XmlExpVisitor<M_, W_>::get() const
    {
      return label_;
    }

    template<typename M_, typename W_>
    xercesc::DOMDocument*
    XmlExpVisitor<M_, W_>::set(xercesc::DOMDocument* v)
    {
      this->doc_ = v;
      return this->doc_;
    }


  } // End of namespace rat.

} // End of namespace vcsn.



#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_XML_EXP_VISITOR_HXX
