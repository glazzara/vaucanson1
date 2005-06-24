// stdstreams_cin.cc: this file is part of the Vaucanson project.
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

