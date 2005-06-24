// visitor_base.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_INCLUDE_LAZY_VISITOR_BASE_HH
# define VCSN_VAUC_INCLUDE_LAZY_VISITOR_BASE_HH

#include <lazy/vauc_constructs.hh>

namespace vcsn
{
  namespace vauc
  {

    
    class VisitorBase
    {
    public:
      typedef lazy::Exp<VisitorBase> exp_t;

      virtual void visit(const lazy::ExpArgs<exp_t, lazy::call_k>& args) = 0;
      virtual void visit(const lazy::ExpArgs<exp_t, lazy::lazy_call_k>& args) = 0;
      virtual void visit(const lazy::ExpArgs<exp_t, lazy::with_k>& args) = 0;
      virtual void visit(const lazy::ExpArgs<exp_t, lazy::in_k>& args) = 0;

     virtual  void visit(std::list<exp_t*>& l) = 0;
     virtual  void visit(Object e) = 0;
    };


  }
}



#endif // ! VCSN_VAUC_INCLUDE_LAZY_VISITOR_BASE_HH
