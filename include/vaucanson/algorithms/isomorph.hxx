// isomorph.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_ISOMORPH_HXX
# define VCSN_ALGORITHMS_ISOMORPH_HXX

# include <vaucanson/algorithms/isomorph.hh>
# include <vaucanson/algorithms/determinize.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <vaucanson/algorithms/internal/skeleton.hh>

# include <queue>
# include <set>
# include <list>
# include <utility>

namespace vcsn
{

  /*--------------------------------------.
  | Helper for are_isomorphic algorithm.  |
  `--------------------------------------*/

  class Trie
  {
    public:
      Trie();
      /// Needed to avoid the copy of singular iterator when L is not set.
      Trie(const Trie& t);

      Trie* insert(std::vector<int>&);

    public:
      std::list<int> A, B;

      // Node in list C pointing to this node
      std::list<Trie*>::iterator L;

    private:
      /// Whether Trie::L was set.
      bool L_is_valid;
      Trie* insert_suffix(std::vector<int>&, unsigned int);
      std::map<int, Trie> children;
  };

  inline
  Trie::Trie ()
    : A(), B(), L(), L_is_valid(false), children()
  {
  }

  inline
  Trie::Trie (const Trie& t)
    : A(t.A), B(t.B),
      L(), L_is_valid(t.L_is_valid), children(t.children)
  {
    if (L_is_valid)
      L = t.L;
  }


  // Find node associated to the insertion of a vector of integers.
  inline Trie* Trie::insert(std::vector<int>& S)
  {
    return insert_suffix(S, 0);
  }

  inline Trie* Trie::insert_suffix(std::vector<int>& S, unsigned int p)
  {
    if (p == S.capacity() - 1)
      return this;

    return children[S[p]].insert_suffix(S, p + 1);
  }



  /*--------------------------------------.
  | Functor for are_isomorphic algorithm. |
  `--------------------------------------*/

  template<typename A, typename T>
  class Isomorpher
  {
    public:

      typedef Element<A, T> auto_t;
      AUTOMATON_TYPES(auto_t);

      typedef std::vector< std::list<int> > delta_t;
      typedef std::vector<int> trans_t;

      struct automaton_vars
      {
	  // We have to build the vector T_L using a valid iterator (i.e., not a
	  // singular one).  We use a temp int list to this end.
	  automaton_vars(const Element<A, T>& aut)
	    : s(aut),
	      aut(aut),
	      perm(aut.states().size(), -1),
	      T_L(aut.states().size(), std::list<int>().end()),
	      delta_det_in(aut.states().size()),
	      delta_det_out(aut.states().size()),
	      class_state(aut.states().size())
	  {
	  }

	  void
	  shrink_unused()
	  {
	    T_L.clear();
	    delta_det_in.clear();
	    delta_det_out.clear();
	    class_state.clear();
	    class_state.clear();
	  }


	  Skeleton<A, T> s;
	  const Element<A, T> aut;

	  // perm[i] = state of another automaton corresponding to state i in
	  // the isomorphism, or -1 when the association
	  // is yet undefined.
	  trans_t perm;

	  // Vector indexed by states that points to the corresponding node
	  // of the list of states of each class of states stored in the
	  // Tries.
	  std::vector<std::list<int>::iterator> T_L;

	  // Lists of deterministic ingoing and outgoing transitions
	  // for each state (delta_det_in[i] = list of deterministic ingoing
	  // transitions for state i, idem for delta_det_out[i])
	  delta_t delta_det_in;
	  delta_t delta_det_out;

	  // class_state_A[i] = class (node of a Trie) of state i for automaton A
	  std::vector<Trie*> class_state;
      };

      Isomorpher(const Element<A, T>& a, const Element<A, T>& b)
	: a_(a), b_(b)
      {
      }

      bool
      operator()()
      {
	if (fails_on_quick_tests())
	  return false;

	list_in_out_det_trans(a_);
	list_in_out_det_trans(b_);

	if (!construct_tries())
	  return false;

	// Analyzes co-deterministic ingoing and outgoing transitions
	//(obs: if the automata are deterministic, the isomorphism test
	// ends here)
	if (!analyse_det_trans())
	  return false;

	a_.shrink_unused();
	b_.shrink_unused();

	return backtracking();
      }

    private:
      /*!
       Performs quick and basic tests on both automata.
       If the the automata are not isomorphic, this function
       returns true.
       */
      bool
      fails_on_quick_tests()
      {
	return a_.aut.states().size() != b_.aut.states().size()
	  || a_.aut.transitions().size() != b_.aut.transitions().size()
	  || a_.aut.initial().size() != b_.aut.initial().size()
	  || a_.aut.final().size() != b_.aut.final().size();
      }


      /*!
       Constructs lists of deterministic ingoing and outgoing transitions
       for each state (delta_det_in[i] = list of deterministic ingoing
       transitions for state i, idem for delta_det_out[i]).
       */
      void
      list_in_out_det_trans(automaton_vars& av)
      {
	for (int i = 0; i < static_cast<int>(av.aut.states().size()); i++)
	{
	  if (av.s.delta_in[i].size() > 0)
	    list_det_trans(av, av.delta_det_in, av.s.delta_in, i);

	  if (av.s.delta_out[i].size() > 0)
	    list_det_trans(av, av.delta_det_out, av.s.delta_out, i);
	}
      }


      /*!
       This function create tries of classes of states with the same sequence
       of ingoing and outgoing transitions in lex. order for both automata.

       This function returns false if it discovers that the two automata
       are not isomorphic during the construction of the tries.
       */
      bool
      construct_tries()
      {
	// Constructs Tries for Automaton A.
	for (int i = 0; i < static_cast<int>(a_.aut.states().size()); i++)
	{
	  Trie *T_aux = add_all_transitions_to_trie(a_, i);

	  // New class?
	  if (T_aux->A.size() == 0)
	  {
	    // Inserts in list C of classes (nodes of Tries)
	    C_.push_front(T_aux);

	    // Each Trie node points to its node in list C
	    T_aux->L = C_.begin();
	  }

	  // Inserts the state in the list A of its corresponding class
	  T_aux->A.push_front(i);
	  // Defines class of state i
	  a_.class_state[i] = T_aux;
	  // T_L_A[i] = node of the list of states of class of state i
	  a_.T_L[i] = T_aux->A.begin();
	}


	// Constructs Tries for automaton B.
	for (int i = 0; i < static_cast<int>(b_.aut.states().size()); i++)
	{
	  Trie *T_aux = add_all_transitions_to_trie(b_, i);

          // Does the class of state i have more states for automaton B
	  // than those for automaton A ?
	  if (T_aux->A.size() == T_aux->B.size())
	    return false;

	  // Inserts the state in the list B of its corresponding class
	  T_aux->B.push_front(i);
	  // Defines class of state i
	  b_.class_state[i] = T_aux;
	  // T_L_B[i] = node of the list of states of class of state i
	  b_.T_L[i] = T_aux->B.begin();
	}

	return true;
      }


      /*!
       Searches for classes having only one state for each
       automaton. These states must be identified. These classes are
       then stored in list U.
       Also tests if all classes have the same number of states in
       lists A and B.

       This function return false if it finds that the two automata
       are not isomorphic during the construction of the list.
       */
      bool
      construct_list_of_classes_with_one_state(std::list<int>& U)
      {
	std::list<Trie*>::iterator itr_C = C_.begin();

	while (itr_C != C_.end())
	{
	  // Do automata A and B have the same number of states in the
	  // current class?
	  if ((*itr_C)->A.size() != (*itr_C)->B.size())
	    return false;

	  // Class *itr_C contains only one state of each automata?
	  if ((*itr_C)->A.size() == 1)
	  {
	    // States *((*itr_C).A.begin()) and
	    // *((*itr_C).B.begin()) have to be identified.
	    int k = *((*itr_C)->A.begin());
	    U.push_front(k);
	    int l = *((*itr_C)->B.begin());
	    a_.perm[k] = l;
	    b_.perm[l] = k;

	    // Just for coherence, lists A and B of class *itr_C are voided
	    ((*itr_C)->A).erase((*itr_C)->A.begin());
	    ((*itr_C)->B).erase((*itr_C)->B.begin());
	    // Deletes current node and points to the next.
	    itr_C = C_.erase(itr_C);
	  }
	  else
	    itr_C++;
	}
	return true;
      }

      /*!
       Fill a list of deterministic ingoing or outgoing transitions
       (according to the 'delta_in_or_not' set passed to the function)
       for a state 'i' (delta_det_in[i] = list of deterministic ingoing
       transitions for state i, idem for delta_det_out[i]).

       Usually, you would like to call this function with either S.delta_in
       or S.delta_out as 'delta_in_or_out' parameter.
       */
      void
      list_det_trans(automaton_vars& av,
		     delta_t& delta_det,
		     const delta_t& delta_in_or_out,
		     int i)
      {
	std::list<int>::const_iterator it = delta_in_or_out[i].begin();
	// Number of transitions with the same label
	int j = 1;

	for (it++; it != delta_in_or_out[i].end(); it++)
	{
	  // It seems there is no iterator arithmetics in C++:
	  // *(it_int - 1) doesn't compile.
	  int k = *(--it);
	  it++;
	  // New label?
	  if (av.s.transitions_labels[*it] != av.s.transitions_labels[k])
	    // The last transition is deterministic?
	    if (j == 1)
	      delta_det[i].push_back(k);
	  // Several transitions with the same label?
	    else
	      // Does nothing. A series of transitions with a new label begins.
	      j = 1;
	  // Same label?
	  else
	    j++;
	}
	// The last label visited is deterministic?
	if (j == 1)
	{
	  delta_det[i].push_back(*(--it));
	  it++;
	}
      }

      /*!
       Construct a list of all the given state's transitions and add them to
       the correct Trie.

       This function returns a pointer to the Trie where this list has been
       added.
       */
      Trie *
      add_all_transitions_to_trie(const automaton_vars& av,
				  int i)
      {
	// Vector all_transitions_lex contains the sequence of labels of
	// ingoing and outgoing transitions of state i in lex. order,
	// separated by a mark (-1)
	trans_t all_transitions_lex(av.s.delta_in[i].size() +
				    av.s.delta_out[i].size() + 1);

	// First stores the sequence of ingoing transitions
	for (std::list<int>::const_iterator it = av.s.delta_in[i].begin();
	     it != av.s.delta_in[i].end(); ++it)
	  all_transitions_lex.push_back(av.s.transitions_labels[*it]);

	all_transitions_lex.push_back(-1);

	// Next, outgoing transitions
	for (std::list<int>::const_iterator it = av.s.delta_out[i].begin();
	     it != av.s.delta_out[i].end(); ++it)
	  all_transitions_lex.push_back(av.s.transitions_labels[*it]);

	// Gets the node of the correct Trie (Trie of initial, final or normal
	// states) for the sequence of transitions of state i
	if (av.aut.is_initial(av.s.states[i]))
	  return T_I_.insert(all_transitions_lex);
	if (av.aut.is_final(av.s.states[i]))
	  return T_T_.insert(all_transitions_lex);

	return T_Q_IT_.insert(all_transitions_lex);
      }

      /*!
       Tries to discover more fixed states implied by states in U.
       During the loop, a state i of A is in its Trie if perm_A[i] = -1
       Time complexity: O(m).

       Returns false if this function finds that the two automata are
       not isomorphic.
       (obs: if the automata are deterministic, the isomorphism test
       ends here)
       */
      bool
      analyse_det_trans()
      {
	std::list<int> U;

	if (!construct_list_of_classes_with_one_state(U))
	  return false;

	for (; !U.empty(); U.pop_front())
	  if (!do_analyse_det_trans(U,
				    a_.delta_det_in,
				    b_.delta_det_in,
				    a_.s.src_transitions,
				    b_.s.src_transitions)
	      || !do_analyse_det_trans(U,
				       a_.delta_det_out,
				       b_.delta_det_out,
				       a_.s.dst_transitions,
				       b_.s.dst_transitions))
	    return false;

	return true;
      }


      bool
      do_analyse_det_trans(std::list<int>& U,
			   const delta_t& delta_det_A,
			   const delta_t& delta_det_B,
			   const std::vector<int>& transitions_A,
			   const std::vector<int>& transitions_B)
      {
	// Each state in U has already an image (perm_A and perm_B are
	// defined for this state)

	// i = current state in automaton A, j = its image in automaton B
	int i = U.front();
	int j = a_.perm[i];

	// As states i and j are already associated, they belong to
	// the same class, then have the same sequence of
	// deterministic transitions.
	std::list<int>::const_iterator it = delta_det_A[i].begin();
	std::list<int>::const_iterator it_aux = delta_det_B[j].begin();
	for (; it != delta_det_A[i].end(); ++it, ++it_aux)
	{

	  // The states being considered are the sources of current
	  // co-deterministic transitions (k for automaton A, l for B)
	  int k = transitions_A[*it];
	  int l = transitions_B[*it_aux];

	  // Has state k already been visited?
	  if (a_.perm[k] >= 0)
	  {
	    // If it has already been visited, does the current image
	    // matches state l?
	    if (a_.perm[k] != l)
	      return false;
	  }
	  else
	  {
	    // State k has not already been visited. The same must be
	    // true for state l.
	    if (b_.perm[l] != -1)
	      return false;
	    // Tries to associate states k and l

	    // Does k and l belongs to different classes?
	    if (a_.class_state[k] != b_.class_state[l])
	      return false;
	    // The states k and l belong to the same class and can be
	    // associated.
	    a_.perm[b_.perm[l] = k] = l;
	    // Removes k and l from theirs lists of states in theirs
	    // classes (O(1))
	    a_.class_state[k]->A.erase(a_.T_L[k]);
	    b_.class_state[l]->B.erase(b_.T_L[l]);
	    U.push_front(k);
	    if (a_.class_state[k]->A.size() == 1)
	    {
	      // If it remains only one state of each
	      // automaton in the class of the current states,
	      // they must be associated. Then they are
	      // putted in list U, and the class are removed
	      // from C.
	      // From now on k and l represent these states.
	      Trie* T_aux = a_.class_state[k];
	      k = T_aux->A.front();
	      l = T_aux->B.front();
	      a_.perm[b_.perm[l] = k] = l;

	      U.push_front(k);

	      // Removes class T_aux from C
	      C_.erase(T_aux->L);
	    }
	  }
	}
	return true;
      }


      /*!
       Tries to associate remaining states (in remaining classes
       in C). This is the backtracking phase.
       */
      bool
      backtracking()
      {
	// Stores in l the number of non-fixed states
	int l = 0;
	for (std::list<Trie*>::iterator it = C_.begin();
	     it != C_.end(); ++it)
	  l += (*it)->A.size();

	// Vectors of classes of remaining states.	States in the same
	// class are stored contiguously, and in the case of vector for
	// automaton B, classes are separated by two enTries: one with -1,
	// denoting the end of the class, and the following with the
	// position where the class begins in this vector.
	trans_t C_A(l);
	trans_t C_B(l + 2 * C_.size());
	// current[i] = position in C_B of image of state C_A[i] during
	// backtracking.
	std::vector<int> current(l);


	// Vector for test of correspondence of transitions of states already
	// attributed
	trans_t correspondence_transitions(a_.aut.states().size(), 0);

	list_remaining(C_A, C_B, current);

	// Tries to associate states of C_A and C_B

	int i = 0;
	bool rvalue = true;

	// Backtracking loop. Each iteration Tries to associate state
	// C_A[i]. If i = C_A.size(), the automata are isomorphic.
	while (i < static_cast<int>(C_A.size()))
	{
	  int j;
	  // Searches for the first free state in the class of C_A[i]
	  for (j = current[i]; C_B[j] != -1 && b_.perm[C_B[j]] >= 0; j++)
	    continue;

	  // There is no possibility for state C_A[i]
	  if (C_B[j] == -1)
	  {
	    // If there is no possibility for C_A[0], the automata are not
	    // isomorphic
	    if (i == 0)
	      return false;
	    else
	    {
	      // Prepares for backtracking in next iteration.
	      // Image of C_A[i] is set to first state of its class
	      current[i] = C_B[j + 1];
	      // Next iteration will try to associate state i - 1
	      // to next possible position
	      i--;
	      b_.perm[a_.perm[C_A[i]]] = -1;
	      a_.perm[C_A[i]] = -1;
	      current[i]++;
	    }
	  }
	  // Tries to associate state C_A[i] to state C_B[j]
	  else
	  {
	    current[i] = j;
	    a_.perm[C_A[i]] = C_B[j];
	    b_.perm[C_B[j]] = C_A[i];

	    rvalue = (test_correspondence(a_.s.delta_in, b_.s.delta_in,
					  a_.s.src_transitions,
					  b_.s.src_transitions,
					  C_A, C_B, i, j,
					  correspondence_transitions)
		      && test_correspondence(a_.s.delta_out, b_.s.delta_out,
					     a_.s.dst_transitions,
					     b_.s.dst_transitions,
					     C_A, C_B, i, j,
					     correspondence_transitions));

	    // States C_A[i] and C_B[j] can be associated.
	    if (rvalue)
	      // Tries to associate state in C_A[i + 1] in next iteration
	      i++;
	    // Impossible to associate C_A[i] to C_B[j]
	    else
	    {
	      // Tries C_A[i] to C_B[j + 1] in next iteration
	      b_.perm[a_.perm[C_A[i]]] = -1;
	      a_.perm[C_A[i]] = -1;
	      current[i]++;
	    }
	  }
	}
	return rvalue;
      }

      /*!
       Stores remaining states in C_A and C_B. Partial results of the
       backtracking are stored in vector current, that is initialized
       with the first element of each class.
       */
      void
      list_remaining(trans_t& C_A,
		     trans_t& C_B,
		     trans_t& current)
      {
	int i = 0, j = 0;
	for (std::list<Trie*>::iterator it = C_.begin(); it != C_.end();
	     it++)
	{
	  std::list<int>::iterator it_A = (*it)->A.begin();
	  std::list<int>::iterator it_B = (*it)->B.begin();
	  C_A[i] = *it_A;
	  C_B[j] = *it_B;
	  current[i++] = j++;
	  for (it_A++, it_B++; it_A != (*it)->A.end();
	       it_A++, it_B++)
	  {
	    C_A[i] = *it_A;
	    C_B[j++] = *it_B;
	    current[i] = current[i - 1];
	    i++;
	  }
	  // End of class
	  C_B[j++] = -1;
	  // Position where the class begins
	  C_B[j++] = current[i - 1];
	}
      }

      /*!
       Tests correspondence of transitions, considering
       states that are already in the permutation.
       */
      bool
      test_correspondence(const delta_t& delta_A,
			  const delta_t& delta_B,
			  const std::vector<int>& transitions_A,
			  const std::vector<int>& transitions_B,
			  trans_t& C_A,
			  trans_t& C_B,
			  int i,
			  int j,
			  trans_t& correspondence_transitions)
      {
	std::list<int>::const_iterator it_A = delta_A[C_A[i]].begin();
	std::list<int>::const_iterator it_B = delta_B[C_B[j]].begin();

	// Each iteration considers a sequence of ingoing labels
	// with the same label. The sequence begins at it_int
	while (it_A != delta_A[C_A[i]].end())
	{
	  // Searches for sources of ingoing transitions for current
	  // label that have already been associated. For each state
	  // visited, its position in correspondence_transitions is
	  // incremented.
	  int k = 0;
	  std::list<int>::const_iterator it_aux;
	  for (it_aux = it_A;
	       (it_aux != delta_A[C_A[i]].end()) &&
		 (a_.s.transitions_labels[*it_aux] ==
		  a_.s.transitions_labels[*it_A]);
	       it_aux++, k++)
	    // Is the source of current transition associated?
	    if (a_.perm[transitions_A[*it_aux]] >= 0)
	      correspondence_transitions[transitions_A[*it_aux]]++;

	  // Here, k = number of ingoing transitions for current label

	  // Idem for ingoing transitions of state C_B[j], but positions in
	  // correspondence_transitions are decremented.
	  for (; (k > 0); it_B++, k--)
	    // Has the source of current transition already been visited?
	    if (b_.perm[transitions_B[*it_B]] >= 0)
	      // Trying to decrement a position with 0 means that the
	      // corresponding state in A is not correct.
	      if (correspondence_transitions[b_.perm[transitions_B[*it_B]]] == 0)
		// The association of C_A[i] and C_B[j] is impossible
		return false;
	      else
		correspondence_transitions[b_.perm[transitions_B[*it_B]]]--;

	  // Verifies correspondence_transitions. The correspondence for
	  // current label is correct iff correspondence_transitions[l] = 0
	  // for all src l of ingoing transitions of C_A[i] labelled by
	  // the current label.
	  // For this, int_itr visits all transitions until int_itr_aux.

	  for (; it_A != it_aux; it_A++)
	  {
	    if (a_.perm[transitions_A[*it_A]] >= 0)
	      if (correspondence_transitions[transitions_A[*it_A]] != 0)
		return false;
	    // All positions must be 0 for next iteration
	    correspondence_transitions[transitions_A[*it_A]] = 0;
	  }

	}
	return true;
      }



      //Private Attributes
      automaton_vars a_;
      automaton_vars b_;
      std::list<Trie*> C_;
      // Tries of classes of normal, initial and final states.
      Trie T_Q_IT_;
      Trie T_I_;
      Trie T_T_;
  };


  /*---------------.
  | are_isomorphic |
  `---------------*/

  template<typename A, typename T>
  bool
  are_isomorphic(const Element<A, T>& a, const Element<A, T>& b)
  {
    TIMER_SCOPED("are_isomorphic");

    Isomorpher<A, T> isomorpher(a, b);

    return isomorpher();
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_ISOMORPH_HXX
