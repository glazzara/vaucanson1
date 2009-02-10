// printers.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007 The Vaucanson Group.
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

#ifndef VCSN_XML_PRINTERS_HH
# define VCSN_XML_PRINTERS_HH

/**
 * @file printers.hh
 *
 * Printers classes for the FSMXML document.
 *
 * @see vcsn::xml
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */

# include <vector>
# include <map>
# include <iostream>

# include <xercesc/dom/DOM.hpp>
# include <xercesc/util/XMLString.hpp>
# include <xercesc/util/PlatformUtils.hpp>

namespace vcsn
{
  namespace xml
  {
    /*
     * Printer class dedicated to parse an FSMXML document.
     */
    class Printer
    {
      public:
	Printer ();
	virtual ~Printer () = 0;
    };

    /*
     * Printer class dedicated to the parse an automaton.
     */
    template <typename Auto>
    class AutPrinter : public Printer
    {
      public:
	AutPrinter (const Auto& aut, const std::string& name = "");
	virtual ~AutPrinter ();

	void
	print (std::ostream& out);

      protected:
	typedef typename Auto::hstate_t			hstate_t;
	typedef typename Auto::htransition_t		htransition_t;
	typedef std::map<hstate_t, std::string>		map_t;
	typedef typename Auto::set_t			auto_set_t;
	typedef typename Auto::value_t			auto_impl_t;
	typedef typename Auto::series_set_elt_t		series_set_elt_t;

	std::string
	create_state(hstate_t s,
		     xercesc::DOMElement* root);
	void
	create_transition(htransition_t e,
			  xercesc::DOMElement* root);
	void
	create_initial(hstate_t s,
		       xercesc::DOMElement* root);
	void
	create_final(hstate_t s,
		     xercesc::DOMElement* root);

	void
	create_geometry(hstate_t&,
			xercesc::DOMElement* root);

	const Auto&			aut_;
	const std::string&		name_;

	map_t			state2str_;

	xercesc::DOMImplementation*	impl_;
	xercesc::DOMDocument*		doc_;
	xercesc::DOMElement*		root_;
    };

    /*
     * Printer class dedicated to the parse a rational expression.
     */
    template <typename RE>
    class RegExpPrinter : public Printer
    {
      public:
	RegExpPrinter (const RE& regexp, const std::string& name = "");
	virtual ~RegExpPrinter ();

	void
	print (std::ostream& out);

      protected:
	const RE&			regexp_;
	const std::string&		name_;

	xercesc::DOMImplementation*	impl_;
	xercesc::DOMDocument*		doc_;
	xercesc::DOMElement*		root_;
    };
  } // !xml
} // !vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/xml/printers.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_XML_PRINTERS_HH
