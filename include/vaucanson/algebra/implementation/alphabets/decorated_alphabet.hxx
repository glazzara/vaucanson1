// decorated_alphabet.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_DECORATED_ALPHABET_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_DECORATED_ALPHABET_HXX

# include <vaucanson/algebra/concept/letter.hh>
# include <vaucanson/algebra/implementation/alphabets/decorated_alphabet.hh>

namespace vcsn {

  namespace algebra
  {
    template <typename L, typename T>
    AlphabetDecorator<L, T>::~AlphabetDecorator()
    {
      if (alphabet_owner_)
	delete alphabet_;
    }

    template <typename L, typename T>
    AlphabetDecorator<L, T>::AlphabetDecorator()
    {
      alphabet_ = new T();
      joker_ = letter_traits<L>::default_joker;
      other_ =  letter_traits<L>::default_other;
      alphabet_owner_ = true;
    }

    template <typename L, typename T>
    AlphabetDecorator<L, T>::AlphabetDecorator(alphabet_impl_t& alphabet) :
      alphabet_(&alphabet)
    {
      alphabet_owner_ = false;
      if (std::find(alphabet.begin(), alphabet.end(),
		    letter_traits<L>::default_joker())
	  == alphabet.end())
	joker_ = letter_traits<L>::default_joker();
      else
	{
	  joker_ = letter_traits<L>::default_joker();
	  do {
	    ++joker_;
	    if (joker_ == letter_traits<L>::default_joker())
	      {
		std::cerr << "Did not find a valid 'joker' ! Exiting !"
			  << std::endl;
		exit(EXIT_FAILURE);
	      }
	  } while (std::find(alphabet.begin(), alphabet.end(),
			     joker_) != alphabet.end());
	}
      if (std::find(alphabet.begin(), alphabet.end(),
		    letter_traits<L>::default_other())
	  == alphabet.end())
	other_ = letter_traits<L>::default_other();
      else
	{
	  other_ = letter_traits<L>::default_other();
	  do {
	    ++other_;
	    if (other_ == letter_traits<L>::default_other())
	      {
		std::cerr << "Did not find a valid 'other' ! Exiting !"
			  << std::endl;
		exit(EXIT_FAILURE);
	      }
	  } while (std::find(alphabet.begin(), alphabet.end(),
			     other_) != alphabet.end());
	}
    }

    template <typename L, typename T>
    void
    AlphabetDecorator<L, T>::insert(L l)
    {
      alphabet().insert(l);
    }


    template <typename L, typename T>
    unsigned
    AlphabetDecorator<L, T>::size() const
    {
      return alphabet().size();
    }

    template <typename L, typename T>
    typename AlphabetDecorator<L, T>::iterator
    AlphabetDecorator<L, T>::begin()
    {
      return alphabet().begin();
    }

    template <typename L, typename T>
    typename AlphabetDecorator<L, T>::iterator
    AlphabetDecorator<L, T>::end()
    {
      return alphabet().end();
    }

    template <typename L, typename T>
    typename AlphabetDecorator<L, T>::const_iterator
    AlphabetDecorator<L, T>::begin() const
    {
      return alphabet().begin();
    }

    template <typename L, typename T>
    typename AlphabetDecorator<L, T>::const_iterator
    AlphabetDecorator<L, T>::end() const
    {
      return alphabet().end();
    }

    template <typename L, typename T>
    const T& AlphabetDecorator<L, T>::alphabet() const
    {
      return *alphabet_;
    }

    template <typename L, typename T>
    T& AlphabetDecorator<L, T>::alphabet()
    {
      return *alphabet_;
    }

    template <typename L, typename T>
    L AlphabetDecorator<L, T>::joker() const
    {
      return joker_;
    }

    template <typename L, typename T>
    L AlphabetDecorator<L, T>::other() const
    {
      return other_;
    }
  }

  template <typename L, typename T>
  L MetaElement<algebra::AlphabetSet<L>, algebra::AlphabetDecorator<L, T> >::
  joker() const
  {
    return this->value().joker();
  }

  template <typename L, typename T>
  L MetaElement<algebra::AlphabetSet<L>, algebra::AlphabetDecorator<L, T> >::
  other() const
  {
    return this->value().other();
  }

  /*--------------------------------------------------.
    | Definition of an alphabet implementation based on |
    | AlphabetDecorator                                 |
    `--------------------------------------------------*/

  template <typename L, typename T>
  bool op_contains(const algebra::AlphabetSet<L>& s, const algebra::AlphabetDecorator<L, T>& a)
  {
    return true;
  }

  template <typename L, typename T>
  bool op_is_finite(const algebra::AlphabetSet<L>& s, const algebra::AlphabetDecorator<L, T>& a)
  {
    return true;
  }

  template <typename L, typename T>
  bool op_contains_e(const algebra::AlphabetSet<L>& s,
		     const algebra::AlphabetDecorator<L, T>& a,
		     const L& v)
  {
    if (v == a.joker())
      return true;
    if (v == a.other())
      return false;
    return Element<algebra::AlphabetSet<L>, T>(s, a.alphabet()).contains(v);
  }

  template <typename T, typename L>
  bool op_letter_equality(const algebra::AlphabetSet<L>& s,
				 const algebra::AlphabetDecorator<L, T>& a,
				 L lhs,
				 L rhs)
  {
    Element<algebra::AlphabetSet<L>, algebra::AlphabetDecorator<L, T> > e(s, a);
    if (lhs == a.joker())
      return e.contains(rhs);
    if (rhs == a.joker())
      return e.contains(lhs);
    if (lhs == a.other())
      return ! e.contains(rhs);
    if (rhs == a.other())
      return ! e.contains(lhs);
    return lhs == rhs;
  }


} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_ALPHABETS_DECORATED_ALPHABET_HXX
