// XML.hxx: this file is part of the Vaucanson project.
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


namespace vcsn
{
  namespace xml
  {

    template<typename Saver, typename Conv>
    void XML::operator()(std::ostream& out, const Saver& s,
			 const Conv&) const
    {
      xercesc::XMLPlatformUtils::Initialize();

      typedef typename Saver::automaton_t automaton_t;

      xml_converter<automaton_t> xc;
      xc.save(s.automaton(), out);

      xercesc::XMLPlatformUtils::Terminate();
    }


    template <typename Loader>
    void
    XML::operator()(std::istream& in, Loader& l)
    {
      xercesc::XMLPlatformUtils::Initialize();

      typedef typename Loader::automaton_t automaton_t;

      xml_converter<automaton_t> xc;
      xc.load(l.automaton(), in);

      xercesc::XMLPlatformUtils::Terminate();
    }


  } // !xml

} // !vcsn


#endif // ! VCSN_XML_XML_HXX
