/*-------------------------------------------------------.
| kern/stdstreams_cerr.hh : cppsh kernel / standard input |
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
#ifndef CPPSH_STDSTREAMS_CERR_HH
#define CPPSH_STDSTREAMS_CERR_HH

#include "kern/stdstreams.hh"

namespace cppsh
{
  namespace internals
  {
    struct StdCerrStreamSlot : StreamSlot
    {
      virtual access_type kind() const;
      virtual std::ostream& as_ostream(); 
      virtual const std::string& describe() const;
      virtual ~StdCerrStreamSlot();
      StdCerrStreamSlot();
    protected:
      std::string _description;
    };
  }
}

#endif
