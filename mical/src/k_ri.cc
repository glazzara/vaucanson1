// k_ri.cc
//
// MICAL_HEADER


#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <utility>
#include <vector>

#include <algorithms/is_structurally_complete.hh>
#include <vaucanson/fundamental/predefs.hh>
#include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>
#include <vaucanson/algebra/concrete/series/polynoms.hh>
#include <vaucanson/automata/concept/automata.hh>
#include <vaucanson/tools/usual.hh>
#include <vaucanson/algorithms/determinize.hh>

#include <tools/load_sample.hh>
#include <algorithms/make_mca.hh>
#include <algorithms/make_pta.hh>
#include <algorithms/is_not_compatible.hh>


# include <vaucanson/algebra/concrete/predefs.hh>

#include <algorithms/k_ri.hh>

int main(int argc, char** argv)
{
  using std::cout;
  using std::endl;
  using std::pair;
  using std::map;
  using std::set;
  using std::vector;
  using namespace vcsn::algebra::char_letter;
  using namespace vcsn::algebra;
  using namespace vcsn;
  using namespace mical;


  pair<std::set<Word>, std::set<Word> > dsample;
  dsample = load_samples(SELECT(Word), "training/vtrain.toy");

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

  A.series().monoid().alphabet() = a;

  k_ri(A, 1, dsample.first);

  SAVE_AUTOMATON_DOT_SIMPLE("k_ri", A);

  return 0;
}
