// tester.cc: this file is part of the Vaucanson project.
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
#include <iomanip>
#include <string>
#include "tester.hh"

namespace tests {

  const unsigned Tester::nb_col_msg = 50;

  Tester::Tester() :
    passed_(0),
    failed_(0),
    verbose_(none)
  {
    std::string s = getenv("VERBOSE");
    if (s == "x" || s == "high")
      verbose_ = high;
    else if (s != "")
      verbose_ = medium;  
  }

  Tester::Tester(verbose_level v) : 
    passed_ (0),
    failed_(0),
    verbose_(v)
  {
  }

  bool 
  Tester::all_passed() 
  {
    return (failed_ == 0);
  }

  void 
  Tester::ok(std::string test_label)
  {
    if (verbose_ != none)
      std::cout << "TEST: [OK]   " << test_label << std::endl;
    passed_++;
  }

  void 
  Tester::ko(std::string test_label)
  {
    if (verbose_ != none)
      std::cout << "TEST: [KO]   " << test_label << std::endl;
    failed_++;
  }
  
  verbose_level Tester::verbose() const
  {
    return verbose_;
  }

  // FIXME: Add statistics stuff.

} // tests

