/**********************
 * <lazy/exp_base.hh> *
 **********************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef LAZY_EXP_BASE_HH
#define LAZY_EXP_BASE_HH

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

#endif
