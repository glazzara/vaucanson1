// constraints.hh
//
//
// $Id$
// VCSN_HEADER

#ifndef UTILITY_CONSTRAINTS_HH
# define UTILITY_CONSTRAINTS_HH


namespace utility
{

  /*---------------------------.
  | Static constraint checking |
  `---------------------------*/

  // this stuff is heavily inspired from the C++ Boost Library.
  // Use it sparingly, it can cause HUGE amounts of template instanciations.

#if defined(__GNUC__)
#define UnusedConceptVar __attribute__ ((__unused__))
#else
#define UnusedConceptVar /* unused */
#endif

  namespace concepts
  {
    template <typename Concept_>
    static inline void function_requires()
    {
      void (Concept_::*ptr)() UnusedConceptVar = &Concept_::constraints;
    }

    // deep wizardry at work here...

#define UTILITY_CLASS_CHECKING_IDX(Lineno, Concept, T) \
  ConceptChecking##Lineno##_##Concept##T
#define UTILITY_CLASS_CHECKING_ID(Lineno, Concept, T) \
  UTILITY_CLASS_CHECKING_IDX(Lineno, Concept, T)
#define UTILITY_CLASS_FPTR_IDX(Lineno, Concept, T) \
  Concept##Lineno##_fptr_##T
#define UTILITY_CLASS_FPTR_ID(Lineno, Concept, T) \
  UTILITY_CLASS_FPTR_IDX(Lineno, Concept, T)

#ifdef NDEBUG

#define UTILITY_CLASS_REQUIRE_CONCEPT(Var, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#define UTILITY_CLASS_REQUIRE_CONCEPT2(Var1, Var2, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#define UTILITY_CLASS_REQUIRE_CONCEPT3(Var1, Var2, Var3, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#define UTILITY_CLASS_REQUIRE_CONCEPT4(Var1, Var2, Var3, Var4, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#define UTILITY_REQUIRE_CONCEPT(Var, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#define UTILITY_REQUIRE_CONCEPT2(Var1, Var2, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#define UTILITY_REQUIRE_CONCEPT3(Var1, Var2, Var3, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)
#define UTILITY_REQUIRE_CONCEPT4(Var1, Var2, Var3, Var4, Namespace, Concept) \
    typedef void UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)

#else

    // these should be left 120 columns wide for better readability

#define UTILITY_CLASS_REQUIRE_CONCEPT(Var, Namespace, Concept)						\
  typedef void (Namespace::Concept <Var>::* UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t))();		\
  template <UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t) UTILITY_CLASS_FPTR_ID(__LINE__, Concept, arg)>	\
  struct UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s) {};						\
  typedef UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s)<& Namespace::Concept<Var>::constraints>	\
	UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)

#define UTILITY_CLASS_REQUIRE_CONCEPT2(Var1, Var2, Namespace, Concept)					\
  typedef void (Namespace::Concept <Var1,Var2>::* UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t))();	\
  template <UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t) UTILITY_CLASS_FPTR_ID(__LINE__, Concept, arg)>	\
  struct UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s) {};						\
  typedef UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s)<& Namespace::Concept<Var1,Var2>::constraints> \
	UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)

#define UTILITY_CLASS_REQUIRE_CONCEPT3(Var1, Var2, Var3, Namespace, Concept)				\
  typedef void (Namespace::Concept <Var1,Var2,Var3>::* UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t))();	\
  template <UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t) UTILITY_CLASS_FPTR_ID(__LINE__, Concept, arg)>	\
  struct UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s) {};						\
  typedef UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s)<& Namespace::Concept<Var1,Var2,Var3>::constraints> \
	UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)

#define UTILITY_CLASS_REQUIRE_CONCEPT4(Var1, Var2, Var3, Var4, Namespace, Concept)			\
  typedef void (Namespace::Concept <Var1,Var2,Var3,Var4>::* UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t))();\
  template <UTILITY_CLASS_FPTR_ID(__LINE__, Concept, t) UTILITY_CLASS_FPTR_ID(__LINE__, Concept, arg)>	\
  struct UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s) {};						\
  typedef UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _s)<& Namespace::Concept<Var1,Var2,Var3,Var4>::constraints> \
	UTILITY_CLASS_CHECKING_ID(__LINE__, Concept, _t)

#define UTILITY_REQUIRE_CONCEPT(Var, Namespace, Concept) \
  utility::concepts::function_requires<Namespace::Concept <Var> >()
#define UTILITY_REQUIRE_CONCEPT2(Var1, Var2, Namespace, Concept) \
  utility::concepts::function_requires<Namespace::Concept <Var1, Var2> >()
#define UTILITY_REQUIRE_CONCEPT3(Var1, Var2, Var3, Namespace, Concept) \
  utility::concepts::function_requires<Namespace::Concept <Var1, Var2, Var3> >()
#define UTILITY_REQUIRE_CONCEPT4(Var1, Var2, Var3, Var4, Namespace, Concept) \
  utility::concepts::function_requires<Namespace::Concept <Var1, Var2, Var3, Var4> >()

#endif

  } // concepts
} // utility

#endif
