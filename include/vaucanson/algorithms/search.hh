// search.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//

#ifndef VCSN_ALGORITHMS_SEARCH_HH
# define VCSN_ALGORITHMS_SEARCH_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file search.hh
 *
 * @brief Rational expression search in text.
 *
 * This file contains functions to perform rational expression search.
 *
 * @see search()
 */
/** @} */

# include <vaucanson/automata/concept/automata.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Search for a rational expression into a text.
   *
   * This function searches a rational expression into a text, given a
   * iterator on the text and an automaton which recognizes the
   * corresponding langage. The result cannot spread over two lines.
   *
   * @param a The automaton which recognizes the searched words.
   * @param begin An input iterator to the begining of the text.
   * @param end An iterator to the end of the text.
   * @param eol The character to use for ending a line.
   * @param f A functor with an operator () method taking 3 InputIterator as
   *	      argument which will be called each time a match is found.
   *          the first one points to the begining of the stream. The two
   *          following ones are respectively the first and the last position
   *          of the match in the stream.
   *
   * @authors Thomas Claveirole <thomas@lrde.epita.fr>
   *
   * @bug Multiple implementations of search() should be
   *	  implemented. When a call to search is performed an heuristic
   *      should decide which implementation to use. For the moment there
   *      is no such mechanism since only one implementation of search is
   *      provided.
   */
  template <class InputIterator, class FoundFunctor, class Series, class T>
  void
  search(const Element<Automata<Series>, T>& a,
	 const InputIterator& begin,
	 const InputIterator& end,
	 typename Element<Automata<Series>, T>::letter_t eol,
	 FoundFunctor& f);

  /**
   * Specific implementation for search().
   *
   * This class owns a specific implementation of search. This implementation
   * deleguates the search to another implementation, choosing which one with
   * an heuristic.
   *
   * @see search(), WindowedBackSearch
   *
   * @author Thomas Claveirole <thomas@lrde.epita.fr>
   */
  struct FindBestSearch
  {
    template <class InputIterator, class FoundFunctor, class Series, class T>
    static
    void
    search(const Element<Automata<Series>, T>& a,
	   const InputIterator& begin,
	   const InputIterator& end,
	   typename Element<Automata<Series>, T>::letter_t eol,
	   FoundFunctor& f);
  };

  /**
   * Specific implementation for search().
   *
   * This class owns a specific implementation of search. This implementation
   * use an algorithm able to skip characters in the input stream, using a
   * backward search inside windows in the stream.
   *
   * One important precondition for using this algorithm is that there *must*
   * be no spontaneous transition inside the given automaton.
   *
   * @see search(), FindBestSearch
   *
   * @author Thomas Claveirole <thomas@lrde.epita.fr>
   */
  struct WindowedBackSearch
  {
    template <class InputIterator, class FoundFunctor, class Series, class T>
    static
    void
    search(const Element<Automata<Series>, T>& a,
	   const InputIterator& begin,
	   const InputIterator& end,
	   typename Element<Automata<Series>, T>::letter_t eol,
	   FoundFunctor& f);
  };

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/search.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGORITHMS_SEARCH_HH
