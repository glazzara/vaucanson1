// numerical_semiring.hh
//
// $Id$
// VCSN_HEADER

#ifndef ALGEBRA_NUMERICAL_SEMIRING_HH
# define ALGEBRA_NUMERICAL_SEMIRING_HH

# include <vaucanson/algebra/concept/numerical_semiring.hh>
# include <vaucanson/misc/numerical_constraints.hh>

namespace vcsn {

  template<typename T>
  bool op_contains(const NumericalSemiring& s, T c);

  template<typename T, typename U>
  void op_in_mul(const NumericalSemiring& s1, T& dst, U arg);

  template<typename T, typename U>
  void op_in_add(const NumericalSemiring& s1, T& dst, U arg);

  template<typename T, typename U>
  T op_mul(const NumericalSemiring& s, T a, U b);

  template<typename T, typename U>
  T op_add(const NumericalSemiring& s, T a, U b);

  template<typename T>
  T identity_value(SELECTOR(NumericalSemiring), SELECTOR(T));
    
  template<typename T>
  T zero_value(SELECTOR(NumericalSemiring), SELECTOR(T));

  template <class T>
  Element<NumericalSemiring, T>
  op_choose(const NumericalSemiring& s, SELECTOR(T));
  
  /*-----------------------------.
  | specializations for booleans |
  `-----------------------------*/
  template<typename T>
  inline void op_in_mul(const NumericalSemiring& s1,
			bool& dst, bool src);
  
  inline bool op_mul(const NumericalSemiring& s, bool a, bool b);
  
  inline void op_in_add(const NumericalSemiring& s1,
			bool& dst, bool src);
  
  inline bool op_add(const NumericalSemiring& s, bool a, bool b);
  
  inline bool identity_value(SELECTOR(NumericalSemiring), 
			     SELECTOR(bool));
  
  inline bool zero_value(SELECTOR(NumericalSemiring), 
			 SELECTOR(bool));
  
  inline bool op_stareable(const NumericalSemiring& s, bool b);
  
  inline void op_in_star(const NumericalSemiring& s, bool& b);
  
      
  /*-------------------------.
    | goodies for real numbers |
    `-------------------------*/
  template<typename T>
  bool op_stareable(const NumericalSemiring& s, T v);

   inline bool op_stareable(const NumericalSemiring& s, 
				  const float& f);

   inline bool op_stareable(const NumericalSemiring& s, 
				  const double& f);

   inline void op_in_star(const NumericalSemiring& s, float& f);

   inline void op_in_star(const NumericalSemiring& s, double& f);

  // TODO: add some more operators as syntactic sugar

} // vcsn

# include <vaucanson/algebra/concrete/semiring/numerical_semiring.hxx>

#endif // ALGEBRA_NUMERICAL_SEMIRING_HH


