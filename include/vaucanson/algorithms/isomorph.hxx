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

  Trie::Trie ()
    : A(), B(), L(), L_is_valid(false), children()
  {
  }

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


  /*---------------.
  | are_isomorphic |
  `---------------*/

  template<typename A, typename T>
  bool
  are_isomorphic(const Element<A, T>& a, const Element<A, T>& b)
  {
    TIMER_SCOPED("are_isomorphic");
    typedef Element<A, T> automaton_t;

    AUTOMATON_TYPES(automaton_t);

    // We can start with good suppositions.
    if (a.states().size() != b.states().size()
	|| a.transitions().size() != b.transitions().size()
	|| a.initial().size() != b.initial().size()
	|| a.final().size() != b.final().size())
      return false;

    std::list<int>::iterator it_int, it_int_B, it_int_aux;


    // Tries of classes of normal, initial and final states.
    Trie T_Q_IT, T_I, T_T;

    // List of fixed states emerged from classes stored in C.
    std::list<int> U;
    // class_state_A[i] = class (node of a Trie) of state i for automaton A
    std::vector<Trie*> class_state_A(a.states().size());
    // class_state_A[i] = idem for automaton B
    std::vector<Trie*> class_state_B(b.states().size());

    // perm_A[i] = state of automaton B corresponding to state i in
    // the isomorphism (idem for perm_B), or -1 when the association
    // is yet undefined
    std::vector<int> perm_A(a.states().size());
    std::vector<int> perm_B(b.states().size());

    Skeleton<A, T> Sa(a);
    Skeleton<A, T> Sb(b);

    // The automata are isomorphic unless one proves the contrary
    bool iso = true;

    // Constructs lists of deterministic ingoing and outgoing transitions
    // for each state (delta_det_in[i] = list of deterministic ingoing
    // transitions for state i, idem for delta_det_out[i])

    std::vector< std::list<int> > delta_det_in_A(a.states().size());
    std::vector< std::list<int> > delta_det_out_A(a.states().size());
    std::vector< std::list<int> > delta_det_in_B(b.states().size());
    std::vector< std::list<int> > delta_det_out_B(b.states().size());

    // Automaton A
    for (int i = 0; i < static_cast<int>(a.states().size()); i++)
    {
      if (Sa.delta_in[i].size() > 0)
      {
	it_int = Sa.delta_in[i].begin();
	// Number of transitions with the same label
	int j = 1;
	for (it_int++; it_int != Sa.delta_in[i].end(); it_int++)
	{
	  // It seems there is no iterator arithmetics in C++:
	  // *(it_int - 1) doesn't compile.
	  int k = *(--it_int);
	  it_int++;
	  // New label?
	  if (Sa.transitions_labels[*it_int] != Sa.transitions_labels[k])
	    // The last transition is deterministic?
	    if (j == 1)
	      delta_det_in_A[i].push_back(k);
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
	  delta_det_in_A[i].push_back(*(--it_int));
	  it_int++;
	}
      }
      if (Sa.delta_out[i].size() > 0)
      {
	it_int = Sa.delta_out[i].begin();
	// Number of transitions with the same label
	int j = 1;
	for (it_int++; it_int != Sa.delta_out[i].end(); it_int++)
	{
	  // It seems there is no iterator arithmetics in C++:
	  // *(it_int - 1) doesn't compile.
	  int k = *(--it_int);
	  it_int++;
	  // New label?
	  if (Sa.transitions_labels[*it_int] != Sa.transitions_labels[k])
	    // The last transition is deterministic?
	    if (j == 1)
	      delta_det_out_A[i].push_back(k);
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
	  delta_det_out_A[i].push_back(*(--it_int));
	  ++it_int;
	}
      }
    }

    // Automaton B
    for (int i = 0; i < static_cast<int>(a.states().size()); i++)
    {
      if (Sb.delta_in[i].size() > 0)
      {
	it_int = Sb.delta_in[i].begin();
	// Number of transitions with the same label
	int j = 1;
	for (it_int++; it_int != Sb.delta_in[i].end(); it_int++)
	{
	  // It seems there is no iterator arithmetics in C++:
	  // *(it_int - 1) doesn't compile.
	  int k = *(--it_int);
	  it_int++;
	  // New label?
	  if (Sb.transitions_labels[*it_int] != Sb.transitions_labels[k])
	    // The last transition is deterministic?
	    if (j == 1)
	      delta_det_in_B[i].push_back(k);
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
	  delta_det_in_B[i].push_back(*(--it_int));
	  ++it_int;
	}
      }
      if (Sb.delta_out[i].size() > 0)
      {
	it_int = Sb.delta_out[i].begin();
	// Number of transitions with the same label
	int j = 1;
	for (it_int++; it_int != Sb.delta_out[i].end(); it_int++)
	{
	  // It seems there is no iterator arithmetics in C++:
	  // *(it_int - 1) doesn't compile.
	  int k = *(--it_int);
	  it_int++;
	  // New label?
	  if (Sb.transitions_labels[*it_int] != Sb.transitions_labels[k])
	    // The last transition is deterministic?
	    if (j == 1)
	      delta_det_out_B[i].push_back(k);
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
	  delta_det_out_B[i].push_back(*(--it_int));
	  it_int++;
	}
      }
    }


    // Vector indexed by states that points to the corresponding node
    // of the list of states of each class of states stored in the
    // Tries (for automata A & B).
    //
    // We have to build the vector using a valid iterator (i.e., not a
    // singular one).  We use a dummy int list to this end.
    std::list<int> dummy;
    std::vector<std::list<int>::iterator>
      T_L_A (a.states().size(), dummy.end()),
      T_L_B (b.states().size(), dummy.end());

    std::list<Trie*> C;

    // Constructs Tries of classes of states with the same sequence of
    // ingoing and outgoing transitions in lex. order (for automaton A)
    for (int i = 0; i < static_cast<int>(a.states().size()); i++)
    {
      // Vector all_transitions_lex contains the sequence of labels of
      // ingoing and outgoing transitions of state i in lex. order,
      // separated by a mark (-1)
      std::vector<int> all_transitions_lex(Sa.delta_in[i].size() +
					   Sa.delta_out[i].size() + 1);

      // First stores the sequence of ingoing transitions
      for (it_int = Sa.delta_in[i].begin();
	   it_int != Sa.delta_in[i].end(); ++it_int)
	all_transitions_lex.push_back(Sa.transitions_labels[*it_int]);

      all_transitions_lex.push_back(-1);
      // Next, outgoing transitions
      for (it_int = Sa.delta_out[i].begin();
	   it_int != Sa.delta_out[i].end(); ++it_int)
	all_transitions_lex.push_back(Sa.transitions_labels[*it_int]);

      // Gets the node of the correct Trie (Trie of initial, final or normal
      // states) for the sequence of transitions of state i
      Trie *T_aux;
      if (a.is_initial(Sa.states[i]))
	T_aux = T_I.insert(all_transitions_lex);
      else if (a.is_final(Sa.states[i]))
	T_aux = T_T.insert(all_transitions_lex);
      else
	T_aux = T_Q_IT.insert(all_transitions_lex);

      // New class?
      if (T_aux->A.size() == 0)
      {
	// Inserts in list C of classes (nodes of Tries)
	C.push_front(T_aux);

	// Each Trie node points to its node in list C
	T_aux->L = C.begin();
      }

      // Inserts the state in the list A of its corresponding class
      T_aux->A.push_front(i);
      // Defines class of state i
      class_state_A[i] = T_aux;
      // T_L_A[i] = node of the list of states of class of state i
      T_L_A[i] = T_aux->A.begin();
    }


    // Constructs Tries of classes of states with the same sequence of
    // ingoing and outgoing transitions in lex. order (for automaton B)
    for (int i = 0; i < static_cast<int>(b.states().size()) && iso; i++)
    {
      // Vector all_transitions_lex contains the sequence of labels of
      // ingoing and outgoing transitions of state i in lex. order,
      // separated by a mark (-1)
      std::vector<int> all_transitions_lex(Sb.delta_in[i].size() +
					   Sb.delta_out[i].size() + 1);
      // First stores the sequence of ingoing transitions
      for (it_int = Sb.delta_in[i].begin();
	   it_int != Sb.delta_in[i].end(); ++it_int)
	all_transitions_lex.push_back(Sb.transitions_labels[*it_int]);

      all_transitions_lex.push_back(-1);
      // Next, outgoing transitions
      for (it_int = Sb.delta_out[i].begin();
	   it_int != Sb.delta_out[i].end(); ++it_int)
	all_transitions_lex.push_back(Sb.transitions_labels[*it_int]);

      // Gets the node of the correct Trie (Trie of initial, final or
      // normal states) for the sequence of transitions of state i
      Trie *T_aux;
      if (b.is_initial(Sa.states[i]))
	T_aux = T_I.insert(all_transitions_lex);
      else if (b.is_final(Sa.states[i]))
	T_aux = T_T.insert(all_transitions_lex);
      else
	T_aux = T_Q_IT.insert(all_transitions_lex);

      // Does the class of state i have more states for automaton B
      // than those for automaton A ?
      if (T_aux->A.size() == T_aux->B.size())
	iso = false;
      else
      {
	// Inserts the state in the list B of its corresponding class
	T_aux->B.push_front(i);
	// Defines class of state i
	class_state_B[i] = T_aux;
	// T_L_B[i] = node of the list of states of class of state i
	T_L_B[i] = T_aux->B.begin();
      }
    }

    // Have we discovered that the automata are not isomorphic?
    if (!iso)
      return false;

    for (int i = 0; i < static_cast<int>(a.states().size()); i++)
      perm_A[i] = perm_B[i] = -1;


    // Searches for classes having only one state for each
    // automaton. These states must be identified. These classes are
    // then stored in list U.
    // Also tests if all classes have the same number of states in
    // lists A and B.

    std::list<Trie*>::iterator itr_C;

    itr_C = C.begin();

    while (itr_C != C.end() && iso)
    {
      // Do automata A and B have the same number of states in the
      // current class?
      if ((*itr_C)->A.size() != (*itr_C)->B.size())
      {
	iso = false;
	itr_C++;
      }
      else
	// Class *itr_C contains only one state of each automata?
	if ((*itr_C)->A.size() == 1)
	{
	  // States *((*itr_C).A.begin()) and
	  // *((*itr_C).B.begin()) have to be identified.
	  int k = *((*itr_C)->A.begin());
	  U.push_front(k);
	  int l = *((*itr_C)->B.begin());
	  perm_A[k] = l;
	  perm_B[l] = k;

	  // Just for coherence, lists A and B of class *itr_C are voided
	  ((*itr_C)->A).erase((*itr_C)->A.begin());
	  ((*itr_C)->B).erase((*itr_C)->B.begin());
	  // Deletes current node and points to the next.
	  itr_C = C.erase(itr_C);
	}
	else
	  itr_C++;
    }

    // Have we discovered that the automata are not isomorphic?
    if (!iso)
      return false;

    // Tries to discover more fixed states implied by states in U
    // During the loop, a state i of A is in its Trie iff perm_A[i] = -1
    // Time complexity: O(m)
    // (obs: if the automata are deterministic, the isomorphism test
    // ends here)
    while (!U.empty() && iso)
    {
      // Each state in U has already an image (perm_A and perm_B are
      // defined for this state)

      // i = current state in automaton A, j = its image in automaton B
      int i = U.front();
      int j = perm_A[i];
      U.pop_front();

      // Deterministic ingoing and outgoing transitions are analyzed

      // As states i and j are already associated, they belong to
      // the same class, then have the same sequence of
      // deterministic transitions.

      // First analyzes co-deterministic ingoing transitions
      it_int = delta_det_in_A[i].begin();
      it_int_aux = delta_det_in_B[j].begin();
      for (; it_int != delta_det_in_A[i].end() and iso; ++it_int, ++it_int_aux)
      {

	// The states being considered are the sources of current
	// co-deterministic transitions (k for automaton A, l for B)
	int k = Sa.src_transitions[*it_int];
	int l = Sb.src_transitions[*it_int_aux];

	// Has state k already been visited?
	if (perm_A[k] >= 0)
	{
	  // If it has already been visited, does the current image
	  // matches state l?
	  if (perm_A[k] != l)
	    iso = false;
	}
	else
	  // State k has not already been visited. The same must be
	  // true for state l.
	  if (perm_B[l] != -1)
	    iso = false;
	// Tries to associate states k and l
	  else
	    // Does k and l belongs to different classes?
	    if (class_state_A[k] != class_state_B[l])
	      iso = false;
	// The states k and l belong to the same class and can be
	// associated.
	    else
	    {
	      perm_A[perm_B[l] = k] = l;
	      // Removes k and l from theirs lists of states in theirs
	      // classes (O(1))
	      class_state_A[k]->A.erase(T_L_A[k]);
	      class_state_B[l]->B.erase(T_L_B[l]);
	      U.push_front(k);
	      if (class_state_A[k]->A.size() == 1)
	      {
		// If it remains only one state of each
		// automaton in the class of the current states,
		// they must be associated. Then they are
		// putted in list U, and the class are removed
		// from C.
		// From now on k and l represent these states.
		Trie* T_aux = class_state_A[k];
		k = T_aux->A.front();
		l = T_aux->B.front();
		perm_A[perm_B[l] = k] = l;

		U.push_front(k);

		// Removes class T_aux from C
		C.erase(T_aux->L);
	      }
	    }
      }


      // Next analyzes deterministic outgoing transitions
      it_int = delta_det_out_A[i].begin();
      it_int_aux = delta_det_out_B[j].begin();
      for (; it_int != delta_det_out_A[i].end() && iso; ++it_int, ++it_int_aux)
      {

	// The states being considered are the ends of current
	// deterministic transitions (k for automaton A, l for B)
	int k = Sa.dst_transitions[*it_int];
	int l = Sb.dst_transitions[*it_int_aux];

	// Has state k already been visited?
	if (perm_A[k] >= 0)
	{
	  // If it has already been visited, does the current image
	  // matches state l?
	  if (perm_A[k] != l)
	    iso = false;
	}
	else
	  // State k has not already been visited. The same must be
	  // true for state l.
	  if (perm_B[l] != -1)
	    iso = false;
	// Tries to associate states k and l
	  else
	    // Does k and l belongs to different classes?
	    if (class_state_A[k] != class_state_B[l])
	      iso = false;
	// The states belong to the same class and can be associated.
	    else
	    {
	      perm_A[perm_B[l] = k] = l;
	      // Removes k and l from theirs lists of states in theirs
	      // classes (O(1))
	      class_state_A[k]->A.erase(T_L_A[k]);
	      class_state_B[l]->B.erase(T_L_B[l]);
	      U.push_front(k);

	      if (class_state_A[k]->A.size() == 1)
	      {
		// If it remains only one state of each
		// automaton in the class of the current states,
		// they must be associated. Then they are
		// inserted in list U, and the class are removed
		// from C.
		// From now on k and l represent these states.
		Trie* T_aux = class_state_A[k];
		k = T_aux->A.front();
		l = T_aux->B.front();
		perm_A[perm_B[l] = k] = l;

		U.push_front(k);

		// Removes class T_aux from C
		C.erase(T_aux->L);
	      }
	    }
      }

    }

    // Have we discovered that the automata are not isomorphic?
    if (!iso)
      return false;


    // Next, Tries to associate remaining states (in remaining classes
    // in C). This is the backtracking phase.

    // Stores in l the number of non-fixed states
    int l = 0;
    for (itr_C = C.begin(); itr_C != C.end(); ++itr_C)
      l += (*itr_C)->A.size();

    // Vectors of classes of remaining states.	States in the same
    // class are stored contiguously, and in the case of vector for
    // automaton B, classes are separated by two enTries: one with -1,
    // denoting the end of the class, and the following with the
    // position where the class begins in this vector.
    std::vector<int> C_A(l);
    std::vector<int> C_B(l + 2 * C.size());
    // current[i] = position in C_B of image of state C_A[i] during
    // backtracking.
    std::vector<int> current(l);


    // Vector for test of correspondence of transitions of states already
    // attributed
    std::vector<int> correspondence_transitions(a.states().size());

    for (int i = 0; i < static_cast<int>(a.states().size()); ++i)
      correspondence_transitions[i] = 0;

    // Stores states in C_A and C_B. Partial results of the
    // backtracking are stored in vector current, that is initialized
    // with the first element of each class.
    int i = 0, j = 0;
    for (itr_C = C.begin(); itr_C != C.end(); itr_C++)
    {
      it_int = (*itr_C)->A.begin();
      it_int_B = (*itr_C)->B.begin();
      C_A[i] = *it_int;
      C_B[j] = *it_int_B;
      current[i++] = j++;
      for (it_int++, it_int_B++; it_int != (*itr_C)->A.end();
	   it_int++, it_int_B++)
      {
	C_A[i] = *it_int;
	C_B[j++] = *it_int_B;
	current[i] = current[i - 1];
	i++;
      }
      // End of class
      C_B[j++] = -1;
      // Position where the class begins
      C_B[j++] = current[i - 1];
    }

    // Tries to associate states of C_A and C_B

    i = 0;

    // Backtracking loop. Each iteration Tries to associate state
    // C_A[i]. If i = C_A.size(), the automata are isomorphic.
    while (iso && (i < static_cast<int>(C_A.size())))
    {
      // Searches for the first free state in the class of C_A[i]
      for (j = current[i]; (C_B[j] != -1) && (perm_B[C_B[j]] >= 0); j++)
	;

      // There is no possibility for state C_A[i]
      if (C_B[j] == -1)
      {
	// If there is no possibility for C_A[0], the automata are not
	// isomorphic
	if (i == 0)
	  iso = false;
	else
	{
	  // Prepares for backtracking in next iteration.
	  // Image of C_A[i] is set to first state of its class
	  current[i] = C_B[j + 1];
	  // Next iteration will try to associate state i - 1
	  // to next possible position
	  i--;
	  perm_B[perm_A[C_A[i]]] = -1;
	  perm_A[C_A[i]] = -1;
	  current[i]++;
	}
      }
      // Tries to associate state C_A[i] to state C_B[j]
      else
      {

	current[i] = j;
	perm_A[C_A[i]] = C_B[j];
	perm_B[C_B[j]] = C_A[i];

	// Tests correspondence of ingoing transitions, considering
	// states that are already in the permutation.

	std::list<int>::iterator int_itr_B;

	it_int = Sa.delta_in[C_A[i]].begin();
	it_int_B = Sb.delta_in[C_B[j]].begin();
	bool b = true;

	// Each iteration considers a sequence of ingoing labels
	// with the same label. The sequence begins at it_int
	while ((it_int != Sa.delta_in[C_A[i]].end()) && b)
	{
	  // Searches for sources of ingoing transitions for current
	  // label that have already been associated. For each state
	  // visited, its position in correspondence_transitions is
	  // incremented.
	  int k = 0;
	  for (it_int_aux = it_int;
	       (it_int_aux != Sa.delta_in[C_A[i]].end()) &&
		 (Sa.transitions_labels[*it_int_aux] ==
		  Sa.transitions_labels[*it_int]);
	       it_int_aux++, k++)
	    // Is the source of current transition associated?
	    if (perm_A[Sa.src_transitions[*it_int_aux]] >= 0)
	      correspondence_transitions[Sa.src_transitions[*it_int_aux]]++;

	  // Here, k = number of ingoing transitions for current label

	  // Idem for ingoing transitions of state C_B[j], but positions in
	  // correspondence_transitions are decremented.
	  for (; (k > 0) && b; it_int_B++, k--)
	    // Has the source of current transition already been visited?
	    if (perm_B[Sb.src_transitions[*it_int_B]] >= 0)
	      // Trying to decrement a position with 0 means that the
	      // corresponding state in A is not correct.
	      if (correspondence_transitions[perm_B[Sb.src_transitions[*it_int_B]]] == 0)
		// The association of C_A[i] and C_B[j] is impossible
		b = false;
	      else
		correspondence_transitions[perm_B[Sb.src_transitions[*it_int_B]]]--;

	  // Verifies correspondence_transitions. The correspondence for
	  // current label is correct iff correspondence_transitions[l] = 0
	  // for all src l of ingoing transitions of C_A[i] labelled by
	  // the current label.
	  // For this, int_itr visits all transitions until int_itr_aux.

	  for (; it_int != it_int_aux; it_int++)
	  {
	    if (perm_A[Sa.src_transitions[*it_int]] >= 0)
	      if (correspondence_transitions[Sa.src_transitions[*it_int]] != 0)
		b = false;
	    // All positions must be 0 for next iteration
	    correspondence_transitions[Sa.src_transitions[*it_int]] = 0;
	  }

	} // end while for ingoing transitions

	// Ok for ingoing transitions? Tests outgoing transitions.
	if (b)
	{
	  // Tests correspondence of outgoing transitions, considering
	  // states that are already in the permutation.

	  std::list<int>::iterator int_itr_B;

	  it_int = Sa.delta_out[C_A[i]].begin();
	  it_int_B = Sb.delta_out[C_B[j]].begin();

	  // Each iteration considers a sequence of outgoing labels
	  // with the same label. The sequence begins at it_int
	  while ((it_int != Sa.delta_out[C_A[i]].end()) && b)
	  {
	    // Searches for ends of outgoing transitions for current
	    // label that have already been associated. For each
	    // state visited, its position in correspondence_transitions
	    // is incremented.
	    int k = 0;
	    for (it_int_aux = it_int;
		 (it_int_aux != Sa.delta_out[C_A[i]].end()) &&
		   (Sa.transitions_labels[*it_int_aux] ==
		    Sa.transitions_labels[*it_int]);
		 it_int_aux++, k++)
	      // Is the end of current transition associated?
	      if (perm_A[Sa.dst_transitions[*it_int_aux]] >= 0)
		correspondence_transitions[Sa.dst_transitions[*it_int_aux]]++;

	    // Here, k = number of outgoing transitions for current label

	    // Idem for outgoing transitions of state C_B[j], but positions in
	    // correspondence_transitions are decremented.
	    for (; k > 0 && b; it_int_B++, k--)
	      // Has the end of current transition already been visited?
	      if (perm_B[Sb.dst_transitions[*it_int_B]] >= 0)
		// Trying to decrement a position with 0 means that
		// the corresponding state in A is not correct.
		if (correspondence_transitions[perm_B[Sb.dst_transitions[*it_int_B]]] == 0)
		  // The association of C_A[i] and C_B[j] is
		  // impossible
		  b = false;
		else
		  correspondence_transitions[perm_B[Sb.dst_transitions[*it_int_B]]]--;

	    // Verifies correspondence_transitions. The correspondence
	    // for current label is correct iff
	    // correspondence_transitions[l] = 0 for all end l of
	    // outgoing transitions of C_A[i] labelled by the current
	    // label.
	    // For this, int_itr visits all transitions until int_itr_aux.

	    for (; it_int != it_int_aux; it_int++)
	    {
	      if (perm_A[Sa.dst_transitions[*it_int]] >= 0)
		if (correspondence_transitions[Sa.dst_transitions[*it_int]] != 0)
		  b = false;
	      // All positions must be 0 for next iteration
	      correspondence_transitions[Sa.dst_transitions[*it_int]] = 0;
	    }

	  } // End while for outgoing transitions

	} // End of test of outgoing transitions

	// States C_A[i] and C_B[j] can be associated.
	if (b)
	  // Tries to associate state in C_A[i + 1] in next iteration
	  i++;
	// Impossible to associate C_A[i] to C_B[j]
	else
	{
	  // Tries C_A[i] to C_B[j + 1] in next iteration
	  perm_B[perm_A[C_A[i]]] = -1;
	  perm_A[C_A[i]] = -1;
	  current[i]++;
	}

      } // end of association of states C_A[i] and C_B[j]

    } // end of backtracking loop

    return iso;

  } // end of are_isomorphic

} // vcsn

#endif // ! VCSN_ALGORITHMS_ISOMORPH_HXX
