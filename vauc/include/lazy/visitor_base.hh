/**************************
 * <lazy/visitor_base.hh> *
 **************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef LAZY_VISITOR_BASE_HH
#define LAZY_VISITOR_BASE_HH

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



#endif
