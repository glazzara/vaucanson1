// dump_visitor.hh: this file is part of the Vaucanson project.
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
    struct setpm : public utility::iomanip<setpm>
    {
      setpm (print_mode_t mode);
      std::ostream& operator () (std::ostream& ostr) const;
    protected:
      print_mode_t mode_;
    };

    /// Retrieve the print mode of a stream.
    print_mode_t getpm(const std::ostream& ostr);

    /// Manipulator to set the representation of the null series.
    struct setzero : public utility::iomanip<setzero>
    {
      setzero(const std::string& zero);
      std::ostream& operator () (std::ostream& ostr) const;
    protected:
      const std::string& z_;
    };

    /// Manipulator to set the representation of the identity series.
    struct setid : public utility::iomanip<setid>
    {
      setid(const std::string& id);
      std::ostream& operator () (std::ostream& ostr) const;
    protected:
      const std::string& i_;
    };

  } // End of namespace rat.

} // End of namespace vcsn.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/implementation/series/rat/dump_visitor.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DUMP_VISITOR_HH
