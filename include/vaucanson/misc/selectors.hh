// misc/selectors.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

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
