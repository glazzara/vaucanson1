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
  namespace tools
  {
    template <typename Auto, typename T, typename Format>
    struct automaton_saver_;

    template <typename RE, typename T, typename Format>
    struct regexp_saver_;

    template <typename Auto, typename T, typename Format>
    struct automaton_loader_;

    template <typename RE, typename T, typename Format>
    struct regexp_loader_;
  } // !tools

  namespace xml
  {

    class XML
    {
      public:
	XML(const std::string& name = "");
	XML(const XML& old);
	~XML();

	/**
	 * Write the automaton in the saver @a s to @a out.
	 */
	template <typename Auto, typename T, typename Format, typename Conv>
	void operator()(std::ostream& out,
			const vcsn::tools::automaton_saver_<Auto, T, Format>& s,
			const Conv& conv) const;

	/**
	 * Write the rational expression in the saver @a s to @a out.
	 */
	template <typename RE, typename T, typename Format, typename Conv>
	void operator()(std::ostream& out,
			const vcsn::tools::regexp_saver_<RE, T, Format>& s,
			const Conv& conv) const;

        /**
	 * Load an automaton from @a in into the loader @a l.
	 */
	template <typename Auto, typename T, typename Format>
	void operator()(std::istream& in, vcsn::tools::automaton_loader_<Auto, T, Format>& l, bool check = true);

	/**
	 * Load a rational expression from @a in into the loader @a l.
	 */
	template <typename RE, typename T, typename Format>
	void operator()(std::istream& in, vcsn::tools::regexp_loader_<RE, T, Format>& l, bool check = true);


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
