// letter.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCEPT_LETTER_HXX
# define VCSN_ALGEBRA_CONCEPT_LETTER_HXX

# include <string>
# include <vector>

# include <vaucanson/misc/contract.hh>
# include <vaucanson/algebra/concept/letter.hh>

namespace vcsn {

  namespace algebra {

    // Dummy implementation.
    template <typename L>
    L
    letter_traits<L>::literal_to_letter(const std::string&)
    {
      return 0;
    }

    // Dummy implementation.
    template <typename L>
    std::string
    letter_traits<L>::letter_to_literal(const L&)
    {
      return 0;
    }

    // Concept defaults.
# define STATIC_DEFAULT(name) \
    template <typename L> \
    const std::string \
    letter_traits<L>::default_##name () \
    { \
      static_error(need_default_##name) \
      return 0; \
    } \
    template <> \
    inline const std::string \
    letter_traits<misc::true_t>::default_##name () \
    { \
      return ""; \
    }

    STATIC_DEFAULT(open_par)
    STATIC_DEFAULT(close_par)
    STATIC_DEFAULT(plus)
    STATIC_DEFAULT(times)
    STATIC_DEFAULT(star)
    STATIC_DEFAULT(epsilon)
    STATIC_DEFAULT(zero)
    STATIC_DEFAULT(open_weight)
    STATIC_DEFAULT(close_weight)
    STATIC_DEFAULT(space)

# undef STATIC_DEFAULT

    // Default CTOR.
    template <typename L>
    token_representation<L>::token_representation() :
	open_par(letter_traits<L>::default_open_par()),
	close_par(letter_traits<L>::default_close_par()),
	plus(letter_traits<L>::default_plus()),
	times(letter_traits<L>::default_times()),
	star(letter_traits<L>::default_star()),
	one(letter_traits<L>::default_epsilon()),
	zero(letter_traits<L>::default_zero()),
	open_weight(letter_traits<L>::default_open_weight()),
	close_weight(letter_traits<L>::default_close_weight())
    {
      spaces.push_back(letter_traits<L>::default_space());
    }

    // Convertion CTOR.
    template <typename L>
    template <typename U>
    token_representation<L>::
    token_representation(const token_representation<U>& arg) :
      	open_par(arg.open_par),
	close_par(arg.close_par),
	plus(arg.plus),
	times(arg.times),
	star(arg.star),
	one(arg.one),
	zero(arg.zero),
	open_weight(arg.open_weight),
	close_weight(arg.close_weight),
	spaces(arg.spaces)
    {
    }

  } // ! algebra

} // ! vcsn

#endif // ! VCSN_ALGEBRA_CONCEPT_LETTER_HXX
