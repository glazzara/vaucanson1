// usual.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey 
// and Regis-Gianas.
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
#ifndef VCSN_TOOLS_USUAL_HH
# define VCSN_TOOLS_USUAL_HH

# include <vaucanson/config/system.hh>
# include <fstream>
# include <sstream>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/algebra/concrete/predefs.hh>
# include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
# include <vaucanson/algebra/concrete/series/polynoms.hh>
# include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>
# include <vaucanson/algebra/concrete/series/series.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concrete/graph.hh>
// FIXME: when dot_dump is re-integrated : # include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {

  namespace tools {

    using namespace vcsn;
    using namespace vcsn::algebra;
    using namespace vcsn::algebra::char_letter;

    typedef polynom<WordValue, bool> usual_serie_value;

    typedef Series<NumericalSemiring, Words> usual_series_t;
   
    typedef Graph
    <
      labels_are_series,
      WordValue,
      bool, 
      polynom<WordValue, bool>,
      char,
      NoTag>
    usual_automaton_impl_t;

    typedef Element<Automata<usual_series_t>, usual_automaton_impl_t>
    usual_automaton_t;

    template <class T>
    usual_automaton_t new_automaton(const T& alphabet);

    template <class InputIterator>
    usual_automaton_t new_automaton(InputIterator, InputIterator);

#define SAVE_AUTOMATON_DOT(Dir, Name, Auto, Index)		\
    {								\
      std::ostringstream s;					\
      s << Dir << "/" << Name << "_" << Index << ".dot";	\
      std::ofstream f(s.str().c_str());				\
      misc::dot_dump(f, Auto, Name);				\
    }

#define SAVE_AUTOMATON_DOT_SIMPLE(Name, Auto)			\
    {								\
      std::ostringstream s;					\
      s << Name << ".dot";					\
      std::ofstream f(s.str().c_str());				\
      misc::dot_dump(f, Auto, Name);				\
    }

#define RAND___(Max)						\
((unsigned) int(((float) rand() / (float) RAND_MAX) * Max));

  } // tools

} // vcsn

# include <vaucanson/tools/usual.hxx>

# endif // VCSN_TOOLS_USUAL_HH
