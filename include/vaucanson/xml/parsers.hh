// parsers.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_PARSERS_HH
# define VCSN_XML_PARSERS_HH

/**
 * @file parsers.hh
 *
 * Parsers classes for the FSMXML document.
 *
 * @see vcsn::xml
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */

# include <iostream>

# include <xercesc/sax2/SAX2XMLReader.hpp>

# include <vaucanson/xml/handlers.hh>
# include <vaucanson/xml/xmleq.hh>

namespace vcsn
{
  namespace xml
  {
    /*
     * Parser class dedicated to parse an FSMXML document.
     */
    class Parser
    {
      public:
	Parser (bool check = true);
	virtual ~Parser ();

      protected:
	std::string
	get_xsd_path ();

	ErrHandler*			err_handler_;
	/// Required to enable a change of the Handler while parsing.
	xercesc::SAX2XMLReader*		parser_;
	/// Store all the known token to make comparison quicker.
	XMLEq				eq_;
    };

    /*
     * Parser class dedicated to the parse an automaton.
     */
    template <typename Auto>
    class AutParser : public Parser
    {
      public:
	AutParser (Auto& a, bool check = true);
	virtual ~AutParser ();

	void
	parse (std::istream& in);

      protected:
	AutHandler<Auto>*	doc_handler_;
	Auto&			a_;
    };

    /*
     * Parser class dedicated to the parse of list of automata.
     */
    class SessParser : public Parser
    {
      public:
	SessParser (bool check = true);
	virtual ~SessParser();

	void
	init (std::istream& in);

	template <typename Auto>
	bool
	operator() (Auto& a);

      private:
	bool			      got_more_;
	xercesc::XMLPScanToken	      token_;
    };
  } // !xml
} // !vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/xml/parsers.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_XML_PARSERS_HH
