// constraints.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_MISC_CONSTRAINTS_HH
# define VCSN_MISC_CONSTRAINTS_HH


namespace vcsn
{
  namespace misc
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

# define MISC_CLASS_CHECKING_IDX(Lineno, Concept, T) \
      ConceptChecking ## Lineno ## _ ## Concept ## T
# define MISC_CLASS_CHECKING_ID(Lineno, Concept, T)	\
      MISC_CLASS_CHECKING_IDX(Lineno, Concept, T)
# define MISC_CLASS_FPTR_IDX(Lineno, Concept, T)	\
      Concept ## Lineno ## _fptr_ ## T
# define MISC_CLASS_FPTR_ID(Lineno, Concept, T)	\
      MISC_CLASS_FPTR_IDX(Lineno, Concept, T)

# ifdef VCSN_NDEBUG

#  define MISC_CLASS_REQUIRE_CONCEPT(Var, Namespace, Concept)	\
      typedef void MISC_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#  define MISC_CLASS_REQUIRE_CONCEPT2(Var1, Var2, Namespace, Concept) \
      typedef void MISC_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#  define MISC_CLASS_REQUIRE_CONCEPT3(Var1, Var2, Var3, Namespace, Concept) \
      typedef void MISC_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#  define MISC_CLASS_REQUIRE_CONCEPT4(Var1, Var2, Var3, Var4, Namespace, Concept) \
      typedef void MISC_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#  define MISC_REQUIRE_CONCEPT(Var, Namespace, Concept)		\
      typedef void MISC_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#  define MISC_REQUIRE_CONCEPT2(Var1, Var2, Namespace, Concept)	\
      typedef void MISC_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#  define MISC_REQUIRE_CONCEPT3(Var1, Var2, Var3, Namespace, Concept) \
      typedef void MISC_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#  define MISC_REQUIRE_CONCEPT4(Var1, Var2, Var3, Var4, Namespace, Concept) \
      typedef void MISC_CLASS_CHECKING_ID(__LINE__, Concept, _t)

# else // VCSN_NDEBUG

      // these should be left 120 columns wide for better readability

#  define MISC_CLASS_REQUIRE_CONCEPT(Var, Namespace, Concept)	\
      typedef void (Namespace::Concept <Var>::* MISC_CLASS_FPTR_ID(__LINE__, Concept, t))();	\
      template <MISC_CLASS_FPTR_ID(__LINE__, Concept, t) MISC_CLASS_FPTR_ID(__LINE__, Concept, arg)> \
      struct MISC_CLASS_CHECKING_ID(__LINE__, Concept, _s) {};	\
      typedef MISC_CLASS_CHECKING_ID(__LINE__, Concept, _s)<& Namespace::Concept<Var>::constraints> \
	      MISC_CLASS_CHECKING_ID(__LINE__, Concept, _t)

#  define MISC_CLASS_REQUIRE_CONCEPT2(Var1, Var2, Namespace, Concept) \
      typedef void (Namespace::Concept <Var1,Var2>::* MISC_CLASS_FPTR_ID(__LINE__, Concept, t))(); \
      template <MISC_CLASS_FPTR_ID(__LINE__, Concept, t) MISC_CLASS_FPTR_ID(__LINE__, Concept, arg)> \
      struct MISC_CLASS_CHECKING_ID(__LINE__, Concept, _s) {};	\
      typedef MISC_CLASS_CHECKING_ID(__LINE__, Concept, _s)<& Namespace::Concept<Var1,Var2>::constraints> \
	      MISC_CLASS_CHECKING_ID(__LINE__, Concept, _t)

#  define MISC_CLASS_REQUIRE_CONCEPT3(Var1, Var2, Var3, Namespace, Concept) \
      typedef void (Namespace::Concept <Var1,Var2,Var3>::* MISC_CLASS_FPTR_ID(__LINE__, Concept, t))(); \
      template <MISC_CLASS_FPTR_ID(__LINE__, Concept, t) MISC_CLASS_FPTR_ID(__LINE__, Concept, arg)> \
      struct MISC_CLASS_CHECKING_ID(__LINE__, Concept, _s) {};	\
      typedef MISC_CLASS_CHECKING_ID(__LINE__, Concept, _s)<& Namespace::Concept<Var1,Var2,Var3>::constraints> \
	      MISC_CLASS_CHECKING_ID(__LINE__, Concept, _t)

#  define MISC_CLASS_REQUIRE_CONCEPT4(Var1, Var2, Var3, Var4, Namespace, Concept) \
      typedef void (Namespace::Concept <Var1,Var2,Var3,Var4>::* MISC_CLASS_FPTR_ID(__LINE__, Concept, t))();	\
      template <MISC_CLASS_FPTR_ID(__LINE__, Concept, t) MISC_CLASS_FPTR_ID(__LINE__, Concept, arg)> \
      struct MISC_CLASS_CHECKING_ID(__LINE__, Concept, _s) {};	\
      typedef MISC_CLASS_CHECKING_ID(__LINE__, Concept, _s)<& Namespace::Concept<Var1,Var2,Var3,Var4>::constraints> \
	      MISC_CLASS_CHECKING_ID(__LINE__, Concept, _t)

#  define MISC_REQUIRE_CONCEPT(Var, Namespace, Concept)		\
      vcsn::misc::concepts::function_requires<Namespace::Concept <Var> >()
#  define MISC_REQUIRE_CONCEPT2(Var1, Var2, Namespace, Concept)	\
      vcsn::misc::concepts::function_requires<Namespace::Concept <Var1, Var2> >()
#  define MISC_REQUIRE_CONCEPT3(Var1, Var2, Var3, Namespace, Concept) \
      vcsn::misc::concepts::function_requires<Namespace::Concept <Var1, Var2, Var3> >()
#  define MISC_REQUIRE_CONCEPT4(Var1, Var2, Var3, Var4, Namespace, Concept) \
      vcsn::misc::concepts::function_requires<Namespace::Concept <Var1, Var2, Var3, Var4> >()

# endif // ! VCSN_NDEBUG

    } // concepts
  } // misc
} // vcsn

#endif // ! VCSN_MISC_CONSTRAINTS_HH
