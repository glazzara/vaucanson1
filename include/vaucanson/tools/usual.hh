// usual.hh
//
// $Id$
// VCSN_HEADER

#ifndef MISC_USUAL_HH
# define MISC_USUAL_HH

# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
# include <vaucanson/algebra/concrete/series/polynoms.hh>
# include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/automata/concrete/manylinks.hh>
# include <vaucanson/misc/ref.hh>


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
		    polynom<std::string, int>,
		    ManyLinks<polynom<std::string, int>, NoTag, NoTag>,
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
 typedef typename Prefix##monoid_t::alphabets_elt_t Prefix##alphabets_elt_t;  \
 typedef typename Prefix##monoid_t::alphabet_t      Prefix##alphabet_t;	      \
 typedef typename Prefix##alphabet_t::iterator      Prefix##alphabet_iterator;\
 typedef typename AutoType::weights_t               Prefix##weights_t;	      \
 typedef typename AutoType::label_t		    Prefix##label_t;	      \
 typedef typename AutoType::tag_t		    Prefix##tag_t;

#define AUTOMATON_TYPES(AutoType)                   AUTOMATON_TYPE(AutoType,)

  } // tools

} // vcsn

# endif // MISC_USUAL_HH
