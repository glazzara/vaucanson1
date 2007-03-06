// random.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_RANDOM_HH
# define VCSN_MISC_RANDOM_HH

/**
 * @file random.hh
 * Definition of random generators.
 */

# include <vaucanson/algebra/implementation/letter/range.hh>
# include <vaucanson/algebra/implementation/semiring/rational_number.hh>

namespace vcsn {
  namespace misc {

    /// The namespace for the random generation tools.
    namespace random {

      /** @addtogroup misc *//** @{ */

      /// Generate a random value.
      template<typename T>
      T generate ();

      /** Generate a random value between bounds.
       * This function returns a value between @c min
       * and @c max (inclusive).
       */
      template<typename T>
      T generate (T min, T max);


      /// Generate a random character.
      template<>
      char generate<char> ();

      /// Generate a random character between bounds.
      template<>
      char generate<char> (char min, char max);

      /// Generate a random lowercase letter.
      char generate_letter ();

      /// Generate a random digit.
      char generate_digit ();

      /// Generate a random Boolean.
      template<>
      bool generate<bool> ();

      /// Generate a random integer.
      template<>
      int generate<int> ();

      /// Generate a random integer between two bounds.
      template<>
      int generate<int> (int min, int max);

      /// Generate a random unsigned integer.
      template<>
      unsigned generate<unsigned> ();

      /// Generate a random unsigned between two bounds.
      template<>
      unsigned generate<unsigned> (unsigned min, unsigned max);

      /// Generate a random float between -2 and 2.
      template<>
      float generate<float> ();

      /// Generate a random float between min and max.
      template<>
      float generate<float> (float min, float max);

      /// Generate a random double between -2 and 2.
      template<>
      double generate<double> ();

      /// Generate a random double between min and max.
      template<>
      double generate<double> (double min, double max);

      /// Generate of n sample from a range to an output iterator.
      template <class InputIterator, class OutputIterator>
      void sample_n (InputIterator first, InputIterator end,
		     OutputIterator out, unsigned n);

      /// Generate a random rational number.
      template<>
      vcsn::algebra::RationalNumber generate<vcsn::algebra::RationalNumber> ();

      /**
       * Generates a bounded random rational number.
       *
       * Both fractions are first brought to the same denominator. Then,
       * the  maximum	of  the	 denominator  and   both  numerators  is
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
      std::pair<char, int> generate<std::pair<char, int> > ();

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
      generate<small_alpha_letter_t> ();
      /** @} */

      /** @} */

    }
  } // end of namespace misc.
} // end of namespace vcsn.


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/misc/random.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_MISC_RANDOM_HH
