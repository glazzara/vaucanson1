// usual.hh
//
// $Id$
// VCSN_HEADER

#ifndef TOOLS_USUAL_HH
# define TOOLS_USUAL_HH

# include <fstream>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
# include <vaucanson/algebra/concrete/series/polynoms.hh>
# include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>
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
    
    typedef Element
    <
      Automata, 
      utility::ref< 
      AutomatonImpl<labels_are_series,
		    Series<NumericalSemiring, Words>,
		    polynom<std::string, bool>,
		    ManyLinks<polynom<std::string, bool>, NoTag, NoTag>,
		    NoTag,
		    std::map> >
    >
    usual_automaton_t;

#define AUTOMATON_TYPES_(AutoType,Prefix)				      \
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
    {							\
      char buf[128];					\
      snprintf(buf, 128, "%s/%s_%d.dot", Dir, Name, Index);	\
      std::ofstream f(buf);				\
      misc::dot_dump(f, Auto, Name);				\
    }

#define RAND___(Max)							\
((unsigned) trunc(((float) random() / (float) RAND_MAX) * Max));

  } // tools

} // vcsn

# endif // TOOLS_USUAL_HH
