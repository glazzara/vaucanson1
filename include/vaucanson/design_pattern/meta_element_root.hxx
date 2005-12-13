// meta_element_root.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_DESIGN_PATTERN_META_ELEMENT_ROOT_HXX
# define VCSN_DESIGN_PATTERN_META_ELEMENT_ROOT_HXX

# include <vaucanson/design_pattern/meta_element_root.hh>

namespace vcsn {

  template <class S, class T>
  MetaElement<Structure<S>, T>::MetaElement()
  {}

  template <class S, class T>
  MetaElement<Structure<S>, T>::MetaElement(const MetaElement& o) :
    SyntacticDecorator<S, T>(o)
  {}

} // vcsn

#endif // ! VCSN_DESIGN_PATTERN_META_ELEMENT_ROOT_HXX
