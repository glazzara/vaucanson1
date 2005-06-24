// stdstreams_cerr.cc: this file is part of the Vaucanson project.
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
#include "stdstreams_cerr.hh"

namespace cppsh
{
  namespace internals
  {
    StreamSlot::access_type
    StdCerrStreamSlot::kind() const
    { return output; }

    std::ostream&
    StdCerrStreamSlot::as_ostream()
    { return std::cerr; }

    const std::string& 
    StdCerrStreamSlot::describe() const
    { return _description; }

    StdCerrStreamSlot::~StdCerrStreamSlot()
    { }

    StdCerrStreamSlot::StdCerrStreamSlot()
      : _description("standard error")
    { }

  }

  ref<StreamSlot> sslot_of_cerr()
  {
    static ref<StreamSlot> _instance 
      = new internals::StdCerrStreamSlot();
    return _instance;
  }

}

