//  numerical_semiring.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifndef ALGEBRA_NUMERICAL_SEMIRING_HXX
# define ALGEBRA_NUMERICAL_SEMIRING_HXX

# include <vaucanson/algebra/concept/semiring_base.hh>
# include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>
# include <vaucanson/misc/random.hh>
# include <vaucanson/misc/numerical_constraints.hh>

namespace vcsn {

  template<typename T>
  bool op_contains(const NumericalSemiring& s, T c)
  { 
    using namespace utility::concepts;

    function_requires<HasLimits<T> >();
    return true; 
  }

  template<typename T, typename U>
  void op_in_mul(const NumericalSemiring& s1,
		 T& dst, U arg)
  { 
    dst *= arg; 
  }

  template<typename T, typename U>
  void op_in_add(const NumericalSemiring& s1,
		 T& dst, U arg)
  { 
    dst += arg; 
  }

  // FIXME: there should be specializations of op_add_traits and
  // op_mul_traits giving the type of the result depending on the
  // type of the arguments. 

  template<typename T, typename U>
  T op_mul(const NumericalSemiring& s, T a, U b)
  { 
    return a * b; 
  }

  template<typename T, typename U>
  T op_add(const NumericalSemiring& s, T a, U b)
  { 
    return a + b; 
  }

  template<typename T>
  T identity_value(SELECTOR(NumericalSemiring), SELECTOR(T))
  { 
    return T(1); 
  }
    
  template<typename T>
  T zero_value(SELECTOR(NumericalSemiring), SELECTOR(T))
  { 
    return T(0); 
  }

  template <class T>
  Element<NumericalSemiring, T>
  op_choose(const NumericalSemiring& s, SELECTOR(T))
  {
    return misc::RandomGenerator<T>::do_it();
  }

  /*-----------------------------.
  | specializations for booleans |
  `-----------------------------*/
  template<typename T>
  inline void op_in_mul(const NumericalSemiring& s1,
			bool& dst, bool src)
  { 
    dst = dst && src; 
  }

  inline bool op_mul(const NumericalSemiring& s, bool a, bool b)
  { 
    return a && b; 
  }

  inline void op_in_add(const NumericalSemiring& s1,
			bool& dst, bool src)
  { 
    dst = dst || src; 
  }

  inline bool op_add(const NumericalSemiring& s, bool a, bool b)
  { 
    return a || b; 
  }

  inline bool identity_value(SELECTOR(NumericalSemiring), 
			     SELECTOR(bool))
  { 
    return true; 
  }

  inline bool zero_value(SELECTOR(NumericalSemiring), SELECTOR(bool))
  { 
    return false; 
  }

  inline bool op_stareable(const NumericalSemiring& s, bool b)
  { 
    return true; 
  }

  inline void op_in_star(const NumericalSemiring& s, bool& b)
  { 
    b = true; 
  }

  /*--------------------------------------------.
  | specialization for floating point numbers.  |
  `--------------------------------------------*/

  template<typename T>
  bool op_stareable(const NumericalSemiring& s, T v)
  { 
    return v == 0; 
  }

  inline bool op_stareable(const NumericalSemiring& s, 
			   const float& f)
  { 
    return (0.0 <= f) && (f < 1.0); 
  }

  inline bool op_stareable(const NumericalSemiring& s, 
			   const double& f)
  { 
    return (0.0 <= f) && (f < 1.0); 
  }

  inline void op_in_star(const NumericalSemiring& s, float& f)
  { 
    if (f < 1.0)
      f = (1.0 / (1.0 - f));
    else
      f = std::numeric_limits<float>::infinity();
  }

  inline void op_in_star(const NumericalSemiring& s, double& f)
  { 
    if (f < 1.0)
      f = (1.0 / (1.0 - f));
    else
      assert(! "star not defined.");
  }

  // FIXME: add some more operators as syntactic sugar

} // vcsn

#endif // ALGEBRA_NUMERICAL_SEMIRING_HXX


