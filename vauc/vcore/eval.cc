// eval.cc: this file is part of the Vaucanson project.
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
#include <lazy/eval_visitor.hh>
#include <types/symbol.hh>
#include <vcore/exception.hh>
#include <vcore/partial_call.hh>
#include <vcore/interrupt_handler.hh>

static int _recursions = 0;

namespace vcsn
{
  namespace vauc
  {

    EvalVisitor::EvalVisitor(Env& env)
      : env_(env)
    {
      if (_recursions > 1000)
	RAISE("evaluating", "recursion level exceeded");
      if (interrupted())
	{
	  interrupt_ack();
	  RAISE("evaluating", "interrupted (" + describe_interrupt() + ')');
	}
	  
      ++_recursions;
    }

    void EvalVisitor::visit_call(Callable &c, std::list<Object>& args)
    {
      const FunctionImpl::sig_t& sig = c.signature();

      if (prefixes_.size() + args.size() != sig.size())
	RAISE("evaluating", "wrong number of arguments");

      std::vector<Object> argv(prefixes_.begin(), prefixes_.end());

      argv.insert(argv.end(), args.begin(), args.end());

      std::vector<Object>::const_iterator i;
      FunctionImpl::sig_t::const_iterator j;
      for (i = argv.begin(), j = sig.begin();
	   i != argv.end();
	   ++i, ++j)
	if (i->cpp_type().name() != *j && *j != "")
	  RAISE("evaluating", "wrong argument type");

      exp_ = c.call(env_, argv);
    }

    void EvalVisitor::visit_lazy(Callable &c, std::list<Object>& args)
    {
      const FunctionImpl::sig_t& sig = c.signature();

      if (prefixes_.size() + args.size() > sig.size())
	RAISE("evaluating", "too many arguments");

      std::vector<Object> argv(args.begin(), args.end());

      PartialCall* pc = dynamic_cast<PartialCall*>(c.get());

      if (argv.size() == 0)
	{
	  exp_ = Object(Closure());
	  if (pc)
	    OBJECT_CAST(exp_, Closure)->merge_fun(PartialCall(*pc));
	  else
	    OBJECT_CAST(exp_, Closure)->merge_fun(PartialCall(c));
	}
      else
	{
	  if (pc)
	    {
	      PartialCall _p(*pc);
	      _p.append_args(argv);
	      exp_ = Object(Callable(new PartialCall(_p)));
	    }
	  else
	    {
	      PartialCall _p(c);
	      _p.append_args(argv);
	      exp_ = Object(Callable(new PartialCall(_p)));
	    }
	}
    }

    void EvalVisitor::visit_call(Closure &c, std::list<Object>& args)
    {
      std::vector<Object> argv(prefixes_.begin(), prefixes_.end());

      argv.insert(argv.end(), args.begin(), args.end());

      Callable _c = c.resolve_call(env_, argv);

      exp_ = _c.call(env_, std::vector<Object>());
    }

    void EvalVisitor::visit_lazy(Closure &c, std::list<Object>& args)
    {
      std::vector<Object> argv(args.begin(), args.end());

      exp_ = Object(Closure(c));

      OBJECT_CAST(exp_, Closure)->restrict(argv);

      if (argv.size() == 0)
	OBJECT_CAST(exp_, Closure)->freeze(env_);
    }

      
    void EvalVisitor::visit(const lazy::ExpArgs<lazy::Exp<VisitorBase>, lazy::call_k>& args)
    {
      try
	{
	  args[lazy::call_k::a_fun].accept(*this);
	}
      catch(EXCEPTION(e))
	{
	  ATTACH(e, "evaluating", "at call");
	  RETHROW(e);
	}
      Object f = exp_;
      if (!OBJECT_IS_A(f, Closure) && !OBJECT_IS_A(f, Callable))
	RAISE("evaluating", "object is not a function");

      try 
	{
	  args[lazy::call_k::a_args].accept(*this);
	}
      catch(EXCEPTION(e))
	{
	  ATTACH(e, "evaluating", "at call");
	  RETHROW(e);
	}
      Object l = exp_;
      if (!OBJECT_IS_A(l, std::list<Object>))
	RAISE("evaluating", "call argument is not a list");
      

      if (OBJECT_IS_A(f, Closure))
	visit_call(*OBJECT_CAST(f, Closure), *OBJECT_CAST(l, std::list<Object>));
      else
	visit_call(*OBJECT_CAST(f, Callable), *OBJECT_CAST(l, std::list<Object>));
    }

    void EvalVisitor::visit(const lazy::ExpArgs<lazy::Exp<VisitorBase>, lazy::lazy_call_k>& args)
    {
      try
	{
	  args[lazy::lazy_call_k::a_fun].accept(*this);
	}
      catch(EXCEPTION(e))
	{
	  ATTACH(e, "evaluating", "at lazy call");
	  RETHROW(e);
	}
      Object f = exp_;
      if (f.cpp_type() != typeid(Closure) && f.cpp_type() != typeid(Callable))
	RAISE("evaluating", "object is not a function");

      try 
	{
	  args[lazy::lazy_call_k::a_args].accept(*this);
	}
      catch(EXCEPTION(e))
	{
	  ATTACH(e, "evaluating", "at lazy call");
	  RETHROW(e);
	}
      Object l = exp_;
      if (OBJECT_IS_A(l, std::list<Object>))
	RAISE("evaluating", "lazy call argument is not a list");
      

      if (OBJECT_IS_A(f, Closure))
	visit_lazy(*OBJECT_CAST(f, Closure), *OBJECT_CAST(l, std::list<Object>));
      else
	visit_lazy(*OBJECT_CAST(f, Callable), *OBJECT_CAST(l, std::list<Object>));
    }

      
			    

    void EvalVisitor::visit(std::list<lazy::Exp<VisitorBase>*>& l)
    {
      try
	{
	  Object obj = Object(std::list<Object>());
	  
	  std::list<Object>& o = *OBJECT_CAST(obj, std::list<Object>);
	  
	  for(std::list<lazy::Exp<VisitorBase>*>::const_iterator i = l.begin();
	      i != l.end();
	      ++i)
	    {
	      (*i)->accept(*this);
	      o.push_back(exp_);
	    }
	  exp_ = obj;
	}
      catch(EXCEPTION(e))
	{
	  ATTACH(e, "evaluating", "within list");
	  RETHROW(e);
	}
    }

    void EvalVisitor::visit(const lazy::ExpArgs<lazy::Exp<VisitorBase>, lazy::with_k>& args)
    {
      try
	{
	  args[lazy::with_k::a_obj].accept(*this);
	}
      catch(EXCEPTION(e))
	{
	  ATTACH(e, "evaluating", "within `with' argument");
	  RETHROW(e);
	}

      prefixes_.push_back(exp_);
      try
	{
	  args[lazy::with_k::a_action].accept(*this);
	  prefixes_.pop_back();
	}
      catch(EXCEPTION(e))
	{
	  prefixes_.pop_back();
	  ATTACH(e, "evaluating", "within `with' body");
	  RETHROW(e);
	}
      catch(std::exception& e)
	{
	  prefixes_.pop_back();
	  throw e;
	}
    }

    void EvalVisitor::visit(const lazy::ExpArgs<lazy::Exp<VisitorBase>, lazy::in_k>& args)
    {
      RAISE("evaluating", "in not supported");
//       try
// 	{
// 	  args[lazy::in_k::a_what].accept(*this);
// 	}
//       catch(EXCEPTION(e))
// 	{
// 	  ATTACH(e, "evaluating", "within `in' argument");
// 	  throw e;
// 	}

//       env_.set_front(exp_);
//       exp_ = Object();
    }

    void EvalVisitor::visit(Symbol e)
    {
      size_t n = std::find(e.value().begin(), e.value().end(), '/') - e.value().begin();
      if (n != e.value().size())
	{
	  Symbol ns(e.value().substr(0, n));
	  Symbol obj(e.value().substr(n + 2, e.value().size() - n - 2));

	  if (! env_.contains(ns, obj))
	    RAISE("evaluating", "object " + obj.value() + " not found in module " + ns.value());
	  else
	    exp_ = env_.at(ns, obj);
	}
      else
	{
	  if (! env_.contains(e))
	    RAISE("evaluating", "object not found: " + e.value());
	  else
	    exp_ = env_.at(e);
	}
    }

    void EvalVisitor::visit(Object e)
    {
      if (e.cpp_type() == typeid(Symbol))
	visit(*OBJECT_CAST(e, Symbol));
      else
	exp_ = e;
    }

    EvalVisitor::~EvalVisitor()
    {
      --_recursions;
    }

    Object EvalVisitor::get() const
    {
      return exp_;
    }

  }
}

