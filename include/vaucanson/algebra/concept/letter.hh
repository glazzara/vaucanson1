// letter.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_CONCEPT_LETTER_HH
# define VCSN_ALGEBRA_CONCEPT_LETTER_HH

# include <vaucanson/misc/static.hh>

namespace vcsn {

  namespace algebra {

    template <class L>
    struct letter_traits
    {
      enum
	{
	  cardinal = utility::static_pow<2, sizeof(L) * 8>::value
	};
    };

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_CONCEPT_LETTER_HH
