//  numerical_semiring.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and
//  Regis-Gianas.
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
  | specializations for integers |
  `-----------------------------*/

  inline
  bool
  op_can_choose_non_stareable(const NumericalSemiring& set,
			      SELECTOR(int))
  {
    return true; // Every integer excepted Zero is non-stareable
  }

  inline
  Element<NumericalSemiring, int>
  op_choose_stareable(const NumericalSemiring& set, SELECTOR(int))
  {
    // 0 is the only one integer to be stareable. So we have no choice !
    return 0;
  }
  
  inline
  Element<NumericalSemiring, int> 
  op_choose_non_stareable(const NumericalSemiring& set, SELECTOR(int))
  {
    // We want anything but 0.
    int r;

    do
      r = op_choose(set, SELECT(int));
    while (r == 0);
    return r;
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

  inline
  Element<NumericalSemiring, bool>
  op_choose_stareable(const NumericalSemiring& set, SELECTOR(bool))
  {
    // Every boolean is stareable !
    return op_choose(set, SELECT(bool));
  }
  
  inline
  Element<NumericalSemiring, bool> 
  op_choose_non_stareable(const NumericalSemiring& set, SELECTOR(bool))
  {
    assert(! "Cannot choose non-stareable boolean: that does not exist");
    return false;
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

  inline
  bool
  op_can_choose_non_stareable(const NumericalSemiring& set,
			      SELECTOR(float))
  {
    return true; // Every float which is less than 0 or greater than 1 is
		 // non-stareable.
  }

  inline
  Element<NumericalSemiring, float>
  op_choose_stareable(const NumericalSemiring& set, SELECTOR(float))
  {
    return misc::RandomGenerator<float>::do_it(true);
  }
  
  inline
  Element<NumericalSemiring, float> 
  op_choose_non_stareable(const NumericalSemiring& set, SELECTOR(float))
  {
    float r;
    do
      r = misc::RandomGenerator<float>::do_it();
    while ((0.0 <= r) && (r < 1.0));
    return r;
  }

  // FIXME: add some more operators as syntactic sugar

} // vcsn

#endif // ALGEBRA_NUMERICAL_SEMIRING_HXX


