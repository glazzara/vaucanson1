// freemonoid_base.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_CONCEPT_FREEMONOID_BASE_HXX
# define VCSN_ALGEBRA_CONCEPT_FREEMONOID_BASE_HXX

# include <vaucanson/algebra/concept/freemonoid_base.hh>

namespace vcsn {

  namespace algebra {

    /*---------------------.
    | FreeMonoidBase<Self> |
    `---------------------*/
    template <class Self>
    typename FreeMonoidBase<Self>::alphabet_t&
    FreeMonoidBase<Self>::alphabet()
    {
      return this->self().alphabet();
    }

    template <class Self>
    const typename FreeMonoidBase<Self>::alphabet_t&
    FreeMonoidBase<Self>::alphabet() const
    {
      return this->self().alphabet();
    }

    template <class Self>
    FreeMonoidBase<Self>::FreeMonoidBase()
    {}

    template <class Self>
    FreeMonoidBase<Self>::FreeMonoidBase(const FreeMonoidBase& m) :
      MonoidBase<Self>(m)
    {}

  } // algebra

  /*-------------------------------------.
  | MetaElement<FreeMonoidBase<Self>, T> |
  `-------------------------------------*/
  template <class Self, typename T>
  size_t
  MetaElement<algebra::FreeMonoidBase<Self>, T>::length() const
  {
    return op_size(this->set(), this->value());
  }

  template <class Self, typename T>
  void
  MetaElement<algebra::FreeMonoidBase<Self>, T>::mirror()
  {
    op_in_mirror(this->set(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::begin()
  {
    return op_begin(this->set(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::const_iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::begin() const
  {
    return op_begin_const(this->set(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::reverse_iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::rbegin()
  {
    return op_rbegin(this->set(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::const_reverse_iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::rbegin() const
  {
    return op_rbegin_const(this->set(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::end()
  {
    return op_end(this->set(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::const_iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::end() const
  {
    return op_end_const(this->set(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::reverse_iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::rend()
  {
    return op_rend(this->set(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::const_reverse_iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::rend() const
  {
    return op_rend_const(this->set(), this->value());
  }

  template <class Self, typename T>
  MetaElement<algebra::FreeMonoidBase<Self>, T>::MetaElement() :
    MetaElement<algebra::MonoidBase<Self>, T>()
  {}

  template <class Self, typename T>
  MetaElement<algebra::FreeMonoidBase<Self>, T>::MetaElement(const MetaElement& o)  :
    MetaElement<algebra::MonoidBase<Self>, T>(o)
  {}

  /*-------------------.
  | External functions |
  `-------------------*/

  template <typename S, typename T>
  Element<S, T>
  mirror(const Element<S, T>& e)
  {
    Element<S, T>	ret(e);
    ret.mirror();
    return ret;
  }

  template <typename S, typename T, typename CharContainer>
  bool
  parse_word(Element<S, T>& dest,
	     const std::string& s,
	     typename std::string::const_iterator& i,
	     const CharContainer& escaped)
  {
    return op_parse(dest.set(), dest.value(), s, i, escaped);
  }

  // default implementation of word parsing assumes the fact that
  // an alphabet letter can be constructed from a 'char'.
  // specialized this function according to your alphabet if this
  // is not the case.
  template <typename S, typename T, typename CharContainer>
  bool op_parse(const algebra::FreeMonoidBase<S>& set, T& v,
		const std::string& s,
		typename std::string::const_iterator& i,
		const CharContainer& escaped)
  {
    typename std::string::const_iterator j = i;
    typename std::string::const_iterator k;

    while ((i != s.end()) &&
           ((*i == '\\') || (set.alphabet().contains(*i) &&
	   (std::find(escaped.begin(), escaped.end(), *i) == escaped.end()))))
      if (*i == '\\')
	{
	  k = i;
	  ++k;
	  if (k != s.end())
	    i = k;
	  if (not set.alphabet().contains(*i))
	    return (i != j);
	  v += *i;
	  ++i;
	}
      else
	{
	  v += *i;
	  ++i;
	}
    return (i != j);
  }

  template <typename Self, typename T>
  void
  op_in_mirror(const algebra::FreeMonoidBase<Self>& s, T& v)
  {
    const T		new_v(v);
    typename MetaElement<algebra::FreeMonoidBase<Self>, T>::iterator  it
      = op_begin(s.self(), v);

    for (typename MetaElement<algebra::FreeMonoidBase<Self>, T>::
	   const_reverse_iterator i = op_rbegin_const(s.self(), new_v);
	 i != op_rend_const(s.self(), new_v);
	 ++i)
      *it++ = *i;
  }

  template <typename Self, typename T>
  bool
  op_contains(const algebra::FreeMonoidBase<Self>& s, const T& v)
  {
    typedef typename op_begin_traits<Self, T>::const_ret_t const_iterator;

    for (const_iterator i = op_begin_const(s.self(), v);
	 i != op_end_const(s.self(), v);
	 ++i)
      if (! s.alphabet().contains(*i))
	return false;
    return true;
  }

  template <typename Self, typename St, typename T>
  St&
  op_rout(const algebra::FreeMonoidBase<Self>& s,
	  St& st,
	  const T& v)
  {
    typedef typename op_begin_traits<Self, T>::const_ret_t const_iterator;

    for (const_iterator i = op_begin_const(s.self(), v);
	 i != op_end_const(s.self(), v);
	 ++i)
      st << *i;
    return st;
  }

} // vcsn

#endif // VCSN_ALGEBRA_CONCEPT_FREEMONOID_BASE_HXX
