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

  // boucle
  A.add_letter_edge(n_3, n_3, 'a');
  A.set_final(n_3);
  
  used_t delta_edge;
  acceptation_t acceptation;

  Word str(free_monoid, argv[1]);

//   depth_compute(A, str.begin(), n_0, acceptation, delta_edge);
  
//   for (acceptation_t::iterator i = acceptation.begin(); i != acceptation.end(); i++)
//     {
//       cout << "Other acceptation" << endl;
//       for (delta_edge_t::iterator j = i->first.begin(); j != i->first.end(); j++)
// 	cout << A.origin_of(*j) << " " << A.aim_of(*j)  << endl;
//     }
  
  cout << is_structurally_complete(A, dsample.first) << endl;

//   typedef set<hedge_t> delta_edge_t;
//   typedef set<delta_edge_t> acceptation_t;
//   typedef set<acceptation_t> set_acceptation_t;
//   typedef vector<acceptation_t> i_familly_t;

  // i_familly_t i_familly = get_indexed_familly(A, dsample.first);
  
//   for (i_familly_t::iterator i = i_familly.begin(); i != i_familly.end(); i++)
//     {
//       cout << "FAMILLY" << endl;
//       for (acceptation_t::iterator j = i->begin(); j != i->end(); j++)
// 	{
// 	  cout << "ACCEPTATION : " << j->second << endl;
// 	  for (delta_edge_t::iterator k = j->first.begin(); 
// 	       k != j->first.end(); k++)
// 	    cout << A.origin_of(*k) << " " << A.aim_of(*k)  << endl;
// 	}
//     }

//  cout << it_exists_acceptation(A, i_familly) << endl;


  return 0;
}
