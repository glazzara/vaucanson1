// vcontext.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_DEMOS_VAUCANSWIG_META_VCONTEXT_HH
# define VCSN_DEMOS_VAUCANSWIG_META_VCONTEXT_HH

#include <list>
#include <string>

namespace vcsn
{
  struct virtual_context 
  {
    virtual std::list<char> alphabet_letters() const = 0;
    virtual std::string describe_alphabet(bool with_cpp = false) const = 0;
    virtual std::string describe_semiring(bool with_cpp = false) const = 0;
    virtual std::string describe_monoid(bool with_cpp = false) const = 0;
    virtual std::string describe_series(bool with_cpp = false) const = 0;
    virtual std::string describe_automata_structure(bool with_cpp = false) const = 0;
    virtual ~virtual_context();
  };
}

#endif // ! VCSN_DEMOS_VAUCANSWIG_META_VCONTEXT_HH
