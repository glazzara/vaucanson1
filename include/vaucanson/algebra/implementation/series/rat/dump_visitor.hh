// dump_visitor.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DUMP_VISITOR_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DUMP_VISITOR_HH

# include <ostream>
# include <string>
# include <set>

# include <vaucanson/algebra/implementation/series/rat/exp.hh>
# include <vaucanson/misc/iomanip.hh>

namespace vcsn
{

  namespace rat
  {

    /// Flags to indicate how to print a rational expression.
    enum print_mode_t
      {
	MODE_NONE	= 0x0,	///<<  a+b+c, a.b.c, 2 a, a 2, a*
	MODE_ADD	= 0x1,	///<<  ((a+b)+c)
	MODE_MUL	= 0x2,	///<<  ((a.b).c)
	MODE_STAR	= 0x4,	///<<  (a)*
	MODE_RWEIGHT	= 0x8,  ///<<  (2 a)
	MODE_LWEIGHT	= 0x10, ///<<  (a 2)
	MODE_WEIGHT	= 0x18, ///<<  ((2 a) 2), (2 (a 2))
	MODE_ALL	= 0x1F	///<<  ((a+b)+c), ((a.b).c), ...
      };

    /// Printing of a rational expression.
    template <class Word, class Weight>
    std::ostream&
    operator << (std::ostream& ostr, const exp<Word, Weight>& e);

    /// Manipulator to set the print mode of a rational expression.
    struct setpm : public misc::iomanip<setpm>
    {
      setpm (print_mode_t mode);
      std::ostream& operator () (std::ostream& ostr) const;
    protected:
      print_mode_t mode_;
    };

    /// Retrieve the print mode of a stream.
    print_mode_t getpm(const std::ostream& ostr);

    /// Manipulator to set the representation of the null series.
    struct setzero : public misc::iomanip<setzero>
    {
      setzero(const std::string& zero);
      std::ostream& operator () (std::ostream& ostr) const;
    protected:
      const std::string& z_;
    };

    /// Manipulator to set the representation of the identity series.
    struct setid : public misc::iomanip<setid>
    {
      setid(const std::string& id);
      std::ostream& operator () (std::ostream& ostr) const;
    protected:
      const std::string& i_;
    };

  } // End of namespace rat.

} // End of namespace vcsn.

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/series/rat/dump_visitor.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DUMP_VISITOR_HH
