// XML.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_XML_HH
# define VCSN_XML_XML_HH

/**
 * @file XML.hh
 *
 * XML main file. Contains the base functor to load / save XML.
 *
 * @see io::automaton_loader, io::automaton_saver
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */


# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/xml/xml_converter.hh>


namespace vcsn
{
  namespace xml
  {
    struct XML
    {
      XML() : name_("")
	{}
      XML(const std::string& name) : name_(name)
	{}

      template <typename Saver, typename Conv>
      void operator()(std::ostream& out,
		      const Saver& s,
		      const Conv& conv) const;

      template<typename Loader>
      void operator()(std::istream& in, Loader& l);

    protected:
      const std::string name_;
    };

  } // !xml

} // !vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/XML.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_XML_XML_HH
