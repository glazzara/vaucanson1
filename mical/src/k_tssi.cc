// k_tssi_.cc
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

#include <algebra/concrete/k_words.hh>
# include <vaucanson/algebra/concrete/alphabets/predefs.hh>

#include <internal/k_window.hh>
#include <algorithms/k_tssi.hh>

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

  typedef std::set<hstate_t> delta_state_t;
  typedef std::set<hedge_t> delta_edge_t;
  typedef pair<delta_edge_t, hstate_t> used_t;
  typedef set<used_t> acceptation_t;
  typedef set<acceptation_t> set_acceptation_t;
  typedef vector<acceptation_t> i_familly_t;


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

  //  hstate_t n_0 = A.add_state();
//   hstate_t n_1 = A.add_state();
//   hstate_t n_2 = A.add_state();
//   hstate_t n_3 = A.add_state();
//   hstate_t n_4 = A.add_state();
//   hstate_t n_5 = A.add_state();

//  A.set_initial(n_0);
//   A.set_final(n_2);
//   A.set_final(n_5);

//   A.add_letter_edge(n_0, n_1, 'b');
//   A.add_letter_edge(n_1, n_2, 'a');

//   A.add_letter_edge(n_0, n_3, 'b');
//   A.add_letter_edge(n_3, n_4, 'a');
//   A.add_letter_edge(n_4, n_5, 'a');

//   // boucle
//   A.add_letter_edge(n_3, n_3, 'a');
//   A.set_final(n_3);
  

//  KWindow<Word::set_t::letter_t> win(2);
  
  //  win.insert(str);
//   cout << win.size() << endl;
//   cout << win.get_window(Word()) << endl;

//   map<Word, hstate_t> mappy;

//   mappy[Word()] = n_0;

//   add_word(A, str.begin(), n_0, win, mappy);

  k_tssi(A, 2, dsample.first);

  SAVE_AUTOMATON_DOT_SIMPLE("k_tssi", A);

  return 0;
}
