// callback.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_XML_CALLBACK_HXX
# define VCSN_XML_CALLBACK_HXX

# include <vaucanson/xml/callback.hh>
# include <vaucanson/algebra/implementation/free_monoid/tools.hh>
# include <vaucanson/algebra/implementation/letter/couple_letter.hh>
# include <vaucanson/algebra/implementation/letter/int_letter.hh>

# ifdef VCSN_XML_GENRERIC_WEIGHTED
#  define CHOOSE_SEMIRING_SET_WEIGHTED(X, Do...)	\
  else if ( X .semiring_value() == XmlStructure::Z) {	\
    typedef int semiring_set;				\
    Do;							\
  }							\
  else if ( X .semiring_value() == XmlStructure::R) {	\
    typedef float semiring_set;				\
    Do;							\
  }
# else //!VCSN_XML_GENRERIC_WEIGHTED
#  define CHOOSE_SEMIRING_SET_WEIGHTED(X, Do...)
# endif //VCSN_XML_GENRERIC_WEIGHTED

# define CHOOSE_SEMIRING_SET_NOREC_(X, Do...)		\
  if (( X .semiring_value() == XmlStructure::UNSET)	\
      || ( X .semiring_value() == XmlStructure::B)) {	\
    typedef bool semiring_set;				\
    Do;							\
  }							\
  CHOOSE_SEMIRING_SET_WEIGHTED(X, Do)

# define CHOOSE_SEMIRING_SET_NOREC(X, Do...)	\
  CHOOSE_SEMIRING_SET_NOREC_(X, Do)		\
  else						\
    FAIL("Unknown semiring set.");

# ifdef VCSN_XML_GENRERIC_TRANSDUCERS

#  define CHOOSE_SEMIRING_SET(X, Do...)				\
  CHOOSE_SEMIRING_SET_NOREC_(X, Do)				\
  else if ( X .semiring_value() == XmlStructure::RATSERIES) {	\
     CHOOSE_SEMIRING_TYPE_FOR_RATSERIES(X, Do);			\
  }								\
  else								\
    FAIL("Unknown semiring set.");

# else //!VCSN_XML_GENRERIC_TRANSDUCERS

#  define CHOOSE_SEMIRING_SET(X, Do...)                      \
          CHOOSE_SEMIRING_SET_NOREC(X, Do)

# endif //VCSN_XML_GENRERIC_TRANSDUCERS

# define CHOOSE_SEMIRING_TYPE_FOR_RATSERIES(X, Do...)			\
  if (( X .semiring_structure() == XmlStructure::UNSET)			\
      || ( X .semiring_structure() == XmlStructure::FUNCTION)) {	\
    XmlStructure subx = X;						\
    subx = subx.get_substructure();					\
    CHOOSE_SEMIRING_SET_NOREC(subx,					\
      CHOOSE_SEMIRING_TYPE(subx,					\
        CHOOSE_MONOID_TYPE(subx,					\
	  CHOOSE_MONOID_SET(subx,					\
            { DEFINE_SEM_SERIES;					\
     	      Do;							\
	    }))));							\
  }

# define DEFINE_SEM_SERIES					\
  typedef Series<semiring_type, monoid_type> semiring_type;	\
  typedef rat::exp<monoid_set, semiring_set> semiring_set;

# define CHOOSE_SEMIRING_TYPE(X, Do...)					\
  if (( X .semiring_structure() == XmlStructure::UNSET)			\
      || ( X .semiring_structure() == XmlStructure::NUMERICAL)		\
      || ( X .semiring_structure() == XmlStructure::BOOLEAN)) {		\
    typedef NumericalSemiring semiring_type;				\
    Do;									\
  }									\
  else if ( X .semiring_structure() == XmlStructure::TROPICAL_MAX) {	\
    typedef TropicalSemiring<TropicalMax> semiring_type;		\
    Do;									\
  }									\
  else if ( X .semiring_structure() == XmlStructure::TROPICAL_MIN) {	\
    typedef TropicalSemiring<TropicalMin> semiring_type;		\
    Do;									\
  }									\
  else									\
    FAIL("Unknown semiring type.");

# ifdef VCSN_XML_GENRERIC_CHAR_PAIRS
#  define CHOOSE_MONOID_TYPE_CHAR_PAIRS(X, Do...)		\
  else if ( X .monoid_structure() == XmlStructure::PAIRS) {	\
    using namespace vcsn::algebra::char_pair;			\
    typedef Words monoid_type;					\
    Do;								\
  }
# else //!VCSN_XML_GENRERIC_CHAR_PAIRS
#  define CHOOSE_MONOID_TYPE_CHAR_PAIRS(X, Do...)
# endif //VCSN_XML_GENRERIC_CHAR_PAIRS

# ifdef VCSN_XML_GENRERIC_WEIGHTED_LETTERS
#  define CHOOSE_MONOID_TYPE_WEIGHTED(X, Do...)			\
  else if ( X .monoid_structure() == XmlStructure::WEIGHTED) {	\
    using namespace vcsn::algebra::weighted_letter;		\
    typedef Words monoid_type;					\
    Do;								\
  }
# else //!VCSN_XML_GENRERIC_WEIGHTED_LETTERS
#  define CHOOSE_MONOID_TYPE_WEIGHTED(X, Do...)
# endif //VCSN_XML_GENRERIC_WEIGHTED_LETTERS

# ifdef VCSN_XML_GENRERIC_INT_LETTERS
#  define CHOOSE_MONOID_TYPE_INT(X, Do...)			\
  else if ( X .monoid_structure() == XmlStructure::INTEGERS) {	\
    using namespace vcsn::algebra::int_letter;			\
    typedef Words monoid_type;					\
    Do;								\
  }
# else //!VCSN_XML_GENRERIC_INT_LETTERS
#  define CHOOSE_MONOID_TYPE_INT(X, Do...)
# endif //VCSN_XML_GENRERIC_INT_LETTERS

# define CHOOSE_MONOID_TYPE(X, Do...);				\
  if (( X .monoid_structure() == XmlStructure::UNSET)		\
      || ( X .monoid_structure() == XmlStructure::LETTERS)) {	\
    using namespace vcsn::algebra::char_letter;			\
    typedef Words monoid_type;					\
    Do;								\
  }								\
  CHOOSE_MONOID_TYPE_CHAR_PAIRS(X, Do)				\
  CHOOSE_MONOID_TYPE_WEIGHTED(X, Do)				\
  CHOOSE_MONOID_TYPE_INT(X, Do)					\
  else								\
    FAIL("Unknown monoid type.");

# define CHOOSE_MONOID_SET(X, Do...)			\
  if (( X .monoid_value() == XmlStructure::UNSET)	\
      || ( X .monoid_value() == XmlStructure::WORDS)) {	\
    typedef WordValue monoid_set;			\
    Do;							\
  }							\
  else if ( X .monoid_value() == XmlStructure::UNIT) {	\
    typedef WordValue monoid_set;			\
    Do;							\
  }							\
  else							\
    FAIL("Unknown monoid type.");

# define CALL_BACK						\
typedef Series<semiring_type, monoid_type>	series_set_t;	\
typedef Automata<series_set_t>			automata_set_t;	\
typedef								\
  Element<automata_set_t,					\
	  Graph<labels_are_series, monoid_set, semiring_set,	\
		rat::exp<monoid_set, semiring_set>, Letter,	\
		XmlInfosTag> >			automaton_t;	\
automaton_t a = x;						\
Callback<automaton_t> cb;					\
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

      xml_automata_set_t	xs;
      xml_automaton_t		x (xs);

      in >> x;

      CHOOSE_SEMIRING_SET(x.structure(),
	CHOOSE_SEMIRING_TYPE(x.structure(),
	  CHOOSE_MONOID_TYPE(x.structure(),
            CHOOSE_MONOID_SET(x.structure(),
              CALL_BACK))));
     }
  }
}

#endif // ! VCSN_XML_CALLBACK_HXX
