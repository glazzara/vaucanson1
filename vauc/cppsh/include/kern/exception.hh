/*--------------------------------------------------------------.
| include/kern/exception.hh : cppsh kernel / verbose exceptions |
`--------------------------------------------------------------*/
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
#ifndef CPPSHK_EXCEPTION_HH
#define CPPSHK_EXCEPTION_HH

#include <exception>
#include <string>

namespace cppsh
{
  class ExceptionVisitor
  {
  public:
    virtual void visitExceptionInfos(const std::string& location,
				     const std::string& action) = 0;
    virtual ~ExceptionVisitor();
  };

  class Exception
  {
  public:

    virtual void add_trace(const std::string& location,
			   const std::string& action) = 0;

    virtual const std::string& description() const = 0;

    virtual void accept(ExceptionVisitor& v) const = 0;
    virtual void raccept(ExceptionVisitor& v) const = 0;

    virtual ~Exception();
  protected:
  };

  void failwith(const std::string& first_location,
		const std::string& first_action,
		const std::string& description);

  void rethrow(Exception& e);

}

#endif
