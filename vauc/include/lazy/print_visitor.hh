/***************************
 * <lazy/print_visitor.hh> *
 ***************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef LAZY_PRINT_VISITOR_HH
#define LAZY_PRINT_VISITOR_HH

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


#endif
