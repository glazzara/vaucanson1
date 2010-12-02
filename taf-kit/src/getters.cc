// getters.xx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008, 2009, 2010 The Vaucanson Group.
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

# include "common.hh"

# include CONTEXT_HEADER
# if defined(WITH_TWO_ALPHABETS) || defined(FMP_CONTEXT) || defined(FMPI_CONTEXT)
#  include <vaucanson/xml/contexts/fmp.hh>
# endif
# include <vaucanson/xml/XML.hh>
using vcsn::xml::XML;
# include <vaucanson/tools/dot_display.hh>

# include <vaucanson/tools/fsm_load.hh>
# include <string>
# include <cstdlib>
# include "getters.hh"
# include "library_commands.hh"
# include "pipe_getters.hh"
# include "pipe_writers.hh"
# include "pipe.hxx"
# include "pipe_getters.hxx"
# include "pipe_writers.hxx"
#include <sstream>
#include <boost/spirit/core.hpp>
#include "boost_spirit_compatibility.hh"

using namespace CONTEXT_NAMESPACE;
using namespace vcsn;
using namespace vcsn::tools;

// We can not pass rules by value (hence the references).
# define ALPHABET_DEFINITION(letter_type) \
void \
if_is_char_letter(boost::VCSN_SPIRIT_CLASSIC::rule<boost::VCSN_SPIRIT_CLASSIC::scanner<const char*> >& def, \
		  const boost::VCSN_SPIRIT_CLASSIC::rule<boost::VCSN_SPIRIT_CLASSIC::scanner<const char*> >& case_true, \
		  const boost::VCSN_SPIRIT_CLASSIC::rule<boost::VCSN_SPIRIT_CLASSIC::scanner<const char*> >& case_false) \
{ \
  def = misc::static_if< \
  misc::static_eq<vcsn::algebra::letter_traits<letter_type>::is_char_letter, misc::true_t>::value, \
  boost::VCSN_SPIRIT_CLASSIC::rule<boost::VCSN_SPIRIT_CLASSIC::scanner<const char*> >&, \
  boost::VCSN_SPIRIT_CLASSIC::rule<boost::VCSN_SPIRIT_CLASSIC::scanner<const char*> >& \
  >::choose(case_true, case_false); \
}

// Setup letter context.
# define LETTER_CONTEXT(letter_type) \
ALPHABET_DEFINITION(letter_type)

unsigned get_unsigned (const arguments_t& args, int n)
{
  const char* s(args.args[n]);
  std::stringstream ss(s);
  unsigned result;
  if ((ss >> result).fail() || !(ss >> std::ws).eof())
    {
      std::cerr << "Error: cannot parse `" << s << "' as unsigned integer."
		<< std::endl;
      exit(1);
    }
  return result;
}


  /*---------------------------------------------.
  | Getters for alphabet, RatExp and automaton.  |
  `---------------------------------------------*/
# define DEFINE_GET_ALPHABET(Name, Type, Opt)				\
Type Name (const std::vector<std::string>& al)			\
{									\
  Type a;								\
  if (al.empty())							\
  {									\
    warn ("Error: alphabet should be explicitly defined using --" Opt);	\
    exit (-2);								\
  }									\
  for (std::vector<std::string>::const_iterator i = al.begin();		\
       i != al.end(); ++i)						\
    a.insert (*i);							\
  return a;								\
}


/// Getter for alphabet.
# ifndef WITH_TWO_ALPHABETS

DEFINE_GET_ALPHABET(get_alphabet, alphabet_t, "alphabet");

alphabet_t get_alphabet (const rat_exp_t& exp)
{
  return exp.structure().monoid().alphabet();
}

# else

DEFINE_GET_ALPHABET (get_first_alphabet, first_alphabet_t, "alphabet1");
DEFINE_GET_ALPHABET (get_second_alphabet, second_alphabet_t, "alphabet2");

# endif

bool
file_exists(const char* name, bool abort_if_empty)
{
  struct stat s;

  if ((stat(name, &s) != 0))
    return false;

  if (abort_if_empty && s.st_size == 0)
    {
      std::cerr << "Error: `" << name << "' is an empty file." << std::endl;
      exit(1);
    }

  return true;
}

std::string
locate_file(const arguments_t& args, const std::string& s,
	    bool abort_if_empty)
{
  // First, try to load the file as given.
  const char* ss = s.c_str();
  if (file_exists(ss))
    return s;

  // Then, try the automata path.
  const std::list<std::string>& path = get_automata_path();

  std::list<std::string>::const_iterator i;
  for (i = path.begin(); i != path.end(); ++i)
    {
      std::string file = *i + "/" + s;
      const char* f = file.c_str();
      if (file_exists(f, abort_if_empty))
	return file;
    }

  // If we failed, return the filename unchanged, so
  // we can complain about it.
  return s;
}

# ifndef WITH_TWO_ALPHABETS
/// Getter for RatExp.
rat_exp_t get_exp(const arguments_t& args, const int& n)
{
  const std::string& s = args.args[n];
  const std::vector<std::string>& alphabet = args.alphabet;

  // Build a monoid and a series with smart token representations.
  //
  // FIXME: ideally we should call get_alphabet() when s == "-" and we
  // are reading from STDIN, but it's not clear how to detect that
  // here.  When s == "-", there is more chances that we are reading
  // the output of the previous command and we should not force the
  // call to get_alphabet().
  alphabet_t alpha;
  monoid_t M((!alphabet.empty() ||
	      (s != "-" && g_res.input_exp_type == INPUT_TYPE_EXP))
	     ? get_alphabet(alphabet) : alpha);
  semiring_t S;
  series_set_t series(S, M);


  rat_exp_t	e(series);

  if (s == "-")
  {
    rat_exp_t e =
      boost::apply_visitor(rat_exp_getter(M.alphabet(),
					  g_res.name,
					  g_res.input_exp_type,
					  *(M.representation()),
					  *(series.representation())),
			   g_res.output);
    // Overwrite the writing data before return if any where supplied
    // on the command line.
    set_writing_data(e, args);
    return e;
  }

  switch (g_res.input_exp_type)
  {
    case INPUT_TYPE_XML:
    {
      std::string ifile = locate_file(args, s);
      std::istream* is = new std::ifstream(ifile.c_str());
      if (not is->fail ())
      {
	using namespace vcsn::tools;
	using namespace vcsn::xml;

	*is >> regexp_loader(e, string_out(), XML());

	delete is;

	// Overwrite the writing data before return if any where supplied
	// on the command line.
	set_writing_data(e, args);
	return e;
      }
      else
      {
	std::cerr << "Error: cannot open `" << ifile << "'." << std::endl;
	exit(1);
      }
      break;
    }
    case INPUT_TYPE_EXP:
    {
      set_monoid_writing_data_(*(M.representation()), args.mrep, args.cf);
      set_series_writing_data_(*(series.representation()), args.srep, args.cf);

      e = make_rat_exp(M.alphabet(),
		       s,
		       *(M.representation()),
		       *(series.representation()));

      break;
    }
    default:
      std::cerr << "Error: could not load rational expression." << std::endl;
      exit(1);
  }

  return e;
}


# endif // !WITH_TWO_ALPHABETS

/// Getter for automaton.
automaton_t get_aut (const arguments_t& args, int n)
{
  const std::string& s = args.args[n];

  if (s == "-")
    {
      automaton_t a = boost::apply_visitor
	(automaton_getter (g_res.name,
			   g_res.input_aut_type), g_res.output);

      // Set the writing data before return.
      set_writing_data(a, args);

      return a;
    }

  std::string ifile = locate_file(args, s);
  std::istream* is = new std::ifstream(ifile.c_str());

  if (not is->fail ())
  {
    using namespace vcsn::tools;
    using namespace vcsn::xml;

# ifndef WITH_TWO_ALPHABETS
    automaton_t a = make_automaton(alphabet_t());
# else
    automaton_t a = make_automaton(first_alphabet_t(), second_alphabet_t());
# endif // !WITH_TWO_ALPHABETS

    switch (g_res.input_aut_type)
      {
      case INPUT_TYPE_XML:
	*is >> automaton_loader(a, string_out (), XML ());
	break;
# ifndef WITH_TWO_ALPHABETS
      case INPUT_TYPE_FSM:
	fsm_load(*is, a);
	break;
# endif // !WITH_TWO_ALPHABETS
      default:
	std::cerr << "Error: could not load automaton `"
		  << ifile << "'." << std::endl;
	exit(1);
      }

    delete is;

    // Set the writing data before return.
    set_writing_data(a, args);

    return a;
  }
  else
  {
    std::cerr << "Error: cannot open `" << ifile << "'." << std::endl;
    exit(1);
  }
}


int
write_aut(const automaton_t& aut, const arguments_t& args, int n)
{
  std::ofstream output(args.args[n]);
  if (not output.good())
  {
    warn("Error opening `" << args.args[n] << "'.");
    return -1;
  }

  output << automaton_saver(aut, string_out(), XML());
  output.close ();
  return 0;
}

int
display_aut(const automaton_t& aut, const arguments_t& args, int n)
{
  return vcsn::tools::dot_display(aut, args.args[n], true);
}

#ifdef WITH_TWO_ALPHABETS
IOAUT_CONTEXT::automaton_t get_boolean_aut(const arguments_t& args, const int& n)
{
  const std::string& s = args.args[n];

  if (s == "-")
  {
    IOAUT_CONTEXT::automaton_t a =
      boost::apply_visitor(boolean_automaton_getter
			   (g_res.name, g_res.input_aut_type),
			   g_res.output);

    // Set the writing data before return.
    set_boolean_writing_data(a, args);

    return a;
  }

  std::string ifile = locate_file(args, s);
  std::istream* is = new std::ifstream(ifile.c_str());

  if (not is->fail())
  {
    using namespace vcsn::tools;
    using namespace vcsn::xml;

    IOAUT_CONTEXT::automaton_t a =
      IOAUT_CONTEXT::make_automaton(first_alphabet_t());

    switch (g_res.input_aut_type)
      {
      case INPUT_TYPE_XML:
	*is >> automaton_loader(a, string_out (), XML ());
	break;
      case INPUT_TYPE_FSM:
	fsm_load(*is, a);
	break;
      default:
	std::cerr << "Error: could not load automaton `"
		  << ifile << "'." << std::endl;
	exit(1);
      }

    delete is;

    // Set the writing data before return.
    set_boolean_writing_data(a, args);

    return a;
  }
  else
  {
    std::cerr << "Error: could not load automaton `"
	      << ifile << "'." << std::endl;
    exit(1);
  }
}

mute_ltl_to_pair<automaton_t::set_t, automaton_t::value_t>::ret
get_pair_aut(const arguments_t& args, const int& n)
{
  const std::string& s = args.args[n];

  if (s == "-")
  {
    mute_ltl_to_pair<automaton_t::set_t, automaton_t::value_t>::ret a =
      boost::apply_visitor(pair_automaton_getter
			   (g_res.name, g_res.input_aut_type),
			   g_res.output);

    // We don't set the writing data before return because the
    // pair automaton will be passed to pair_to_fmp and we will
    // force the writing data on the resulting fmp.

    return a;
  }

  std::string ifile = locate_file(args, s);
  std::istream* is = new std::ifstream(ifile.c_str());

  if (not is->fail())
  {
    using namespace vcsn::tools;
    using namespace vcsn::xml;

    mute_ltl_to_pair<automaton_t::set_t, automaton_t::value_t>::ret a =
      mute_ltl_to_pair<automaton_t::set_t, automaton_t::value_t>::
      make_automaton(mute_ltl_to_pair<automaton_t::set_t,
		                      automaton_t::value_t>::ret_alphabet_t());

    switch (g_res.input_aut_type)
      {
      case INPUT_TYPE_XML:
	*is >> automaton_loader(a, string_out (), XML ());
	break;
      case INPUT_TYPE_FSM:
	fsm_load(*is, a);
	break;
      default:
	std::cerr << "Error: could not load automaton `"
		  << ifile << "'." << std::endl;
	exit(1);
      }

    delete is;

    // We don't set the writing data before return because the
    // pair automaton will be passed to pair_to_fmp and we will
    // force the writing data on the resulting fmp.
    return a;
  }
  else
  {
    std::cerr << "Error: could not load automaton `"
	      << ifile << "'." << std::endl;
    exit(1);
  }
}
#endif // !WITH_TWO_ALPHABETS

# ifdef WITH_TWO_ALPHABETS

LETTER_CONTEXT(automaton_t::monoid_t::first_monoid_t::letter_t)

void set_boolean_writing_data(IOAUT_CONTEXT::automaton_t& a,
			      const arguments_t& args)
{
  set_series_writing_data_(*(a.structure().series().representation()),
			   args.srep.first_representation(), args.cf1);
  set_monoid_writing_data_(*(a.structure().series().monoid().representation()),
			   args.mrep1, args.cf1);
}
void set_writing_data(automaton_t& a, const arguments_t& args)
{
  set_series_writing_data_(*(a.structure().series().representation()),
			   args.srep, args.cf);
  set_monoid_writing_data_(*(a.structure().series().monoid().representation()),
			   args.mrep, args.cf);

  set_series_writing_data_(a.structure().series().representation()->first_representation(),
			   args.srep.first_representation(), args.cf1);
  set_monoid_writing_data_(*(a.structure().series().monoid().first_monoid().representation()),
			   args.mrep1, args.cf1);

  set_series_writing_data_(a.structure().series().representation()->second_representation(),
			   args.srep.second_representation(), args.cf2);
  set_monoid_writing_data_(*(a.structure().series().monoid().second_monoid().representation()),
			   args.mrep2, args.cf2);
}
# else

LETTER_CONTEXT(letter_t)

void set_writing_data(automaton_t& a, const arguments_t& args)
{
  set_series_writing_data_(*(a.structure().series().representation()),
			   args.srep, args.cf);
  set_monoid_writing_data_(*(a.structure().series().monoid().representation()),
			   args.mrep, args.cf);
}

void set_writing_data(rat_exp_t& e, const arguments_t& args)
{
  set_series_writing_data_(*(e.structure().representation()),
			   args.srep, args.cf);
  set_monoid_writing_data_(*(e.structure().monoid().representation()),
			   args.mrep, args.cf);
}

# endif // ! WITH_TWO_ALPHABETS
