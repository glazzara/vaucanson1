/*----------------------------------------------------------.
| include/kern/stdstreams.hh : cppsh i/o / standard streams |
`----------------------------------------------------------*/
//     Copyright (C) 2002  LRDE.

//     libcppshio is free software; you can redistribute it and/or
//     modify it under the terms of the GNU Lesser General Public
//     License as published by the Free Software Foundation; either
//     version 2 of the License, or (at your option) any later version.

//     libcppshio is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//     Lesser General Public License for more details.

//     You should have received a copy of the GNU Lesser General Public
//     License along with this library; if not, write to the Free Software
//     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
#ifndef CPPSHIO_STDSTREAMS_HH
#define CPPSHIO_STDSTREAMS_HH

#include "kern/streams.hh"

namespace cppsh
{

  ref<StreamSlot> sslot_of_cin();
  ref<StreamSlot> sslot_of_cout();
  ref<StreamSlot> sslot_of_cerr();

}


#endif
