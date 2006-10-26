// xml_exp_visitor.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_XML_EXP_VISITOR_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_XML_EXP_VISITOR_HH

/**
 * @file xml_exp_visitor.hh
 *
 * Visits the expression so as to give back an XML tree of the expression.
 *
 * @author Florent Terrones <florent.terrones@lrde.epita.fr>
 */

# include <xercesc/dom/DOM.hpp>
# include <xercesc/util/XMLString.hpp>
# include <xercesc/util/PlatformUtils.hpp>
# include <vaucanson/misc/usual_macros.hh>
# include <string>
# include <cstddef>

# include <vaucanson/algebra/implementation/series/rat/nodes.hh>

namespace vcsn {

  namespace rat {

    template<typename M_, typename W_>
    class XmlExpVisitor : public ConstNodeVisitor<M_, W_>
    {
    public:
      XmlExpVisitor(xercesc::DOMDocument* doc, const char* node_name);

      virtual void
      product(const Node<M_, W_>* left_, const Node<M_, W_>* right_);

      virtual void
      sum(const Node<M_, W_>* left_, const Node<M_, W_>* right_);

      virtual void
      star(const Node<M_, W_>* node);

      virtual void
      left_weight(const W_&, const Node<M_, W_>* node);

      virtual void
      right_weight(const W_&, const Node<M_, W_>* node);

      virtual void
      constant(const M_& m);

      virtual void zero();

      virtual void one();

      xercesc::DOMElement* get() const;

      xercesc::DOMDocument* set(xercesc::DOMDocument* v);

    protected:
      void sum_or_product(const Node<M_, W_>* left_, const Node<M_, W_>* right_);
      void weight_or_star(const Node<M_, W_>* node);

    protected:
      xercesc::DOMDocument*	doc_;
      xercesc::DOMElement*	label_;
      xercesc::DOMElement*	current_;
      std::string		weight_;
    };

  } // rat

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/implementation/series/rat/xml_exp_visitor.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_XML_EXP_VISITOR_HH
