#ifndef VCSN_XML_CALLBACK_HXX
# define VCSN_XML_CALLBACK_HXX

# include <vaucanson/xml/callback.hh>

# define CHOOSE_SEMIRING_SET	                             \
  if ((x.set().semiring_set() == XmlSet::UNSET)              \
      || (x.set().semiring_set() == XmlSet::B)) {            \
    typedef bool semiring_set;                               \
    CHOOSE_SEMIRING_TYPE;                                    \
  }                                                          \
  else if (x.set().semiring_set() == XmlSet::Z) {            \
    typedef int semiring_set;                                \
    CHOOSE_SEMIRING_TYPE;                                    \
  }                                                          \
  else if (x.set().semiring_set() == XmlSet::R) {            \
    typedef float semiring_set;                              \
    CHOOSE_SEMIRING_TYPE;                                    \
  }                                                          \
  else                                                       \
    FAIL("Unknown semiring set.");

/*FIXME: handle tansducers.
  else if (x.set().semiring_set() == XmlSet::LETTERS) {      \
    typedef vcsn::algebra::char_letter::                     \
            WordValue semiring_set;                          \
    CHOOSE_SEMIRING_TYPE;                                    \
  }                                                          \
  else                                                       \
    FAIL("Unknown semiring set.");
 */

# define CHOOSE_SEMIRING_TYPE	                             \
  if ((x.set().semiring_type() == XmlSet::UNSET)             \
      || (x.set().semiring_type() == XmlSet::NUMERICAL)) {   \
    typedef NumericalSemiring semiring_type;                 \
    CHOOSE_MONOID_TYPE;                                      \
  }                                                          \
  else if (x.set().semiring_type() == XmlSet::TROPICAL_MAX) {\
    typedef TropicalSemiring<TropicalMax> semiring_type;     \
    CHOOSE_MONOID_TYPE;                                      \
  }                                                          \
  else if (x.set().semiring_type() == XmlSet::TROPICAL_MIN) {\
    typedef TropicalSemiring<TropicalMin> semiring_type;     \
    CHOOSE_MONOID_TYPE;                                      \
  }                                                          \
  else                                                       \
    FAIL("Unknown semiring type.");

# define CHOOSE_MONOID_TYPE	                             \
  if ((x.set().monoid_type() == XmlSet::UNSET)               \
      || (x.set().monoid_type() == XmlSet::LETTERS)) {       \
    using namespace vcsn::algebra::char_letter;              \
    typedef Words monoid_type;                               \
    CHOOSE_MONOID_SET;                                       \
  }                                                          \
  else                                                       \
    FAIL("Unknown monoid type.");

# define CHOOSE_MONOID_SET	                             \
  if ((x.set().monoid_set() == XmlSet::UNSET)                \
      || (x.set().monoid_set() == XmlSet::WORDS)) {          \
    typedef WordValue monoid_set;                            \
    CALL_BACK;                                               \
  }                                                          \
  else                                                       \
    FAIL("Unknown monoid type.");

# define CALL_BACK                                           \
  typedef                                                    \
  Element<Automata<Series<semiring_type, monoid_type> >,     \
    Graph<labels_are_series, monoid_set, semiring_set,       \
      rat::exp<monoid_set, semiring_set>, Letter,            \
      XmlInfosTag> > auto_t;	       			     \
  typedef XmlOf<auto_t>::ret xml_auto_t;                     \
  xml_auto_t x2;                                             \
  auto_t a;                                                  \
  x2 = x;                                                    \
  a = x2;						     \
  Callback<auto_t> cb;                                       \
  return cb(a, user);


# define CHOOSE_IMPL CHOOSE_SEMIRING_SET

namespace vcsn
{
  namespace xml
  {
    template <template <typename I> class Callback,
	      typename User>
    inline
    int
    apply(std::istream& in, User& user)
    {
      using namespace vcsn::algebra;

      Element<XmlSet, XmlAutomaton> x;

      in >> x;

      CHOOSE_SEMIRING_SET;
    }
  }
}

#endif // VCSN_XML_CALLBACK_HXX
