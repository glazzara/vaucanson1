/******************
 * <lazy/exp.hxx> *
 ******************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef LAZY_EXP_HXX
#define LAZY_EXP_HXX

# include <lazy/exp.hh>

namespace vcsn
{
  namespace vauc
  {
 
    inline LazyExp::LazyExp(const lazy::Exp<VisitorBase>& e)
      : exp_(e.clone())
    {}

    inline LazyExp::LazyExp(lazy::Exp<VisitorBase>* e)
      : exp_(e)
    {}
    
    inline LazyExp::LazyExp() 
      : exp_(NULL) 
    {}

    inline LazyExp::LazyExp(const LazyExp& other)
      : exp_(NULL)
    {
      if (other.exp_)
	exp_ = other.exp_->clone();
    }
    
    inline LazyExp& 
    LazyExp::operator=(const LazyExp& other)
    {
      if (exp_ != other.exp_)
	{
	  delete this->exp_;
	  this->exp_ = 0;
	  if (other.exp_)
	    this->exp_ = other.exp_->clone();
	}
      return *this;
    }

    inline bool 
    LazyExp::bound() const
    { return (NULL != exp_); }

    inline lazy::Exp<VisitorBase>& 
    LazyExp::exp() const
    { 
      assert(exp_ != NULL);
      return *exp_; 
    }

    inline void
    LazyExp::attach(lazy::Exp<VisitorBase>* e)
    {
      if (exp_ != e)
	delete exp_;
      exp_ = e;
    }

    inline LazyExp::~LazyExp() 
    { delete exp_; }
   
  }
}

#endif
