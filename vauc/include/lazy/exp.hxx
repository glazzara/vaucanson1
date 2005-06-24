// exp.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_INCLUDE_LAZY_EXP_HXX
# define VCSN_VAUC_INCLUDE_LAZY_EXP_HXX

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

#endif // ! VCSN_VAUC_INCLUDE_LAZY_EXP_HXX
