// ORR_rt_gen.cc: this file is part of the Vaucanson project.
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

/* @file ORR_rt_gen.cc
 *
 * Considering the words u and v given as input to the program, build
 * the cautious left sequential transducer,
 * the cautious right sequential transducer,
 * the left transducer composed by right transducer,
 * the right transducer composed by left transducer,
 * with transducers seen as automata in the semiring of series, which
 * operate the replacement of u by v. Then produce the corresponding
 * xml files.
 *
 */

#include <vaucanson/boolean_transducer.hh>
#include <vaucanson/algorithms/realtime_composition.hh>
#include <vaucanson/algorithms/transpose.hh>
#include <vaucanson/tools/xml_dump.hh>

using namespace vcsn;
using namespace vcsn::boolean_transducer;

static
void
usage(int, char** argv)
{
  std::cerr << "Usage: " << std::endl
	    << "\t" << argv[0] << " <word> <replace_word> <name>" << std::endl;
  exit(1);
}

std::string
prefsuf(const std::string& u, const std::string& v)
{
  int	vs = v.size();
  int	s = std::min(u.size(), v.size());

  for (int n = s; n > 0; --n)
    {
      std::string tmp = u.substr(0, n);
      if (tmp == v.substr(vs - n, n))
	return tmp;
    }

  return "";
}

std::string
alpha_convert(const std::map<letter_t, letter_t>& conv_map,
	      const std::string& str)
{
  std::string r;
  int n = str.size();
  r.reserve(n);

  for (int i = 0; i < n; ++i)
    r += conv_map.find(str[i])->second;

  return r;
}

std::map<letter_t, letter_t>
alpha_map(const alphabet_t& A,
	  const alphabet_t& B)
{
  typedef alphabet_t::const_iterator alphabet_iterator;

  std::map<letter_t, letter_t>	m;

  alphabet_iterator j = B.begin();
  for_each_letter(i, A)
    m[*i] = *j++;

  return m;
}

automaton_t
replace_left(const std::string& from,	const std::string& to,
	     const alphabet_t& A,	const alphabet_t& B)
{
  automaton_t	a = new_automaton(A, B);

  int		n = from.size();

  // Create a map to make the 2 alphabets correspond.
  std::map<letter_t, letter_t> a2b = alpha_map(A, B);

  // Create a vector to handle all the states.
  std::vector<hstate_t>	s (n);

  // Create states and set them all final.
  for (int i = 0; i < n; ++i)
    {
      s[i] = a.add_state();
      a.set_o_final(s[i], alpha_convert(a2b, from.substr(0, i)));
    }

  // Set the first state initial.
  a.set_initial(s[0]);

  // Create all the edges of the type (ui | 1).
  for (int i = 0; i < n - 1; ++i)
    {
      const letter_t l[] = {from[i], 0 };
      a.add_io_edge(s[i], s[i + 1], l, "");
    }

  // Create the backward edges.
  for (int i = 0; i < n; ++i)
    for_each_letter(j, A)
      if (*j != from[i])
	{
	  const letter_t	l[] = {*j, 0};

	  const std::string	in = from.substr(0, i) + *j;
	  const std::string	factor = prefsuf(from, in);
	  const int		len = factor.size();

	  a.add_io_edge(s[i], s[len], l,
			alpha_convert(a2b, in.substr(0, i - len + 1)));
	}

  // Last state goes back to state i (length of w) with an edge
  // of the type : (un | y) (to = y.w)
  const letter_t	l[] = {from[n - 1], 0};

  std::string		f = prefsuf(alpha_convert(a2b, from), to);
  int			f_len = f.size();

  a.add_io_edge(s[n - 1], s[f_len], l, to.substr(0, n - f_len));

  return a;
}

automaton_t
replace_right(const std::string& from,	const std::string& to,
	      const alphabet_t& A,	const alphabet_t& B)
{
  monoid_elt_t from_elt(A, from);
  monoid_elt_t to_elt(B, to);
  from_elt.mirror();
  to_elt.mirror();

  automaton_t left = replace_left(from_elt.value(), to_elt.value(), A, B);
  return transpose(left);
}

int main(int argc, char** argv)
{
  if (argc != 4)
    usage(argc, argv);

  alphabet_t	A;
  A.insert('a');
  A.insert('b');

  std::string	from = argv[1];
  std::string	to = argv[2];
  std::string	name = argv[3];

  automaton_t	left_auto = replace_left(from, to, A, A);

  automaton_t   right_auto = replace_right(from, to, A, A);

  automaton_t	left_right_auto = new_automaton(A, A);
  automaton_t	right_left_auto = new_automaton(A, A);

  realtime_composition(left_auto, right_auto, left_right_auto);
  realtime_composition(right_auto, left_auto, right_left_auto);

  std::string	left_name = name + "_left.xml";
  std::string	right_name = name + "_right.xml";
  std::string	left_right_name = name + "_left_right.xml";
  std::string	right_left_name = name + "_right_left.xml";

  std::ofstream left(left_name.c_str());
  std::ofstream right(right_name.c_str());
  std::ofstream left_right(left_right_name.c_str());
  std::ofstream right_left(right_left_name.c_str());

  tools::xml_dump(left, left_auto, "left");
  tools::xml_dump(right, right_auto, "right");
  tools::xml_dump(left_right, left_right_auto, "left_right");
  tools::xml_dump(right_left, right_left_auto, "right_left");


  std::cout << "Cautious left sequential transducer: " << left_name
	    << std::endl
	    << "Cautious right sequential transducer: " << right_name
	    << std::endl
	    << "Left transducer composed by right transducer: "
	    << left_right_name
	    << std::endl
	    << "Right transducer composed by left transducer: "
	    << right_left_name
	    << std::endl;
}
