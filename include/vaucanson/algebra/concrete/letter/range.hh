// range.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCRETE_LETTER_RANGE_HH
# define VCSN_ALGEBRA_CONCRETE_LETTER_RANGE_HH

namespace vcsn {

  namespace algebra {

    template <class T, class Interval>
    class static_ranged
    {
    public:
      static_ranged();
      static_ranged(const T& v);
      static_ranged(const static_ranged& r);
      operator T() const;
      static_ranged	randomized();
      T&		value();
      const T&		value() const;

      // FIXME: add operator++ !!! It should loop from 'begin' to 'to' !

    private:
      T	       value_;
    };
    
    template <char From, char To>
    struct static_char_interval
    {
      static bool check(char c);
      static char from();
      static char to();
      static char random();
    };

    // FIXME: op_leq may be more adapted.
    template <class T, class Interval>
    bool operator<(const static_ranged<T, Interval>& lhs, 
		   const static_ranged<T, Interval>& rhs);

    template <class T, class Interval>
    bool operator==(const static_ranged<T, Interval>& lhs, 
		    const static_ranged<T, Interval>& rhs);

    template <class Stream, class T, class Interval>
    Stream& operator<<(Stream& s, static_ranged<T, Interval>& sr)
    {
      s << sr.value ();
      return s;
    }

  } // algebra

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algebra/concrete/letter/range.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_ALGEBRA_CONCRETE_LETTER_RANGE_HH
