// numerical_semiring.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and
// Regis-Gianas.
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


#ifndef ALGEBRA_NUMERICAL_SEMIRING_HH
# define ALGEBRA_NUMERICAL_SEMIRING_HH

# include <vaucanson/algebra/concept/numerical_semiring.hh>

namespace vcsn {

  template<typename T>
  bool op_contains(const algebra::NumericalSemiring& s, T c);

  template<typename T, typename U>
  void op_in_mul(const algebra::NumericalSemiring& s1, T& dst, U arg);

  template<typename T, typename U>
  void op_in_add(const algebra::NumericalSemiring& s1, T& dst, U arg);

  template<typename T, typename U>
  T op_mul(const algebra::NumericalSemiring& s, T a, U b);

  template<typename T, typename U>
  T op_add(const algebra::NumericalSemiring& s, T a, U b);

  template<typename T>
  T identity_value(SELECTOR(algebra::NumericalSemiring), SELECTOR(T));
    
  template<typename T>
  T zero_value(SELECTOR(algebra::NumericalSemiring), SELECTOR(T));

  template <class T>
  Element<algebra::NumericalSemiring, T>
  op_choose(const algebra::NumericalSemiring& s, SELECTOR(T));

  /*-----------------------------.
  | specializations for integers |
  `-----------------------------*/

  bool
  op_can_choose_non_stareable(const algebra::NumericalSemiring& set, SELECTOR(int));

  Element<algebra::NumericalSemiring, int>
  op_choose_stareable(const algebra::NumericalSemiring& set, SELECTOR(int));
  
  Element<algebra::NumericalSemiring, int> 
  op_choose_non_stareable(const algebra::NumericalSemiring& set, SELECTOR(int));

  /*-----------------------------.
  | specializations for booleans |
  `-----------------------------*/
  template<typename T>
  inline void op_in_mul(const algebra::NumericalSemiring& s1,
			bool& dst, bool src);
  
  inline bool op_mul(const algebra::NumericalSemiring& s, bool a, bool b);
  
  inline void op_in_add(const algebra::NumericalSemiring& s1,
			bool& dst, bool src);
  
  inline bool op_add(const algebra::NumericalSemiring& s, bool a, bool b);
  
  inline bool identity_value(SELECTOR(algebra::NumericalSemiring), 
			     SELECTOR(bool));
  
  inline bool zero_value(SELECTOR(algebra::NumericalSemiring), 
			 SELECTOR(bool));
  
  inline bool op_stareable(const algebra::NumericalSemiring& s, bool b);
  
  inline void op_in_star(const algebra::NumericalSemiring& s, bool& b);

  Element<algebra::NumericalSemiring, bool>
  op_choose_stareable(const algebra::NumericalSemiring& set, SELECTOR(bool));
  
  Element<algebra::NumericalSemiring, bool> 
  op_choose_non_stareable(const algebra::NumericalSemiring& set, SELECTOR(bool));

  /*-------------------------.
  | goodies for real numbers |
  `-------------------------*/
  template<typename T>
  bool op_stareable(const algebra::NumericalSemiring& s, T v);
  
  inline bool op_stareable(const algebra::NumericalSemiring& s, 
				  const float& f);

   inline bool op_stareable(const algebra::NumericalSemiring& s, 
				  const double& f);

   inline void op_in_star(const algebra::NumericalSemiring& s, float& f);

   inline void op_in_star(const algebra::NumericalSemiring& s, double& f);

  bool
  op_can_choose_non_stareable(const algebra::NumericalSemiring& set,
			      SELECTOR(float));

  Element<algebra::NumericalSemiring, float>
  op_choose_stareable(const algebra::NumericalSemiring& set, SELECTOR(float));
  
  Element<algebra::NumericalSemiring, float> 
  op_choose_non_stareable(const algebra::NumericalSemiring& set, SELECTOR(float));

} // vcsn

# include <vaucanson/algebra/concrete/semiring/numerical_semiring.hxx>

#endif // ALGEBRA_NUMERICAL_SEMIRING_HH


