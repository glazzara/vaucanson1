// tests_stuff.cc
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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


#include "tests_stuff.hh"

namespace tests {

  const unsigned Tester::nb_col_msg = 60;

  Tester::Tester(verbose_level_e verbose_level) : 
    passed_ (0),
    non_passed_(0),
    verbose_(verbose_level)
  {}

  bool 
  Tester::all_passed() 
  {
    return (non_passed_ == 0);
  }

  void 
  Tester::ok(std::string test_label)
  {
    if (verbose_ != none)
      {
	std::cout << "TEST: ";
	std::cout.fill(' ') ;
	int last = std::cout.width(nb_col_msg);
	std::cout << test_label;
	std::cout << " : OK" << std::endl;
	std::cout.width(last);
      }
    passed_++;
  }

  void 
  Tester::ko(std::string test_label)
  {
    if (verbose_ != none)
      {
	std::cout << "TEST: ";
	std::cout.fill(' ') ;
	int last = std::cout.width(nb_col_msg);
	std::cout << test_label;
	std::cout << " : KO" << std::endl;
	std::cout.width(last);
      }
    non_passed_++;
  }
  
  verbose_level_e Tester::verbose() const
  {
    return verbose_;
  }

  // FIXME: Add statistics stuff.

} // tests
