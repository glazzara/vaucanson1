// ex2.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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

/**
 * @file ex2.cc
 *
 * Build an automaton "An" with  "n" states whose determinized has 2^n
 * states.
 *
 * For every order on the n states, computes (by the state elimination
 * method) the expression of the language accepted by "An".
 *
 * Compute the standard automaton of that expression, then determinize
 * and minimize it; the result should have 2^n states.
 */

#include <vaucanson/boolean_automaton.hh>

#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/complement.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <vaucanson/algorithms/complete.hh>
#include <vaucanson/algorithms/trim.hh>
#include <vaucanson/algorithms/product.hh>

#include <ostream>
#include <sstream>

/**
 * Compute the next permutation.
 *
 * Generate  the  next  permutation  of   (O,  ...,  n  -  1)  in  the
 * lexicographic ordering
 */
int
nextperm(std::vector<int>& p)
{
  const unsigned n = p.size();
  int i, j;
  int z;

  for (i = n - 2; i >= 0 and p[i] > p[i+1]; --i)
    ;
  if (i < 0)
    return 0;
  z = p[i];
  for (j = n - 1; j >= i + 1 and p[j] < z; --j)
    ;
  p[i] = p[j];
  p[j] = z;

  i = i + 1;
  j = n - 1;
  while (i < j)
    {
      z = p[j];
      p[j] = p[i];
      p[i] = z;
      ++i;
      --j;
    }
  return 1;
}

/// Generate the permutation (0, 1, 2, ..., n - 1).
std::vector<int>
firstperm(unsigned n)
{
  std::vector<int> p (n);

  for (unsigned i = 0; i < n ; ++i)
    p[i] = i;

  return p;
}

/// Print a vector onto stdout.
template <class T>
std::ostream&
operator << (std::ostream& ostr, const std::vector<T>& v)
{
  for (typename std::vector<T>::const_iterator i = v.begin();
       i != v.end();
       ++i)
    {
      ostr << *i;
      if (i + 1 != v.end())
	ostr << " ";
    }
  return ostr;
}

using namespace vcsn;
using namespace vcsn::boolean_automaton;

/// Test whether two automata are equivalents.
bool
is_equivalent(const automaton_t &a, const automaton_t &b)
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

int
main(int argc, char** argv)
{
  if (argc != 2)
    {
      std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
      return 1;
    }

  unsigned		n;
  {
    std::istringstream	os (argv[1]);
    os >> n;
  }

  alphabet_t alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t an = new_automaton(alpha);

  hstate_t p = an.add_state();
  hstate_t x = p;
  for(unsigned i = 1; i < n; ++i)
    {
      hstate_t y = an.add_state();
      an.add_letter_edge(x, y, 'a');
      an.add_letter_edge(y, y, 'b');
      an.add_letter_edge(y, y, 'c');
      an.add_letter_edge(y, p, 'c');
      x = y;
    }
  an.add_letter_edge(x, p, 'a');
  an.set_initial(p);
  an.set_final(p);

  automaton_t dn = determinize(an);

  std::vector<int> q = firstperm(n);
  do
    {
      std::cout << q << std::endl;

      const std::list<hstate_t> l (q.begin(), q.end());
      rat_exp_t e = aut_to_exp(an, ListChooser (l));
      std::cout << e << std::endl;

      automaton_t sn = standard_of(e);
      std::cout << "S_n  =  " << sn << std::endl;

      automaton_t tn = determinize(sn);
      std::cout << "T_n  =  " << tn << std::endl;

      automaton_t un = minimization_hopcroft(tn);
      std::cout << "U_n  =  " << un << std::endl;

      if (not is_equivalent(dn, un))
	std::cerr << "U_n NOT EQUIVALENT TO A_n!" << std::endl;
      if (un.states().size() != unsigned (1 << n))
	std::cerr << "U_n HAS NOT THE CORRECT SIZE!" << std::endl;
      std::cout << std::endl;
    }
  while (nextperm(q)) ;
}
