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
# include <utility>

# include <vaucanson/design_pattern/predecls.hh>
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

      /// Whether the letter has a first projection computable.
      typedef undefined_type first_projection_t;

      /// Whether the letter has a second projection computable.
      typedef undefined_type second_projection_t;

      /// Provide a way to create a letter from its literal
      /// representation:
      static std::pair<bool, L> literal_to_letter(const std::string&);

      /// Provide a way to represent a letter.
      static std::string letter_to_literal(const L&);
    };

  } // ! algebra

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/concept/letter.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_CONCEPT_LETTER_HH
