/*-----------------------------------------------------------.
| include/kern/exnprint.hh : cppsh kernel / exception dumper |
`-----------------------------------------------------------*/
//     Copyright (C) 2002  LRDE.

//     libcppshk is free software; you can redistribute it and/or
//     modify it under the terms of the GNU Lesser General Public
//     License as published by the Free Software Foundation; either
//     version 2 of the License, or (at your option) any later version.

//     libcppshk is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//     Lesser General Public License for more details.

//     You should have received a copy of the GNU Lesser General Public
//     License along with this library; if not, write to the Free Software
//     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
#ifndef CPPSH_EXNPRINT_HH
#define CPPSH_EXNPRINT_HH

#include "kern/exception.hh"
#include <iostream>

namespace cppsh
{
  std::ostream& operator<<(std::ostream&, const Exception&);
}

#endif
