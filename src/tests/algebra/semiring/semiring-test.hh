// semiring-test.hh
//
//
// $Id$
// VCSN_HEADER

#ifndef SEMIRING_TEST_HH
# define SEMIRING_TEST_HH

# include <check/tests_stuff.hh>

template <class S, class T>
bool test_semiring(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef Element<S, T> element_t;
  element_t e1;
  element_t z = e1.set().zero(SELECT(T));
  element_t o = e1.set().identity(SELECT(T));
  element_t e2;
  element_t e3(o);

  TEST(t, "commutativity of plus.", (e1 + e2) == (e2 + e1));
  TEST(t, "distributivity of mult with plus.", 
       (e1 + e2) * e3 == e2 * e3 + e1 * e3);
  TEST(t, "0 is a zero for mult.", 
       (e1 * z == z));

  TEST(t, "stareable works. (1)", z.stareable() ? true  : false);
  // FIXME: add some other tests.
  return t.all_passed();
}



#endif // SEMIRING_TEST_HH
