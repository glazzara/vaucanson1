// krat_exp_parse_test.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef KRAT_EXP_PARSE_TEST_HH
# define KRAT_EXP_PARSE_TEST_HH

# include <check/tester.hh>
# include <sstream>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algebra/concrete/series/krat_exp_parser.hh>
# include <vaucanson/misc/selectors.hh>

# define KRAT_EXP_PARSE_TEST_USUAL_DECS(Expr)			\
  typedef Expr					krat_exp_t;	\
  typedef typename krat_exp_t::value_t		kexp_t;		\
  typedef typename krat_exp_t::monoid_elt_t	monoid_elt_t;	\
  typedef typename monoid_elt_t::set_t		monoid_t;	\
  typedef typename krat_exp_t::weight_t		weight_t;	\
  typedef typename weight_t::set_t		weights_t;	\
  typedef typename krat_exp_t::set_t		series_t;	\
  typedef typename monoid_t::letter_t		letter_t;	\
  typedef typename monoid_t::alphabet_t		alphabet_t;

void
error(const std::string& original,
      const std::string& result,
      const std::string& expected)
{
  std::cerr << "*** PARSER TEST ***" << std::endl
	    << "On \"" << original << '\"' << std::endl
	    << "Got \"" << result << '\"' << std::endl
	    << "Instead of \"" << expected << '\"' << std::endl;
}

template <class Expr>
bool krat_exp_parse_random_test(tests::Tester& tg)
{
  KRAT_EXP_PARSE_TEST_USUAL_DECS(Expr);
  tests::Tester t(tg.verbose());
  srand(time(0));
  alphabet_t alphabet;
  letter_t a = alphabet.random_letter();
  letter_t b = alphabet.random_letter();
  alphabet.insert(a);
  alphabet.insert(b);
  alphabet.insert('a');
  monoid_t monoid(alphabet);
  weights_t semiring;
  series_t s(semiring, monoid);
  // FIXME: !!!
  const unsigned nb_test = 100;
  unsigned nb_success    = 0;
  for (unsigned i = 0; i < 100; ++i)
    {
      krat_exp_t exp = s.choose(SELECT(kexp_t));
      std::ostringstream sstr;
      sstr << exp;
      krat_exp_t out(s);
      std::pair<bool, std::string> ret = parse(sstr.str(), out);
      std::ostringstream ostr;
      ostr << out;
      if (ostr.str() != sstr.str())
	error(sstr.str(), ostr.str(), sstr.str());
      else if (ret.first)
	error(sstr.str(), ret.second, sstr.str());
      else 
	++nb_success;
    }
  std::string rate;
  SUCCESS_RATE(rate, nb_success, nb_test);
  TEST(t, "parsing random rational expression " + rate, nb_success == nb_test);
  return t.all_passed();
}

static struct { char* exp; char* out; } samples[] =
  {
    // Good ones
    { "0", "0" },
    { "1", "1" },
    { "a", "a" },
    { "(a)", "a" },
    { "ab", "ab" },
    { "(ab)", "ab" },
    { "a.b", "(a.b)" },
    { "(a.b)", "(a.b)" },
    { "a+b", "(a+b)" },
    { "(a+b)", "(a+b)" },
    { "a.b.c", "((a.b).c)" },
    { "a+b+c", "((a+b)+c)" },
    { "a.b+c", "((a.b)+c)" },
    { "a+b.c", "(a+(b.c))" },
    { "(a+b).c", "((a+b).c)" },
    { "(a+b)c", "((a+b).c)" },
    { "a(b+c)", "(a.(b+c))" },
    { "a*", "a*" },
    { "ab*", "ab*" },
    { "a.b*", "(a.b*)" },
    { "a*.b", "(a*.b)" },
    { "a*b", "(a*.b)"},
    { "1 a", "a" },
    { "a 1", "a" },
    { "0 a", "0" },
    { "1 (a+b)", "(a+b)" },
    { "1 (a.b)", "(a.b)" },
    { "(a.b) 1", "(a.b)" },
    { "(a+b) 1", "(a+b)" },
    { "2 (a+b)", "(2 (a+b))" },
    { "2 (a.b)", "(2 (a.b))" },
    { "(a.b) 2", "((a.b) 2)" },
    { "(a+b) 2", "((a+b) 2)" },
    { "0 (a.b)", "0" },
    { "0 (a+b)", "0" },
    { "(a.b) 0", "0" },
    { "(a+b) 0", "0" },
    { "0.a", "0" },
    { "0a", "0" },
    { "1.a", "a" },
    { "1a", "a" },
    { "1 a.1 b", "(a.b)" },
    { "1 a1 b", "(a.b)" },
    { "2 a.2 b", "((2 a).(2 b))" },
    { "2 a2 b", "((2 a).(2 b))" },
    { "2 1", "(2 1)"},
    { "1 2", "(2 1)"},
    // Bad ones
    { "2", 0 },
    { "2.2", 0 },
    { "2+2", 0 },
    { "2 2", 0 },
    { "2.", 0 },
    { "2+", 0 },
    { "2 ", 0 },
    { "0.", 0 },
    { "0+", 0 },
    { "0 ", 0 },
    { "1.", 0 },
    { "1+", 0 },
    { "1 ", 0 },
    { "a.", 0 },
    { "a+", 0 },
    { "a ", 0 },
    { "x", 0 },
    {0, 0}
  };

template <class Expr>
bool krat_exp_parse_exhaustive_test (tests::Tester& tg)
{
  KRAT_EXP_PARSE_TEST_USUAL_DECS(Expr);
  tests::Tester t(tg.verbose());
  alphabet_t alphabet;
  alphabet.insert('a');
  alphabet.insert('b');
  alphabet.insert('c');
  monoid_t monoid(alphabet);
  weights_t semiring;
  series_t s(semiring, monoid);
  
  unsigned int nb_success = 0;
  unsigned int nb_test;
  for (nb_test = 0; samples[nb_test].exp != 0; ++nb_test)
    {
      krat_exp_t exp(s);
      std::pair<bool, std::string> r = parse(samples[nb_test].exp, exp);
      if (r.first)
	{
	  if (samples[nb_test].out != 0)
	    error(samples[nb_test].exp, r.second, samples[nb_test].out);
	  else
	    nb_success++;
	}
      else
	{
	  std::ostringstream ostr;
	  ostr << exp;
	  if (samples[nb_test].out == 0)
	    error(samples[nb_test].exp, ostr.str(), "error");
	  else if (samples[nb_test].out != ostr.str())
	    error(samples[nb_test].exp, ostr.str(), samples[nb_test].out);
	  else
	    nb_success++;
	}
    }
  
  std::string rate;
  SUCCESS_RATE(rate, nb_success, nb_test);
  TEST(t, "parsing hardcoded rational expressions " + rate,
       nb_success == nb_test);
  return t.all_passed();
}

template <class Expr>
bool krat_exp_parse_test(tests::Tester& tg)
{
  return
    krat_exp_parse_random_test<Expr>(tg) &
    krat_exp_parse_exhaustive_test<Expr>(tg);
}

#endif // KRAT_EXP_PARSE_TEST_HH
