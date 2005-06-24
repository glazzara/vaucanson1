// streams.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_CPPSH_INCLUDE_KERN_STREAMS_HH
# define VCSN_VAUC_CPPSH_INCLUDE_KERN_STREAMS_HH

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


#endif // ! VCSN_VAUC_CPPSH_INCLUDE_KERN_STREAMS_HH
