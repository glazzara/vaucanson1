// dot_format.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TOOLS_DOT_FORMAT_HH
# define VCSN_TOOLS_DOT_FORMAT_HH

#include <iostream>
#include <string>

namespace vcsn {

  namespace io {

    struct dot
    {
      inline dot(const std::string& auto_name = "automaton");

      template <typename Saver, typename Conv>
      void operator()(std::ostream& out,
		      const Saver& s,
		      const Conv& conv) const;

    protected:
      std::string name_;
    };

    struct transducer_dot
    {
      inline transducer_dot(const std::string& auto_name = "transducer");

      template <typename Saver, typename Conv>
      void operator()(std::ostream& out,
		      const Saver& s,
		      const Conv& conv) const;

    protected:
      std::string name_;
    };

  } // io

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
# include <vaucanson/tools/dot_format.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_TOOLS_DOT_FORMAT_HH
