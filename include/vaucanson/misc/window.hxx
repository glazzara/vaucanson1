// window.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_MISC_WINDOW_HXX
# define VCSN_MISC_WINDOW_HXX

/**
 * @file   window.hxx
 * @brief  Window class for regular expression search on streams.
 *
 * @author Thomas Claveirole <thomas@lrde.epita.fr>
 * @see Window
 */

# include <vaucanson/misc/window.hh>
# include <vaucanson/misc/contract.hh>

namespace utility {

  /** @addtogroup utility *//** @{ */

  template <class InputIterator, class Letter>
  Window<InputIterator, Letter>::Window(const iterator_t& stream,
					const iterator_t& eof,
					letter_t eol,
					length_t length) :
    begin_	(stream),
    stream_	(stream),
    end_	(eof),
    eol_	(eol),
    length_	(length)
  {
    precondition(length > 0);

    compute_size();
  }

  template <class InputIterator, class Letter>
  bool
  Window<InputIterator, Letter>::eof() const
  {
    return stream_ == end_;
  }

  template <class InputIterator, class Letter>
  bool
  Window<InputIterator, Letter>::eol() const
  {
    return eof() || (*stream_ == eol_);
  }

  template <class InputIterator, class Letter>
  void
  Window<InputIterator, Letter>::shift(unsigned int n)
  {
    precondition(n <= size_);

    if ((stream_ != end_) && (*stream_ == eol_))
      ++stream_;
    else
      stream_ += n;
    compute_size();
  }

  template <class InputIterator, class Letter>
  void
  Window<InputIterator, Letter>::shift()
  {
    shift(size());
  }

  template <class InputIterator, class Letter>
  void
  Window<InputIterator, Letter>::moveto(length_t offset)
  {
    stream_ = begin_ + offset;
    compute_size();
  }

  template <class InputIterator, class Letter>
  void
  Window<InputIterator, Letter>::moveto(iterator_t position)
  {
    stream_ = position;
    compute_size();
  }

  template <class InputIterator, class Letter>
  typename Window<InputIterator, Letter>::length_t
  Window<InputIterator, Letter>::size() const
  {
    return size_;
  }

  template <class InputIterator, class Letter>
  typename Window<InputIterator, Letter>::letter_t
  Window<InputIterator, Letter>::operator [] (length_t i) const
  {
    precondition (i < size_);

    return stream_[i];
  }

  template <class InputIterator, class Letter>
  std::ostream&
  Window<InputIterator, Letter>::print(std::ostream& ostr) const
  {
    return ostr << window();
  }

  template <class InputIterator, class Letter>
  typename Window<InputIterator, Letter>::letter_t
  Window<InputIterator, Letter>::eol_value() const
  {
    return eol_;
  }

  template <class InputIterator, class Letter>
  typename Window<InputIterator, Letter>::iterator_t
  Window<InputIterator, Letter>::begin() const
  {
    return begin_;
  }

  template <class InputIterator, class Letter>
  typename Window<InputIterator, Letter>::iterator_t
  Window<InputIterator, Letter>::stream() const
  {
    return stream_;
  }

  template <class InputIterator, class Letter>
  typename Window<InputIterator, Letter>::iterator_t
  Window<InputIterator, Letter>::end() const
  {
    return end_;
  }

  template <class InputIterator, class Letter>
  size_t
  Window<InputIterator, Letter>::offset() const
  {
    return stream_ - begin_;
  }

  template <class InputIterator, class Letter>
  typename Window<InputIterator, Letter>::length_t
  Window<InputIterator, Letter>::length() const
  {
    return length_;
  }

  template <class InputIterator, class Letter>
  typename Window<InputIterator, Letter>::string_t
  Window<InputIterator, Letter>::window() const
  {
    return string_t (stream_, stream_ + size_);
  }

  template <class InputIterator, class Letter>
  void
  Window<InputIterator, Letter>::compute_size()
  {
    size_ = 0;
    while ((size_ < length_) &&
	   (stream_ + size_ != end_) &&
	   (stream_[size_] != eol_))
      ++size_;
  }

  template <class InputIterator, class Letter>
  std::ostream&
  operator << (std::ostream& ostr, const Window<InputIterator, Letter>& w)
  {
    return w.print(ostr);
  }

  /** @} */

} // utility

#endif // ! VCSN_MISC_WINDOW_HXX
