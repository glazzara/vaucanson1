// concepts.hxx
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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


#ifndef ALGEBRA_CONCEPTS_HXX
# define ALGEBRA_CONCEPTS_HXX

#include <vaucanson/fundamental/fundamental.hh>

#include <vaucanson/misc/type_constraints.hh>
#include <vaucanson/misc/misc_constraints.hh>

#include <vaucanson/algebra/concept/alphabets_base.hh>
    
namespace vcsn
{
  namespace algebra
  {
    /*----------.
    | Alphabets |
    `----------*/

    

    template<typename S, typename T> 
    void AlphabetsConcept<S, T>::constraints() 
      {
	// FIXME: add comments here.

	(void)check_inheritance();
	(void)check_elt_inheritance();

	using namespace utility::concepts;
	//	function_requires<vcsn::StructureConcept<S, T> >();

	typedef typename elt_t::letter_t required;

	function_requires<DefaultConstructible<required> >();
	function_requires<CopyConstructible<required> >();
	function_requires<Assignable<required> >();
	
	(void)check_is_finite(a);

	// FIXME: add constraints on iterators
	(void)check_begin(a);
	(void)check_end(a);
	(void)check_contains(a, required());
	(void)check_size(a);
      }

    template<typename S, typename T> 
    AlphabetsBase<S>& AlphabetsConcept<S, T>::check_inheritance()     
    { 
      return s; 
    }

    template<typename S, typename T> 
    MetaElement<AlphabetsBase<S>, T>&
    AlphabetsConcept<S, T>::check_elt_inheritance() 
    { 
      return a; 
    }

    template<typename S, typename T>
    bool AlphabetsConcept<S, T>::check_is_finite(const Element<S, T>& a)
    { 
      return a.is_finite(); 
    }

    template<typename S, typename T>
    typename Element<S, T>::const_iterator 
    AlphabetsConcept<S, T>::check_begin(const elt_t& a)
    { 
      return a.begin(); 
    }
	
    template<typename S, typename T>	      
    typename Element<S, T>::const_iterator
    AlphabetsConcept<S, T>::check_end(const Element<S, T>& a)
    { 
      return a.end(); 
    }

    template<typename S, typename T>
    size_t AlphabetsConcept<S, T>::check_size(const Element<S, T>& a)
    { 
      return a.size(); 
    }

    template<typename S, typename T>
    bool AlphabetsConcept<S, T>::check_contains(const Element<S, T>& a, 
						const typename Element<S, T>::letter_t& l)
    { 
      return a.contains(l); 
    }

  } // algebra
} // vcsn


#include <vaucanson/algebra/concept/semigroup_base.hh>

namespace vcsn
{
  namespace algebra
  {

    /*------------------.
    | Semigroup concept |
    `------------------*/


    // mul_kind

    template<typename S, typename T>
    void SemigroupConcept<S, T, mul_kind>::constraints()
    {
      using namespace utility::concepts;
      //	function_requires<AlgebraicStructureConcept<S, T> >();

      function_requires<InplaceMultipliable<elt_t> >();
      function_requires<Multipliable<elt_t> >();
      function_requires<InplaceMultipliable<elt_t, T> >();
      function_requires<Multipliable<elt_t, elt_t, T> >();
      function_requires<Multipliable<elt_t, T, elt_t> >();

      (void)check_inheritance();
      (void)check_elt_inheritance();

    }

    template<typename S, typename T>
    SemigroupBase<S>&			
    SemigroupConcept<S, T, mul_kind>::check_inheritance()     
    { 
      return s; 
    }
    
    template<typename S, typename T>
    MetaElement<SemigroupBase<S>, T>& 
    SemigroupConcept<S, T, mul_kind>::check_elt_inheritance() 
    { 
      return elt; 
    }


    // add_kind

    
    template<typename S, typename T>	
    void SemigroupConcept<S, T, add_kind>::constraints()
    {
      using namespace utility::concepts;
      //	function_requires<AlgebraicStructureConcept<S, T> >();
      
      function_requires<InplaceAddable<elt_t> >();
      function_requires<Addable<elt_t> >();
      function_requires<InplaceAddable<elt_t, T> >();
      function_requires<Addable<elt_t, elt_t, T> >();
      function_requires<Addable<elt_t, T, elt_t> >();
      
      (void)check_inheritance();
      (void)check_elt_inheritance();  
    }

    template<typename S, typename T>
    SemigroupBase<S>&			
    SemigroupConcept<S, T, add_kind>::check_inheritance()     
    { 
      return s; 
    }
      
    template<typename S, typename T>
    MetaElement<SemigroupBase<S>, T>& 
    SemigroupConcept<S, T, add_kind>::check_elt_inheritance() 
    {
      return elt;
    }

	
  }
}

#include <vaucanson/algebra/concept/monoid_base.hh>

namespace vcsn
{
  namespace algebra
  {

    /*---------------.
    | Monoid concept |
    `---------------*/


      template<typename S, typename T, typename kind>
      void MonoidConcept<S, T, kind>::constraints()
      {
	using namespace utility::concepts;
	function_requires<SemigroupConcept<S, T, kind> >();

	(void)check_constant(kind());
	(void)check_elt_constant(s, kind());

	(void)check_inheritance();
	(void)check_elt_inheritance();


      }

      template<typename S, typename T, typename kind>
      MonoidBase<S>&		       
      MonoidConcept<S, T, kind>::check_inheritance()     
      { 
	return s;
      }

      template<typename S, typename T, typename kind>
      MetaElement<MonoidBase<S>, T>&	
      MonoidConcept<S, T, kind>::check_elt_inheritance() 
      { 
	return elt;
      }

      template<typename S, typename T, typename kind>
      T MonoidConcept<S, T, kind>::check_constant(mul_kind k)
      { 
	return identity_value(SELECT(S), SELECT(T)); 
      }

      template<typename S, typename T, typename kind>
      T MonoidConcept<S, T, kind>::check_constant(add_kind k)
      {
	return zero_value(SELECT(S), SELECT(T)); 
      }

      template<typename S, typename T, typename kind>
      Element<S, T> 
      MonoidConcept<S, T, kind>::check_elt_constant(const S& s, mul_kind k)
      {
	return s.identity(SELECT(T));
      }

      template<typename S, typename T, typename kind>
      Element<S, T> 
      MonoidConcept<S, T, kind>::check_elt_constant(const S& s, add_kind k)
      {
	return s.zero(SELECT(T)); 
      }

  }
}

#include <vaucanson/algebra/concept/bimonoid_base.hh>

namespace vcsn
{
  namespace algebra
  {

    /*-----------------.
    | Bimonoid concept |
    `-----------------*/

    
      template<typename S, typename T>
      void BimonoidConcept<S, T>::constraints()
      {
	using namespace utility::concepts;

	typedef typename S::lmonoid_t required_lmonoid_t;
	typedef typename S::rmonoid_t required_rmonoid_t;

	(void)check_lmonoid(s);
	(void)check_rmonoid(s);
	// FIXME: add checks for non-const monoid() and weights().
	// note: these checks are not written (yet) but the methods
	// are mandatory according to the concept.


	typedef typename elt_t::lmonoid_elt_t lmonoid_elt_t;
	typedef typename elt_t::lmonoid_value_t lmonoid_value_t;
	function_requires<MonoidConcept<
	  required_lmonoid_t,
	  lmonoid_value_t,
	  typename MetaSet<required_lmonoid_t>::semigroup_kind> >();
	  	  
	typedef typename elt_t::rmonoid_elt_t rmonoid_elt_t;
	typedef typename elt_t::rmonoid_value_t rmonoid_value_t;
	function_requires<MonoidConcept<
	  required_rmonoid_t,
	  rmonoid_value_t,
	  typename MetaSet<required_rmonoid_t>::semigroup_kind> >();


	function_requires<MonoidConcept<S, T, typename MetaSet<S>::semigroup_kind> >();

	(void)check_left();
	(void)check_right();
	(void)check_left_value();
	(void)check_right_value();

      }

      template<typename S, typename T>
      BimonoidBase<S>& 
      BimonoidConcept<S, T>::check_inheritance()
      {
	return s; 
      }

      template<typename S, typename T>
      MetaElement<BimonoidBase<S>, T>&	
      BimonoidConcept<S, T>::check_elt_inheritance() 
      {
	return elt; 
      }

      template<typename S, typename T>
      const typename S::lmonoid_t& 
      BimonoidConcept<S, T>::check_lmonoid(const S& s)
      {
	return s.lmonoid(); 
      }

      template<typename S, typename T>
      const typename S::rmonoid_t& 
      BimonoidConcept<S, T>::check_rmonoid(const S& s)
      {
	return s.rmonoid(); 
      }

      template<typename S, typename T>
      Element<typename S::lmonoid_t, typename Element<S, T>::lmonoid_value_t>
      BimonoidConcept<S, T>::check_left()
      {
	return elt.left(); 
      }

      template<typename S, typename T>
      Element<typename S::rmonoid_t, typename Element<S, T>::rmonoid_value_t>
      BimonoidConcept<S, T>::check_right()
      { 
	return elt.right(); 
      }

      template<typename S, typename T>
      typename Element<S, T>::lmonoid_value_t& 
      BimonoidConcept<S, T>::check_left_value()
      {
	return elt.left_value(); 
      }

      template<typename S, typename T>
      typename Element<S, T>::rmonoid_value_t&
      BimonoidConcept<S, T>::check_right_value()
      {
	return elt.right_value(); 
      }


  }
}



#include <vaucanson/algebra/concept/freemonoid_base.hh>

namespace vcsn
{
  namespace algebra
  {

    /*--------------------.
    | Free monoid concept |
    `--------------------*/

    
      template<typename S, typename T, typename kind>
      void FreeMonoidConcept<S, T, kind>::constraints()
      {
	using namespace utility::concepts;
	function_requires<MonoidConcept<S, T, kind> >();

	(void)check_inheritance();
	(void)check_elt_inheritance();

	typedef typename S::alphabet_t required;
	function_requires<AlphabetsConcept<
	  typename required::set_t,
	  typename required::value_t> >();

	(void)check_alphabet(elt);

	typedef typename required::letter_t required2;
	function_requires<SameType<required2, typename S::letter_t> >();

	function_requires<Assignable<elt_t, required2> >();
	function_requires<Convertible<required2, elt_t > >();
	function_requires<InplaceMultipliable<elt_t, required2> >();
	function_requires<Multipliable<elt_t, elt_t, required2> >();
	function_requires<Multipliable<elt_t, required2, elt_t> >();

	(void)check_length(elt);
	(void)check_begin(elt);
	(void)check_rbegin(elt);
	(void)check_end(elt);
	(void)check_rend(elt);
	// fixme: check that iterators dereference to letter_t

      }

      template<typename S, typename T, typename kind>
      FreeMonoidBase<S>& 
      FreeMonoidConcept<S, T, kind>::check_inheritance()
      {
	return s; 
      }

      template<typename S, typename T, typename kind>
      MetaElement<FreeMonoidBase<S>, T>& 
      FreeMonoidConcept<S, T, kind>::check_elt_inheritance() 
      { 
	return elt; 
      }

      template<typename S, typename T, typename kind>
      const typename S::alphabet_t&
      FreeMonoidConcept<S, T, kind>::check_alphabet(const Element<S, T>& elt)
      {
	return elt.set().alphabet(); 
      }

      template<typename S, typename T, typename kind>
      size_t FreeMonoidConcept<S, T, kind>::check_length(const Element<S, T>& e)
      {
	return e.length(); 
      }

      template<typename S, typename T, typename kind>
      typename Element<S, T>::const_iterator 
      FreeMonoidConcept<S, T, kind>::check_begin(const Element<S, T>& e)
      {
	return e.begin(); 
      }

      template<typename S, typename T, typename kind>
      typename Element<S, T>::const_iterator 
      FreeMonoidConcept<S, T, kind>::check_end(const Element<S, T>& e)
      {
	return e.end(); 
      }

      template<typename S, typename T, typename kind>
      typename Element<S, T>::const_reverse_iterator 
      FreeMonoidConcept<S, T, kind>::check_rbegin(const Element<S, T>& e)
      {
	return e.rbegin(); 
      }

      template<typename S, typename T, typename kind>
      typename Element<S, T>::const_reverse_iterator 
      FreeMonoidConcept<S, T, kind>::check_rend(const Element<S, T>& e)
      {
	return e.rend(); 
      }

  }
}

#include <vaucanson/algebra/concept/semiring_base.hh>

namespace vcsn
{
  namespace algebra
  {

    /*-----------------.
    | Semiring concept |
    `-----------------*/

    template<typename S, typename T>
    void SemiringConcept<S,T>::constraints()
    {
      using namespace utility::concepts;
	function_requires<MonoidConcept<S, T, mul_kind> >();

	// a semiring is also a commutative monoid for the addition,
	// but (unfortunately) we have no way to test commutativity here.
	function_requires<MonoidConcept<S, T, add_kind> >();

	(void)check_in_stareable(elt);
	(void)check_stareable(elt);
	(void)check_in_star();
	(void)check_star(elt);

	(void)check_inheritance();
	(void)check_elt_inheritance();

      }

      template<typename S, typename T>
      Element<S, T>& SemiringConcept<S,T>::check_in_star()
      {
	return elt.star(); 
      }

      template<typename S, typename T>
      Element<S, T> SemiringConcept<S,T>::check_star(const Element<S, T>& elt)
      {
	return star(elt); 
      }

      template<typename S, typename T>
      bool SemiringConcept<S,T>::check_in_stareable(const Element<S, T>& elt)
      {
	return elt.stareable(); 
      }

      template<typename S, typename T>
      bool SemiringConcept<S,T>::check_stareable(const Element<S, T>& elt)
      {
	return stareable(elt); 
      }

      template<typename S, typename T>
      SemiringBase<S>& 
      SemiringConcept<S,T>::check_inheritance()     
      {
	return s;
      }

      template<typename S, typename T>
      MetaElement<SemiringBase<S>, T>& 
      SemiringConcept<S,T>::check_elt_inheritance()
      {
	return elt; 
      }

  }
}

#include <vaucanson/algebra/concept/series_base.hh>

namespace vcsn
{
  namespace algebra
  {

    /*---------------.
    | Series concept |
    `---------------*/

   
      template<typename S, typename T>
      void SeriesConcept<S, T>::constraints()
      {
	using namespace utility::concepts;
	function_requires<SemiringConcept<S, T> >();

	typedef typename S::monoid_t		required_monoid_t;
	typedef typename S::weights_t		required_weights_t;

	(void)check_monoid(s);
	(void)check_weights(s);
	// FIXME: add checks for non-const monoid() and weights().
	// note: these checks are not written (yet) but the methods
	// are mandatory according to the concept.


	typedef typename elt_t::monoid_elt_t		monoid_elt_t;
	typedef typename elt_t::monoid_value_t		monoid_value_t;
	function_requires<MonoidConcept<
	  typename monoid_elt_t::set_t,
	  monoid_value_t,
	  mul_kind> >();
	  	  
	typedef typename elt_t::weight_t		weight_t;
	typedef typename elt_t::weights_value_t		weights_value_t;
	function_requires<SemiringConcept<
	  typename weight_t::set_t,
	  weights_value_t> >();

	function_requires<InplaceMultipliable<elt_t, weight_t> >();
	function_requires<Multipliable<elt_t, elt_t, weight_t> >();
	function_requires<Multipliable<elt_t, weight_t, elt_t> >();
	function_requires<Convertible<weight_t, elt_t> >();
	function_requires<Assignable<elt_t, weight_t> >();
	function_requires<InplaceAddable<elt_t, weight_t> >();
	function_requires<Addable<elt_t, elt_t, weight_t> >();
	function_requires<Addable<elt_t, weight_t, elt_t> >();

	function_requires<Convertible<monoid_elt_t, elt_t> >();
	function_requires<Assignable<elt_t, monoid_elt_t> >();
	function_requires<InplaceAddable<elt_t, monoid_elt_t> >();
	function_requires<Addable<elt_t, elt_t, monoid_elt_t> >();
	function_requires<Addable<elt_t, monoid_elt_t, elt_t> >();

	(void)check_is_finite_app(elt);
	(void)check_get(elt, monoid_elt_t());
	(void)check_value_get(elt, monoid_value_t());

	// on mutable finite applications, you can also use
	// set() and value_set(). 
	// FIXME: check them.

      }

      template<typename S, typename T>
      SeriesBase<S>& 
      SeriesConcept<S, T>::check_inheritance()     
      { 
	return s; 
      }

      template<typename S, typename T>
      MetaElement<SeriesBase<S>, T>& 
      SeriesConcept<S, T>::check_elt_inheritance() 
      { 
	return elt; 
      }

      template<typename S, typename T>
      typename Element<S, T>::weight_t 
      SeriesConcept<S, T>::check_get(const Element<S, T>& elt, 
				     const typename Element<S, T>::monoid_elt_t& m)
      { 
	return elt.get(m); 
      }

      template<typename S, typename T>
      typename Element<S, T>::weights_value_t 
      SeriesConcept<S, T>::check_value_get(const Element<S, T>& elt, 
					   const typename Element<S, T>::monoid_value_t& w)
      { 
	return elt.value_get(w); 
      }

      template<typename S, typename T>
      const typename S::monoid_t& 
      SeriesConcept<S, T>::check_monoid(const S& s)
      { 
	return s.monoid(); 
      }

      template<typename S, typename T>
      const typename S::weights_t& 
      SeriesConcept<S, T>::check_weights(const S& s)
      { 
	return s.weights(); 
      }

      template<typename S, typename T>
      bool SeriesConcept<S, T>::check_is_finite_app(const Element<S, T>& elt)
      { 
	return elt.is_finite_app(); 
      }

  } // algebra
} // vcsn


#endif
