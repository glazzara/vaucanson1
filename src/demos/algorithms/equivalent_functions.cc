// equivalent_functions.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//

/**
 * @file equivalent_functions.cc
 *
 * Contains several functions useful to programs are_equivalent and
 * exp_recognized, including get_aut, get_exp (to retrieve the input
 * expression and automaton) and the are_equivalent function.
 *
 */


#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/complement.hh>
#include <vaucanson/algorithms/complete.hh>
#include <vaucanson/algorithms/trim.hh>
#include <vaucanson/algorithms/product.hh>
#include <vaucanson/xml/XML.hh>
#include <ostream>
#include <sstream>

#include "equivalent_functions.hh"

rat_exp_t
get_exp(std::string s)
{
  alphabet_t	a;
  a.insert('a');
  a.insert('b');

  return new_rat_exp(a, s);
}

automaton_t
get_aut(std::string s)
{
  std::istream* is (new std::ifstream (s.c_str()));
  if (not is->fail())
    {
      using namespace vcsn::io;
      using namespace vcsn::xml;

      automaton_t a = new_automaton(alphabet_t ());
      *is >> automaton_loader(a, string_out (), XML ());

      if (s != "-")
	delete is;
      return a;
    }
  else
    {
      std::cerr << "FATAL: Could not load automaton." << std::endl;
      exit(1);
    }
}


bool
are_equivalent(const automaton_t &a, const automaton_t &b)
{
  automaton_t c (a);
  automaton_t d (b);

  if (not is_deterministic(c))
    c = determinize(a);
  else if (not is_complete(c))
    complete_here(c);

  if(not is_deterministic(d))
    d = determinize(b);
  else if(not is_complete(d))
    complete_here(d);

  complement_here(c);
  complement_here(d);
  c = trim(product(c, b));
  d = trim(product(a, d));
  return c.states().size() == 0 and d.states().size() == 0;
}
