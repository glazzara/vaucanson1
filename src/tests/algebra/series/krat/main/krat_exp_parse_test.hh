// krat_exp_parse_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003,2004 The Vaucanson Group.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_PARSE_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_PARSE_TEST_HH

# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>

# include <sstream>

# define KRAT_EXP_PARSE_TEST_USUAL_DECS(Expr)			\
  typedef Expr					krat_exp_t;	\
  typedef typename krat_exp_t::value_t		kexp_t;		\
  typedef typename krat_exp_t::monoid_elt_t	monoid_elt_t;	\
  typedef typename krat_exp_t::semiring_elt_value_t semiring_elt_value_t;\
  typedef typename monoid_elt_t::set_t		monoid_t;	\
  typedef typename krat_exp_t::semiring_elt_t		semiring_elt_t;	\
  typedef typename semiring_elt_t::set_t		semiring_t;	\
  typedef typename krat_exp_t::set_t		series_set_t;	\
  typedef typename monoid_t::letter_t		letter_t;	\
  typedef typename monoid_t::alphabet_t		alphabet_t;

template <class Alphabet>
void
error(const std::string& original,
      const std::string& result,
      const std::string& expected,
      const Alphabet& a)
{
  std::cerr << "*** PARSER TEST ***" << std::endl
	    << "On \"" << original << '\"' << std::endl
	    << "Got \"" << result << '\"' << std::endl
	    << "Instead of \"" << expected << '\"' << std::endl
	    << "(Alphabet is " << a << " )" << std::endl;
}

template <class Expr>
bool krat_exp_parse_random_test(tests::Tester& tg)
{
  KRAT_EXP_PARSE_TEST_USUAL_DECS(Expr);
  tests::Tester t(tg.verbose());
  srand(time(0));

  unsigned nb_test	 = 0;
  unsigned nb_success    = 0;

  char buff[2048];
  char letters[2][2] = { {'a', 'b'}, {'\\', '.'} };

  std::string typeid_name;
  if (typeid(semiring_elt_value_t) == typeid(double) ||
      typeid(semiring_elt_value_t) == typeid(float))
    typeid_name = "f";
  if (typeid(semiring_elt_value_t) == typeid(int))
    typeid_name = "i";
  if (typeid(semiring_elt_value_t) == typeid(bool))
    typeid_name = "b";
  
  std::string path_to_test(VCSN_SRC_DIR);
  path_to_test += "/src/tests/algebra/series/krat/tests/";
  std::string filename =
    path_to_test + "random_krat_exp_" + typeid_name + "_ab";
  std::ifstream file(filename.c_str());

  for (int j = 0; file.is_open() && j < 2; ++j)
    {
      alphabet_t alphabet;
      alphabet.insert(letters[j][0]);
      alphabet.insert(letters[j][1]);
      monoid_t monoid(alphabet);
      semiring_t semiring;
      series_set_t s(semiring, monoid);
      krat_exp_t exp(s);

      file.getline(buff, 2048);
      while (!file.eof())
	{
	  std::ostringstream sstr;
	  sstr << buff;
	  std::pair<bool, std::string> ret = parse(sstr.str(), exp);
	  if (ret.first)
	    error(sstr.str(), ret.second, sstr.str(),
		  exp.structure().monoid().alphabet());
	  else
	    {
	      std::ostringstream ostr;
	      ostr << exp;
	      if (ostr.str() != sstr.str())
		error(sstr.str(), ostr.str(), sstr.str(),
		      exp.structure().monoid().alphabet());
	      else
		++nb_success;
	    }
	  ++nb_test;
	  file.getline(buff, 2048);
	}
      
      file.close();
      file.clear();
      filename = path_to_test + "random_krat_exp_" + typeid_name + "_weird";
      file.open(filename.c_str());
    }

  std::string rate;
  SUCCESS_RATE(rate, nb_success, nb_test);
  TEST(t, "parsing random rational expression " + rate,
       nb_success == nb_test);
  return t.all_passed();
}

struct sample_t { char* exp; char* out; };

static sample_t bool_samples[] =
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
    { "0.a", "0" },
    { "0a", "0" },
    { "1.a", "a" },
    { "1a", "a" },
    { "(a+b)*", "(a+b)*" },
    { "a+b*", "(a+b*)" },
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

static sample_t mul_samples[] =
  {
    // Good ones
    { "1 a", "a" },
    { "a 1", "a" },
    { "0 a", "0" },
    { "1 (a+b)", "(a+b)" },
    { "1 (a.b)", "(a.b)" },
    { "(a.b) 1", "(a.b)" },
    { "(a+b) 1", "(a+b)" },
    { "2 (a+b)", "2 (a+b)" },
    { "2 (a.b)", "2 (a.b)" },
    { "(a.b) 2", "(a.b) 2" },
    { "(a+b) 2", "(a+b) 2" },
    { "0 (a.b)", "0" },
    { "0 (a+b)", "0" },
    { "(a.b) 0", "0" },
    { "(a+b) 0", "0" },
    { "1 a.1 b", "(a.b)" },
    { "1 a1 b", "(a.b)" },
    { "2 a.2 b", "(2 a.2 b)" },
    { "2 a2 b", "(2 a.2 b)" },
    { "2 1", "2 1"},
    { "1 2", "2 1"},
    {0, 0}
  };

template <class Expr>
bool krat_exp_parse_exhaustive_test (tests::Tester& tg, sample_t samples[])
{
  KRAT_EXP_PARSE_TEST_USUAL_DECS(Expr);
  tests::Tester t(tg.verbose());
  alphabet_t alphabet;
  alphabet.insert('a');
  alphabet.insert('b');
  alphabet.insert('c');
  monoid_t monoid(alphabet);
  semiring_t semiring;
  series_set_t s(semiring, monoid);

  unsigned int nb_success = 0;
  unsigned int nb_test;
  for (nb_test = 0; samples[nb_test].exp != 0; ++nb_test)
    {
      krat_exp_t exp(s);

      std::pair<bool, std::string> r = parse(samples[nb_test].exp, exp);
      if (r.first)
	{
	  if (samples[nb_test].out != 0)
	    error(samples[nb_test].exp, r.second, samples[nb_test].out,
		  exp.structure().monoid().alphabet());
	  else
	    nb_success++;
	}
      else
	{
	  using vcsn::rat::print_mode_t;
	  using vcsn::rat::MODE_ALL;
	  using vcsn::rat::MODE_STAR;
	  using vcsn::rat::MODE_WEIGHT;
	  using vcsn::rat::setpm;

	  std::ostringstream ostr;
	  ostr << setpm (print_mode_t (MODE_ALL & ~MODE_STAR & ~MODE_WEIGHT))
	       << exp;
	  if (samples[nb_test].out == 0)
	    error(samples[nb_test].exp, ostr.str(), "error",
		  exp.structure().monoid().alphabet());
	  else if (samples[nb_test].out != ostr.str())
	    error(samples[nb_test].exp, ostr.str(), samples[nb_test].out,
		  exp.structure().monoid().alphabet());
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

template <typename T, typename Expr>
struct exhaustive_test_dispatch
{
  static bool run(tests::Tester& tg)
  {
    return krat_exp_parse_exhaustive_test<Expr>(tg, mul_samples) &&
      krat_exp_parse_exhaustive_test<Expr>(tg, bool_samples);
  }
};

template <typename Expr>
struct exhaustive_test_dispatch<bool, Expr>
{
  static bool run(tests::Tester& tg)
  {
    return krat_exp_parse_exhaustive_test<Expr>(tg, bool_samples);
  }
};

template <class Expr>
bool krat_exp_parse_test(tests::Tester& tg)
{
  KRAT_EXP_PARSE_TEST_USUAL_DECS(Expr);

  return
    krat_exp_parse_random_test<Expr>(tg) &&
    exhaustive_test_dispatch<typename semiring_elt_t::value_t, Expr>::run(tg);
}

#endif // VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_PARSE_TEST_HH
