// window.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_WINDOW_HH
# define VCSN_MISC_WINDOW_HH

/** @addtogroup utility *//** @{ */
/**
 * @file   window.hh
 *
 * Window class for regular expression search on streams.
 *
 * @author Thomas Claveirole <thomas@lrde.epita.fr>
 * @see @ref window "@c Window"
 */
/** @} */

# include <iostream>
# include <string>

namespace utility {

  /** @addtogroup utility *//** @{ */

  /**
   * Handle windows in streams for performing regular expression search.
   *
   * A window is a portion of a stream, viewable as a string, on which
   * several operations can be performed:
   *
   *  - Read the window's characters.
   *  - Shift the window forward.
   *
   * A window has a constant size, unless an end of line ('\\n') or an
   * end of file occurs, in which case a window is shorter than its
   * supposed size.
   *
   * @param InputIterator The type of input iterator used to read the stream.
   *                      It shall be a random access iterator.
   * @param Letter The type  used for letters.
   *
   * @author Thomas Claveirole <thomas@lrde.epita.fr>
   * @anchor window
   */
  template <class InputIterator, class Letter>
  struct Window
  {
    typedef InputIterator				iterator_t;
    typedef Letter					letter_t;
    typedef typename std::basic_string<letter_t>	string_t;
    typedef unsigned int				length_t;

    /**
     * Standard constructor for the Window class.
     *
     * Build a window from a couple of begin/end iterator, a newline
     * character and a window length.
     *
     * @param stream Iterator to the begining of the stream.
     * @param eof Iterator to the end of the stream.
     * @param eol The newline character.
     * @param length The window length.
     *
     * @see Window
     */
    Window(const iterator_t& stream,
	   const iterator_t& eof,
	   letter_t eol,
	   length_t length);

    /// Indicates wether the end of the stream has been reached or not.
    bool		eof() const;
    /// Indicates wether a new line has been reached or not.
    bool		eol() const;

    /**
     * Shift the window.
     *
     * @param n The number of character the window must be shifted.
     */
    void		shift(unsigned int n);
    /// Shift the window completely (equivalent to shift(size())).
    void		shift();

    //@{
    /// Move to a specific offset.
    void		moveto(length_t offset);
    void		moveto(iterator_t position);
    //@}

    /// Returns the actual window size.
    length_t		size() const;

    /// Returns the i-th character of the window.
    letter_t		operator [] (length_t i) const;

    /// Print the window.
    std::ostream&	print(std::ostream& ostr) const;

    /// @name Accessors
    //@{
    /// Get an iterator to the beginning of the stream.
    iterator_t		begin() const;
    /// Get an iterator to the current position in the stream.
    iterator_t		stream() const;
    /// Get an iterator to the end of the stream.
    iterator_t		end() const;
    /// Get the actual offset in the stream.
    size_t		offset() const;
    /// Get the letter value used for ending lines.
    letter_t		eol_value() const;
    /// Get the maximum length of the window.
    length_t		length() const;
    /// Get the window as a @c basic_string<letter_t>.
    string_t		window() const;
    //@}
  protected:
    void		compute_size();

    iterator_t		begin_;
    iterator_t		stream_;
    iterator_t		end_;
    letter_t		eol_;
    length_t		length_;
    length_t		size_;
  };

  template <class InputIterator, class Letter>
  std::ostream&
  operator << (std::ostream& ostr, const Window<InputIterator, Letter>& w);

  /** @} */

} // utility

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/misc/window.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_MISC_WINDOW_HH
