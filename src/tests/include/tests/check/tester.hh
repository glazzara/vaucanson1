// tester.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TESTS_CHECK_TESTER_HH
# define VCSN_TESTS_CHECK_TESTER_HH

# include <sstream>
# include <fstream>
# include <iostream>
# include <string>

# define SAVE_AUTOMATON_XML_SIMPLE(Name, Auto)			\
  do {								\
    std::ostringstream s;					\
    s << Name << ".xml";					\
    std::string name = s.str();					\
    std::ofstream f(name.c_str());				\
    vcsn::tools::xml_dump(f, Auto, name);			\
    TEST_MSG("Automaton saved in " << name);			\
  } while (0)

# define SAVE_AUTOMATON_XML(Dir, Name, Auto, Index)	\
  SAVE_AUTOMATON_XML_SIMPLE (Dir << "/" << Name << "_" << Index, Auto)

namespace tests {

  class Tester
  {
  public:
    enum verbose_level
      {
	none,
	low,
	medium,
	high
      };

    Tester();
    Tester(int argc, char **argv);
    Tester(const Tester& t);

    /// Set up the tester.
    ///
    /// To be called at the end of each ctor.
    void finalize_initialization ();

    /// Process the command line arguments.
    ///
    /// Skips argv[0], the command name.
    void process_options (int argc, char **argv);

    /// Process one command line option.
    void process_option (const std::string& s);

    /// The current verbosity level.
    verbose_level verbose() const;
    /// Whether l is higher or equal to the current verbosity level.
    bool verbose (verbose_level l) const;

    /// The current seed.
    unsigned seed() const;

    /// Number of times to run the test where it applies.
    unsigned test_num () const;

    /// Whether all tests passed.
    bool all_passed();

    /// Whether test @c label passed or not.
    void ok_or_ko(std::string test, bool pass);
    /// Sugar for ok_or_ko().
    void ok(std::string test);
    /// Sugar for ok_or_ko().
    void ko(std::string test);

    static const unsigned nb_col_msg;
    /// A specific non null number to request a random seed.
    static const unsigned seed_time;
    // FIXME: Add statistics stuff.

  private:
    /// Number of passed tested.
    unsigned int	passed_;
    /// Number of failed tested.
    unsigned int	failed_;
    /// Level of verbosity.
    verbose_level	verbose_;
    /// The random seed.
    unsigned seed_;
  };

} // tests


/// To avoid unprintable char printing.
template <typename T>
inline std::string printable(T t)
{
  std::ostringstream	basic_output;
  std::string		basic_output_s;
  std::ostringstream	printable_output;
  unsigned		n;

  basic_output << t;
  basic_output_s = basic_output.str();
  printable_output.setf(std::ios_base::hex, std::ios_base::basefield);
  for (std::string::const_iterator c = basic_output_s.begin();
       c != basic_output_s.end(); ++c)
  {
    n = static_cast<unsigned char>(*c);
    if (n < 0x10)
      printable_output << "0x0" << n;
    else
      if (n >= 0x20 and n < 0x7F)
	printable_output << *c;
      else
	printable_output << "0x" << n;
  }
  return printable_output.str();
}

#define TEST_MSG(Label) \
  std::cerr << "TEST: * " << Label << std::endl;

#define TEST_GROUP(Label) \
  std::cerr << "GROUP *** " << Label << " ***" << std::endl;

#define TEST_ASSERT(Code, Label) \
  std::cerr << ((Code) ? "PASS" : "FAIL") << " * " << Label << std::endl; assert(Code);
#define TEST_XASSERT(Code, Label) \
  std::cerr << ((Code) ? "PASS" : "XFAIL") << " * " << Label << std::endl;

#define TEST_FAIL_SAVE(TestName, Iteration, Data)			\
  {									\
    std::ostringstream s;						\
    s << "/tmp/" << TestName << "_" << Iteration << ".txt";		\
    std::ofstream f(s.str().c_str());					\
    f << Data;								\
    f.close();								\
    std::cerr << "FAIL: Test failed at iteration "			\
	      << Iteration << std::endl;				\
    std::cerr << "FAIL: Relevant information saved in "		\
	      << s.str() << std::endl;					\
  }

#define TEST_RETURN(aTester)			\
  if (aTester.all_passed())			\
    return EXIT_SUCCESS;			\
  else						\
    return EXIT_FAILURE;


#define TEST(aTester, Label, Code)		\
{						\
  bool result = (Code);				\
  if (result)					\
    aTester.ok(Label);				\
  else						\
   {						\
     std::cerr << "(" << #Code << " is false)"	\
	       << std::endl;			\
     aTester.ko(Label);				\
   }						\
}

#define EQTEST(aTester, Label, Code, V)			\
{							\
  bool result = ((Code) == (V));			\
  if (aTester.verbose(tests::Tester::high))		\
    std::cerr << printable(Code) << " =? "		\
	      << printable(V) << std::endl;		\
  if (result)						\
    aTester.ok(printable(Label));			\
  else							\
   {							\
     std::cerr << "(" << printable(Code)		\
	       << " != " << printable(V)		\
	       << ")" << std::endl;			\
     aTester.ko(Label);					\
   }							\
}

#define SUCCESS_RATE(OutStr, success, over)	\
{						\
  std::ostringstream s;				\
  s << "(" << success << "/" << over << ")";	\
  OutStr = s.str();				\
}

#endif // ! VCSN_TESTS_CHECK_TESTER_HH
