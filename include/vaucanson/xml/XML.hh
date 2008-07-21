// XML.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_XML_HH
# define VCSN_XML_XML_HH

/**
 * @file XML.hh
 *
 * XML Format functor to load and save an automaton.
 *
 * @see io::automaton_loader, io::automaton_saver
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */

# include <string>
# include <iostream>

namespace vcsn
{
  namespace xml
  {
    class Handler;

    class XML
    {
      public:
	XML(const std::string& name = "");
	XML(const XML& old);
	~XML();

	/**
	 * Write the automaton in the saver @a s to @a out.
	 */
	template <typename Saver, typename Conv>
	void operator()(std::ostream& out,
			const Saver& s,
			const Conv& conv) const;

        /**
	 * Load an automaton from @a in into the loader @a l.
	 */
	template <typename Loader>
	void operator()(std::istream& in, Loader& l, bool check = true); // FIXME set to false

	/**
	 * Counter of instances of XML
	 * Required to intialize and clean xercesc only once.
	 */
	static int inst_;
      protected:
	const	std::string name_;
    };
  } // !xml
} // !vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/XML.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_XML_XML_HH
