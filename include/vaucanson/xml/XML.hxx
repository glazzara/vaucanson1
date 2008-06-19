// XML.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_XML_HXX
# define VCSN_XML_XML_HXX

# include <vaucanson/xml/parsers.hh>
# include <vaucanson/xml/printers.hh>

namespace vcsn
{
  namespace xml
  {
    XML::XML(const std::string& name)
      :	name_(name)
    {
      XML::inst_ += 1;
      if (XML::inst_ == 1)
	xercesc::XMLPlatformUtils::Initialize();
    }

    XML::~XML()
    {
      XML::inst_ -= 1;
      if (!XML::inst_)
	xercesc::XMLPlatformUtils::Terminate();
    }

    XML::XML(const XML& old)
      :	name_(old.name_)
    {
      XML::inst_ += 1;
    }

    template<typename Saver, typename Conv>
    void XML::operator()(std::ostream& out,
			 const Saver& s,
			 const Conv&) const
    {
      typedef typename Saver::automaton_t automaton_t;
      AutPrinter<automaton_t>* printer = new AutPrinter<automaton_t>(s.automaton(), name_);
      printer->print(out);
      delete printer;
    }

    template <typename Loader>
    void
    XML::operator()(std::istream& in,
		    Loader& l,
		    bool check)
    {
      typedef typename Loader::automaton_t	automaton_t;
      AutParser<automaton_t>* parser = new AutParser<automaton_t>(l.automaton(), check);
      parser->parse(in);
      delete parser;
    }

    int XML::inst_ = 0;
  } // !xml
} // !vcsn

#endif // ! VCSN_XML_XML_HXX
