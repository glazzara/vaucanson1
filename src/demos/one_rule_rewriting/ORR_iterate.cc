// ORR_iterate.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008, 2009 The Vaucanson Group.
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

#include <sstream>

#include <vaucanson/boolean_transducer.hh>
#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/fmp_transducer.hh>

#include <vaucanson/tools/xml_dump.hh>

#include "one_rule_rewriting.hh"
#include "shortest.hh"

vcsn::boolean_automaton::automaton_t
qcq(const vcsn::boolean_automaton::automaton_t& a)
{
  return transpose(quotient(transpose(quotient(a))));
}

static void
usage(int, char** argv)
{
  std::cerr << "Usage: " << argv[0] << " <no_of_letters> <word> <replace_word>" << std::endl;
  exit(1);
}

int
main(int argc, char** argv)
{
  using namespace vcsn;
  using namespace vcsn::boolean_transducer;

  // Read the parameters.
  if (argc != 4)
    usage(argc, argv);

  // Get the number of letters.
  std::stringstream ss(argv[1]);
  int nb_letter = 0;
  ss >> nb_letter;

  // Check nb_letter is valid.
  if (!nb_letter)
    usage(argc, argv);

  std::string from = argv[2];
  std::string to = argv[3];

  // Creation of the alphabet.
  alphabet_t A;
  for (int i = 0; i < nb_letter; i++)
    A.insert('a' + i);

  // Compute an automaton for the non-reduced words.
  boolean_automaton::rat_exp_t expA = boolean_automaton::make_rat_exp(A, "0");
  // expA = (a+b+...)*
  for_all_letters (x, A)
    expA += *x;
  expA.star();

  // Convert the "from" string to a rat exp.
  boolean_automaton::rat_exp_t expfrom = boolean_automaton::make_rat_exp(A, from);

  // expL = (a+b+...)*.expfrom.(a+b+...)*
  boolean_automaton::rat_exp_t expL = expA * expfrom * expA;

  // Compute the automaton.
  boolean_automaton::automaton_t autL = qcq(boolean_automaton::standard_of(expL));

  // The cautious transducers.
  automaton_t left_tdc = ORR::replace_left(from, to, A, A);
  automaton_t right_tdc = ORR::replace_right(from, to, A, A);

  // Composition of the left cautious and the right cautious.
  // Call trim to improve performances by removing useless states.
  automaton_t lr_tdc = trim(rw_composition(left_tdc, right_tdc));

  // Initialize the first iteration.
  automaton_t iter_tdc = lr_tdc;
  int iteration = 1;

  while (1)
  {
    std::cout << "Iteration " << iteration << std::endl
	      << "iter_tdc: " << iter_tdc << std::endl;

    // Calculate the image of iter_tdc.
    boolean_automaton::automaton_t iter_ima = boolean_automaton::make_automaton(A);
    fmp_transducer::automaton_t iter_fmp = fmp_transducer::make_automaton(A, A);
    rw_to_fmp(iter_tdc, iter_fmp);

    image(iter_fmp, iter_ima);
    std::cout << "iter_ima: " << iter_ima << std::endl;

    // Dump the image of iteration.
    std::ofstream file;
    std::stringstream filename;
    filename << "iter_ima_" << iteration << ".xml";
    file.open(filename.str().c_str());
    tools::xml_dump(file, iter_ima, "iter_ima");
    file.close();

    boolean_automaton::automaton_t iter_imac = qcq(realtime(iter_ima));
    std::cout << "iter_imac: " << iter_imac << std::endl;

    // Is it reduced?
    boolean_automaton::automaton_t autR = product(iter_imac, autL);

    if (trim(autR).states().size() == 0)
    {
      // We can stop because all the words are reduced in the image.
      std::cout << "Reduction complete." << std::endl;
      break;
    }
    else
    {
      std::cout << "Reduction incomplete. Searching the shortest unreduced word..." << std::endl;
      std::cout << "Shortest unreduced word: " << shortest(autR) << std::endl;

      // Ask whether or not to iterate as it may never stop.
      std::cout << "Do you want to iterate [y/n]? ";

      // Get user input.
      std::string user_string;
      getline(std::cin, user_string);

      if (user_string != "y")
	// The user do not want to iterate anymore.
        break;
    }

    // Iterate.
    iter_tdc = trim(rw_composition(iter_tdc, lr_tdc));
    iteration++;
  }

  return 0;
}
