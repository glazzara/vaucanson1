/*------------------------------------------------------.
| include/kern/streams.hh : cppsh i/o / generic streams |
`------------------------------------------------------*/
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
#ifndef CPPSHIO_STREAMS_HH
#define CPPSHIO_STREAMS_HH

#include <iostream>
#include <string>
#include "kern/ref.hh"

namespace cppsh
{
  struct StreamSlot
  {
    enum access_type { input = 1, output = 2, both = 3 };
    
    virtual access_type kind() const = 0;

    virtual std::istream& as_istream();
    virtual std::ostream& as_ostream();
    virtual std::iostream& as_iostream();
    
    virtual const std::string& describe() const = 0;
    
    virtual ~StreamSlot();
    

  };
   
  class Stream
  {
  public:
    Stream(StreamSlot *s);
    Stream(ref<StreamSlot> other);
    
    StreamSlot::access_type kind() const;
    std::istream& as_istream();
    std::ostream& as_ostream();
    std::iostream& as_iostream();
    
    const std::string& describe() const;
    
    Stream(const Stream& other);
    
  protected:
    ref<StreamSlot> s_;
  };


}


#endif
