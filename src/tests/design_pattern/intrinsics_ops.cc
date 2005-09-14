// intrinsics_ops.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#include "intrinsics.hh"

namespace vcsn
{
  vcsn_test::T op_convert(const vcsn_test::S&,
			  SELECTOR(vcsn_test::T),
			  const int&)
  { tag += "c"; return vcsn_test::T(); }

#define DEF_OP_IN(Op, OpName)						\
  void op_in_##OpName (const vcsn_test::S& s1, const vcsn_test::S& s2,	\
		       vcsn_test::T& t1, const vcsn_test::T& t2)	\
  {									\
    if (&s1)								\
      tag += "s1";							\
    if (&s2)								\
      tag += "s2";							\
    tag += #Op;								\
    t1 = t2;								\
  }									\
  void op_in_##OpName (const vcsn_test::S& s,				\
		       vcsn_test::T& , const vcsn_test::T& )		\
  {									\
    if (&s)								\
      tag += "s";							\
    tag += #Op;								\
  }
  DEF_OP_IN(+=, add)
  DEF_OP_IN(-=, sub)
  DEF_OP_IN(/=, div)
  DEF_OP_IN(*=, mul)
  DEF_OP_IN(%=, mod)
#undef DEF_OP_IN
#define DEF_OP(Op, OpName)				\
   vcsn_test::T op_##OpName(const vcsn_test::S& s1,	\
		     const vcsn_test::S& s2,		\
		     const vcsn_test::T&,		\
		     const vcsn_test::T&)		\
  {							\
    if (&s1)						\
      tag += "s1";					\
    if (&s2)						\
      tag += "s2";					\
    tag += #Op;						\
    return vcsn_test::T();				\
  }							\
					\
  vcsn_test::T op_##OpName(const vcsn_test::S& s,	\
			   const vcsn_test::T& ,	\
			   const vcsn_test::T& )	\
  {							\
    if (&s)						\
      tag += "s";					\
    tag += #Op;					\
    return vcsn_test::T();				\
  }

    DEF_OP(+, add)
    DEF_OP(-, sub)
    DEF_OP(*, mul)
    DEF_OP(/, div)
    DEF_OP(%, mod)

    void op_in_inc(const vcsn_test::S& s,
		   vcsn_test::T&)
  {
    if (&s)
      tag += "s";
    tag += "++";
  }
    void op_in_dec(const vcsn_test::S& s,
		   vcsn_test::T&)
  {
    if (&s)
      tag += "s";
    tag += "--";
  }

  vcsn_test::T op_neg(const vcsn_test::S& s,
		      const vcsn_test::T&)
  {
    if (&s)
      tag += "s";
    tag += "neg";
    return vcsn_test::T();
  }


}


void test_ops(const vcsn_test::S& s)
{
  TEST_GROUP(std::string("element arithmetics") + (&s ? " with s.e." : ""));

  std::string it = typeid(int).name();
  t e1 (s);
  t e2 (s);
  int v1 = 0; int v2 = 42;

  std::string ss2 = (&s ? "s1s2" : "");
  std::string ss1 = (&s ? "s" : "");

#define TEST_OP(Op, Label) \
  tag = ""; e1 Op e2; TEST_ASSERT(tag == ss2 + #Op, "binary " Label); \
  TEST_ASSERT(& (e1 Op e1).structure() == &e1.structure(), "binary " Label " preserves s.e."); \
  tag = ""; v1 Op e2; TEST_ASSERT(tag == "c" + ss1 + #Op, "left " Label); \
  TEST_ASSERT(& (v1 Op e2).structure() == &e2.structure(), "left " Label " preserves s.e."); \
  tag = ""; e1 Op v2; TEST_ASSERT(tag == "c" + ss1 + #Op, "right " Label); \
  TEST_ASSERT(& (e1 Op v2).structure() == &e1.structure(), "right " Label " preserves s.e.")

  TEST_OP(+, "add");
  TEST_OP(-, "sub");
  TEST_OP(*, "mul");
  TEST_OP(/, "div");
  TEST_OP(%, "mod");
#undef TEST_OP
#define TEST_OP(Op, Label)  \
  tag = ""; e1 Op e2; TEST_ASSERT(tag == ss2 + #Op, "inplace " Label); \
  TEST_ASSERT(& (e1 Op e2) == & e1, "inplace " Label " returns reference to element"); \
  tag = ""; e1 Op v2; TEST_ASSERT(tag == "c" + ss1 + #Op, "inplace foreign " Label); \
  TEST_ASSERT(& (e1 Op e2) == & e1, "inplace foreign " Label " returns reference to element")
  TEST_OP(+=, "add");
  TEST_OP(-=, "sub");
  TEST_OP(*=, "mul");
  TEST_OP(/=, "div");
  TEST_OP(%=, "mod");
#undef TEST_OP

  tag = ""; e1++; TEST_ASSERT(tag == ss1 + "++", "increment");
  TEST_ASSERT(&(e1++).structure() == &e1.structure(), "increment preserves s.e.");
  tag = ""; ++e1; TEST_ASSERT(tag == ss1 + "++", "inplace increment");
  TEST_ASSERT(&(++e1) == &e1, "inplace increment returns reference to element");
  TEST_ASSERT(&(++e1).structure() == &e1.structure(), "inplace increment preserves s.e.");

  tag = ""; e1--; TEST_ASSERT(tag == ss1 + "--", "decrement");
  TEST_ASSERT(&(e1--).structure() == &e1.structure(), "increment preserves s.e.");
  tag = ""; --e1; TEST_ASSERT(tag == ss1 + "--", "inplace decrement");
  TEST_ASSERT(&(--e1) == &e1, "inplace decrement returns reference to element");
  TEST_ASSERT(&(--e1).structure() == &e1.structure(), "inplace increment preserves s.e.");

  tag = ""; -e1; TEST_ASSERT(tag == ss1 + "neg", "negation");
  TEST_ASSERT(&(-e1).structure() == &e1.structure(), "negation preserves s.e.");
}

namespace vcsn
{
  bool op_eq(const vcsn_test::S& s1,
	     const vcsn_test::S& s2,
	     const vcsn_test::T&,
	     const vcsn_test::T&)
  {
    if (&s1)
      tag += "s1";
    if (&s2)
      tag += "s2";
    tag += "eq";
    return true;
  }
  bool op_eq(const vcsn_test::S& s,
	     const vcsn_test::T&,
	     const vcsn_test::T&)
  {
    if (&s)
      tag += "s";
    tag += "eq";
    return true;
  }
  bool op_lt(const vcsn_test::S& s1,
	     const vcsn_test::S& s2,
	     const vcsn_test::T&,
	     const vcsn_test::T&)
  {
    if (&s1)
      tag += "s1";
    if (&s2)
      tag += "s2";
    tag += "lt";
    return true;
  }
  bool op_lt(const vcsn_test::S& s,
	     const vcsn_test::T&,
	     const vcsn_test::T&)
  {
    if (&s)
      tag += "s";
    tag += "lt";
    return true;
  }
}

void test_compare(const vcsn_test::S& s)
{
  TEST_GROUP(std::string("element comparison") + (&s ? " with s.e." : ""));

  std::string it = typeid(int).name();
  t e1 (s);
  t e2 (s);
  int v1 = 0; int v2 = 42;

  std::string ss2 = (&s ? "s1s2" : "");
  std::string ss1 = (&s ? "s" : "");
  bool val;

  
#define TEST_OP(Op, Equiv, Label) \
  tag = ""; val = (true == (e1 Op e2)); \
  TEST_ASSERT(tag == ss2 + Equiv, "binary " Label); \
  tag = ""; val = (true == (v1 Op e2)); \
  TEST_ASSERT(tag == "c" + ss1 + Equiv, "left " Label); \
  tag = ""; val = (true == (e1 Op v2)); \
  TEST_ASSERT(tag == "c" + ss1 + Equiv, "right " Label);

  TEST_OP(==, "eq", "equality");
  TEST_OP(!=, "eq", "difference");
  TEST_OP(<, "lt", "lower");
  TEST_OP(>, "lt", "greater");
  TEST_OP(<=, "lt", "lower or equal");
  TEST_OP(>=, "lt", "greater or equal");
#undef TEST_OP
}

int main()
{
  test_ops(SELECT(vcsn_test::S));
  test_compare(SELECT(vcsn_test::S));
  vcsn_test::S s;
  test_ops(s);
  test_compare(s);
}

