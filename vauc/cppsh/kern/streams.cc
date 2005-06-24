// streams.cc: this file is part of the Vaucanson project.
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

