// vgrep.cc
//
// $Id$

#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/tools/usual.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/realtime.hh>
#include <vaucanson/algorithms/complete.hh>
#include <vaucanson/algebra/concrete/series/rat/exp.hh>
#include <vaucanson/algebra/concrete/series/krat.hh>
#include <vaucanson/algebra/concrete/series/krat_exp_parser.hh>
#include <vaucanson/algorithms/glushkov.hh>
#include <vaucanson/algorithms/thompson.hh>
#include <vaucanson/algorithms/compute.hh>
#include <vaucanson/algorithms/hopcroft.hh>
#include <vaucanson/misc/dot_dump.hh>
#include <iostream>
#include <vector>
#include <ctype.h>
#include <string>
#include <getopt.h>
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
      bool ret = false;
      ret = compute(automaton, w.current());
      if (ret)
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
    int option_index = 0;
    static struct option long_options[5] = 
      {
	{"after-context",  1, 0, 'A'},
	{"before-context", 1, 0, 'B'},
	{"invert-match",   1, 0, 'v'},
	{"file",           1, 0, 'f'},
	{0, 0, 0, 0}
      };
    
    c = getopt_long (argc, argv, "A:B:vf:",
		     long_options, 
		     &option_index);
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
	if (isprint(l) && (l != '*') && (l != '.') && (l != '+')
	    && (l != '(') && (l != ')'))
	  alpha.insert(char(l));
      
      automaton_t automaton = new_automaton(alpha);
      Element<series_t, rat::exp<monoid_elt_value_t, weight_value_t> >
	krat_exp(automaton.set().series());
      parse(exp, krat_exp);
      glushkov(automaton, krat_exp.value());
      realtime_here(automaton);
      auto_in_complete(automaton);
      std::cerr << "complete ok" << std::endl;
      misc::dot_dump(std::cout, automaton, "automaton");
      // STATE FINAL => sigma * on it.
      for_each_initial_state(s, automaton)
	for (unsigned l = 0; l <= 255; ++l)
	  if (isprint(l) && (l != '*') && (l != '.') && (l != '+')
	      && (l != '(') && (l != ')'))
	    automaton.add_letter_edge(*s, *s, char(l));
      for_each_final_state(s, automaton)
	for (unsigned l = 0; l <= 255; ++l)
	  if (isprint(l) && (l != '*') && (l != '.') && (l != '+')
	      && (l != '(') && (l != ')'))
	    automaton.add_letter_edge(*s, *s, char(l));

      automaton = determinize(automaton);
      std::cerr << "determinize ok" << std::endl;
      misc::dot_dump(std::cout, automaton, "automaton");
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
