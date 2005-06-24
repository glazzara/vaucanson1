// vauc_constructs.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_INCLUDE_LAZY_VAUC_CONSTRUCTS_HXX
# define VCSN_VAUC_INCLUDE_LAZY_VAUC_CONSTRUCTS_HXX

# include <lazy/vauc_constructs.hh>

namespace vcsn
{
  namespace vauc
  {

    namespace lazy
    {
      
      /*-----------------.
      | Expression lists |
      `-----------------*/
      
      template<typename Visitor>
      inline List<Visitor>::List() {}

      template< typename Visitor>
      inline List<Visitor>::List(const List<Visitor>& other) 
      {
	for (typename std::list<Exp<Visitor>*>::const_iterator i = other.list().begin();
	     i != other.list().end();
	     ++i)
	  list_.push_back((*i)->clone());
      }

      template< typename Visitor>
      inline List<Visitor>::~List() 
      {
	for (typename std::list<Exp<Visitor>*>::iterator i = list_.begin();
	     i != list_.end();
	     ++i)
	  delete *i;
      }
      
      template< typename Visitor>
      inline void List<Visitor>::push_back(const Exp<Visitor>& other)
      {
	list_.push_back(other.clone());
      }

      template< typename Visitor>
      inline List<Visitor>* List<Visitor>::attach_back(Exp<Visitor>* other)
      {
	list_.push_back(other);
	return this;
      }

      template< typename Visitor>
      inline List<Visitor>* List<Visitor>::attach_front(Exp<Visitor>* other)
      {
	list_.push_front(other);
	return this;
      }



      template< typename Visitor>
      inline void List<Visitor>::accept(Visitor& v)
      { v.visit(list_); }

      

    }
    
  }
  
}

// some useful macros:

#define NEW_VAUC_CALL(Name)												  \
((new vcsn::vauc::lazy::Call<vcsn::vauc::VisitorBase>)								  \
 ->attach(vcsn::vauc::lazy::call_k::a_fun, new vcsn::vauc::lazy::Constant<vcsn::vauc::VisitorBase>(vcsn::vauc::Symbol(Name))) \
 ->attach(vcsn::vauc::lazy::call_k::a_args, new vcsn::vauc::lazy::List<vcsn::vauc::VisitorBase>))

#define NEW_VAUC_CALL1(Name, Arg)											  \
((new vcsn::vauc::lazy::Call<vcsn::vauc::VisitorBase>)								  \
 ->attach(vcsn::vauc::lazy::call_k::a_fun, new vcsn::vauc::lazy::Constant<vcsn::vauc::VisitorBase>(vcsn::vauc::Symbol(Name))) \
 ->attach(vcsn::vauc::lazy::call_k::a_args, (new vcsn::vauc::lazy::List<vcsn::vauc::VisitorBase>)		  \
	  ->attach_back(Arg)))

#define NEW_VAUC_CALL2(Name, Arg1, Arg2)										  \
((new vcsn::vauc::lazy::Call<vcsn::vauc::VisitorBase>)								  \
 ->attach(vcsn::vauc::lazy::call_k::a_fun, new vcsn::vauc::lazy::Constant<vcsn::vauc::VisitorBase>(vcsn::vauc::Symbol(Name))) \
 ->attach(vcsn::vauc::lazy::call_k::a_args, (new vcsn::vauc::lazy::List<vcsn::vauc::VisitorBase>)		  \
	  ->attach_back(Arg1)											  \
	  ->attach_back(Arg2)))

#define NEW_VAUC_CALL3(Name, Arg1, Arg2, Arg3)									  \
((new vcsn::vauc::lazy::Call<vcsn::vauc::VisitorBase>)								  \
 ->attach(vcsn::vauc::lazy::call_k::a_fun, new vcsn::vauc::lazy::Constant<vcsn::vauc::VisitorBase>(vcsn::vauc::Symbol(Name))) \
 ->attach(vcsn::vauc::lazy::call_k::a_args, (new vcsn::vauc::lazy::List<vcsn::vauc::VisitorBase>)		  \
	  ->attach_back(Arg1)											  \
	  ->attach_back(Arg2)											  \
	  ->attach_back(Arg3)))

#define NEW_VAUC_CALL4(Name, Arg1, Arg2, Arg3, Arg4)									  \
((new vcsn::vauc::lazy::Call<vcsn::vauc::VisitorBase>)								  \
 ->attach(vcsn::vauc::lazy::call_k::a_fun, new vcsn::vauc::lazy::Constant<vcsn::vauc::VisitorBase>(vcsn::vauc::Symbol(Name))) \
 ->attach(vcsn::vauc::lazy::call_k::a_args, (new vcsn::vauc::lazy::List<vcsn::vauc::VisitorBase>)		  \
	  ->attach_back(Arg1)											  \
	  ->attach_back(Arg2)											  \
	  ->attach_back(Arg3)											  \
	  ->attach_back(Arg4)))

#endif // ! VCSN_VAUC_INCLUDE_LAZY_VAUC_CONSTRUCTS_HXX
