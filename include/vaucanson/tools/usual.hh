// usual.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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
#ifndef TOOLS_USUAL_HH
# define TOOLS_USUAL_HH

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
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/automata/concrete/manylinks.hh>
# include <vaucanson/misc/ref.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {

  namespace tools {

    using namespace vcsn;
    using namespace vcsn::algebra;
    using namespace vcsn::algebra::char_letter;

    template <class F, class T>
    struct map : std::map<F,T>
    {};
    
    typedef Element
    <
      Automata, 
      utility::ref< 
      AutomatonImpl<labels_are_series,
		    Series<NumericalSemiring, Words>,
		    polynom<Word::value_t, bool>,
		    ManyLinks<polynom<Word::value_t, bool>, NoTag, NoTag>,
		    NoTag,
		    map> >
    >
    usual_automaton_t;

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

# endif // TOOLS_USUAL_HH
