// stdstreams_cout.cc: this file is part of the Vaucanson project.
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
#include "stdstreams_cout.hh"

namespace cppsh
{
  namespace internals
  {
    StreamSlot::access_type
    StdCoutStreamSlot::kind() const
    { return output; }

    std::ostream&
    StdCoutStreamSlot::as_ostream()
    { return std::cout; }

    const std::string& 
    StdCoutStreamSlot::describe() const
    { return _description; }

    StdCoutStreamSlot::~StdCoutStreamSlot()
    { }

    StdCoutStreamSlot::StdCoutStreamSlot()
      : _description("standard output")
    { }

  }

  ref<StreamSlot> sslot_of_cout()
  {
    static ref<StreamSlot> _instance 
      = new internals::StdCoutStreamSlot();
    return _instance;
  }

}

