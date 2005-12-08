// generalized.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_GENERALIZED_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_GENERALIZED_HH

# include <vaucanson/misc/selectors.hh>
# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/implementation/series/polynoms.hh>
# include <vaucanson/algebra/implementation/series/krat.hh>

namespace vcsn {

    /*----------------------.
    | Generalized converter |
    `----------------------*/
    template<typename W, typename M, typename Tm, typename Tw>
    rat::exp<Tm, Tw> op_convert(const algebra::Series<W, M>& s1,
				SELECTOR2(rat::exp<Tm, Tw>),
				const algebra::Series<W, M>& s2,
				const algebra::polynom<Tm, Tw>& p_value);

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algebra/implementation/series/generalized.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_GENERALIZED_HH
