// vgrep.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/realtime.hh>
#include <vaucanson/algorithms/complete.hh>
#include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>
#include <vaucanson/algorithms/standard_of.hh>
#include <vaucanson/algorithms/thompson.hh>
#include <vaucanson/algorithms/eval.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <vaucanson/tools/dot_dump.hh>

#include <iostream>
#include <vector>
#include <ctype.h>
#include <string>
#include <unistd.h>
#include <cstdlib>

class window
{
  public:
    window(std::istream& is, unsigned before, unsigned after) :
      stream_(is),
      before_(before),
      after_(after)
    {
      int count = 0;
      char buffer[512];
      std::string s;
      while (count < after_ + 1) {
	do {
	  stream_.getline(buffer, 512);
	  s += buffer;
	} while (stream_.fail() && (!(s.size() == 0  || stream_.eof())));
	buffer_.push_back(s);
	if (stream_.eof())
	  break;
	++count;
      }
      current_pos_ = buffer_.begin();
      for (int i = 0; i != after_; ++i)
	current_pos_++;
    }

    bool discard_line()
    {
      char buffer[512];
      std::string s;
      do {
	stream_.getline(buffer, 512);
	s += buffer;
      } while (stream_.fail() && (!stream_.eof()));
      if (stream_.eof())
      {
	++current_pos_;
	if (current_pos_ == buffer_.end())
	  return false;
	return true;
      }
      buffer_.push_back(s);
      ++current_pos_;
      buffer_.pop_front();
      return true;
    }

    std::string current()
    {
      return *current_pos_;
    }

  private:
    std::istream&				   stream_;
    std::list<std::string>		   buffer_;
    std::list<std::string>::iterator	   current_pos_;
    int					   before_;
    int					   after_;
};

void grep(std::ostream& out,
	  const vcsn::boolean_automaton::automaton_t& automaton,
	  window w)
{
  do
  {
    vcsn::boolean_automaton::semiring_elt_t ret =
      eval(automaton, w.current());
    if (ret.value())
      out << w.current() << std::endl;
  }
  while (w.discard_line());
}

//
// Error handling
//
void exit_on_error(const std::string& msg)
{
  std::cerr << "vgrep:" << msg << std::endl;
  exit(EXIT_FAILURE);
}

const std::string error_before_context =
				  "'before-context' expect a valid integer argument";
const std::string error_after_context =
				  "'after-context' expect a valid integer argument";

//
// What's the program does ...
//
int main(int argc, char **argv)
{
  // Parse options.
  int c;
  int after_context = 0;
  int before_context = 0;
  bool invert_match = false;
  std::string filename;

  while (true) {
    c = getopt(argc, argv, "A:B:vf:");

    if (c == -1)
      break;

    switch (c)
    {
      case 'A':
      {
	char *endptr;
	after_context = strtol(optarg, &endptr, 10);
	if (optarg == endptr)
	  exit_on_error(error_after_context);
	break;
      }
      case 'B':
      {
	char *endptr;
	before_context = strtol(optarg, &endptr, 10);
	if (optarg == endptr)
	  exit_on_error(error_before_context);

	break;
      }
      case 'v':
      {
	invert_match = true;
	break;
      }
      case 'f':
      {
	filename = optarg;
      }
    }
  }
  // Determine the streams to be filtered.
  int optcount = optind;
  if (optind < argc)
  {
    using namespace vcsn::boolean_automaton;
    using namespace vcsn;

    // The first argument is the rational expression.
    std::string exp = argv[1];
    ++optcount;

    // Construct the associated automaton.
    alphabet_t alpha;
    for (unsigned l = 0; l <= 255; ++l)
      alpha.insert(char(l));

    automaton_t automaton = make_automaton(alpha);
    Element<series_set_t, rat::exp<monoid_elt_value_t, semiring_elt_value_t> >
      krat_exp(automaton.structure().series());
    parse(exp, krat_exp);
    automaton = standard_of(krat_exp);
    realtime_here(automaton);
    complete_here(automaton);
    // FIXME: tools::dot_dump(std::cout, automaton, "automaton");
    // STATE FINAL => sigma * on it.
    for_all_initial_states(s, automaton)
      for (unsigned l = 0; l <= 255; ++l)
	automaton.add_letter_transition(*s, *s, char(l));
    for_all_final_states(s, automaton)
      for (unsigned l = 0; l <= 255; ++l)
	automaton.add_letter_transition(*s, *s, char(l));

    automaton = determinize(automaton);
    //	    tools::dot_dump(std::cerr, automaton, "automaton");
    // No file means standard input.
    if (optcount == argc)
    {
      grep(std::cout,
	   automaton,
	   window(std::cin, before_context, after_context));
    }
    //
    //	if (argv[optind++] == std::string("-"))
    //	  grep(window win(std::cin, before_context, after_context),

  }
  // Parse the rational expression.

}

