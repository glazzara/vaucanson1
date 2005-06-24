// eval_visitor.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_INCLUDE_LAZY_EVAL_VISITOR_HH
# define VCSN_VAUC_INCLUDE_LAZY_EVAL_VISITOR_HH

#include <iostream>

#include <lazy/exp.hh>
#include <lazy/visitor_base.hh>
#include <vcore/env.hh>
#include <vcore/closure.hh>

namespace vcsn
{
  namespace vauc
  {
    
    class EvalVisitor 
      : public VisitorBase
    {
    public:
      EvalVisitor(Env& env);

      typedef lazy::Exp<VisitorBase> exp_t;

      virtual void visit(const lazy::ExpArgs<exp_t, lazy::call_k>& args);
      virtual void visit(const lazy::ExpArgs<exp_t, lazy::lazy_call_k>& args);
      virtual void visit(const lazy::ExpArgs<exp_t, lazy::with_k>& args);
      virtual void visit(const lazy::ExpArgs<exp_t, lazy::in_k>& args);

      virtual void visit(std::list<exp_t*>& l);
      virtual void visit(Object e);
      virtual void visit(Symbol e);

      void visit_call(Callable &c, std::list<Object>& args);
      void visit_call(Closure &c, std::list<Object>& args);
      void visit_lazy(Callable &c, std::list<Object>& args);
      void visit_lazy(Closure &c, std::list<Object>& args);
      
      virtual ~EvalVisitor();

      Object get() const;

    protected:
      Env& env_;
      Object exp_;
      std::vector<Object> prefixes_;
    };


  }
}


#endif // ! VCSN_VAUC_INCLUDE_LAZY_EVAL_VISITOR_HH
