// concepts.hh
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


#ifndef ALGEBRA_CONCEPTS_HH
# define ALGEBRA_CONCEPTS_HH

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
    struct AlphabetsConcept
    {
      typedef Element<S, T>	elt_t;

      S		s; 
      T		v;
      elt_t	a;

      void constraints();

      AlphabetsBase<S>& 
      check_inheritance();

      MetaElement<AlphabetsBase<S>, T>& 
      check_elt_inheritance();

      bool check_is_finite(const elt_t& a);

      typename elt_t::const_iterator
      check_begin(const elt_t& a);
			      
      typename elt_t::const_iterator
      check_end(const elt_t& a);

      size_t check_size(const elt_t& a);

      bool check_contains(const elt_t& a, 
			  const typename elt_t::letter_t& l);

    };

  }
}


#include <vaucanson/algebra/concept/semigroup_base.hh>

namespace vcsn
{
  namespace algebra
  {

    /*------------------.
    | Semigroup concept |
    `------------------*/

    template<typename S, typename T, typename kind>
    struct SemigroupConcept
    {};

    template<typename S, typename T>
    struct SemigroupConcept<S, T, mul_kind>
    {
      typedef Element<S, T> elt_t;
     
      elt_t	elt;
      S		s;

      void constraints();

      SemigroupBase<S>&		        check_inheritance();
      MetaElement<SemigroupBase<S>, T>& check_elt_inheritance();
    };

    template<typename S, typename T>
    struct SemigroupConcept<S, T, add_kind>
    {
      typedef Element<S, T> elt_t;

      elt_t elt;
      S s;

      void constraints();

      SemigroupBase<S>&			check_inheritance();
      MetaElement<SemigroupBase<S>, T>& check_elt_inheritance();
    };
	
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
    struct MonoidConcept
    { 
      S s;
      Element<S, T> elt;

      void constraints();

      MonoidBase<S>&			check_inheritance();
      MetaElement<MonoidBase<S>, T>&	check_elt_inheritance();

      T check_constant(mul_kind k);
      T check_constant(add_kind k);

      Element<S, T> check_elt_constant(const S& s, mul_kind k);
      Element<S, T> check_elt_constant(const S& s, add_kind k);

    };


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
    struct FreeMonoidConcept
    {
      typedef Element<S, T> elt_t;

      elt_t elt;

      S s;

      void constraints();
     
      FreeMonoidBase<S>&		 check_inheritance();
      MetaElement<FreeMonoidBase<S>, T>& check_elt_inheritance();

      const typename S::alphabet_t&
      check_alphabet(const elt_t& elt);

      size_t check_length(const elt_t& e);

      typename elt_t::const_iterator 
      check_begin(const elt_t& e);

      typename elt_t::const_iterator 
      check_end(const elt_t& e);

      typename elt_t::const_reverse_iterator 
      check_rbegin(const elt_t& e);

      typename elt_t::const_reverse_iterator 
      check_rend(const elt_t& e);

    };
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
    struct SemiringConcept
    {
      S s;
      typedef Element<S, T> elt_t;
      elt_t elt;

      void constraints();

      elt_t& check_in_star();
      elt_t check_star(const elt_t& elt);

      bool check_in_stareable(const elt_t& elt);
      bool check_stareable(const elt_t& elt);

      SemiringBase<S>&			check_inheritance();
      MetaElement<SemiringBase<S>, T>&  check_elt_inheritance();

    };


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
    struct SeriesConcept
    {
      S s;
      typedef Element<S, T> elt_t;
      elt_t elt;

      void constraints();

      SeriesBase<S>&			check_inheritance();
      MetaElement<SeriesBase<S>, T>&	check_elt_inheritance();

      typename elt_t::weight_t check_get(const elt_t& elt, 
					 const typename elt_t::monoid_elt_t& m);
      typename elt_t::weights_value_t 
      check_value_get(const elt_t& elt, const typename elt_t::monoid_value_t& w);


      const typename S::monoid_t& check_monoid(const S& s);
      const typename S::weights_t& check_weights(const S& s);

      bool check_is_finite_app(const elt_t& elt);

    };
  } // algebra
} // vcsn

# include <vaucanson/algebra/concept/concepts.hxx>

#endif
