// misc/selectors.hh
//
// $Id$
// VCSN_HEADER
#ifndef MISC_SELECTORS_HH
# define MISC_SELECTORS_HH

/*------------------------.
| Simple selectors macros |
`------------------------*/
#define SELECT(T) ((const T*)0)
#define SELECT2(T1, T2) ((const T1 , T2 *)0)
#define SELECT3(T1, T2, T3) ((const T1 , T2, T3 *)0)
#define SELECT4(T1, T2, T3, T4) ((const T1 , T2, T3, T4 *)0)
#define SELECTOR(T) const T *
#define SELECTOR2(T1, T2) const T1 , T2 *
#define SELECTOR3(T1, T2, T3) const T1 , T2, T3 *
#define SELECTOR4(T1, T2, T3, T4) const T1 , T2, T3, T4 *

#endif // MISC_SELECTORS_HH
