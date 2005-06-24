// exp_base.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_INCLUDE_LAZY_EXP_BASE_HH
# define VCSN_VAUC_INCLUDE_LAZY_EXP_BASE_HH

#ifdef HEAVY_DEBUG
#include <iostream>
#endif

#include <cstdlib>

namespace vcsn
{
  namespace vauc
  {

    namespace lazy
    {

      template<typename Exp, typename Kind>
      class ExpArgs
      {
      public:
	ExpArgs();

	Exp& operator[](typename Kind::types i) const;
	void structure(typename Kind::types i, const Exp& e);
	void attach(typename Kind::types i, Exp* p);

	~ExpArgs();

	ExpArgs(const ExpArgs& other);
	ExpArgs& operator=(const ExpArgs& other);

      protected:
	Exp *tab_[Kind::arity];
      };

      /*--------------------------------------.
      | The base unevaluated expression class |
      `--------------------------------------*/
      // derivated classes represent abstract constructs
      // in the language.
      template<typename Visitor>
      class Exp
      {
      public:
#ifdef HEAVY_DEBUG
	Exp()
	{
	  std::cerr << "An exp was created at " << this << std::endl;
	}
#endif

	virtual void 
	accept(Visitor& v) = 0;
	
	virtual Exp<Visitor>* 
	clone() const = 0;
	
	virtual 
	~Exp() 
	{
#ifdef HEAVY_DEBUG
	  std::cerr << "An exp was deleted at " << this << std::endl;
#endif
	}
      };
      
      template<typename Visitor, typename Kind>
      class ExpImpl : public Exp<Visitor>
      {
      public:
	virtual void accept(Visitor& v);

	ExpImpl(const ExpImpl& other)
	  : args_(other.args_)
	{}
	ExpImpl()
	  : args_()
	{}
	
	ExpImpl& operator=(const ExpImpl& other)
	{ args_ = other.args_; }

	
	ExpArgs<Exp<Visitor>, Kind>& args();
	const ExpArgs<Exp<Visitor>, Kind>& args() const;

	ExpImpl* attach(typename Kind::types i, Exp<Visitor>* e);

	virtual Exp<Visitor>* clone() const;

      protected:
	ExpArgs<Exp<Visitor>, Kind> args_;
      };
    }
  }
}

#include <lazy/exp_base.hxx>

#endif // ! VCSN_VAUC_INCLUDE_LAZY_EXP_BASE_HH
