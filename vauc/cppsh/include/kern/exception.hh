// exception.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.

// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_VAUC_CPPSH_INCLUDE_KERN_EXCEPTION_HH
# define VCSN_VAUC_CPPSH_INCLUDE_KERN_EXCEPTION_HH

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

#endif // ! VCSN_VAUC_CPPSH_INCLUDE_KERN_EXCEPTION_HH
