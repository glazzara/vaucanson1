// dot_dump.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TOOLS_SIMPLE_DUMP_HH
# define VCSN_TOOLS_SIMPLE_DUMP_HH

# include <iostream>

namespace vcsn
{
  namespace tools
  {
    template <typename Auto, typename Converter>
    void simple_dump(std::ostream& o, const Auto& a, const Converter& conv);

  }
}

# include <vaucanson/tools/simple_dump.hxx>

#endif // ! VCSN_TOOLS_SIMPLE_DUMP_HH
