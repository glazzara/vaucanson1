// military_order.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008, 2009 The Vaucanson Group.
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
#ifndef MILITARY_ORDER_HH
#define MILITARY_ORDER_HH

	/* Military strict order predicate.
	 * This predicate applies to any type which provides a length method.
	 * If two elements have the same length they are compared with operator<,
	 * otherwise, the shorter is the smaller.
	 *
	 * Known algorithms using this : enumerate return a list sorted w.r.t military order.
	 */

namespace vcsn{

	template<typename T>
	struct MilitaryOrder{

		bool operator()(const T& x, const T& y) const {
			if(x.length()==y.length()) return (x<y);
			else
				return x.length()<y.length();
		}

	};

} // ! vcsn

#endif // ! MILITARY_ORDER_HH
