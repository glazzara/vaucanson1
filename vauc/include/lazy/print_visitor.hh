// print_visitor.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_INCLUDE_LAZY_PRINT_VISITOR_HH
# define VCSN_VAUC_INCLUDE_LAZY_PRINT_VISITOR_HH

#include <iostream>

#include <lazy/exp.hh>
#include <lazy/visitor_base.hh>

namespace vcsn
{
  namespace vauc
  {
    
    class PrintVisitor 
      : public VisitorBase
    {
    public:
      PrintVisitor(std::ostream& out, bool format = false);

      typedef lazy::Exp<VisitorBase> exp_t;

      void visit(const lazy::ExpArgs<exp_t, lazy::call_k>& args);
      void visit(const lazy::ExpArgs<exp_t, lazy::lazy_call_k>& args);
      void visit(const lazy::ExpArgs<exp_t, lazy::with_k>& args);
      void visit(const lazy::ExpArgs<exp_t, lazy::in_k>& args);

      void visit(std::list<exp_t*>& l);
      void visit(Object e);
	 
    protected:
      std::ostream& out_;
      unsigned level_;
      bool format_;

      void inc(); 
      void dec(); 
      void endl();

    };


  }
}


#endif // ! VCSN_VAUC_INCLUDE_LAZY_PRINT_VISITOR_HH
