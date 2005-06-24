// exp.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_INCLUDE_LAZY_EXP_HH
# define VCSN_VAUC_INCLUDE_LAZY_EXP_HH

#include <lazy/exp_base.hh>
#include <lazy/visitor_base.hh>

namespace vcsn
{
  namespace vauc
  {

    class LazyExp
    {
    public:
      LazyExp(const lazy::Exp<VisitorBase>& e);
      LazyExp(lazy::Exp<VisitorBase>* e);
      LazyExp();
      LazyExp(const LazyExp& other);

      LazyExp& operator=(const LazyExp& other);

      bool bound() const;

      lazy::Exp<VisitorBase>& exp() const;

      ~LazyExp();

      void attach(lazy::Exp<VisitorBase>* e);

    protected:
      lazy::Exp<VisitorBase>* exp_;

    };

  }

}

#include <lazy/exp.hxx>

#endif // ! VCSN_VAUC_INCLUDE_LAZY_EXP_HH
