// check_minimisation.cc
// 
// VCSN_HEADER


#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
#include <vaucanson/algebra/concrete/series/polynoms.hh>
#include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>
#include <vaucanson/algebra/concrete/series/polynoms.hh>

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>

# include <vaucanson/automata/concept/kinds.hh>

# include <vaucanson/automata/concept/tags.hh>

# include <vaucanson/automata/concrete/manylinks.hh>

# include <check/tests_stuff.hh>
# include <map>
# include <algorithm>
# include <list>

# include <vaucanson/misc/ref.hh>
# include <vaucanson/misc/dot_dump.hh>

# include <automata/implementation_check/gen_random.hh>

# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/automata/concept/kinds.hh>

# include <vaucanson/automata/concept/transpose_impl.hh>

# include <time.h>

using namespace vcsn;
using namespace vcsn::algebra;

usual_automaton_t ret_mirror_automata(usual_automaton_t& model)
{
  typedef usual_automaton_t::edge_iterator edge_iterator;
  typedef usual_automaton_t::state_iterator state_iterator;

  std::list<unsigned> new_set;

  for (edge_iterator i = model.edges().begin(); i != model.edges().end(); i++)
    new_set.push_back(*i);
  
  for (edge_iterator i = model.edges().begin(); i != model.edges().end(); i++)
    if (std::find(new_set.begin(), new_set.end(), *i) != new_set.end())
      {
	hedge_t tmp(*i);
	model.aim_of(tmp);
	model.add_edge(model.aim_of(tmp),
		       model.origin_of(tmp), 
		       model.serie_of(tmp));
	model.del_edge(tmp);
      }
  
  for (state_iterator i = model.states().begin(); 
       i != model.states().end(); i++)
    {
      if (model.is_initial(*i)) 
	{ 
	  model.unset_initial(*i); 
	  model.set_final(*i); 
	}
      else if (model.is_final(*i)) 
	{ 
	  model.unset_final(*i); 
	  model.set_initial(*i); 
	}
    }

  return model;
}


int main(int argc, char **argv)
{

  unsigned verbose;

  if ((argc > 1) && (argv[1] == std::string("--noverbose")))
    verbose = 0;
  else
    verbose = 1;
  tests::Tester t(verbose);

  std::filebuf fb;
  fb.open ("automaton.dot", std::ios::out);
  std::ostream os(&fb);

  gen_auto_t gen(time(0x0));

  typedef usual_automaton_t::edge_iterator edge_iterator;
  typedef usual_automaton_t::state_iterator state_iterator;

  usual_automaton_t deter;

  deter.create();

  hstate_t init = deter.add_state();
  hstate_t hide = deter.add_state();
  hstate_t final = deter.add_state();

  deter.set_initial(init);
  deter.set_final(final);

  deter.add_letter_edge(init, init, 'b');
  deter.add_letter_edge(init, hide, 'a');
  deter.add_letter_edge(hide, hide, 'a');
  deter.add_letter_edge(hide, final, 'b');
  deter.add_letter_edge(final, final, 'b');
  deter.add_letter_edge(final, final, 'a');

  typedef transpose_traits<usual_automaton_t>::transpose_t transpose_t;

  //usual_automaton_t co_deter;
  transpose_t co_deter;
  //co_deter.create();

  co_deter = transpose_view(deter);
  
  //  co_deter = determinize(co_deter);
  
  std::cout << co_deter.states().size() << std::endl;

//   for (edge_iterator e = co_deter.edges().begin();
//        e != co_deter.edges().end();
//        ++e)
//     op_rout(co_deter.series(), std::cout, co_deter.label_of(*e));

  typedef std::set<hstate_t>	                     subset_t;
  typedef transpose_t::series_t::monoid_t::alphabet_t alphabet_t;

  subset_t aim;
  const alphabet_t&	   alphabet(co_deter.series().monoid().alphabet());

  for (state_iterator j = co_deter.states().begin();
       j != co_deter.states().end(); j++)
    co_deter.letter_deltac(aim, *j,
			   *alphabet.begin(), delta_kind::states());

  std::cout << aim.size() << std::endl;

  for (subset_t::iterator i = aim.begin(); i != aim.end(); i++)
    std::cout << *i << std::endl;
  
  misc::dot_dump(os, co_deter, "test");

  return 0;
}
