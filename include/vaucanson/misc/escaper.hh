// escaper.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_MISC_ESCAPER_HH
# define VCSN_MISC_ESCAPER_HH

/**
 * @file escaper.hh
 *
 * Declarations of the escaper class and related functions.
 * @see utility::escaper.
 * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
 */

# include <set>

# include <vaucanson/misc/iomanip.hh>

namespace utility
{

  /**
   * IO Manipulator to escape some characters when displaying them.
   *
   * It is often desirable when printing words to escape some
   * particular characters. As an example, when printing a rational
   * expression, the <b>word</b> "foo+bar" (where '+' is a letter from
   * the alphabet) should be printed "foo\+bar".
   *
   * This manipulator allow an user to do so. When used on a stream
   * using an << operator, the argument of type T held by this
   * manipulator is displayed as if its << operator had been called,
   * but with some characters escaped.
   *
   * By default the escaped characters are those returned by
   * vcsn::tools::usual_escaped_characters(). You may control those
   * characters using the ::utility::setesc manipulator.
   *
   * @see make_escaper(), setesc, getesc(), iomanip,
   *      vcsn::tools::usual_escaped_characters().
   * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
   */
  template <class T>
  struct escaper : public iomanip< escaper<T> >
  {
    explicit
    escaper(const T& w);
    std::ostream& operator () (std::ostream& ostr) const;
  protected:
    const T& w_;
  };

  /**
   * Build an escaper.
   *
   * @see escaper, setesc, getesc(), iomanip.
   * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
   */
  template <class T>
  escaper<T>
  make_escaper(const T& w);

  /**
   * IO Manipulator to set the characters that need to be escaped.
   *
   * This manipulator allow an user to control the characters that
   * need to be escaped by the escaper manipulator.
   *
   * @see escaper, getesc(), iomanip.
   * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
   */
  struct setesc : public iomanip<setesc>
  {
    setesc(const std::set<char>& s);
    std::ostream& operator () (std::ostream& ostr) const;
  protected:
    const std::set<char>& s_;
  };

  /**
   * Retrieve the escaped characters set of a stream.
   *
   * @see escaper, setesc, iomanip.
   * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
   */
  std::set<char>& getesc(std::ostream& ostr);

} // End of namespace utility.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/misc/escaper.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_MISC_ESCAPER_HH
