// dumper.hcc: this file is part of the Vaucanson project.   -*- C++ -*-
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2007 The Vaucanson Group.
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

/**
 * @file dumper.hh
 *
 * @brief Wrap calls to dumpers for various formats.
 *
 * This file was written quickly and somewhat dirtily by Raphaël Poss,
 * and slightly cleaned by Akim Demaille.  Undoubtedly, more polishing
 * and thinking might be very useful.  No doubt that such a feature
 * (dumping to several formats) is pleasant.
 *
 * @warning: A context must be opened before using this file (it
 * uses the @c automaton_t type).  That's why this file is not checked
 * for sanity.
 *
 * @author Raphaël Poss <Raphael.Poss@lrde.epita.fr>
 */

#ifndef VCSN_TOOLS_DUMPER_HH
# define VCSN_TOOLS_DUMPER_HH
# ifndef  VCSN_SANITY_CHECK

#  include <string>

namespace vcsn
{
  namespace tools
  {
    /// Return the decimal value of @a s.
    int string_to_int (const std::string& s);

    struct dumper
    {
	/// Build a dumper which arguments are in @a argv starting at @a pos.
        /// Dumps for "xml", unless argv[pos] specifies otherwise.
	dumper (int argc, char **argv, int pos = 1);

	/// Display a help message, and exit with status @a estatus.
	void usage (int estatus);

	enum dump_format
	{
	  fmt_error,
	  fmt_dot,
	  fmt_fsm,
	  fmt_simple,
	  fmt_xml,
	};

	enum dump_format dump_format (std::string fmt);

	const char* get_fmt () const;

	void
	operator () (std::ostream& o,
		     const automaton_t& automaton,
		     const std::string& name = "automaton");
      private:
	enum dump_format fmt_;
	int argc_;
	char** argv_;
    };
  }
}

#  ifndef VCSN_USE_INTERFACE_ONLY
#   include <vaucanson/tools/dumper.hxx>
#  endif // ! VCSN_USE_INTERFACE_ONLY
# endif // ! VCSN_SANITY_CHECK
#endif // ! VCSN_TOOLS_DUMPER_HH && ! VCSN_SANITY_CHECK
