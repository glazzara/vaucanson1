// vaucanson.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUCANSON_HH
# define VCSN_VAUCANSON_HH

# include <vaucanson/config/system.hh>
# include <vaucanson/misc/utility.hh>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/algebra/algebra.hh>

/** @mainpage Vaucanson Documentation
 *
 * @section overview The Vaucanson Project
 *
 * Vaucanson is a finite state machine manipulation platform, composed
 * of a library and tools implemented on top of it. It benefits from
 * the expertize we capitalized during our intensive work on high
 * performance generic programming for Olena. On the other hand, its
 * theoretical wellfoundness in the area of automata is ensured thanks
 * to a collaborative work with Jacques Sakarovitch, at the
 * &Eacute;cole Nationale Sup&eacute;rieure des
 * T&eacute;l&eacute;communications (<A
 * HREF="http://www.enst.fr/">ENST</A>).
 *
 * See also <A HREF="http://www.lrde.epita.fr/cgi-bin/twiki/view/Projects/Vaucanson">
 * the web page of the Vaucanson project</A>.
 *
 * @section intro Purpose of this documentation
 *
 * This documentation aims at being used as a reference manual for
 * Vaucanson.  Its purpose is to describe exhaustively the definitions
 * of:
 *
 * <ul>
 *  <li>Meta-programmation tools</li>
 *  <li>Algebra constructs and operators</li>
 *  <li>Automaton structures</li>
 *  <li>Algorithms</li>
 * </ul>
 *
 * It is <strong>not</strong> a tutorial and should contain little or
 * no example of uses of the library. A separate tutorial and source
 * examples are available in the source code distribution.
 *
 * <strong>Note:</strong> this documentation is also <em>a work in
 * progress</em>.  This means that while we are working our best to
 * document every aspect of the library, the documentation is <em>not
 * yet</em> complete. This also means that more structures and algorithms
 * are available in the library than those currently documented.
 * For an extensive listing of all the available algorithms, browse
 * the @c include/vaucanson/algorithms source directory.
 *
 * @section howto How to read
 *
 * This documentation is separated into "chapters" each describing the
 * library under a different point of view.
 *
 * <ul>
 *
 * <li><A HREF="modules.html">Modules</A> are the different categories
 * used to classify the features of the library.</li>
 *
 * <li>The class <A HREF="annotated.html">list</A>,
 *  <A HREF="classes.html">index</A> and
 *  <A HREF="hierarchy.html">hierarchy</A> describe the different data
 * structures.</li>
 *
 * <li>The @link design_pattern Fundamental @endlink section describes the
 *     peculiar design pattern used in Vaucanson.</li>
 *
 * <li>The @link algebra algebra constructs listing @endlink describe the algebraic
 *     system used by the library.</li>
 *
 * <li>The @link automata automaton constructs listing @endlink describe the different
 *     automaton structures available.</li>
 *
 * <li>The @link algorithms algorithm listing @endlink describe the different algorithms.</li>
 *
 * <li>The <A HREF="files.html">file listing</A> lists all the source files together
 *       with their documentation.</li>
 *
 * </ul>
 */

#endif // ! VCSN_VAUCANSON_HH
