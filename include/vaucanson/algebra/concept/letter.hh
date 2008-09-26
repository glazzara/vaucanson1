// letter.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The
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
#ifndef VCSN_ALGEBRA_CONCEPT_LETTER_HH
# define VCSN_ALGEBRA_CONCEPT_LETTER_HH

# include <string>
# include <vector>

# include <vaucanson/misc/static.hh>

namespace vcsn {

  namespace algebra {

    template <class L>
    struct letter_traits
    {
      // When we do not know the type we assume false.
      typedef misc::false_t is_char_letter;

      // Default value
      enum
	{
	  cardinal = misc::static_pow<2, sizeof(L) * 8>::value
	};

      /// A class modeling the letter concept must have the
      /// following traits:

      /// A tag to describe the kind of letter (simple or tuple + dim)
      // FIXME: we must add traits to monoids to handle this better
      static std::string kind();
      static int dim();

      /// Provide a way to create a letter from its literal
      /// representation:
      static L literal_to_letter(const std::string&);

      /// Provide a way to represent a letter.
      static std::string letter_to_literal(const L&);

# define DECLARE_DEFAULT(name) \
      static const std::string default_##name ();

      /// Provide a way to represent an "open parenthesis".
      DECLARE_DEFAULT(open_par)

      /// Provide a way to represent a "close parenthesis".
      DECLARE_DEFAULT(close_par)

      /// Provide a way to represent a "plus".
      DECLARE_DEFAULT(plus)

      /// Provide a way to represent a "times".
      DECLARE_DEFAULT(times)

      /// Provide a way to represent a "star".
      DECLARE_DEFAULT(star)

      /// Provide a way to represent an "epsilon".
      DECLARE_DEFAULT(epsilon)

      /// Provide a way to represent a "zero".
      DECLARE_DEFAULT(zero)

      /// Provide a way to represent an "open weight".
      DECLARE_DEFAULT(open_weight)

      /// Provide a way to represent a "close weight".
      DECLARE_DEFAULT(close_weight)

      /// Provide a way to represent a "space".
      DECLARE_DEFAULT(space)

# undef DECLARE_DEFAULT

    };

    template <typename L>
    struct token_representation
    {
      std::string		open_par;
      std::string		close_par;
      std::string		plus;
      std::string		times;
      std::string		star;
      std::string		one;
      std::string		zero;
      std::string		open_weight;
      std::string		close_weight;
      std::vector<std::string>	spaces;

      // Default CTOR.
      token_representation();

      // Convertion CTOR.
      template <typename U>
      token_representation(const token_representation<U>& arg);

    };

    // generic interface to overwrite static defaults
    typedef token_representation<misc::true_t> token_representation_t;

# define LETTER_DEFAULT(name, value) \
    static std::string default_##name () { return value; }

  } // ! algebra

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/concept/letter.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_CONCEPT_LETTER_HH
