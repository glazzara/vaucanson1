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

#ifndef VCSN_TOOLS_DUMPER_HXX
# define VCSN_TOOLS_DUMPER_HXX

# include <vaucanson/tools/usual_io.hh>
# include <vaucanson/tools/xml_dump.hh>
# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/tools/fsm_dump.hh>
# include <vaucanson/tools/simple_dump.hh>
# include <cstring>
# include <cstdlib>
# include <cerrno>
# include <string>

namespace vcsn
{
  namespace tools
  {
    int
    string_to_int (const std::string& s)
    {
      // I don't know how to do that properly in C++.
      errno = 0;
      const char *ccp = s.c_str ();
      char *cp;
      long res = std::strtol (ccp, &cp, 10);
      if (*cp || INT_MAX < res || errno)
      {
	std::cerr << "integer out of bounds: " << s;
	if (errno)
	  std::cerr << " (" << std::strerror (errno) << ")";
	std::cerr << std::endl;
	exit (1);
      }
      return res;
    }

    dumper::dumper (int argc, char **argv, int pos)
      : fmt_ (fmt_xml), argc_ (argc), argv_ (argv)
    {
      if (pos < argc_)
	fmt_ = dump_format (argv_[pos]);

      if (fmt_ == fmt_error)
      {
	std::cerr << "Invalid input: " << pos << " " << argv_[pos] << std::endl;
	usage (1);
      }
    }

    void
    dumper::usage (int estatus)
    {
      std::cerr << "Usage: " << argv_[0] << " ... <fmt>" << std::endl
		<< "where fmt is one of:" << std::endl
		<< "  dot     graphviz format" << std::endl
		<< "  fsm     FSM toolbox format" << std::endl
		<< "  simple  internal Vaucanson format" << std::endl
		<< "  xml     Vaucanson XML I/O format" << std::endl;
      exit (estatus);
    }

    enum dumper::dump_format
    dumper::dump_format (std::string fmt)
    {
      if (fmt == "dot")
	return fmt_dot;
      else if (fmt == "simple")
	return fmt_simple;
      else if (fmt == "xml")
	return fmt_xml;
      else if (fmt == "fsm")
	return fmt_fsm;
      else
	return fmt_error;
    }


    const char*
    dumper::get_fmt() const
    {
      switch(fmt_)
	{
	case fmt_dot: return "dot";
	case fmt_xml: return "xml";
	case fmt_simple: return "simple";
	case fmt_fsm: return "fsm";
	case fmt_error: abort ();
	}
      return "unknown";
    }

    void
    dumper::operator() (std::ostream& o,
			const automaton_t& automaton,
			const std::string& name)
    {
      switch(fmt_)
	{
	case fmt_dot:
	  vcsn::tools::dot_dump (o, automaton, name);
	  break;
	case fmt_xml:
	  vcsn::tools::xml_dump (o, automaton, name);
	  break;
	case fmt_simple:
	  vcsn::tools::simple_dump (o, automaton,
				    vcsn::io::usual_converter_poly<rat_exp_t>());
	  break;
	case fmt_fsm:
	  vcsn::tools::fsm_dump (o, automaton);
	  break;
	case fmt_error:
	  abort ();
	  break;
	}
    }

  }
}

#endif // !VCSN_TOOLS_DUMPER_HXX
