// search.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_SEARCH_HH
# define VCSN_ALGORITHMS_SEARCH_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file search.hh
 *
 * @brief Rational expression search in text.
 *
 * Functions to perform rational expression search.
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
  template <typename InputIterator, typename FoundFunctor, typename Series, typename Kind, typename T>
  void
  search(const Element<Automata<Series, Kind>, T>& a,
	 const InputIterator& begin,
	 const InputIterator& end,
	 typename Element<Automata<Series, Kind>, T>::letter_t eol,
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
      template <typename InputIterator, typename FoundFunctor, typename Series, typename Kind, typename T>
    static
    void
    search(const Element<Automata<Series, Kind>, T>& a,
	   const InputIterator& begin,
	   const InputIterator& end,
	   typename Element<Automata<Series, Kind>, T>::letter_t eol,
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
    template <typename InputIterator, typename FoundFunctor, typename Series, typename Kind, typename T>
    static
    void
    search(const Element<Automata<Series, Kind>, T>& a,
	   const InputIterator& begin,
	   const InputIterator& end,
	   typename Element<Automata<Series, Kind>, T>::letter_t eol,
	   FoundFunctor& f);
  };

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/search.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_SEARCH_HH
