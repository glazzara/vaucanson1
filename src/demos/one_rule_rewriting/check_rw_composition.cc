#include "one_rule_rewriting.hh"

#include <string>

#include <vaucanson/boolean_transducer.hh>
#include <vaucanson/algorithms/rw_composition.hh>

using namespace vcsn;
using namespace vcsn::boolean_transducer;

bool
check_an_expression(const vcsn::boolean_transducer::automaton_t& t,
		    const std::string& str,
		    const std::string& ref)
{
  std::stringstream s_res;
  const alphabet_t& alphabet = t.structure().series().monoid().alphabet();

  using namespace vcsn::boolean_automaton;
  using namespace vcsn::rat; // For setpm and MODE_STAR.

  rat_exp_t exp = make_rat_exp(alphabet, str);

  s_res << setpm(MODE_STAR) << expand(evaluation(t, exp));
  std::string res;
  s_res >> res;

  if (res != ref)
  {
    std::cout << "wrong return value: got " << res << " should be " << ref << std::endl;
    return false;
  }

  return true;
}

int main()
{
  using namespace ORR;

  alphabet_t A;

  A.insert('a');
  A.insert('b');

  std::string from = "abb";
  std::string to = "baa";

  automaton_t left_auto = replace_left(from, to, A, A);

  realtime_here(left_auto);

  automaton_t right_auto = replace_right(from, to, A, A);

  automaton_t res_auto = make_automaton(A, A);
  rw_composition(left_auto, right_auto, res_auto);

  bool tmp;
  bool ret = true;

  std::cout << "abb -> baa" << std::endl;
  tmp = check_an_expression(res_auto, "abb", "baa");
  ret = ret && tmp;
  std::cout << "babb -> bbaa" << std::endl;
  tmp = check_an_expression(res_auto, "babb", "bbaa");
  ret = ret && tmp;
  std::cout << "ababb -> baaaa" << std::endl;
  tmp = check_an_expression(res_auto, "ababb", "baaaa");
  ret = ret && tmp;

  if (ret)
    std::cout << "All tests went OK" << std::endl;

  return !ret;
}
