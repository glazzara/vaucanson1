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


#ifndef ALGEBRA_ALPHABETS_BASE_HXX
# define ALGEBRA_ALPHABETS_BASE_HXX

# include <vaucanson/config/system.hh>
# include <vaucanson/algebra/concept/alphabets_base.hh>
# include <vaucanson/misc/container_ops.hh>
# include <vaucanson/misc/random.hh>

namespace vcsn {

  namespace algebra {

    /*--------------------.
      | AlphabetSetBase<Self> |
      `--------------------*/

    template<class Self>
    AlphabetSetBase<Self>::AlphabetSetBase()
    {}

    template<class Self>
    AlphabetSetBase<Self>::AlphabetSetBase(const AlphabetSetBase& other) 
    {}

  } // algebra

  using namespace algebra;
  
  /*------------------------------------.
    | MetaElement<AlphabetSetBase<Self>, T> |
    `------------------------------------*/
  // Meta-information about element formed from an AlphabetSetBase
  // structuring element.
    
  template<class Self, typename T>
  size_t 
  MetaElement<AlphabetSetBase<Self>, T>::size() const
  { 
    return op_size(this->set(), this->value()); 
  }
    
  template<class Self, typename T>
  bool 
  MetaElement<AlphabetSetBase<Self>, T>::contains(const letter_t& l) const
  { 
    return op_contains_e(this->set(), this->value(), l); 
  }
    
  template<class Self, typename T>
  bool 
  MetaElement<AlphabetSetBase<Self>, T>::is_finite() const
  { 
    return op_is_finite(this->set(), this->value()); 
  }
    
  template<class Self, typename T>
  typename MetaElement<AlphabetSetBase<Self>, T>::iterator 
  MetaElement<AlphabetSetBase<Self>, T>::begin() 
  { 
    return op_begin(this->set(), this->value()); 
  }
    
  template<class Self, typename T> 
  typename MetaElement<AlphabetSetBase<Self>, T>::const_iterator 
  MetaElement<AlphabetSetBase<Self>, T>::begin() const
  { 
    return op_begin_const(this->set(), this->value()); 
  }
    
  template<class Self, typename T>
  typename MetaElement<AlphabetSetBase<Self>, T>::iterator 
  MetaElement<AlphabetSetBase<Self>, T>::end() 
  { 
    return op_end(this->set(), this->value()); 
  }
    
  template<class Self, typename T>
  typename MetaElement<AlphabetSetBase<Self>, T>::const_iterator 
  MetaElement<AlphabetSetBase<Self>, T>::end() const
  { 
    return op_end(this->set(), this->value()); 
  }
    
  template<class Self, typename T>
  void 
  MetaElement<AlphabetSetBase<Self>, T>::insert(const letter_t& l) 
  { 
    op_insert(this->set(), this->value(), l); 
  }

  template<class Self, typename T>
  bool
  MetaElement<AlphabetSetBase<Self>, T>::letter_equality(letter_t lhs, 
							 letter_t rhs) const
  { 
    return op_letter_equality_modulo(this->set(), this->value(), lhs, rhs);
  }
    
  template<class Self, typename T>
  typename alphabet_traits<Self, T>::letter_t
  MetaElement<AlphabetSetBase<Self>, T>::choose() const
  { 
    assert (this->is_finite() && this->size() > 0);
    int  n = this->size();
    int  c = ((unsigned) floor(((float) rand() / (float) RAND_MAX) * n));

    const_iterator it = this->begin();

    for (int k = 0; k < c; ++k)
      ++it;

    return *it;
  }

  template <class Self, typename T>
  typename alphabet_traits<Self, T>::letter_t
  MetaElement<AlphabetSetBase<Self>, T>::random_letter() const
  {
    return
      misc::RandomGenerator<typename alphabet_traits<Self, T>::letter_t>
      ::do_it();
  }


  template<class Self, typename T>
  MetaElement<AlphabetSetBase<Self>, T>::MetaElement() 
  {}
    
  template<class Self, typename T>
  MetaElement<AlphabetSetBase<Self>, T>::MetaElement(const MetaElement& other) :
    MetaElement<Structure<Self>, T>(other)
  {}

  template <typename Self, typename T, typename L>
  bool op_letter_equality_modulo(const AlphabetSetBase<Self>& s, 
				 const T& a, 
				 L lhs,
				 L rhs)
  {
    return lhs == rhs;
  }
  
  template<typename Self, typename St, typename T>
  St& op_rout(const AlphabetSetBase<Self>& s, St& st, const T& a)
  {
    st << "{ ";
    if (op_is_finite(s.self(), a))
      for (typename op_begin_traits<Self, T>::const_ret_t i = op_begin(s.self(), a);
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

#endif // ALGEBRA_ALPHABETS_BASE_HXX
