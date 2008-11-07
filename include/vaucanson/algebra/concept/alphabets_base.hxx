// alphabets_base.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The
// Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCEPT_ALPHABETS_BASE_HXX
# define VCSN_ALGEBRA_CONCEPT_ALPHABETS_BASE_HXX

# include <vaucanson/algebra/concept/alphabets_base.hh>
# include <vaucanson/misc/random.hh>
# include <vaucanson/misc/contract.hh>
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
    return op_size(this->structure(), this->value());
  }

  template<typename S, typename T>
  size_t
  MetaElement<algebra::AlphabetSetBase<S>, T>::max_size() const
  {
    return op_max_size(this->structure(), this->value());
  }

  template<typename S, typename T>
  bool
  MetaElement<algebra::AlphabetSetBase<S>, T>::contains(const letter_t& l) const
  {
    return op_contains_e(this->structure(), this->value(), l);
  }

  template<typename S, typename T>
  bool
  MetaElement<algebra::AlphabetSetBase<S>, T>::is_finite() const
  {
    return op_is_finite(this->structure(), this->value());
  }

  template<typename S, typename T>
  typename MetaElement<algebra::AlphabetSetBase<S>, T>::iterator
  MetaElement<algebra::AlphabetSetBase<S>, T>::begin()
  {
    return op_begin(this->structure(), this->value());
  }

  template<typename S, typename T>
  typename MetaElement<algebra::AlphabetSetBase<S>, T>::const_iterator
  MetaElement<algebra::AlphabetSetBase<S>, T>::begin() const
  {
    return op_begin_const(this->structure(), this->value());
  }

  template<typename S, typename T>
  typename MetaElement<algebra::AlphabetSetBase<S>, T>::iterator
  MetaElement<algebra::AlphabetSetBase<S>, T>::end()
  {
    return op_end(this->structure(), this->value());
  }

  template<typename S, typename T>
  typename MetaElement<algebra::AlphabetSetBase<S>, T>::const_iterator
  MetaElement<algebra::AlphabetSetBase<S>, T>::end() const
  {
    return op_end_const(this->structure(), this->value());
  }

  template<typename S, typename T>
  void
  MetaElement<algebra::AlphabetSetBase<S>, T>::insert(const letter_t& l)
  {
    op_insert(this->structure(), this->value(), l);
  }

  template<typename S, typename T>
  void
  MetaElement<algebra::AlphabetSetBase<S>, T>::insert(const std::string& lit)
  {
    op_insert(this->structure(), this->value(), algebra::letter_traits<letter_t>::literal_to_letter(lit).second);
  }

  template<typename S, typename T>
  bool
  MetaElement<algebra::AlphabetSetBase<S>, T>::letter_equality(letter_t lhs,
							       letter_t rhs) const
  {
    return op_letter_equality(this->structure(), this->value(), lhs, rhs);
  }

  template<typename S, typename T>
  typename algebra::alphabet_traits<S, T>::letter_t
  MetaElement<algebra::AlphabetSetBase<S>, T>::choose() const
  {
    // FIXME: recommendation(overload this operator)
    precondition (is_finite());
    precondition (size() > 0);

    int  nr = misc::random::generate<int>(0, size() - 1);

    const_iterator it = begin();
    for (int k = 0; k < nr; ++k)
      ++it;

    return *it;
  }

  template <class S, typename T>
  typename algebra::alphabet_traits<S, T>::letter_t
  MetaElement<algebra::AlphabetSetBase<S>, T>::random_letter() const
  {
    return misc::random::generate
      <typename algebra::alphabet_traits<S, T>::letter_t>();
  }

  template<typename S, typename T>
  MetaElement<algebra::AlphabetSetBase<S>, T>::MetaElement()
  {}

  template<typename S, typename T>
  MetaElement<algebra::AlphabetSetBase<S>, T>::MetaElement(const MetaElement& other) :
    MetaElement<Structure<S>, T>(other)
  {}

  namespace algebra
  {

    template <typename S, typename L>
    L op_parse(const AlphabetSetBase<S>&,
	       const std::string&,
	       size_t&)
    {
      static_error(no_op_parse_operator_available);
      return 0;
    }

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
	for (typename op_begin_traits<S, T>::const_ret_t i = op_begin_const(s.self(), a);
	     i != op_end_const(s.self(), a);
	     ++i)
	  {
	    if (i != op_begin_const(s.self(), a))
	      st << ", ";
	    st << *i;
	  }
      else
	st << "<many letters>";
      st << " }";
      return st;
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_CONCEPT_ALPHABETS_BASE_HXX
