/****************
 * core/eval.cc *
 ****************/
// $Id$

/* this file is part of the Vaucanson project */

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
	    exp_.cast<Closure>()->merge_fun(PartialCall(*pc));
	  else
	    exp_.cast<Closure>()->merge_fun(PartialCall(c));
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

      exp_.cast<Closure>()->restrict(argv);

      if (argv.size() == 0)
	exp_.cast<Closure>()->freeze(env_);
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
	  throw e;
	}
      Object f = exp_;
      if (f.cpp_type() != typeid(Closure) && f.cpp_type() != typeid(Callable))
	RAISE("evaluating", "object is not a function");

      try 
	{
	  args[lazy::call_k::a_args].accept(*this);
	}
      catch(EXCEPTION(e))
	{
	  ATTACH(e, "evaluating", "at call");
	  throw e;
	}
      Object l = exp_;
      if (l.cpp_type() != typeid(std::list<Object>))
	RAISE("evaluating", "call argument is not a list");
      

      if (f.cpp_type() == typeid(Closure))
	visit_call(*f.cast<Closure>(), *l.cast<std::list<Object> >());
      else
	visit_call(*f.cast<Callable>(), *l.cast<std::list<Object> >());
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
	  throw e;
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
	  throw e;
	}
      Object l = exp_;
      if (l.cpp_type() != typeid(std::list<Object>))
	RAISE("evaluating", "lazy call argument is not a list");
      

      if (f.cpp_type() == typeid(Closure))
	visit_lazy(*f.cast<Closure>(), *l.cast<std::list<Object> >());
      else
	visit_lazy(*f.cast<Callable>(), *l.cast<std::list<Object> >());
    }

      
			    

    void EvalVisitor::visit(std::list<lazy::Exp<VisitorBase>*>& l)
    {
      try
	{
	  Object obj = Object(std::list<Object>());
	  
	  std::list<Object>& o = *obj.cast<std::list<Object> >();
	  
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
	  throw e;
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
	  throw e;
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
	  throw e;
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
      size_t n = std::find(e.name().begin(), e.name().end(), '/') - e.name().begin();
      if (n != e.name().size())
	{
	  Symbol ns(e.name().substr(0, n));
	  Symbol obj(e.name().substr(n + 2, e.name().size() - n - 2));

	  if (! env_.contains(ns, obj))
	    RAISE("evaluating", "object " + obj.name() + " not found in module " + ns.name());
	  else
	    exp_ = env_.at(ns, obj);
	}
      else
	{
	  if (! env_.contains(e))
	    RAISE("evaluating", "object not found: " + e.name());
	  else
	    exp_ = env_.at(e);
	}
    }

    void EvalVisitor::visit(Object e)
    {
      if (e.cpp_type() == typeid(Symbol))
	visit(*e.cast<Symbol>());
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
