
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
    > A, B;

  A.create();
  B.create();
  
  A.series() = s;
  B.series() = s;
  // fin de creation 

  make_mca(A, dsample.first);

  cout << A.states().size() << endl;

  FactoryBorderSet
    < 
    Automata, 
    utility::ref< 
    AutomatonImpl<labels_are_series,
    Series<NumericalSemiring, Words>,
    polynom<Word::value_t, bool>,
    ManyLinks<polynom<Word::value_t, bool>, NoTag, NoTag>,
    NoTag, map> >,
    Word
    > 
    factory(A, dsample.second);

  hstate_t n = 0;
  hstate_t p = 1;

  std::pair<hstate_t, hstate_t> fstates(n,p);
  bool last;

  cout << dsample.first.size() << " "
       << dsample.second.size() << endl;
  
  while (factory.depth())
    {
      cout << "[ NEW : " << factory.depth() << "]" << endl;
      //      factory.next();      // <--- it is at you to code it
      factory.course_depth();
    }
  
  //  SAVE_AUTOMATON_DOT_SIMPLE("vtrain_rig", B = factory.course_depth());

  return 0;
}
