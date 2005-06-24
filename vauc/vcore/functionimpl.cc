// functionimpl.cc: this file is part of the Vaucanson project.
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
#include <vcore/callable.hh>

namespace vcsn
{
  namespace vauc
  {

    const std::string& FunctionImpl::description() const
    {
      static const std::string instance = "<no description available>";
      return instance;
    }

    FunctionImpl::~FunctionImpl()
    {}

//     const std::string& FunctionImpl::origin() const
//     {
//       static const std::string instance = "~ \"no origin for this function\"";
//       return instance;
//     }

  }
}

