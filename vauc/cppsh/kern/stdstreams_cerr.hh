// stdstreams_cerr.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_CPPSH_KERN_STDSTREAMS_CERR_HH
# define VCSN_VAUC_CPPSH_KERN_STDSTREAMS_CERR_HH

#include "kern/stdstreams.hh"

namespace cppsh
{
  namespace internals
  {
    struct StdCerrStreamSlot : StreamSlot
    {
      virtual access_type kind() const;
      virtual std::ostream& as_ostream(); 
      virtual const std::string& describe() const;
      virtual ~StdCerrStreamSlot();
      StdCerrStreamSlot();
    protected:
      std::string _description;
    };
  }
}

#endif // ! VCSN_VAUC_CPPSH_KERN_STDSTREAMS_CERR_HH
