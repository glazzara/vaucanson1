// -*- C++ -*-

%no-parser

%{
namespace ll_lisp
{
  int cons(int, int) { return 0; }
  int symbol(const char*) { return 0; }
  int nil() { return 0; }
  int t() { return 0; }
  int list(int) { return 0; }
  int& car(int& x) { return x; }
  int& cdr(int& x) { return x; }
  int list(int, int) { return 0; }
  int list(int, int, int) { return 0; }
  int list(int, int, int, int) { return 0; }
  int list(int, int, int, int, int) { return 0; }
}

namespace lisp
{
  int cons(int, int) { return 0; }
}

static int yylex() { return 0; }
static void yyerror(const char*) {}

#define IN_DEBUG(Arg) Arg

#define CSYM(S) ll_lisp::symbol(S)
#define LCONS(C1, C2) lisp::cons(C1, C2)
#define CCONS(C1, C2) ll_lisp::cons(C1, C2)
#define CLIST1(L) ll_lisp::list(L)
#define CLIST2(L1,L2) ll_lisp::list(L1,L2)
#define CLIST3(L1,L2,L3) ll_lisp::list(L1,L2,L3)
#define CLIST4(L1,L2,L3,L4) ll_lisp::list(L1,L2,L3,L4)
#define CLIST5(L1,L2,L3,L4,L5) ll_lisp::list(L1,L2,L3,L4,L5)
#define CNIL ll_lisp::nil()
#define CQUOTE(E) CLIST2(CSYM("quote"), E)
#define CCDR(E) ll_lisp::cdr(E)
#define CCAR(E) ll_lisp::car(E)
#define CT ll_lisp::t()

%}

