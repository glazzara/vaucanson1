// k_deterministic.cc
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

#include <algorithms/is_kdeterministic.hh>
#include <algorithms/is_kreversible.hh>

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
  a.insert('c');
  
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


  hstate_t n_0 = A.add_state();
  hstate_t n_1 = A.add_state();
  hstate_t n_2 = A.add_state();
  hstate_t n_3 = A.add_state();
  hstate_t n_4 = A.add_state();
  hstate_t n_5 = A.add_state();

  A.set_initial(n_5);

  A.add_letter_edge(n_5, n_4, 'c');
  A.add_letter_edge(n_5, n_3, 'a');

  A.add_letter_edge(n_2, n_2, 'b');
  A.add_letter_edge(n_1, n_1, 'b');
  
  A.add_letter_edge(n_4, n_2, 'b');
  A.add_letter_edge(n_3, n_1, 'b');

  A.add_letter_edge(n_2, n_0, 'a');
  A.add_letter_edge(n_1, n_0, 'c');

  A.set_final(n_0);

  //  cout << is_kdeterministic(A, 2) << endl;;

  cout << is_kreversible(A, 1) << endl;

  return 0;
}
