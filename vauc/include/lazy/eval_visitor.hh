/**************************
 * <lazy/eval_visitor.hh> *
 **************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef LAZY_EVAL_VISITOR_HH
#define LAZY_EVAL_VISITOR_HH

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


#endif
