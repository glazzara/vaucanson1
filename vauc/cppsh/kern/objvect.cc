/*----------------------------------------------.
| kern/objvect.cc : cppsh kernel / object array |
`----------------------------------------------*/
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
#include "kern/objvect.hh"
#include <string>
#include <sstream>
#include <stdexcept>

namespace cppsh
{

  void
  ObjVectBase::autoclone() const
  { 
    for (size_t i = 0; i < n_; ++i)
	vec_[i] = vec_[i].clone();
  }

  void
  ObjVectBase::ensure_size(size_t expected) const
  {
    if (expected != this->n_)
      {
	std::ostringstream s;
	s << "objvect size is " << this->n_
	  << ", expected " << expected;
	throw std::logic_error(s.str());
      }
  }
}
