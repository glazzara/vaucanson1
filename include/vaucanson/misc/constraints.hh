// constraints.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
//    * Michael Cadilhac <michael.cadilhac@lrde.epita.fr>
//
#ifndef VCSN_MISC_CONSTRAINTS_HH
# define VCSN_MISC_CONSTRAINTS_HH


namespace utility
{

  /*---------------------------.
  | Static constraint checking |
  `---------------------------*/

  // this stuff is heavily inspired from the C++ Boost Library.
  // Use it sparingly, it can cause HUGE amounts of template instanciations.

# if defined(__GNUC__)
#  define UnusedConceptVar __attribute__ ((__unused__))
# else
#  define UnusedConceptVar /* unused */
# endif

  namespace concepts
  {
    template <typename Concept_>
    static void function_requires()
    {
      void (Concept_::*ptr)() UnusedConceptVar = &Concept_::constraints;
    }

    // deep wizardry at work here...

# define UTILITY_CLASS_CHECKING_IDX(Lineno, Concept, T) \
  ConceptChecking##Lineno##_##Concept##T
# define UTILITY_CLASS_CHECKING_ID(Lineno, Concept, T) \
  UTILITY_CLASS_CHECKING_IDX(Lineno, Concept, T)
# define UTILITY_CLASS_FPTR_IDX(Lineno, Concept, T) \
  Concept##Lineno##_fptr_##T
# define UTILITY_CLASS_FPTR_ID(Lineno, Concept, T) \
  UTILITY_CLASS_FPTR_IDX(Lineno, Concept, T)

# ifdef VCSN_NDEBUG

#  define UTILITY_CLASS_REQUIRE_CONCEPT(Var, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#  define UTILITY_CLASS_REQUIRE_CONCEPT2(Var1, Var2, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#  define UTILITY_CLASS_REQUIRE_CONCEPT3(Var1, Var2, Var3, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#  define UTILITY_CLASS_REQUIRE_CONCEPT4(Var1, Var2, Var3, Var4, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#  define UTILITY_REQUIRE_CONCEPT(Var, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#  define UTILITY_REQUIRE_CONCEPT2(Var1, Var2, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#  define UTILITY_REQUIRE_CONCEPT3(Var1, Var2, Var3, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#  define UTILITY_REQUIRE_CONCEPT4(Var1, Var2, Var3, Var4, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)

# else // VCSN_NDEBUG

    // these should be left 120 columns wide for better readability

#  define UTILITY_CLASS_REQUIRE_CONCEPT(Var, Namespace, Concept)					\
  typedef void (Namespace::Concept <Var>::* UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t))();		\
  template <UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t) UTILITY_CLASS_FPTR_ID(__LINE__, Concept, arg)>	\
  struct UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s) {};						\
  typedef UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s)<& Namespace::Concept<Var>::constraints>	\
	UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)

#  define UTILITY_CLASS_REQUIRE_CONCEPT2(Var1, Var2, Namespace, Concept)				\
  typedef void (Namespace::Concept <Var1,Var2>::* UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t))();	\
  template <UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t) UTILITY_CLASS_FPTR_ID(__LINE__, Concept, arg)>	\
  struct UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s) {};						\
  typedef UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s)<& Namespace::Concept<Var1,Var2>::constraints> \
	UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)

#  define UTILITY_CLASS_REQUIRE_CONCEPT3(Var1, Var2, Var3, Namespace, Concept)				\
  typedef void (Namespace::Concept <Var1,Var2,Var3>::* UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t))();	\
  template <UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t) UTILITY_CLASS_FPTR_ID(__LINE__, Concept, arg)>	\
  struct UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s) {};						\
  typedef UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s)<& Namespace::Concept<Var1,Var2,Var3>::constraints> \
	UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)

#  define UTILITY_CLASS_REQUIRE_CONCEPT4(Var1, Var2, Var3, Var4, Namespace, Concept)			\
  typedef void (Namespace::Concept <Var1,Var2,Var3,Var4>::* UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t))();\
  template <UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t) UTILITY_CLASS_FPTR_ID(__LINE__, Concept, arg)>	\
  struct UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s) {};						\
  typedef UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s)<& Namespace::Concept<Var1,Var2,Var3,Var4>::constraints> \
	UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)

#  define UTILITY_REQUIRE_CONCEPT(Var, Namespace, Concept) \
  utility::concepts::function_requires<Namespace::Concept <Var> >()
#  define UTILITY_REQUIRE_CONCEPT2(Var1, Var2, Namespace, Concept) \
  utility::concepts::function_requires<Namespace::Concept <Var1, Var2> >()
#  define UTILITY_REQUIRE_CONCEPT3(Var1, Var2, Var3, Namespace, Concept) \
  utility::concepts::function_requires<Namespace::Concept <Var1, Var2, Var3> >()
#  define UTILITY_REQUIRE_CONCEPT4(Var1, Var2, Var3, Var4, Namespace, Concept) \
  utility::concepts::function_requires<Namespace::Concept <Var1, Var2, Var3, Var4> >()

# endif // ! VCSN_NDEBUG

  } // concepts
} // utility

#endif // ! VCSN_MISC_CONSTRAINTS_HH
