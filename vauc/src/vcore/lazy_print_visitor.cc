/******************************
 * core/lazy_print_visitor.cc *
 ******************************/
// $Id$

/* this file is part of the Vaucanson project */

#include <lazy/print_visitor.hh>
#include <types/symbol.hh>

namespace vcsn
{
  namespace vauc
  {

    inline void PrintVisitor::inc()
    { ++level_; }
    inline void PrintVisitor::dec() 
    { assert(level_); --level_; }
    inline void PrintVisitor::endl ()
    {
      const unsigned tab_len = 3;
      if (format_)
	{
	  out_ << std::endl;
	  for (unsigned i = 0; i < tab_len * level_; ++i)
	    out_ << ' ';
	}
    }
    
    PrintVisitor::PrintVisitor(std::ostream& out, bool format)
	: out_(out), level_(0), format_(format)
    {}
      
    void PrintVisitor::visit(const lazy::ExpArgs<lazy::Exp<VisitorBase>, lazy::call_k>& args)
    {
      inc();
      out_ << "(";
      args[lazy::call_k::a_fun].accept(*this);
      out_ << ") (";
      args[lazy::call_k::a_args].accept(*this);
      out_ << ")";
      dec();
    }
    void PrintVisitor::visit(const lazy::ExpArgs<lazy::Exp<VisitorBase>, lazy::lazy_call_k>& args)
    {
      inc();
      out_ << "(";
      args[lazy::lazy_call_k::a_fun].accept(*this);
      out_ << ")..(";
      args[lazy::lazy_call_k::a_args].accept(*this);
      out_ << ")";
      dec();
    }


    void PrintVisitor::visit(std::list<lazy::Exp<VisitorBase>*>& l)
    {
      typedef lazy::Exp<VisitorBase> exp_t;
      
      inc();
      out_ << "[ ";
      for (std::list<exp_t*>::const_iterator i = l.begin(); 
	   i != l.end(); 
	   ++i)
	{
	  if (i != l.begin())
	    out_ << ", ";
	  (*i)->accept(*this);
	}
      out_ << " ]";
      dec();
    }

    void PrintVisitor::visit(const lazy::ExpArgs<lazy::Exp<VisitorBase>, lazy::with_k>& args)
    {
      inc();
      out_ << "with (";
      args[lazy::with_k::a_obj].accept(*this);
      out_ << ") do ?(";
      endl();
      args[lazy::with_k::a_action].accept(*this);
      out_ << ")";
      dec();
    }

    void PrintVisitor::visit(const lazy::ExpArgs<lazy::Exp<VisitorBase>, lazy::in_k>& args)
    {
      inc();
      out_ << "in (";
      args[lazy::in_k::a_catalog].accept(*this);
      out_ << ")";
      endl();
      dec();
    }

    void PrintVisitor::visit(Object e)
    {
      inc();
      do
	{
	  if (e.cpp_type() == typeid(Symbol))
	    {
	      out_ << *e.cast<Symbol>();
	      break ;
	    }
	  if (e.cpp_type() == typeid(LazyExp))
	    {
	      out_ << "`(";
	      const LazyExp& exp = *e.cast<LazyExp>();
	      if (exp.bound())
		exp.exp().accept(*this);
	      else
		out_ << "<null expression>";
	      out_ << ")";
	      break ;
	    }
	  if (e.cpp_type() == typeid(std::string))
	    {
	      out_ << '\"' << *e.cast<std::string>() << '\"';
	      break ;
	    }
	  if (e.cpp_type() == typeid(char))
	    {
	      out_ << '\'' << *e.cast<char>() << '\'';
	      break ;
	    }
	  if (e.cpp_type() == typeid(bool))
	    {
	      out_ << (*e.cast<bool>() ? "true" : "false");
	      break ;
	    }
	  if (e.cpp_type() == typeid(int))
	    {
	      out_ << *e.cast<int>();
	      break ;
	    }
	  out_ << "<data with c++ type " << e.cpp_type().name() << ">";

	} 
      while(0);

      dec();
    }

  }
}
