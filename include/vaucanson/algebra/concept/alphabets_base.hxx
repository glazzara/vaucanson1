// alphabets_base.hxx
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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


#ifndef VCSN_ALGEBRA_ALPHABETS_BASE_HXX
# define VCSN_ALGEBRA_ALPHABETS_BASE_HXX

# include <vaucanson/algebra/concept/alphabets_base.hh>
# include <vaucanson/misc/random.hh>
# include <cstddef>

namespace vcsn {

  namespace algebra {

    /*-------------------.
    | AlphabetSetBase<S> |
    `-------------------*/

    template<typename S>
    AlphabetSetBase<S>::AlphabetSetBase()
    {}

    template<typename S>
    AlphabetSetBase<S>::AlphabetSetBase(const AlphabetSetBase& other) 
    {}

  } // algebra

  /*-----------------------------------.
  | MetaElement<AlphabetSetBase<S>, T> |
  `-----------------------------------*/
  // Meta-information about element formed from an AlphabetSetBase
  // structuring element.
    
  template<typename S, typename T>
  size_t 
  MetaElement<algebra::AlphabetSetBase<S>, T>::size() const
  { 
    return op_size(set(), value()); 
  }
    
  template<typename S, typename T>
  bool 
  MetaElement<algebra::AlphabetSetBase<S>, T>::contains(const letter_t& l) const
  { 
    return op_contains_e(set(), value(), l); 
  }
    
  template<typename S, typename T>
  bool 
  MetaElement<algebra::AlphabetSetBase<S>, T>::is_finite() const
  { 
    return op_is_finite(set(), value()); 
  }
    
  template<typename S, typename T>
  typename MetaElement<algebra::AlphabetSetBase<S>, T>::iterator 
  MetaElement<algebra::AlphabetSetBase<S>, T>::begin() 
  { 
    return op_begin(set(), value()); 
  }
    
  template<typename S, typename T> 
  typename MetaElement<algebra::AlphabetSetBase<S>, T>::const_iterator 
  MetaElement<algebra::AlphabetSetBase<S>, T>::begin() const
  { 
    return op_begin_const(set(), value()); 
  }
    
  template<typename S, typename T>
  typename MetaElement<algebra::AlphabetSetBase<S>, T>::iterator 
  MetaElement<algebra::AlphabetSetBase<S>, T>::end() 
  { 
    return op_end(set(), value()); 
  }
    
  template<typename S, typename T>
  typename MetaElement<algebra::AlphabetSetBase<S>, T>::const_iterator 
  MetaElement<algebra::AlphabetSetBase<S>, T>::end() const
  { 
    return op_end(set(), value()); 
  }
    
  template<typename S, typename T>
  void 
  MetaElement<algebra::AlphabetSetBase<S>, T>::insert(const letter_t& l) 
  { 
    op_insert(set(), value(), l); 
  }

  template<typename S, typename T>
  bool
  MetaElement<algebra::AlphabetSetBase<S>, T>::letter_equality(letter_t lhs, 
							       letter_t rhs) const
  { 
    return op_letter_equality(set(), value(), lhs, rhs);
  }
    
  template<typename S, typename T>
  typename algebra::alphabet_traits<S, T>::letter_t
  MetaElement<algebra::AlphabetSetBase<S>, T>::choose() const
  {
    // FIXME: recommendation(overload this operator)
 
    assert (is_finite() && size() > 0);
    
    int  nr = ::utility::random::generate<int>(0, size());

    const_iterator it = begin();
    for (int k = 0; k < nr; ++k)
      ++it;

    return *it;
  }

  template <class Self, typename T>
  typename algebra::alphabet_traits<Self, T>::letter_t
  MetaElement<algebra::AlphabetSetBase<Self>, T>::random_letter() const
  {
    return utility::random::generate<typename algebra::alphabet_traits<Self, T>::letter_t>();
  }

  template<typename S, typename T>
  MetaElement<algebra::AlphabetSetBase<S>, T>::MetaElement() 
  {}
    
  template<typename S, typename T>
  MetaElement<algebra::AlphabetSetBase<S>, T>::MetaElement(const MetaElement& other) :
    MetaElement<Structure<S>, T>(other)
  {}

  template <typename S, typename T, typename L>
  bool op_letter_equality(const algebra::AlphabetSetBase<S>& s, 
			  const T& a, 
			  L lhs,
			  L rhs)
  {
    return lhs == rhs;
  }
  
  template<typename S, typename St, typename T>
  St& op_rout(const algebra::AlphabetSetBase<S>& s, St& st, const T& a)
  {
    st << "{ ";
    if (op_is_finite(s.self(), a))
      for (typename op_begin_traits<S, T>::const_ret_t i = op_begin(s.self(), a);
	   i != op_end(s.self(), a);
	   ++i)
	{
	  if (i != op_begin(s.self(), a))
	    st << ", ";
	  st << *i;
	}
    else
      st << "<many letters>";
    st << " }";
    return st;
  }

} // vcsn

#endif // VCSN_ALGEBRA_ALPHABETS_BASE_HXX
