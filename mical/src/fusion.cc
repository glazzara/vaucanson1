
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <utility>

#include <algorithms/rig.hh>
#include <vaucanson/tools/usual.hh>
#include <vaucanson/algebra/concrete/free_monoid/predefs.hh>

#include <algorithms/make_mca.hh>
#include <algorithms/make_pta.hh>
#include <algorithms/is_not_compatible.hh>
#include <tools/load_sample.hh>
#include <algorithms/fusion.hh>

int main()
{
  using std::cout;
  using std::endl;  
  using std::pair;
  using std::map;

  using namespace vcsn::algebra::char_letter;
  using namespace gi;
  using namespace vcsn;
  using namespace algebra;
   
  // on recupere les echantillons positifs et negatifs
  pair<std::set<Word>, std::set<Word> > dsample;
  dsample = load_samples(SELECT(Word), "training/vtrain.toy");
 
  // creation de l'automate
  Alphabet a;

  a.insert('a');
  a.insert('b');
  
  Words free_monoid(a);
  NumericalSemiring ring;
  Series<NumericalSemiring, Words> s(ring, free_monoid);

  Element
    <
      Automata, 
      utility::ref< 
      AutomatonImpl<labels_are_series,
		    Series<NumericalSemiring, Words>,
		    polynom<Word::value_t, bool>,
		    ManyLinks<polynom<Word::value_t, bool>, NoTag, NoTag>,
		    NoTag,
		    map> >
    > A;

  A.create();
  
  A.series() = s;
  // fin de creation 

  //make_mca(A, dsample.first);

  hstate_t n_0 = A.add_state();
  hstate_t n_1 = A.add_state();
  hstate_t n_2 = A.add_state();
  hstate_t n_3 = A.add_state();
  hstate_t n_4 = A.add_state();
  hstate_t n_5 = A.add_state();

  A.set_initial(n_0);
  A.set_final(n_2);
  A.set_final(n_5);

  A.add_letter_edge(n_0, n_1, 'b');
  A.add_letter_edge(n_1, n_2, 'a');

  A.add_letter_edge(n_0, n_3, 'b');
  A.add_letter_edge(n_3, n_4, 'a');
  A.add_letter_edge(n_4, n_5, 'a');

  SAVE_AUTOMATON_DOT_SIMPLE("before_fusion", A);
  
  fusion(A, n_1, n_0);
  // fusion(A, n_3, n_0);
  // fusion(A, n_2, n_0);
  fusion(A, n_4, n_0);
  // fusion(A, n_5, n_0);
  // fusion(A, n_0, n_0);

  SAVE_AUTOMATON_DOT_SIMPLE("after_fusion", A);

  return 0;
}
