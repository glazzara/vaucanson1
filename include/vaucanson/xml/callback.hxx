#ifndef VCSN_XML_CALLBACK_HXX
# define VCSN_XML_CALLBACK_HXX

# include <vaucanson/xml/callback.hh>
# include <vaucanson/algebra/concrete/free_monoid/tools.hh>
# include <vaucanson/algebra/concrete/letter/couple_letter.hh>
# include <vaucanson/algebra/concrete/letter/int_letter.hh>

# ifdef VCSN_XML_GENRERIC_WEIGHTED
#  define CHOOSE_SEMIRING_SET_WEIGHTED(X, Do...)             \
  else if ( X .semiring_set() == XmlSet::Z) {                \
    typedef int semiring_set;                                \
    Do;                                                      \
  }                                                          \
  else if ( X .semiring_set() == XmlSet::R) {                \
    typedef float semiring_set;                              \
    Do;                                                      \
  }
# else //!VCSN_XML_GENRERIC_WEIGHTED
#  define CHOOSE_SEMIRING_SET_WEIGHTED(X, Do...)
# endif //VCSN_XML_GENRERIC_WEIGHTED

# define CHOOSE_SEMIRING_SET_NOREC_(X, Do...)                \
  if (( X .semiring_set() == XmlSet::UNSET)                  \
      || ( X .semiring_set() == XmlSet::B)) {                \
    typedef bool semiring_set;                               \
    Do;                                                      \
  }                                                          \
  CHOOSE_SEMIRING_SET_WEIGHTED(X, Do)

# define CHOOSE_SEMIRING_SET_NOREC(X, Do...)                 \
  CHOOSE_SEMIRING_SET_NOREC_(X, Do)                          \
  else                                                       \
    FAIL("Unknown semiring set.");

# ifdef VCSN_XML_GENRERIC_TRANSDUCERS

#  define CHOOSE_SEMIRING_SET(X, Do...)                      \
  CHOOSE_SEMIRING_SET_NOREC_(X, Do)                          \
  else if ( X .semiring_set() == XmlSet::RATSERIES) {        \
     CHOOSE_SEMIRING_TYPE_FOR_RATSERIES(X, Do);              \
  }                                                          \
  else                                                       \
    FAIL("Unknown semiring set.");

# else //!VCSN_XML_GENRERIC_TRANSDUCERS

#  define CHOOSE_SEMIRING_SET(X, Do...)                      \
          CHOOSE_SEMIRING_SET_NOREC(X, Do)

# endif //VCSN_XML_GENRERIC_TRANSDUCERS

# define CHOOSE_SEMIRING_TYPE_FOR_RATSERIES(X, Do...)        \
  if (( X .semiring_type() == XmlSet::UNSET)                 \
      || ( X .semiring_type() == XmlSet::FUNCTION)) {        \
    XmlSet subx = X;                                         \
    subx = subx.get_subset();                                \
    CHOOSE_SEMIRING_SET_NOREC(subx,                          \
      CHOOSE_SEMIRING_TYPE(subx,                             \
        CHOOSE_MONOID_TYPE(subx,                             \
	  CHOOSE_MONOID_SET(subx,                            \
            { DEFINE_SEM_SERIES;                             \
     	      Do;                                            \
	    }))));                                           \
  }

# define DEFINE_SEM_SERIES \
  typedef Series<semiring_type, monoid_type> semiring_type;  \
  typedef rat::exp<monoid_set, semiring_set> semiring_set;

# define CHOOSE_SEMIRING_TYPE(X, Do...)                      \
  if (( X .semiring_type() == XmlSet::UNSET)                 \
      || ( X .semiring_type() == XmlSet::NUMERICAL)          \
      || ( X .semiring_type() == XmlSet::BOOLEAN)) {         \
    typedef NumericalSemiring semiring_type;                 \
    Do;                                                      \
  }                                                          \
  else if ( X .semiring_type() == XmlSet::TROPICAL_MAX) {    \
    typedef TropicalSemiring<TropicalMax> semiring_type;     \
    Do;                                                      \
  }                                                          \
  else if ( X .semiring_type() == XmlSet::TROPICAL_MIN) {    \
    typedef TropicalSemiring<TropicalMin> semiring_type;     \
    Do;                                                      \
  }                                                          \
  else                                                       \
    FAIL("Unknown semiring type.");

# ifdef VCSN_XML_GENRERIC_CHAR_PAIRS
#  define CHOOSE_MONOID_TYPE_CHAR_PAIRS(X, Do...)            \
  else if ( X .monoid_type() == XmlSet::PAIRS) {             \
    using namespace vcsn::algebra::char_pair;                \
    typedef Words monoid_type;                               \
    Do;                                                      \
  }
# else //!VCSN_XML_GENRERIC_CHAR_PAIRS
#  define CHOOSE_MONOID_TYPE_CHAR_PAIRS(X, Do...)
# endif //VCSN_XML_GENRERIC_CHAR_PAIRS

# ifdef VCSN_XML_GENRERIC_WEIGHTED_LETTERS
#  define CHOOSE_MONOID_TYPE_WEIGHTED(X, Do...)              \
  else if ( X .monoid_type() == XmlSet::WEIGHTED) {          \
    using namespace vcsn::algebra::weighted_letter;          \
    typedef Words monoid_type;                               \
    Do;                                                      \
  }
# else //!VCSN_XML_GENRERIC_WEIGHTED_LETTERS
#  define CHOOSE_MONOID_TYPE_WEIGHTED(X, Do...)
# endif //VCSN_XML_GENRERIC_WEIGHTED_LETTERS

# ifdef VCSN_XML_GENRERIC_INT_LETTERS
#  define CHOOSE_MONOID_TYPE_INT(X, Do...)                   \
  else if ( X .monoid_type() == XmlSet::INTEGERS) {          \
    using namespace vcsn::algebra::int_letter;               \
    typedef Words monoid_type;                               \
    Do;                                                      \
  }
# else //!VCSN_XML_GENRERIC_INT_LETTERS
#  define CHOOSE_MONOID_TYPE_INT(X, Do...)
# endif //VCSN_XML_GENRERIC_INT_LETTERS

# define CHOOSE_MONOID_TYPE(X, Do...);                       \
  if (( X .monoid_type() == XmlSet::UNSET)                   \
      || ( X .monoid_type() == XmlSet::LETTERS)) {           \
    using namespace vcsn::algebra::char_letter;              \
    typedef Words monoid_type;                               \
    Do;                                                      \
  }                                                          \
  CHOOSE_MONOID_TYPE_CHAR_PAIRS(X, Do)                       \
  CHOOSE_MONOID_TYPE_WEIGHTED(X, Do)                         \
  CHOOSE_MONOID_TYPE_INT(X, Do)                              \
  else                                                       \
    FAIL("Unknown monoid type.");

# define CHOOSE_MONOID_SET(X, Do...)                         \
  if (( X .monoid_set() == XmlSet::UNSET)                    \
      || ( X .monoid_set() == XmlSet::WORDS)) {              \
    typedef WordValue monoid_set;                            \
    Do;                                                      \
  }                                                          \
  else if ( X .monoid_set() == XmlSet::UNIT) {               \
    typedef WordValue monoid_set;                            \
    Do;                                                      \
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

      CHOOSE_SEMIRING_SET(x.set(),
	CHOOSE_SEMIRING_TYPE(x.set(),
	  CHOOSE_MONOID_TYPE(x.set(),
            CHOOSE_MONOID_SET(x.set(),
              CALL_BACK))));
     }
  }
}

#endif // VCSN_XML_CALLBACK_HXX
