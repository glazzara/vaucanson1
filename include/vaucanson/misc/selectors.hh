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

/*------------------------------------------.
| selectors parametrized by the return type |
`------------------------------------------*/

#define UTILITY_SELECTOR_CALL(Namespace, Name, Ret_t) \
(Namespace::Name((typename utility::remove_reference<Ret_t>::t*)0).Name())

#define UTILITY_SELECTOR_BIND(Namespace, Name) \
template<typename Ret_t> \
static inline Ret_t Name () \
{ return UTILITY_SELECTOR_CALL(Namespace, Name, Ret_t); }


#define UTILITY_SELECTOR_CALL1(Namespace, Name, Ret_t, T, Arg) \
(Namespace::Name((typename utility::remove_reference<Ret_t>::t*)0, (T*)0).Name(Arg))

#define UTILITY_SELECTOR_BIND1(Namespace, Name) \
template<typename Ret_t, typename T> \
static inline Ret_t Name (T& arg) \
{ return UTILITY_SELECTOR_CALL1(Namespace, Name, Ret_t, T, arg); }


#define UTILITY_SELECTOR_CALL2(Namespace, Name, Ret_t, T, U, Arg1, Arg2) \
(Namespace::Name((typename utility::remove_reference<Ret_t>::t*)0, (T*)0, (U*)0).Name(Arg1,
 Arg2))

#define UTILITY_SELECTOR_BIND2(Namespace, Name) \
template<typename Ret_t, typename T, typename U> \
static inline Ret_t Name (T& arg1, U& arg2) \
{ return UTILITY_SELECTOR_CALL2(Namespace, Name, Ret_t, T, U, arg1, arg2); }


#define UTILITY_SELECTOR_CALL3(Namespace, Name, Ret_t, T, U, V, Arg1, Arg2, Arg3) \
(Namespace::Name((typename utility::remove_reference<Ret_t>::t*)0, (T*)0, (U*)0, (V*)0).Nam
e(Arg1, Arg2, Arg3))

#define UTILITY_SELECTOR_BIND3(Namespace, Name) \
template<typename Ret_t, typename T, typename U, typename V> \
static inline Ret_t Name (T& arg1, U& arg2, V& arg3) \
{ return UTILITY_SELECTOR_CALL3(Namespace, Name, Ret_t, T, U, V, arg1, arg2, arg3); }


#define UTILITY_SELECTOR_CALL4(Namespace, Name, Ret_t, T, U, V, W, Arg1, Arg2, Arg3, Arg4) 
\
(Namespace::Name((typename utility::remove_reference<Ret_t>::t*)0, (T*)0, (U*)0, (V*)0).Nam
e(Arg1, Arg2, Arg3, Arg4))

#define UTILITY_SELECTOR_BIND4(Namespace, Name) \
template<typename Ret_t, typename T, typename U, typename V, typename W> \
static inline Ret_t Name (T& arg1, U& arg2, V& arg3, W& arg4) \
{ return UTILITY_SELECTOR_CALL4(Namespace, Name, Ret_t, T, U, V, W, arg1, arg2, arg3, arg4)
; }



/*--------------------------------.
| anonymous return type selectors |
`--------------------------------*/

// FIXME: do we actually need these ?

#define UTILITY_SELECTOR_ABIND(Namespace, Ret_t, Name) \
template<typename T> \
static inline Ret_t Name (T& arg) \
{ return Namespace::Name((T*)0).Name(arg); }

#define UTILITY_SELECTOR_ABIND2(Namespace, Ret_t, Name) \
template<typename T, typename U> \
static inline Ret_t Name (T& arg1, U& arg2) \
{ return Namespace::Name((T*)0, (U*)0).Name(arg1, arg2); }

#define UTILITY_SELECTOR_ABIND3(Namespace, Ret_t, Name) \
template<typename T, typename U, typename V> \
static inline Ret_t Name (T& arg1, U& arg2, V& arg3) \
{ return Namespace::Name((T*)0, (U*)0, (V*)0).Name(arg1, arg2, arg3); }

#define UTILITY_SELECTOR_ABIND4(Namespace, Ret_t, Name) \
template<typename T, typename U, typename V, typename W> \
static inline Ret_t Name (T& arg1, U& arg2, V& arg3, W& arg4) \
{ return Namespace::Name((T*)0, (U*)0, (V*)0, (W*)0).Name(arg1, arg2, arg3, arg4); }

#endif // MISC_SELECTORS_HH
