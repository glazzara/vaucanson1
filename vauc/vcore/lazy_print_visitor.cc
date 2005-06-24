// lazy_print_visitor.cc: this file is part of the Vaucanson project.
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
	  if (OBJECT_IS_A(e, Symbol))
	    {
	      out_ << *OBJECT_CAST(e, Symbol);
	      break ;
	    }
	  if (OBJECT_IS_A(e, LazyExp))
	    {
	      out_ << "`(";
	      const LazyExp& exp = *OBJECT_CAST(e, LazyExp);
	      if (exp.bound())
		exp.exp().accept(*this);
	      else
		out_ << "<null expression>";
	      out_ << ")";
	      break ;
	    }
	  if (OBJECT_IS_A(e, std::string))
	    {
	      out_ << '\"' << *OBJECT_CAST(e, std::string) << '\"';
	      break ;
	    }
	  if (OBJECT_IS_A(e, char))
	    {
	      out_ << '\'' << *OBJECT_CAST(e, char) << '\'';
	      break ;
	    }
	  if (OBJECT_IS_A(e, bool))
	    {
	      out_ << (*OBJECT_CAST(e, bool) ? "true" : "false");
	      break ;
	    }
	  if (OBJECT_IS_A(e, int))
	    {
	      out_ << *OBJECT_CAST(e, int);
	      break ;
	    }
	  out_ << "<data with c++ type " << e.cpp_type().name() << ">";

	} 
      while(0);

      dec();
    }

  }
}

