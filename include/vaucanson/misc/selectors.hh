// selectors.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_MISC_SELECTORS_HH
# define VCSN_MISC_SELECTORS_HH

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
