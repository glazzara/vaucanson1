// isomorph.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//    * Michael Cadilhac <michael.cadilhac@lrde.epita.fr>
//
#ifndef VCSN_ALGORITHMS_ISOMORPH_HXX
# define VCSN_ALGORITHMS_ISOMORPH_HXX

# include <vaucanson/algorithms/isomorph.hh>
# include <vaucanson/algorithms/determinize.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/usual_macros.hh>

# include <vaucanson/algorithms/internal/skeleton.hh>

# include <queue>
# include <set>
# include <list>
# include <utility>

namespace vcsn {

  /*--------------------------------------.
  | Helper for are_isomorphic algorithm.  |
  `--------------------------------------*/

  class Trie
  {
    public:
      Trie* insert(std::vector<int>&);

    public:
      std::list<int> A, B;

      // Node in list C pointing to this node
      std::list<Trie*>::iterator L;

    private:
      Trie* insert_suffix(std::vector<int>&, unsigned int);
      std::map<int, Trie> children;
  };

  // Finds node associated to the insertion of a vector of integers
  Trie* Trie::insert(std::vector<int>& S)
  {
    return insert_suffix(S, 0);
  }

  Trie* Trie::insert_suffix(std::vector<int>& S, unsigned int p)
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
    typedef Element<A, T> automaton_t;

    AUTOMATON_TYPES(automaton_t);

    // We can start with good suppositions
    if ((a.states().size() != b.states().size())
	|| (a.edges().size() != b.edges().size())
	|| (a.initial().size() != b.initial().size())
	|| (a.final().size() != b.final().size()))
      return false;


    int i, j , k, l;
    bool iso;
    std::list<int>::iterator it_int, it_int_B, it_int_aux;

    // Vector indexed by states that points to the corresponding
    // node of the list of states of each class of states stored in
    // the Tries (for automaton A).
    std::vector<std::list<int>::iterator> T_L_A(a.states().size());

    // Idem for automaton B.
    std::vector<std::list<int>::iterator> T_L_B(b.states().size());


    // Tries of classes of normal, initial and final states.
    Trie *T_Q_IT, *T_I, *T_T, *T_aux;

    T_Q_IT = new Trie();
    T_I = new Trie();
    T_T = new Trie();

    std::list<Trie*> C;
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
    iso = true;

    // Constructs lists of deterministic ingoing and outgoing edges
    // for each state (delta_det_in[i] = list of deterministic ingoing
    // edges for state i, idem for delta_det_out[i])

    std::vector< std::list<int> > delta_det_in_A(a.states().size());
    std::vector< std::list<int> > delta_det_out_A(a.states().size());
    std::vector< std::list<int> > delta_det_in_B(b.states().size());
    std::vector< std::list<int> > delta_det_out_B(b.states().size());

    // Automaton A
    for (i = 0; i < static_cast<int>(a.states().size()); i++)
    {
      if ((Sa.delta_in[i]).size() > 0)
      {
	it_int = Sa.delta_in[i].begin();
        // Number of edges with the same label
	j = 1;
	for (it_int++; it_int != Sa.delta_in[i].end(); it_int++)
	{
	  // It seems there is no iterator arithmetics in C++:
	  // *(it_int - 1) doesn't compile.
	  k = *(--it_int);
	  it_int++;
	  // New label?
	  if (Sa.edges_labels[*it_int] != Sa.edges_labels[k])
	    // The last edge is deterministic?
	    if (j == 1)
	      delta_det_in_A[i].push_back(k);
            // Several edges with the same label?
	    else
	      // Does nothing. A series of edges with a new label begins.
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
      if ((Sa.delta_out[i]).size() > 0)
      {
	it_int = Sa.delta_out[i].begin();
	// Number of edges with the same label
	j = 1;
	for (it_int++; it_int != Sa.delta_out[i].end(); it_int++)
	{
	  // It seems there is no iterator arithmetics in C++:
	  // *(it_int - 1) doesn't compile.
	  k = *(--it_int);
	  it_int++;
	  // New label?
	  if (Sa.edges_labels[*it_int] != Sa.edges_labels[k])
	    // The last edge is deterministic?
	    if (j == 1)
	      delta_det_out_A[i].push_back(k);
 	    // Several edges with the same label?
	    else
	      // Does nothing. A series of edges with a new label begins.
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
    for (i = 0; i < static_cast<int>(a.states().size()); i++)
    {
      if ((Sb.delta_in[i]).size() > 0)
      {
	it_int = Sb.delta_in[i].begin();
	// Number of edges with the same label
	j = 1;
	for (it_int++; it_int != Sb.delta_in[i].end(); it_int++)
	{
	  // It seems there is no iterator arithmetics in C++:
	  // *(it_int - 1) doesn't compile.
	  k = *(--it_int);
	  it_int++;
	  // New label?
	  if (Sb.edges_labels[*it_int] != Sb.edges_labels[k])
	    // The last edge is deterministic?
	    if (j == 1)
	      delta_det_in_B[i].push_back(k);
	    // Several edges with the same label?
	    else
	      // Does nothing. A series of edges with a new label begins.
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
      if ((Sb.delta_out[i]).size() > 0)
      {
	it_int = Sb.delta_out[i].begin();
	// Number of edges with the same label
	j = 1;
	for (it_int++; it_int != Sb.delta_out[i].end(); it_int++)
	{
	  // It seems there is no iterator arithmetics in C++:
	  // *(it_int - 1) doesn't compile.
	  k = *(--it_int);
	  it_int++;
	  // New label?
	  if (Sb.edges_labels[*it_int] != Sb.edges_labels[k])
	    // The last edge is deterministic?
	    if (j == 1)
	      delta_det_out_B[i].push_back(k);
	    // Several edges with the same label?
	    else
	      // Does nothing. A series of edges with a new label begins.
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

    // Constructs Tries of classes of states with the same sequence of
    // ingoing and outgoing edges in lex. order (for automaton A)
    for (i = 0; i < static_cast<int>(a.states().size()); i++)
    {
      // Vector all_edges_lex contains the sequence of labels of
      // ingoing and outgoing edges of state i in lex. order,
      // separated by a mark (-1)
      std::vector<int> all_edges_lex((Sa.delta_in[i]).size() +
				     (Sa.delta_out[i]).size() + 1);

      // First stores the sequence of ingoing edges
      for (it_int = Sa.delta_in[i].begin();
	   it_int != Sa.delta_in[i].end(); ++it_int)
	all_edges_lex.push_back(Sa.edges_labels[*it_int]);

      all_edges_lex.push_back(-1);
      // Next, outgoing edges
      for (it_int = Sa.delta_out[i].begin();
	   it_int != Sa.delta_out[i].end(); ++it_int)
	all_edges_lex.push_back(Sa.edges_labels[*it_int]);

      // Gets the node of the correct Trie (Trie of initial, final or normal
      // states) for the sequence of transitions of state i
      if (a.is_initial(Sa.states[i]))
	T_aux = T_I->insert(all_edges_lex);
      else
	if (a.is_final(Sa.states[i]))
	  T_aux = T_T->insert(all_edges_lex);
	else
	  T_aux = T_Q_IT->insert(all_edges_lex);

      // New class?
      if ((T_aux->A).size() == 0)
      {
	// Inserts in list C of classes (nodes of Tries)
	C.push_front(T_aux);

	// Each Trie node points to its node in list C
	T_aux->L = C.begin();
      }

      // Inserts the state in the list A of its corresponding class
      (T_aux->A).push_front(i);
      // Defines class of state i
      class_state_A[i] = T_aux;
      // T_L_A[i] = node of the list of states of class of state i
      T_L_A[i] = (T_aux->A).begin();
    }


    // Constructs Tries of classes of states with the same sequence of
    // ingoing and outgoing edges in lex. order (for automaton B)
    for (i = 0; (i < static_cast<int>(b.states().size())) && iso; i++)
    {
      // Vector all_edges_lex contains the sequence of labels of
      // ingoing and outgoing edges of state i in lex. order,
      // separated by a mark (-1)
      std::vector<int> all_edges_lex((Sb.delta_in[i]).size() +
				     (Sb.delta_out[i]).size() + 1);
      // First stores the sequence of ingoing edges
      for (it_int = Sb.delta_in[i].begin();
	   it_int != Sb.delta_in[i].end(); ++it_int)
	all_edges_lex.push_back(Sb.edges_labels[*it_int]);

      all_edges_lex.push_back(-1);
      // Next, outgoing edges
      for (it_int = Sb.delta_out[i].begin();
	   it_int != Sb.delta_out[i].end(); ++it_int)
	all_edges_lex.push_back(Sb.edges_labels[*it_int]);

      // Gets the node of the correct Trie (Trie of initial, final or
      // normal states) for the sequence of transitions of state i
      if (b.is_initial(Sa.states[i]))
	T_aux = T_I->insert(all_edges_lex);
      else
	if (b.is_final(Sa.states[i]))
	  T_aux = T_T->insert(all_edges_lex);
	else
	  T_aux = T_Q_IT->insert(all_edges_lex);

      // Does the class of state i have more states for automaton B
      // than those for automaton A ?
      if ((T_aux->A).size() == (T_aux->B).size())
	iso = false;
      else
      {
	// Inserts the state in the list B of its corresponding class
	(T_aux->B).push_front(i);
	// Defines class of state i
	class_state_B[i] = T_aux;
	// T_L_B[i] = node of the list of states of class of state i
	T_L_B[i] = (T_aux->B).begin();
      }
    }

    // Have we discovered that the automata are not isomorphic?
    if (!iso)
      return false;

    for (i = 0; i < static_cast<int>(a.states().size()); i++)
      perm_A[i] = perm_B[i] = -1;


    // Searches for classes having only one state for each
    // automaton. These states must be identified. These classes are
    // then stored in list U.
    // Also tests if all classes have the same number of states in
    // lists A and B.

    std::list<Trie*>::iterator itr_C;

    itr_C = C.begin();

    while ((itr_C != C.end()) && iso)
    {
      // Do automata A and B have the same number of states in the
      // current class?
      if (((*itr_C)->A).size() != ((*itr_C)->B).size())
      {
	iso = false;
	itr_C++;
      }
      else
	// Class *itr_C contains only one state of each automata?
	if (((*itr_C)->A).size() == 1)
	{
	  // States *((*itr_C).A.begin()) and
	  // *((*itr_C).B.begin()) have to be identified.
	  U.push_front(k = (*(((*itr_C)->A).begin())));
	  perm_A[k] = l = *(((*itr_C)->B).begin());
	  perm_B[l] = k;

	  // Just for coherence, lists A and B of class *itr_C are voided
	  ((*itr_C)->A).erase(((*itr_C)->A).begin());
	  ((*itr_C)->B).erase(((*itr_C)->B).begin());
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
      j = perm_A[i = U.front()];
      U.pop_front();

      // Deterministic ingoing and outgoing edges are analyzed

      // As states i and j are already associated, they belong to
      // the same class, then have the same sequence of
      // deterministic edges.

      // First analyzes co-deterministic ingoing edges
      it_int = delta_det_in_A[i].begin();
      it_int_aux = delta_det_in_B[j].begin();
      for (; it_int != delta_det_in_A[i].end() and iso; ++it_int, ++it_int_aux)
      {

	// The states being considered are the origins of current
	// co-deterministic edges (k for automaton A, l for B)
	k = Sa.origins_edges[*it_int];
	l = Sb.origins_edges[*it_int_aux];

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
	      (class_state_A[k]->A).erase(T_L_A[k]);
	      (class_state_B[l]->B).erase(T_L_B[l]);
	      U.push_front(k);
	      if ((class_state_A[k]->A).size() == 1)
	      {
		// If it remains only one state of each
		// automaton in the class of the current states,
		// they must be associated. Then they are
		// putted in list U, and the class are removed
		// from C.
		// From now on k and l represent these states.

		T_aux = class_state_A[k];
		k = (T_aux->A).front();
		l = (T_aux->B).front();
		perm_A[perm_B[l] = k] = l;

		U.push_front(k);

		// Removes class T_aux from C
		C.erase(T_aux->L);

	      }
	    }
      }


      // Next analyzes deterministic outgoing edges
      it_int = delta_det_out_A[i].begin();
      it_int_aux = delta_det_out_B[j].begin();
      for (; it_int != delta_det_out_A[i].end() && iso; ++it_int, ++it_int_aux)
      {

	// The states being considered are the ends of current
	// deterministic edges (k for automaton A, l for B)
	k = Sa.aims_edges[*it_int];
	l = Sb.aims_edges[*it_int_aux];

	// Has state k already been visited?
	if (perm_A[k] >= 0)
	{
	  // If it has already been visited, does the current image
	  // matches state l?
	  if (perm_A[k] != l)
	    iso = false;
	}
	else
	  // State k has not already been visited. The same must be true for state l.
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
	      (class_state_A[k]->A).erase(T_L_A[k]);
	      (class_state_B[l]->B).erase(T_L_B[l]);
	      U.push_front(k);

	      if ((class_state_A[k]->A).size() == 1)
	      {
		// If it remains only one state of each
		// automaton in the class of the current states,
		// they must be associated. Then they are
		// inserted in list U, and the class are removed
		// from C.
		// From now on k and l represent these states.

		T_aux = class_state_A[k];
		k = (T_aux->A).front();
		l = (T_aux->B).front();
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
    l = 0;
    for (itr_C = C.begin(); itr_C != C.end(); ++itr_C)
      l += (*itr_C)->A.size();

    // Vectors of classes of remaining states.  States in the same
    // class are stored contiguously, and in the case of vector for
    // automaton B, classes are separated by two enTries: one with -1,
    // denoting the end of the class, and the following with the
    // position where the class begins in this vector.
    std::vector<int> C_A(l);
    std::vector<int> C_B(l + 2 * C.size());
    // current[i] = position in C_B of image of state C_A[i] during
    // backtracking.
    std::vector<int> current(l);


    // Vector for test of correspondence of edges of states already
    // attributed
    std::vector<int> correspondence_edges(a.states().size());

    for (i = 0; i < static_cast<int>(a.states().size()); ++i)
      correspondence_edges[i] = 0;

    // Stores states in C_A and C_B. Partial results of the
    // backtracking are stored in vector current, that is initialized
    // with the first element of each class.
    i = j = 0;
    for (itr_C = C.begin(); itr_C != C.end(); itr_C++)
    {
      it_int = ((*itr_C)->A).begin();
      it_int_B = ((*itr_C)->B).begin();
      C_A[i] = *it_int;
      C_B[j] = *it_int_B;
      current[i++] = j++;
      for (it_int++, it_int_B++; it_int != ((*itr_C)->A).end();
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

	// Tests correspondence of ingoing edges, considering
	// states that are already in the permutation.

	std::list<int>::iterator int_itr_B;

	it_int = Sa.delta_in[C_A[i]].begin();
	it_int_B = Sb.delta_in[C_B[j]].begin();
	bool b = true;

	// Each iteration considers a sequence of ingoing labels
	// with the same label. The sequence begins at it_int
	while ((it_int != Sa.delta_in[C_A[i]].end()) && b)
	{
	  // Searches for origins of ingoing edges for current
	  // label that have already been associated. For each
	  // state visited, its position in correspondence_edges
	  // is incremented.
	  k = 0;
	  for (it_int_aux = it_int;
	       (it_int_aux != Sa.delta_in[C_A[i]].end()) &&
		 (Sa.edges_labels[*it_int_aux] == Sa.edges_labels[*it_int]);
	       it_int_aux++, k++)
	    // Is the origin of current edge associated?
	    if (perm_A[Sa.origins_edges[*it_int_aux]] >= 0)
	      correspondence_edges[Sa.origins_edges[*it_int_aux]]++;

	  // Here, k = number of ingoing edges for current label

	  // Idem for ingoing edges of state C_B[j], but positions in
	  // correspondence_edges are decremented.
	  for (; (k > 0) && b; it_int_B++, k--)
	    // Has the origin of current edge already been visited?
	    if (perm_B[Sb.origins_edges[*it_int_B]] >= 0)
	      // Trying to decrement a position with 0 means that the
	      // corresponding state in A is not correct.
	      if (correspondence_edges[perm_B[Sb.origins_edges[*it_int_B]]] == 0)
		// The association of C_A[i] and C_B[j] is impossible
		b = false;
	      else
		correspondence_edges[perm_B[Sb.origins_edges[*it_int_B]]]--;

	  // Verifies correspondence_edges. The correspondence for
	  // current label is correct iff correspondence_edges[l] = 0
	  // for all origin l of ingoing edges of C_A[i] labelled by
	  // the current label.
	  // For this, int_itr visits all edges until int_itr_aux.

	  for (; it_int != it_int_aux; it_int++)
	  {
	    if (perm_A[Sa.origins_edges[*it_int]] >= 0)
	      if (correspondence_edges[Sa.origins_edges[*it_int]] != 0)
		b = false;
	    // All positions must be 0 for next iteration
	    correspondence_edges[Sa.origins_edges[*it_int]] = 0;
	  }

	} // end while for ingoing edges

	// Ok for ingoing edges? Tests outgoing edges.
	if (b)
	{
	  // Tests correspondence of outgoing edges, considering
	  // states that are already in the permutation.

	  std::list<int>::iterator int_itr_B;

	  it_int = Sa.delta_out[C_A[i]].begin();
	  it_int_B = Sb.delta_out[C_B[j]].begin();

	  // Each iteration considers a sequence of outgoing labels
	  // with the same label. The sequence begins at it_int
	  while ((it_int != Sa.delta_out[C_A[i]].end()) && b)
	  {
	    // Searches for ends of outgoing edges for current
	    // label that have already been associated. For each
	    // state visited, its position in correspondence_edges
	    // is incremented.
	    k = 0;
	    for (it_int_aux = it_int;
		 (it_int_aux != Sa.delta_out[C_A[i]].end()) &&
		   (Sa.edges_labels[*it_int_aux] == Sa.edges_labels[*it_int]);
		 it_int_aux++, k++)
	      // Is the end of current edge associated?
	      if (perm_A[Sa.aims_edges[*it_int_aux]] >= 0)
		correspondence_edges[Sa.aims_edges[*it_int_aux]]++;

	    // Here, k = number of outgoing edges for current label

	    // Idem for outgoing edges of state C_B[j], but positions in
	    // correspondence_edges are decremented.
	    for (; (k > 0) && b; it_int_B++, k--)
	      // Has the end of current edge already been visited?
	      if (perm_B[Sb.aims_edges[*it_int_B]] >= 0)
		// Trying to decrement a position with 0 means that
		// the corresponding state in A is not correct.
		if (correspondence_edges[perm_B[Sb.aims_edges[*it_int_B]]] == 0)
		  // The association of C_A[i] and C_B[j] is
		  // impossible
		  b = false;
		else
		  correspondence_edges[perm_B[Sb.aims_edges[*it_int_B]]]--;

	    // Verifies correspondence_edges. The correspondence
	    // for current label is correct iff
	    // correspondence_edges[l] = 0 for all end l of
	    // outgoing edges of C_A[i] labelled by the current
	    // label.
	    // For this, int_itr visits all edges until int_itr_aux.

	    for (; it_int != it_int_aux; it_int++)
	    {
	      if (perm_A[Sa.aims_edges[*it_int]] >= 0)
		if (correspondence_edges[Sa.aims_edges[*it_int]] != 0)
		  b = false;
	      // All positions must be 0 for next iteration
	      correspondence_edges[Sa.aims_edges[*it_int]] = 0;
	    }

	  } // End while for outgoing edges

	} // End of test of outgoing edges

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

    return (iso);

  } // end of are_isomorphic

} // vcsn

#endif // ! VCSN_ALGORITHMS_ISOMORPH_HXX
