// vgrep.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#include <vaucanson/design_pattern/design_pattern.hh>
#include <vaucanson/tools/usual.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/realtime.hh>
#include <vaucanson/algorithms/complete.hh>
#include <vaucanson/algebra/concrete/series/rat/exp.hh>
#include <vaucanson/algebra/concrete/series/krat.hh>
#include <vaucanson/algebra/concrete/series/krat_exp_parser.hh>
#include <vaucanson/algorithms/standard_of.hh>
#include <vaucanson/algorithms/thompson.hh>
#include <vaucanson/algorithms/eval.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <vaucanson/tools/dot_dump.hh>
// #include <vaucanson/misc/unique.hcc>
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

void grep(std::ostream& out, const vcsn::tools::usual_automaton_t& automaton, 
	  window w)
{
  do
    {
      vcsn::tools::usual_automaton_t::semiring_elt_t ret =
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
      using namespace vcsn;
      using namespace vcsn::tools;
      AUTOMATON_TYPES_EXACT(usual_automaton_t);

      // The first argument is the rational expression.
      std::string exp = argv[1];
      ++optcount;

      // Construct the associated automaton.
      alphabet_t alpha;
      for (unsigned l = 0; l <= 255; ++l)
	alpha.insert(char(l));
      
      automaton_t automaton = new_automaton(alpha);
      Element<series_t, rat::exp<monoid_elt_value_t, semiring_elt_value_t> >
	krat_exp(automaton.set().series());
      parse(exp, krat_exp);
      standard_of(automaton, krat_exp.value());
      realtime_here(automaton);
      complete_here(automaton);
      // FIXME: tools::dot_dump(std::cout, automaton, "automaton");
      // STATE FINAL => sigma * on it.
      for_each_initial_state(s, automaton)
	for (unsigned l = 0; l <= 255; ++l)
	  automaton.add_letter_edge(*s, *s, char(l));
      for_each_final_state(s, automaton)
	for (unsigned l = 0; l <= 255; ++l)
	  automaton.add_letter_edge(*s, *s, char(l));
      
      automaton = determinize(automaton);
      //      tools::dot_dump(std::cerr, automaton, "automaton");
      // No file means standard input.
      if (optcount == argc)
	{
	  grep(std::cout,
	       automaton,
	       window(std::cin, before_context, after_context));
	}
      //
      // 	if (argv[optind++] == std::string("-"))
      // 	  grep(window win(std::cin, before_context, after_context),
	       
    }
  // Parse the rational expression.
  
}

