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

/**
 * @file XML.hxx
 *
 * XML main file. Contains the base functor to load / save XML.
 *
 * @see io::automaton_loader, io::automaton_saver
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */

# include <xercesc/sax/SAXException.hpp>

# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/xml/xml_converter.hh>
# include <vaucanson/xml/parsers.hh>

namespace vcsn
{
  namespace xml
  {
    XML::XML(const std::string& name, bool use_label_node)
      :	name_(name), use_label_node_(use_label_node), check_(true)
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
      :	name_(old.name_),
	use_label_node_(old.use_label_node_),
	check_(old.check_)
    {
      XML::inst_ += 1;
    }

    void
    XML::check(bool check)
    {
      check_ = check;
    }

    template<typename Saver, typename Conv>
    void XML::operator()(std::ostream& out, const Saver& s,
			 const Conv&) const
    {
      typedef typename Saver::automaton_t automaton_t;

      xml_converter<automaton_t> xc(use_label_node_);
      xc.save(s.automaton(), out, name_);
    }

    template <typename Loader>
    void
    XML::operator()(std::istream& in, Loader& l)
    {

      typedef typename Loader::automaton_t	automaton_t;
      AutParser<automaton_t>* parser = new AutParser<automaton_t>(l.automaton(), check_);
      parser->parse(in);
      // FIXME The use of xercesc::XMLPlatformUtils::Terminate()
      // does not seems to appreciate the parser to be deleted.
      // delete parser;
    }

    int XML::inst_ = 0;
  } // !xml
} // !vcsn

#endif // ! VCSN_XML_XML_HXX
