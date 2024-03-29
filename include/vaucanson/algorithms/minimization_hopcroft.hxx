// minimization_hopcroft.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_MINIMIZATION_HOPCROFT_HXX
# define VCSN_ALGORITHMS_MINIMIZATION_HOPCROFT_HXX

# include <algorithm>
# include <list>
# include <queue>
# include <set>
# include <vector>

# include <vaucanson/algebra/implementation/semiring/numerical_semiring.hh>
# include <vaucanson/algorithms/minimization_hopcroft.hh>
# include <vaucanson/algorithms/is_deterministic.hh>
# include <vaucanson/algorithms/complete.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>

# ifndef VCSN_NDEBUG
#  include <vaucanson/algorithms/is_deterministic.hh>
# endif // ! VCSN_NDEBUG

namespace vcsn
{

  namespace internal
  {
    namespace hopcroft_minimization_det
    {

# define HOPCROFT_TYPES()						\
      typedef std::set<hstate_t> hstates_t;				\
      typedef std::vector<hstates_t> partition_t;			\
      typedef std::vector<unsigned> class_of_t;				\
      typedef std::queue<std::pair<hstates_t*, unsigned> > to_treat_t;

      /**
       * Splitter for classical Hopcroft minimization.
       */
      template <typename input_t>
      struct splitter_functor
      {
	AUTOMATON_TYPES (input_t);
	AUTOMATON_FREEMONOID_TYPES (input_t);
	HOPCROFT_TYPES ();

	const input_t& input_;
	hstates_t going_in_;
	class_of_t& class_of_;
	std::list<unsigned> maybe_splittable_;
	std::vector<unsigned> count_for_;

	splitter_functor (const input_t& input, unsigned int max_state,
			  class_of_t& class_of)
	  : input_ (input), going_in_ (), class_of_(class_of),
	    count_for_ (max_state)
	{}

	/// True if there's a transition arriving in one of the states ss with letter \a l.
	bool compute_states_going_in (const hstates_t& ss, letter_t l)
	{
	  going_in_.clear ();
	  maybe_splittable_.clear ();
	  for_all_const_ (hstates_t, i, ss)
          {
	    for (rdelta_iterator t(input_.value(), *i); ! t.done(); t.next())
	    {
	      monoid_elt_t w(input_.series_of(*t).structure().monoid(), l);
	      if (input_.series_of(*t).get(w) != input_.series().semiring().wzero_)
	      { /// For each state, store its class (partition) and count.
	        hstate_t s = input_.src_of(*t);
		unsigned class_of_state = class_of_[s];

		if (count_for_[class_of_state] == 0)
		  maybe_splittable_.push_back (class_of_state);
		count_for_[class_of_state]++;
		going_in_.insert (s);
	      }
            }
          }
	  return not going_in_.empty ();
	}

	/// Split @a partition if needed.
	void execute (partition_t& partition, to_treat_t& to_treat,
		      unsigned& n_partition)
	{
	  for_all (std::list<unsigned>, inpartition, maybe_splittable_)
	  {
	    hstates_t& states = partition[*inpartition];
	    if (states.size () == count_for_[*inpartition])
	    { // All elements in states are predecessors, no split.
	      count_for_[*inpartition] = 0;
	      continue;
	    }
	    count_for_[*inpartition] = 0;
	    hstates_t states_inter_going_in;
	    hstates_t& states_minus_going_in = partition[n_partition];
	    // Compute @a states \ @a going_in_.
	    set_difference
	      (states.begin (), states.end (),
	       going_in_.begin (), going_in_.end (),
	       std::insert_iterator<hstates_t> (states_minus_going_in,
						states_minus_going_in.begin ()));
	    // Compute @a states Inter @a going_in_.
	    set_intersection
	      (states.begin(), states.end (),
	       going_in_.begin (), going_in_.end (),
	       std::insert_iterator<hstates_t> (states_inter_going_in,
						states_inter_going_in.begin ()));
	    // A split MUST occur.
	    assertion (not (states_inter_going_in.empty ()
			    or states_minus_going_in.empty ()));
	    // @a states must be the bigger one.
	    if (states_minus_going_in.size () > states_inter_going_in.size ())
	    {
	      states.swap (states_minus_going_in);
	      states_minus_going_in.swap (states_inter_going_in);
	    }
	    else
	      states.swap (states_inter_going_in);
	    for_all_const_ (hstates_t, istate, states_minus_going_in)
	      class_of_[*istate] = n_partition;
	    to_treat.push (std::make_pair (&states_minus_going_in,
					   n_partition++));
	  }
	}
      };

      /// Functor that constructs the transitions.
      template <typename input_t, typename output_t>
      struct transition_adder_functor
      {
	AUTOMATON_TYPES (input_t);
	HOPCROFT_TYPES ();

	const input_t& input_;
	output_t& output_;
	const class_of_t& class_of_;

	unsigned src_;

	transition_adder_functor (const input_t& input, output_t& output,
				  const class_of_t& class_of)
	  : input_ (input), output_ (output), class_of_ (class_of)
	{}

	/// Add the transitions needed by @a representative.
	void execute (hstate_t representative)
	{
	  src_ = class_of_[representative];
          for (delta_iterator t(input_.value(), representative); ! t.done(); t.next())
          {
            output_.add_series_transition (src_, class_of_[input_.dst_of (*t)],
                                           input_.series_of (*t));
          }
	}
      };
    }
  }


  template <typename A, typename AI1, typename AI2>
  void
  do_hopcroft_minimization_det(const AutomataBase<A>&,
			       Element<A, AI2>&		output,
			       const Element<A, AI1>&	input)
  {
    typedef Element<A, AI1> input_t;
    typedef Element<A, AI2> output_t;
    AUTOMATON_TYPES (input_t);
    AUTOMATON_FREEMONOID_TYPES (input_t);
    HOPCROFT_TYPES ();

    using namespace internal::hopcroft_minimization_det;

    precondition(is_deterministic(input));

    unsigned max_state = input.states ().back () + 1;
    partition_t partition (max_state);
    class_of_t class_of (max_state);
    to_treat_t to_treat;
    unsigned n_partition = 0;
    const alphabet_t& alphabet =
      input.structure ().series ().monoid ().alphabet ();

    {
      // Initialize Partition = {Q \ F , F }
      hstates_t* finals = 0, * others = 0;
      int n_finals = -1, n_others = -1,
	count_finals = 0, count_others = 0;

# define add_to_class(Name)			\
      do {					\
	if (not Name)				\
	{					\
	  Name = &(partition[n_partition]);	\
	  n_ ## Name = n_partition++;		\
	}					\
	count_ ## Name ++;			\
	(*Name).insert (*state);		\
	class_of[*state] = n_ ## Name;		\
      } while (0)

      for_all_const_states (state, input)
	if (input.is_final (*state))
	  add_to_class (finals);
	else
	  add_to_class (others);
# undef add_to_class

      if (n_partition == 0)
	return;
      if (n_partition == 1)
      {
	output = input;
	return;
      }
      // Put F or Q \ F in the "To treat" list T.
      if (count_finals > count_others)
	to_treat.push (std::make_pair (others, n_others));
      else
	to_treat.push (std::make_pair (finals, n_finals));
    }

    {
      splitter_functor<input_t> splitter (input, max_state, class_of);

      // While T is not empty,
      while (not to_treat.empty () && n_partition < max_state)
      {
	// Remove a set S of T ,
	hstates_t& states = *(to_treat.front ().first);
	to_treat.pop ();

	// For each letter l in Alphabet,
	for_all_const_letters (letter, alphabet)
	  {
	    if (not splitter.compute_states_going_in (states, *letter))
	      continue;
	    splitter.execute (partition, to_treat, n_partition);
	    if (n_partition == max_state)
	      break;
	  }
      }
    }

    // Build the automaton.
    // Assume that states are numbers starting from 0.
    for (unsigned i = 0; i < n_partition; ++i)
      output.add_state ();

    transition_adder_functor<input_t, output_t>
      transition_adder (input, output, class_of);

    typename partition_t::iterator istates = partition.begin ();
    for (unsigned i = 0; i < n_partition; ++i, ++istates)
    {
      hstate_t representative = *(*istates).begin();

      if (input.is_final (representative))
	output.set_final (class_of[representative]);
      transition_adder.execute (representative);
    }

    for_all_const_initial_states (state, input)
      output.set_initial (class_of[*state]);
  }

# undef HOPCROFT_TYPES

  /**
   * Minimize @a a with Hopcroft algorithm.
   *
   * @param a The automaton.
   * @pre @a a must be a deterministic Boolean automaton.
   * @pre @a a must be a complete automaton.
   *
   * @return
   */
  template<typename A, typename AI>
  Element<A, AI>
  minimization_hopcroft(const Element<A, AI>& a)
  {
    BENCH_TASK_SCOPED("minimization_hopcroft");
    precondition(is_deterministic(a));
    precondition(is_complete(a));
    Element<A, AI> output(a.structure());
    do_hopcroft_minimization_det(a.structure(), output, a);
    return output;
  }


  /*-------------------------------------.
  | Quotient with Boolean multiplicities |
  `-------------------------------------*/
  namespace internal
  {
    namespace hopcroft_minimization_undet
    {

# define QUOTIENT_TYPES()						\
      typedef std::list<hstate_t> partition_t;				\
      typedef std::vector<partition_t> partition_set_t;			\
      typedef typename partition_t::iterator partition_iterator;	\
      typedef std::vector<unsigned> class_of_t;				\
      typedef std::pair<unsigned, letter_t> pair_t;			\
      typedef std::list<pair_t> to_treat_t;

      template <typename input_t>
      class quotient_splitter
      {
      public:
	AUTOMATON_TYPES(input_t);
	AUTOMATON_FREEMONOID_TYPES(input_t);
	QUOTIENT_TYPES();

	typedef std::vector<bool> going_in_t;

	quotient_splitter (const automaton_t& input, class_of_t& class_of,
			   unsigned max_states)
	  : input_(input),
	    alphabet_(input.series().monoid().alphabet()),
	    class_(class_of),
	    count_for_(max_states, 0),
	    twin_(max_states, 0),
	    going_in_(max_states, false)
	{ }

	/// True if there's a transition arriving in state \a p with letter \a a.
	bool compute_going_in_states (partition_t& p, letter_t a)
	{
	  for_all_(going_in_t, s, going_in_)
	    *s = false;


	  semiring_elt_t weight_zero = input_.series().semiring().wzero_;
	  monoid_elt_t w(input_.series().monoid(), a);

	  for_all_(partition_t, s, p)
          {
            for (rdelta_iterator t(input_.value(), *s); ! t.done(); t.next())
	    {
	      series_set_elt_t st = input_.series_of(*t);
              if (st.get(w) != weight_zero)
	      {
                hstate_t s = input_.src_of(*t);
                if (!going_in_[s])
                {
                  /// For each state, store its class (partition) and count.
                  going_in_[s] = true;
                  const unsigned i = class_[s];
                  if (count_for_[i] == 0)
                    met_class_.push_back(i);
                  count_for_[i]++;
                }
              }
            }
          }
	  return !met_class_.empty();
	}

	/// Split partition @a b if needed.
	void split (partition_set_t& parts, unsigned& max_partitions)
	{
	  for_all_(std::list<unsigned>, klass, met_class_)
	  {
	    // if all states are predecessors there is no needed split
	    if (count_for_[*klass] == parts[*klass].size())
	      continue;

	    if (twin_[*klass] == 0)
	      twin_[*klass] = max_partitions++;
	    unsigned new_klass = twin_[*klass];

	    typename partition_t::iterator q;
	    for (typename partition_t::iterator next = parts[*klass].begin();
		 next != parts[*klass].end();)
	    {
	      q = next;
	      ++next;
	      if (going_in_[*q])
	      {
		parts[new_klass].insert(parts[new_klass].end(), *q);
		class_[*q] = new_klass;
		parts[*klass].erase(q);
	      }
	    }
	  }
	}

	void add_new_partitions(to_treat_t&		to_treat,
				const partition_set_t&	part)
	{
	  for_all_(std::list<unsigned>, klass, met_class_)
	  {
	    if (twin_[*klass] != 0)
	    {
	      for_all_const_letters(e, alphabet_)
	      {
		if (find(to_treat.begin(), to_treat.end(), pair_t(*klass, *e)) !=
		    to_treat.end())
		  to_treat.push_back(pair_t(twin_[*klass], *e));
		else
		  if (part[*klass].size() < part[twin_[*klass]].size())
		    to_treat.push_back(pair_t(*klass, *e));
		  else
		    to_treat.push_back(pair_t(twin_[*klass], *e));
	      }
	    }
	  }

	  for_all_(std::list<unsigned>, klass, met_class_)
	  {
	    count_for_[*klass] = 0;
	    twin_[*klass] = 0;
	  }
	  met_class_.clear();
	}

      private:
	const automaton_t& input_;
	const alphabet_t& alphabet_;
	class_of_t& class_;
	std::vector<unsigned> count_for_;
	std::vector<unsigned> twin_;
	going_in_t going_in_;
	std::list<unsigned> met_class_;
      };
    }
  }

  template <typename A, typename AI1, typename AI2>
  void
  do_quotient(const AutomataBase<A>&,
	      const algebra::NumericalSemiring&,
	      SELECTOR(bool),
	      Element<A, AI2>&		output,
	      const Element<A, AI1>&	input)
  {
    BENCH_TASK_SCOPED("do_quotient");

    typedef Element<A, AI1> input_t;
    typedef Element<A, AI2> output_t;
    AUTOMATON_TYPES(input_t);
    AUTOMATON_FREEMONOID_TYPES(input_t);
    QUOTIENT_TYPES();

    using namespace internal::hopcroft_minimization_undet;

    const alphabet_t& alphabet_(input.series().monoid().alphabet());
    unsigned max_states = 0;

    for_all_const_states(i, input)
      max_states = std::max(unsigned(*i), max_states);
    ++max_states;

    /*--------------------------.
    | To label the subsets of Q |
    `--------------------------*/
    unsigned max_partitions = 0;

    /*-----------------------------------------.
    | To manage efficiently the partition of Q |
    `-----------------------------------------*/
    class_of_t		class_(max_states);
    partition_set_t	part(max_states);

    /*-------------------------.
    | To have a list of (P, a) |
    `-------------------------*/
    to_treat_t		to_treat;

    /*-------------------------.
    | Initialize the partition |
    `-------------------------*/
    BENCH_TASK_START("initialize partition");

    // In the general case, we have two sets, part[0] and part[1] One
    // holds the final states, the other the non-final states.	In
    // some cases we may have only one set, for instance if we have no
    // final states, or if we have only final states.  Because we do
    // not want to have an empty part[0], we will fill it with the
    // first kind of state (final / non-final) we encounter.
    unsigned final = 1;

    for_all_const_states (p, input)
    {
      unsigned c;
      if (max_partitions == 0)
	{
	  c = 0;
	  final = !input.is_final(*p);
	}
      else
	{
	  c = input.is_final(*p) ? final : (1 - final);
	}
      class_[*p] = c;
      part[c].insert(part[c].end(), *p);
      max_partitions = std::max(max_partitions, c + 1);
    }

    BENCH_TASK_STOP();

    /*------------------------------.
    | Initialize the list of (P, a) |
    `------------------------------*/
    BENCH_TASK_START("initialize partition");

    if (max_partitions > 0)
      for_all_const_letters (e, alphabet_)
	to_treat.push_back(pair_t(0, *e));

    if (max_partitions > 1)
      for_all_const_letters (e, alphabet_)
	to_treat.push_back(pair_t(1, *e));

    BENCH_TASK_STOP();

    /*----------.
    | Main loop |
    `----------*/
    BENCH_TASK_START("main loop");
    {
      quotient_splitter<input_t> splitter(input, class_, max_states);
      while (!to_treat.empty())
      {
	BENCH_TASK_SCOPED("inner loop");
	pair_t c = to_treat.front();
	to_treat.pop_front();
	unsigned p = c.first;
	letter_t a = c.second;

	if (!splitter.compute_going_in_states(part[p], a))
	  continue;
	{
	  BENCH_TASK_SCOPED("splitter.split");
	  splitter.split(part, max_partitions);
	}
	{
	  BENCH_TASK_SCOPED("splitter.add_new_partitions");
	  splitter.add_new_partitions(to_treat, part);
	}
      }
    }

    BENCH_TASK_STOP();

    /*------------------------------------.
    | Construction of the ouput automaton |
    `------------------------------------*/
    BENCH_TASK_START("construct output automaton");

    // Create the states
    for (unsigned i = 0; i < max_partitions; ++i)
      output.add_state();

    std::set<unsigned> already_linked;
    for (unsigned i = 0; i < max_partitions; ++i)
    {
      // Get the first state of the partition => each state has the
      // same behaviour
      hstate_t s = part[i].front();

      if (input.is_final(s))
	output.set_final(i);

      // Create the transitions
      for_all_const_letters (e, alphabet_)
      {
	already_linked.clear();

        for (delta_iterator t(input.value(), s); ! t.done(); t.next())
	{
          monoid_elt_t w(input.series_of(*t).structure().monoid(), *e);
          if (input.series_of(*t).get(w) != input.series().semiring().wzero_)
          {
	    hstate_t out = input.dst_of(*t);
            unsigned c = class_[out];
            if (already_linked.find(c) == already_linked.end())
            {
              already_linked.insert(c);
	      output.add_letter_transition(i, c, *e);
            }
          }
	}
      }
    }

    // Set initial states.
    for_all_const_initial_states(i, input)
      output.set_initial(class_[*i]);

    BENCH_TASK_STOP();
  }

# undef QUOTIENT_TYPES


  /*----------------------------------------.
  | Quotient with multiplicities (covering) |
  `----------------------------------------*/

  template <class S, class T,
	    typename A, typename input_t, typename output_t>
  void
  do_quotient(const AutomataBase<A>&	,
	      const S&			,
	      const T&			,
	      output_t&			output,
	      const input_t&		input)
  {
    AUTOMATON_TYPES(input_t);
    AUTOMATON_FREEMONOID_TYPES(input_t);
    using namespace std;

    /*----------------------------------------.
    | Declare data structures and variables.  |
    `----------------------------------------*/

    typedef set<htransition_t>		       set_transitions_t;
    typedef set<hstate_t>		       set_states_t;
    typedef set<semiring_elt_t>		       set_semiring_elt_t;
    typedef vector<semiring_elt_t>	       vector_semiring_elt_t;
    typedef pair<unsigned, letter_t>	       pair_class_letter_t;
    typedef pair<hstate_t, semiring_elt_t>     pair_state_semiring_elt_t;
    typedef set<pair_state_semiring_elt_t>     set_pair_state_semiring_elt_t;
    typedef map<semiring_elt_t, unsigned>      map_semiring_elt_t;

    series_set_elt_t	null_series	= input.series().zero_;
    semiring_elt_t	weight_zero	= input.series().semiring().wzero_;
    monoid_elt_t	monoid_identity	= input.series().monoid().VCSN_EMPTY_;
    const alphabet_t&	alphabet (input.series().monoid().alphabet());

    queue<pair_class_letter_t>				the_queue;

    set<unsigned>	met_classes;

    unsigned	max_partition	= 0;
    unsigned	max_states	= 0;

    for_all_const_states(q, input)
      max_states = std::max(unsigned (*q), max_states);
    ++max_states;
    // Avoid special case problem (one initial and final state...)
    max_states = std::max(max_states, 2u);

    vector< vector<set_pair_state_semiring_elt_t> > inverse (max_states);

    map<letter_t, unsigned> pos_of_letter;

    unsigned max_pos = 0;

    for_all_const_letters(a, alphabet)
      pos_of_letter[*a] = max_pos++;

    set_states_t		states_visited;
    set_semiring_elt_t		semiring_had_class;
    vector<set_states_t>	classes (max_states);
    vector<unsigned>		class_of_state (max_states);
    vector_semiring_elt_t	old_weight (max_states);
    map_semiring_elt_t		class_of_weight;

    for (unsigned i = 0; i < max_states; ++i)
      inverse[i].resize(max_pos);

    for_all_const_states(q, input)
      for_all_const_letters(a, alphabet)
      {

	for_all_const_(set_states_t, r, states_visited)
	  old_weight[*r] = weight_zero;
	states_visited.clear();

        for (rdelta_iterator e(input.value(), *q); ! e.done(); e.next())
        {
          monoid_elt_t w(input.series_of(*e).structure().monoid(), *a);
          if (input.series_of(*e).get(w) != input.series().semiring().wzero_)
	  {
	    hstate_t		p = input.src_of(*e);
	    if (states_visited.find(p) != states_visited.end())
	      inverse[*q][pos_of_letter[*a]].
		erase(pair_state_semiring_elt_t (p, old_weight[p]));
	    else
	      states_visited.insert(p);
	    series_set_elt_t	sd = input.series_of(*e);
	    monoid_elt_t	md (input.structure().series().monoid(), *a);
	    semiring_elt_t	wsd = sd.get(md);
	    old_weight[p] += wsd;
	    inverse[*q][pos_of_letter[*a]].
	      insert(pair_state_semiring_elt_t (p, old_weight[p]));
	  }
        }
      }

    /*-----------------------------------------------------------.
    | Initialize the partition with as many classes as there are |
    | final values.                                              |
    `-----------------------------------------------------------*/

    bool	 empty = true;
    unsigned	 class_non_final (0);

    for_all_const_states(q, input)
      {
	if (not input.is_final(*q))
	{
	  if (empty == true)
	  {
	    empty = false;
	    class_non_final = max_partition;
	    max_partition++;
	  }
	  classes[class_non_final].insert(*q);
	  class_of_state[*q] = class_non_final;
	}
	else
	{
	  semiring_elt_t w = input.get_final(*q).get(monoid_identity);
	  if (semiring_had_class.find(w) == semiring_had_class.end())
	  {
	    semiring_had_class.insert(w);
	    classes[max_partition].insert(*q);
	    class_of_weight[w] = max_partition;
	    class_of_state[*q] = max_partition;
	    max_partition++;
	  }
	  else
	  {
	    classes[class_of_weight[w]].insert(*q);
	    class_of_state[*q] = class_of_weight[w];
	  }
	}
      }

    /*-----------------------------------------------------.
    | Initialize the queue with pairs <class_id, letter>.  |
    `-----------------------------------------------------*/

    for (unsigned i = 0; i < max_partition; i++)
      for_all_const_letters(a, alphabet)
	the_queue.push(pair_class_letter_t (i, *a));

    /*----------------.
    | The main loop.  |
    `----------------*/

    unsigned old_max_partition = max_partition;

    while(not the_queue.empty())
    {
      pair_class_letter_t pair = the_queue.front();
      the_queue.pop();
      met_classes.clear();
      vector_semiring_elt_t val (max_states);

      // FIXME: Isn't there an easier way to do this?
      for_all_const_states(q, input)
	val[*q] = 0;

      // First, calculate val[state] and not met_classes.
      for_all_const_(set_states_t, q, classes[pair.first])
	for_all_const_(set_pair_state_semiring_elt_t, pair_,
		       inverse[*q][pos_of_letter[pair.second]])
	{
	  unsigned  state = pair_->first;
	  if (met_classes.find(class_of_state[state]) ==
	      met_classes.end())
	    met_classes.insert(class_of_state[state]);
	  val[state] += pair_->second;
	}

      // Next, for each met class, do the partition.
      for_all_const_(set<unsigned>, class_id, met_classes)
      {
	if (classes[*class_id].size() == 1)
	  continue ;

	queue<hstate_t>	to_erase;
	semiring_elt_t	next_val;
	semiring_elt_t	first_val = val[*(classes[*class_id].begin())];
	class_of_weight.clear();
	semiring_had_class.clear();

	for_all_const_(set_states_t, p, classes[*class_id])
	{
	  next_val = val[*p];
	  // This state must be moved to another class!
	  if (next_val != first_val)
	  {
	    if (semiring_had_class.find(next_val) ==
		semiring_had_class.end()) // Must create a new class
	    {
	      classes[max_partition].insert(*p);
	      class_of_state[*p] = max_partition;
	      semiring_had_class.insert(next_val);
	      class_of_weight[next_val] = max_partition;
	      max_partition++;
	    }
	    else
	    {
	      classes[class_of_weight[next_val]].insert(*p);
	      class_of_state[*p] = class_of_weight[next_val];
	    }
	    to_erase.push(*p);
	  }
	}

	while(not to_erase.empty())
	{
	  hstate_t s = to_erase.front();
	  to_erase.pop();
	  classes[*class_id].erase(s);
	}

	// Push pairs <new_class_id, letter> into the queue.
	for (unsigned i = old_max_partition; i < max_partition; i++)
	  for_all_const_letters(b, alphabet)
	    the_queue.push(pair_class_letter_t(i, *b));
	old_max_partition = max_partition;
      }
    }

    /*------------------.
    | Form the output.  |
    `------------------*/

    typedef vector<series_set_elt_t> vector_series_set_elt_t;

    std::vector<hstate_t>	out_states (max_partition);

    // Add states.
    for(unsigned i = 0; i < max_partition; i++)
    {
      out_states[i]  = output.add_state();
      hstate_t a_state = *classes[i].begin();
      series_set_elt_t a_serie = null_series;

      for_all_const_(set_states_t, state, classes[i])
	if(input.is_initial(*state))
	  a_serie += input.get_initial(*state);

      output.set_initial(out_states[i] , a_serie);

      if (input.is_final(a_state))
	output.set_final(out_states[i] , input.get_final(a_state));
    }

    // Add transitions.
    vector_series_set_elt_t seriesof (max_partition, null_series);

    for(unsigned i = 0; i < max_partition; i++)
    {
      met_classes.clear();

      for (delta_iterator e(input.value(), *classes[i].begin()); ! e.done(); e.next())
	{
	  series_set_elt_t	se = input.series_of(*e);
	  unsigned		cs = class_of_state[input.dst_of(*e)];

	  if (met_classes.find(cs) == met_classes.end())
	  {
	    met_classes.insert(cs);
	    seriesof[cs] = se;
	  }
	  else
	    seriesof[cs] += se;
	}

      for_all_const_(set<unsigned>, cs, met_classes)
	if (seriesof[*cs] != null_series)
	  output.add_series_transition(out_states[i],
				       out_states[*cs],
				       seriesof[*cs]);
    }
  }

  template<typename A, typename AI>
  Element<A, AI>
  quotient(const Element<A, AI>& a)
  {
    BENCH_TASK_SCOPED("quotient");
    precondition(is_realtime(a));
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    automaton_t output(a.structure());
    do_quotient(a.structure(), a.structure().series().semiring(),
		SELECT(semiring_elt_value_t), output, a);
    return output;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_MINIMIZATION_HOPCROFT_HXX
