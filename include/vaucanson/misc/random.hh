// random.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_RANDOM_HH
# define VCSN_MISC_RANDOM_HH

namespace utility {

  /// the namespace for the random generation tools 
  namespace random {

    /** @addtogroup utility *//** @{ */

    /// Generate a random value
    template<typename T>
    T generate();

    /** Generate a random value between bounds.
     * This function returns a value between @c min 
     * and @c max (inclusive).
     */
    template<typename T>
    T generate(T min, T max);
    

    /// Generate a random character
    template<>
    inline char generate<char>();

    /// Generate a random character between bounds
    template<>
    inline char generate<char>(char min, char max);

    /// Generate a random lowercase letter
    inline char generate_letter();

    /// Generate a random digit
    inline char generate_digit();

    /// Generate a random Boolean
    template<>
    inline bool generate<bool>();

    /// Generate a random integer
    template<>
    inline int generate<int>();

    /// Generate a random integer between two bounds
    template<>
    inline int generate<int>(int min, int max);

    /// Generate a random float between 0 and 1
    template<>
    inline float generate<float>();
    
    // Generate of n sample from a range to an output iterator.
    template <class InputIterator, class OutputIterator>
    void sample_n(InputIterator first, InputIterator end, 
		  OutputIterator out, unsigned n);


    /** @} */

  }
}

#include <vaucanson/misc/random.hxx>

#endif // VCSN_MISC_RANDOM_HH
