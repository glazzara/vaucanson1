// random.hh: this file is part of the Vaucanson project.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_MISC_RANDOM_HH
# define VCSN_MISC_RANDOM_HH

# include <vaucanson/algebra/concrete/letter/range.hh>
# include <vaucanson/algebra/concrete/semiring/rational_number.hh>

namespace utility {

  /// The namespace for the random generation tools.
  namespace random {

    /** @addtogroup utility *//** @{ */

    /// Generate a random value.
    template<typename T>
    T generate();

    /** Generate a random value between bounds.
     * This function returns a value between @c min
     * and @c max (inclusive).
     */
    template<typename T>
    T generate(T min, T max);


    /// Generate a random character.
    template<>
    char generate<char>();

    /// Generate a random character between bounds.
    template<>
    char generate<char>(char min, char max);

    /// Generate a random lowercase letter.
    char generate_letter();

    /// Generate a random digit.
    char generate_digit();

    /// Generate a random Boolean.
    template<>
    bool generate<bool>();

    /// Generate a random integer.
    template<>
    int generate<int>();

    /// Generate a random integer between two bounds.
    template<>
    int generate<int>(int min, int max);

    /// Generate a random unsigned integer.
    template<>
    unsigned generate<unsigned>();

    /// Generate a random unsigned between two bounds.
    template<>
    unsigned generate<unsigned>(unsigned min, unsigned max);

    /// Generate a random float between -2 and 2.
    template<>
    float generate<float>();

    /// Generate a random float between min and max.
    template<>
    float generate<float>(float min, float max);

    /// Generate a random double between -2 and 2.
    template<>
    double generate<double>();

    /// Generate a random double between min and max.
    template<>
    double generate<double>(double min, double max);
    
    /// Generate of n sample from a range to an output iterator.
    template <class InputIterator, class OutputIterator>
    void sample_n(InputIterator first, InputIterator end,
		  OutputIterator out, unsigned n);

    /// Generate a random rational number.
    template<>
    vcsn::algebra::RationalNumber generate<vcsn::algebra::RationalNumber>();

    /**
     * Generates a bounded random rational number.
     *
     * Both fractions are first brought to the same denominator. Then,
     * the  maximum   of  the  denominator  and   both  numerators  is
     * taken. With this number, we work  out a ratio, which is used to
     * have a larger range of choice for our new fraction.
     */
    template<>
    vcsn::algebra::RationalNumber
    generate<vcsn::algebra::RationalNumber>
    (const vcsn::algebra::RationalNumber min,
     const vcsn::algebra::RationalNumber max);

    /// Generate a random std::pair<char, int>.
    template <>
    std::pair<char, int> generate<std::pair<char, int> >();

    /// @name Small alphabetic letters random generation tools.
    /** @{ */
    typedef
    vcsn::algebra::static_char_interval<'a', 'z'>
    small_alpha_interval_t;

    typedef
    vcsn::algebra::static_ranged<char, small_alpha_interval_t>
    small_alpha_letter_t;

    /// Generates a random small alphabetic letter.
    template <>
    small_alpha_letter_t
    generate<small_alpha_letter_t>();
    /** @} */

    /** @} */

  }
}


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/misc/random.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // VCSN_MISC_RANDOM_HH
