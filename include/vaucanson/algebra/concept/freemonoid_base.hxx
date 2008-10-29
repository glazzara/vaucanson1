// freemonoid_base.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The Vaucanson
// Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGEBRA_CONCEPT_FREEMONOID_BASE_HXX
# define VCSN_ALGEBRA_CONCEPT_FREEMONOID_BASE_HXX

# include <vaucanson/algebra/concept/freemonoid_base.hh>
# include <vaucanson/misc/escaper.hh>

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

  } // ! algebra

  /*-------------------------------------.
  | MetaElement<FreeMonoidBase<Self>, T> |
  `-------------------------------------*/

  template <class Self, typename T>
  size_t
  MetaElement<algebra::FreeMonoidBase<Self>, T>::length() const
  {
    return op_size(this->structure(), this->value());
  }

  template <class Self, typename T>
  void
  MetaElement<algebra::FreeMonoidBase<Self>, T>::mirror()
  {
    op_in_mirror(this->structure(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::begin()
  {
    return op_begin(this->structure(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::const_iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::begin() const
  {
    return op_begin_const(this->structure(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::reverse_iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::rbegin()
  {
    return op_rbegin(this->structure(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::const_reverse_iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::rbegin() const
  {
    return op_rbegin_const(this->structure(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::end()
  {
    return op_end(this->structure(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::const_iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::end() const
  {
    return op_end_const(this->structure(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::reverse_iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::rend()
  {
    return op_rend(this->structure(), this->value());
  }

  template <class Self, typename T>
  typename MetaElement<algebra::FreeMonoidBase<Self>, T>::const_reverse_iterator
  MetaElement<algebra::FreeMonoidBase<Self>, T>::rend() const
  {
    return op_rend_const(this->structure(), this->value());
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
    return op_parse(dest.structure(), dest.value(), s, i, escaped);
  }

  template<typename S, typename T>
  const std::basic_string<T>&
  op_convert(const algebra::FreeMonoidBase<S>& s,
	     SELECTOR(std::basic_string<T>),
	     const std::basic_string<T>& from_data)
  {
# ifndef VCSN_NDEBUG
    for (typename std::basic_string<T>::const_iterator it = from_data.begin();
	 it != from_data.end();
	 ++it)
      precondition_ (s.alphabet().contains(*it),
		     "The letter " + vcsn::algebra::letter_traits<T>::letter_to_literal(*it) +
		     " is not in the given alphabet");
# else // ! VCSN_NDEBUG
    (void) s;
# endif // ! VCSN_NDEBUG
    return from_data;
  }

  namespace algebra {

    /*------------------.
    | Default Operators |
    `------------------*/

    template <typename S, typename T, typename CharContainer>
    bool op_parse(const algebra::FreeMonoidBase<S>&,
		  T& v,
		  const std::string& s,
		  typename std::string::const_iterator& i,
		  const CharContainer& escaped)
    {
      static_error(no_op_parse_operator_available);
      return false;
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
      return op_rout(s.self(), st, v);
    }

  } // ! algebra

} // ! vcsn

#endif // ! VCSN_ALGEBRA_CONCEPT_FREEMONOID_BASE_HXX
