// selectors.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_MISC_SELECTORS_HH
# define VCSN_MISC_SELECTORS_HH

/**
 * @file selectors.hh
 * Definition of type argument macros.
 */

/** @addtogroup utility *//** @{ */

/** Type argument for types with no commas (simple or 1-par templates) */
#define SELECT(T) (*(const T*)0)
/** Type argument for types with one comma (2-parameters templates) */
#define SELECT2(T1, T2) (*(const T1 , T2 *)0)
/** Type argument for types with two commas (3-parameters templates) */
#define SELECT3(T1, T2, T3) (*(const T1 , T2, T3 *)0)
/** Type argument for types with three commas (4-parameters templates) */
#define SELECT4(T1, T2, T3, T4) (*(const T1 , T2, T3, T4 *)0)

/** Type formal argument for types with no commas (simple or 1-par templates) */
#define SELECTOR(T) const T &
/** Type formal argument for types with one comma (2-parameters templates) */
#define SELECTOR2(T1, T2) const T1 , T2 &
/** Type formal argument for types with two commas (3-parameters templates) */
#define SELECTOR3(T1, T2, T3) const T1 , T2, T3 &
/** Type formal argument for types with three commas (4-parameters templates) */
#define SELECTOR4(T1, T2, T3, T4) const T1 , T2, T3, T4 &

/** @} */

#endif // ! VCSN_MISC_SELECTORS_HH
