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
		    polynom<std::string, bool>,
		    ManyLinks<polynom<std::string, bool>, NoTag, NoTag>,
		    NoTag,
		    map> >
    >
    usual_automaton_t;

#define AUTOMATON_TYPES_(AutoType,Prefix)				      \
 typedef AutoType				    Prefix##automaton_t;      \
 typedef typename AutoType::states_t		    Prefix##states_t;	      \
 typedef typename AutoType::state_iterator	    Prefix##state_iterator;   \
 typedef typename AutoType::edges_t		    Prefix##edges_t;	      \
 typedef typename AutoType::edge_iterator	    Prefix##edge_iterator;    \
 typedef typename AutoType::initial_t	            Prefix##initial_t;	      \
 typedef typename AutoType::final_t		    Prefix##final_t;	      \
 typedef typename AutoType::initial_iterator	    Prefix##initial_iterator; \
 typedef typename AutoType::final_iterator	    Prefix##final_iterator;   \
 typedef typename AutoType::monoid_t		    Prefix##monoid_t;	      \
 typedef typename AutoType::monoid_elt_t	    Prefix##monoid_elt_t;     \
 typedef typename Prefix##monoid_elt_t::value_t	    Prefix##monoid_elt_value_t;     \
 typedef typename Prefix##monoid_t::alphabets_elt_t Prefix##alphabets_elt_t;  \
 typedef typename Prefix##monoid_t::alphabet_t      Prefix##alphabet_t;	      \
 typedef typename Prefix##alphabet_t::iterator      Prefix##alphabet_iterator;\
 typedef typename Prefix##alphabet_t::letter_t      Prefix##letter_t;	      \
 typedef typename AutoType::weights_t               Prefix##weights_t;	      \
 typedef typename AutoType::series_t                Prefix##series_t;	      \
 typedef typename AutoType::series_elt_t            Prefix##series_elt_t;     \
 typedef typename Prefix##series_elt_t::weight_t    Prefix##weight_t;         \
 typedef typename Prefix##weight_t::value_t         Prefix##weight_value_t;   \
 typedef typename AutoType::label_t		    Prefix##label_t;	      \
 typedef typename AutoType::tag_t		    Prefix##tag_t;

#define AUTOMATON_TYPES(AutoType)                   AUTOMATON_TYPES_(AutoType,)

#define zero_	zero(SELECT(typename series_elt_t::value_t))
#define one_	identity(SELECT(typename series_elt_t::value_t))

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
((unsigned) round(((float) rand() / (float) RAND_MAX) * Max));

  } // tools

} // vcsn

# endif // TOOLS_USUAL_HH
