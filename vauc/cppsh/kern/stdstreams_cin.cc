/*-------------------------------------------------------.
| kern/stdstreams_cin.cc : cppsh kernel / standard input |
`-------------------------------------------------------*/
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
#include "stdstreams_cin.hh"

namespace cppsh
{
  namespace internals
  {
    StreamSlot::access_type
    StdCinStreamSlot::kind() const
    { return input; }

    std::istream&
    StdCinStreamSlot::as_istream()
    { return std::cin; }

    const std::string& 
    StdCinStreamSlot::describe() const
    { return _description; }

    StdCinStreamSlot::~StdCinStreamSlot()
    { }

    StdCinStreamSlot::StdCinStreamSlot()
      : _description("standard input")
    { }

  }

  ref<StreamSlot> sslot_of_cin()
  {
    static ref<StreamSlot> _instance 
      = new internals::StdCinStreamSlot();
    return _instance;
  }

}
