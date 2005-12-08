// tools.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_TOOLS_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_TOOLS_HH

# include <vaucanson/algebra/concept/freemonoid_base.hh>
# include <string>
# include <list>

namespace vcsn {

  namespace algebra {

    template <typename L>
    struct list_or_string
    {
      typedef std::list<L> ret;
    };

    template <>
    struct list_or_string<char>
    {
      typedef std::string ret;
    };

    template <>
    struct list_or_string<wchar_t>
    {
      typedef std::basic_string<wchar_t> ret;
    };

    template <typename A, typename B>
    struct list_or_string<std::pair<A,B> >
    {
      typedef std::basic_string<std::pair<A,B> > ret;
    };

  } // algebra

  template<typename A>
  const std::list<typename A::letter_t>&
  identity_value(SELECTOR(algebra::FreeMonoidBase<A>),
                 SELECTOR(std::list<typename A::letter_t>));

  template<typename A>
  std::list<typename A::letter_t>
  op_convert(SELECTOR(algebra::FreeMonoidBase<A>),
             SELECTOR(std::list<typename A::letter_t>),
             const typename A::letter_t& c);

  template <typename A>
  void
  op_in_mul(const algebra::FreeMonoidBase<A>& s,
            std::list<typename A::letter_t>& dst,
            const std::list<typename A::letter_t>& src);

  template <typename A>
  std::list<typename A::letter_t>
  op_mul(const algebra::FreeMonoidBase<A>& s,
         const std::list<typename A::letter_t>& a,
         const std::list<typename A::letter_t>& b);

} // vcsn

/// Declares the alphabet, the free monoid, etc. from the type of letter.
#define USE_LETTERS(X...) \
  typedef X Letter; \
  typedef vcsn::algebra::AlphabetSet< Letter > Alphabets; \
  typedef vcsn::Element<Alphabets, std::set< Letter > > Alphabet; \
  typedef vcsn::algebra::AlphabetDecorator< Letter , std::set< Letter > > DAlphabetImpl; \
  typedef vcsn::Element<Alphabets, DAlphabetImpl> DAlphabet; \
  typedef vcsn::algebra::FreeMonoid<Alphabet> Words; \
  typedef vcsn::algebra::list_or_string< Letter >::ret WordValue; \
  typedef vcsn::Element<Words, WordValue> Word;

#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algebra/implementation/free_monoid/tools.hxx>
#endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_TOOLS_HH
