// freemonoid_base.hxx
//
// $Id$
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

#ifndef ALGEBRA_FREEMONOID_BASE_HXX
# define ALGEBRA_FREEMONOID_BASE_HXX

# include <vaucanson/algebra/concept/freemonoid_base.hh>

namespace vcsn {

  namespace algebra {

    /*---------------------.
    | FreeMonoidBase<Self> |
    `---------------------*/
    template<class Self>
    typename FreeMonoidBase<Self>::alphabet_t& 
    FreeMonoidBase<Self>::alphabet() 
    { 
      return self().alphabet(); 
    }
    
    template<class Self>
    const typename FreeMonoidBase<Self>::alphabet_t& 
    FreeMonoidBase<Self>::alphabet() const
    { 
      return self().alphabet(); 
    }
    
    template<class Self>
    FreeMonoidBase<Self>::FreeMonoidBase() 
    {}
    
    template<class Self>
    FreeMonoidBase<Self>::FreeMonoidBase(const FreeMonoidBase& m) :
      MonoidBase<Self>(m)
    {}

  } // algebra 

  using namespace algebra;

    /*-------------------------------------.
    | MetaElement<FreeMonoidBase<Self>, T> |
    `-------------------------------------*/
    template<class Self, typename T>
    size_t 
    MetaElement<FreeMonoidBase<Self>, T>::length() const
    { 
      return op_size(this->set(), this->value()); 
    }

    template<class Self, typename T>
    void
    MetaElement<FreeMonoidBase<Self>, T>::mirror()
    {
      op_in_mirror(this->set(), this->value());
    }

    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::iterator 
    MetaElement<FreeMonoidBase<Self>, T>::begin() 
    { 
      return op_begin(this->set(), this->value()); 
    }
    
    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::const_iterator 
    MetaElement<FreeMonoidBase<Self>, T>::begin() const
    { 
      return op_begin_const(this->set(), this->value()); 
    }
    
    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::reverse_iterator 
    MetaElement<FreeMonoidBase<Self>, T>::rbegin()
    { 
      return op_rbegin(this->set(), this->value()); 
    }
    
    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::const_reverse_iterator 
    MetaElement<FreeMonoidBase<Self>, T>::rbegin() const
    { 
      return op_rbegin(this->set(), this->value()); 
    }
    
    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::iterator 
    MetaElement<FreeMonoidBase<Self>, T>::end() 
    { 
      return op_end(this->set(), this->value()); 
    }
    
    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::const_iterator 
    MetaElement<FreeMonoidBase<Self>, T>::end() const
    { 
      return op_end(this->set(), this->value()); 
    }
    
    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::reverse_iterator 
    MetaElement<FreeMonoidBase<Self>, T>::rend()
    { 
      return op_rend(this->set(), this->value()); 
    }
    
    template<class Self, typename T>
    typename MetaElement<FreeMonoidBase<Self>, T>::const_reverse_iterator 
    MetaElement<FreeMonoidBase<Self>, T>::rend() const
    { 
      return op_rend(this->set(), this->value()); 
    }

    template<class Self, typename T>
    MetaElement<FreeMonoidBase<Self>, T>::MetaElement() 
    {}
    
    template<class Self, typename T>
    MetaElement<FreeMonoidBase<Self>, T>::MetaElement(const MetaElement& o) :
      MetaElement<MonoidBase<Self>, T>(o)
    {}

    /*-------------------.
    | External functions |
    `-------------------*/

    template<typename S, typename T>
    Element<S, T>
    mirror(const Element<S, T>& e)
    {
      Element<S, T>	ret(e);
      ret.mirror();
      return ret;
    }
    
    template<typename Self, typename T>
    void 
    op_in_mirror(const FreeMonoidBase<Self>& s, T& v)
    {
      const T		new_v(v);
      typename MetaElement<FreeMonoidBase<Self>, T>::iterator  it 
	= op_begin(s.self(), v);

      for (typename MetaElement<FreeMonoidBase<Self>, T>::
	     const_reverse_iterator i = op_rbegin(s.self(), new_v);
	   i != op_rend(s.self(), new_v);
	   ++i)
	*it++ = *i;
    }

    template<typename Self, typename T>
    bool 
    op_contains(const FreeMonoidBase<Self>& s, const T& v)
    { 
      typedef typename op_begin_traits<Self, T>::const_ret_t const_iterator;

      for (const_iterator i = op_begin(s.self(), v);
	   i != op_end(s.self(), v);
	   ++i)
	if (! s.alphabet().contains(*i))
	  return false;
      return true;
    }

    template<typename Self, typename St, typename T>
    St& 
    op_rout(const FreeMonoidBase<Self>& s,
	    St& st, 
	    const T& v)
    {
      typedef typename op_begin_traits<Self, T>::const_ret_t const_iterator;
      
      for (const_iterator i = op_begin_const(s.self(), v);
	   i != op_end(s.self(), v);
	   ++i)
	st << *i;
      return st;
    }

} // vcsn

#endif // ALGEBRA_FREEMONOID_BASE_HXX
