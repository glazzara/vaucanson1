/*---------------------------------------------------------.
| include/kern/streams.cc : cppsh kernel / generic streams |
`---------------------------------------------------------*/
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
#include "kern/streams.hh"

namespace cppsh
{
  StreamSlot::~StreamSlot()
  {}
  
  Stream::Stream(StreamSlot* s)
    : s_(s)
  {}
  
  Stream::Stream(const Stream& other)
    : s_(other.s_)
  {}
  
  Stream::Stream(ref<StreamSlot> other)
    : s_(other)
  {}
  
  std::istream& StreamSlot::as_istream()
  {
    return *static_cast<std::istream*>((void*)0);
  }
  
  std::ostream& StreamSlot::as_ostream()
  {
    return *static_cast<std::ostream*>((void*)0);
  }
  
  std::iostream& StreamSlot::as_iostream()
  {
    return *static_cast<std::iostream*>((void*)0);
  }
  
  StreamSlot::access_type Stream::kind() const
  {
    return s_->kind();
  }
  
  std::ostream& Stream::as_ostream()
  {
    return s_->as_ostream();
  }
  
  std::istream& Stream::as_istream()
  {
    return s_->as_istream();
  }
  
  std::iostream& Stream::as_iostream()
  {
    return s_->as_iostream();
  }
 
  const std::string& Stream::describe() const
  {
    return s_->describe();
  }
  
}

