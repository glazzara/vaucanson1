// escaper.hxx: this file is part of the Vaucanson project.
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
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_MISC_ESCAPER_HXX
# define VCSN_MISC_ESCAPER_HXX

/**
 * @file escaper.hxx
 *
 * Definitions of the escaper class and related functions.
 * @see utility::escaper.
 * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
 */

# include <string>
# include <sstream>

# include <vaucanson/misc/escaper.hh>
# include <vaucanson/tools/usual_escaped_characters.hh>

namespace utility
{

  /// Get the index in the internal extensible array for escaped characters.
  inline
  int
  escaped()
  {
    static const int idx = std::ios::xalloc();
    return idx;
  }

  /*--------.
  | escaper |
  `--------*/

  template <class T>
  escaper<T>::escaper(const T& w) : w_ (w)
  {
  }

  template <class T>
  std::ostream&
  escaper<T>::operator () (std::ostream& ostr) const
  {
    std::ostringstream		o;
    o << w_;
    std::string			w = o.str();
    const std::set<char>&	e = getesc(ostr);
    for (std::string::const_iterator i = w.begin(); i != w.end(); ++i)
      if (e.find(*i) != e.end())
	ostr << "\\" << *i;
      else
	ostr << *i;
    return ostr;
  }

  /*-------------.
  | make_escaper |
  `-------------*/

  template <class T>
  escaper<T>
  make_escaper(const T& w)
  {
    return escaper<T> (w);
  }

  /*-------.
  | setesc |
  `-------*/

  inline
  setesc::setesc(const std::set<char>& s) : s_ (s)
  {
  }

  inline
  std::ostream&
  setesc::operator () (std::ostream& ostr) const
  {
    typedef std::set<char>	esc_set;
    const int			idx = escaped();

    if (not ostr.pword(idx))
      ostr.register_callback(pword_delete<esc_set>, idx);
    else
      delete static_cast<esc_set*> (ostr.pword(idx));
    ostr.pword(idx) = new esc_set (s_);
    return ostr;
  }

  /*-------.
  | getesc |
  `-------*/

  inline
  std::set<char>& getesc(std::ostream& ostr)
  {
    const int idx = escaped();

    if (not ostr.pword(idx))
      ostr << setesc (vcsn::tools::usual_escaped_characters());
    return *static_cast<std::set<char>*> (ostr.pword(idx));
  }

} // End of namespace utility.

#endif // ! VCSN_MISC_ESCAPER_HXX
