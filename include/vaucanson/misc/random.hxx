// random.hxx: this file is part of the Vaucanson project.
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
//
#ifndef VCSN_MISC_RANDOM_HXX
# define VCSN_MISC_RANDOM_HXX

# include <vaucanson/algebra/concrete/alphabets/predefs.hh>
# include <vaucanson/misc/random.hh>
# include <vaucanson/misc/limits.hh>

# include <cmath>
# include <cstdlib>
# include <vector>

namespace utility {
  namespace random {

    template<>
    inline char generate<char>()
    {
      // We do not want any 0, because it could generate errors in strings.
      return char (1 + unsigned(rand()) % ((1 << (sizeof(char) * 8)) - 1));
    }

    template<>
    inline char generate<char>(char min, char max)
    {
      unsigned range = unsigned(max - min) + 1;
      return char(min + rand() % range);
    }

    inline char generate_letter()
    {
      return generate<char>('a', 'z');
    }

    inline char generate_digit()
    {
      return generate<char>('0', '9');
    }

    template<>
    inline bool generate<bool>()
    {
      return static_cast<bool>(rand() & 1);
    }

    template<>
    inline int generate<int>()
    {
      return rand() % utility::limits<int>::max();
    }

    template<>
    inline int generate<int>(int min, int max)
    {
      unsigned range = unsigned(max - min) + 1;
      return min + rand() % range;
    }

    template<>
    inline unsigned generate<unsigned>()
    {
      return rand() % utility::limits<unsigned>::max();
    }

    template<>
    inline unsigned generate<unsigned>(unsigned min, unsigned max)
    {
      unsigned range = unsigned(max - min) + 1;
      return min + rand() % range;
    }

    template<>
    inline float generate<float>()
    {
      // This formula comes from the caml stdlib.
      return ((static_cast<float> (rand()) / RAND_MAX +
	       static_cast<float> (rand())) / RAND_MAX +
	      static_cast<float> (rand())) / RAND_MAX;
    }

    template<>
    inline double generate<double>()
    {
      return ((static_cast<double> (rand()) / RAND_MAX +
	       static_cast<double> (rand())) / RAND_MAX +
	      static_cast<double> (rand())) / RAND_MAX;
    }

    template <class Iterator, class OutputIterator>
    void sample_n(Iterator first, Iterator end,
		  OutputIterator out, unsigned n)
    {
      std::vector<int> from;
      for (Iterator i = first; i != end; ++i)
	  from.push_back(*i);

      while ((from.size () > 0) && (n > 0))
	{
	  int  c = generate<int>(0, from.size() - 1);
	  *out = from[c];
	  ++out;
	  from.erase(from.begin() + c);
	  --n;
	}
    }

    template<>
    inline
    vcsn::algebra::RationalNumber
    generate<vcsn::algebra::RationalNumber>()
    {
      const int num = generate<int>();
      const unsigned denom =
	generate<unsigned>(1, utility::limits<unsigned>::max());
      return vcsn::algebra::RationalNumber(num, denom);
    }

    /**
     * Generates a bounded random rational number.
     *
     * Both fractions are first brought to the same denominator. Then,
     * the  maximum   of  the  denominator  and   both  numerators  is
     * taken. With this number, we work  out a ratio, which is used to
     * have a larger range of choice for our new fraction.
     */
    template<>
    inline
    vcsn::algebra::RationalNumber
    generate<vcsn::algebra::RationalNumber>
    (const vcsn::algebra::RationalNumber min,
     const vcsn::algebra::RationalNumber max)
    {
      const int denom = vcsn::algebra::lcm(min.denom(), max.denom());
      const int num1 = min.num()*denom/min.denom();
      const int num2 = max.num()*denom/max.denom();
      const int maxi = std::max(std::max(abs(num1), abs(num2)),denom);
      const int ratio = (utility::limits<int>::max()-1)/maxi;
      return
	vcsn::algebra::RationalNumber(generate<int>(num1*ratio, num2*ratio),
				      denom * ratio);
    }

    template <>
    inline
    std::pair<char, int> generate<std::pair<char, int> >()
    {
      return std::make_pair(generate<char>(), generate<int>());
    }

    template <>
    inline
    vcsn::algebra::small_alpha_letter::Letter
    generate<vcsn::algebra::small_alpha_letter::Letter>()
    {
      return generate<char>('a', 'z');
    }

  } // Random

} // vcsn

#endif // VCSN_MISC_RANDOM_HXX
