// load_sample.cc

#include <iostream>
#include <set>
#include <string>
#include <utility>

#include <vaucanson/algebra/concrete/free_monoid/predefs.hh>
#include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>
#include <vaucanson/algebra/concrete/series/series.hh>
#include <vaucanson/algebra/concrete/series/polynoms.hh>
#include <vaucanson/automata/concept/automata.hh>
#include <vaucanson/tools/usual.hh>
#include <tools/load_sample.hh>
#include <vaucanson/algorithms/hopcroft.hh>

#include <algorithms/make_mca.hh>
#include <algorithms/make_pta.hh>
#include <algorithms/is_not_compatible.hh>

int main()
{
  using std::cout;
  using std::endl;
  using std::pair;
  using std::map;
  using namespace vcsn::algebra::char_letter;
  using namespace gi;
  using namespace vcsn;
  using namespace mical;

  // on recupere les echantillons positifs et negatifs
  pair<std::set<Word>, std::set<Word> > dsample;
  dsample = load_samples(SELECT(Word), "training/vtrain.toy");

  cout << "Number of positif sample : " << dsample.first.size() << endl;
  cout << "Number of negative sample : " << dsample.second.size() << endl;

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
    > A, B, C; 

  A.create();
  B.create();
  C.create();

  A.series() = s;
  B.series() = s;
  C.series() = s;
  // fin de creation 


  // revenons à nos moutons
  make_mca(A, dsample.first);
  make_pta(C, dsample.first);

  B = hopcroft_minimization_det(A);

  SAVE_AUTOMATON_DOT_SIMPLE("mca", A);
  SAVE_AUTOMATON_DOT_SIMPLE("pta", C);
  SAVE_AUTOMATON_DOT_SIMPLE("mca_mini", B);
  
  return 0;
}
