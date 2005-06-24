// exp_base.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_INCLUDE_LAZY_EXP_BASE_HXX
# define VCSN_VAUC_INCLUDE_LAZY_EXP_BASE_HXX


#include <lazy/exp_base.hh>
#include <cassert>


namespace vcsn
{
  namespace vauc
  {

    namespace lazy
    {

      /*-------------------------------------.
      | Argument vector for lazy expressions |
      `-------------------------------------*/

      template<typename Exp, typename Kind>
      inline ExpArgs<Exp, Kind>::ExpArgs() 
      { 
	for (size_t i = 0; i < Kind::arity; ++i) 
	  tab_[i] = 0; 
      }

      template<typename Exp, typename Kind>
      inline Exp& ExpArgs<Exp, Kind>::operator[](typename Kind::types i) const
      { 
	assert(tab_[i] != 0);
	return *tab_[i]; 
      }

      template<typename Exp, typename Kind>
      inline ExpArgs<Exp, Kind>::~ExpArgs()
      {
	for (size_t i = 0; i < Kind::arity; ++i)
	  delete tab_[i];
      }

      template<typename Exp, typename Kind>
      inline void ExpArgs<Exp, Kind>::set(typename Kind::types i, const Exp& e)
      {
	assert(& e != 0);
	if (tab_[i] != &e)
	  delete tab_[i];
	tab_[i] = e.clone();
      }

      template<typename Exp, typename Kind>
      inline void ExpArgs<Exp, Kind>::attach(typename Kind::types i, Exp* e)
      {
	assert(e != 0);
	if (tab_[i] != e)
	  delete tab_[i];
	tab_[i] = e;
      }

      template<typename Exp, typename Kind>
      inline ExpArgs<Exp, Kind>& ExpArgs<Exp, Kind>::operator=(const ExpArgs<Exp, Kind>& other)
      {
	for (size_t i = 0; i < Kind::arity; ++i)
	  {
	    if (tab_[i] != other.tab_[i])
	      delete tab_[i];
	    tab_[i] = other.tab_[i].clone();
	  }
      }

      template<typename Exp, typename Kind>
      inline ExpArgs<Exp, Kind>::ExpArgs(const ExpArgs<Exp, Kind>& other)
      {
	for (size_t i = 0; i < Kind::arity; ++i)
	  {
	    if (other.tab_[i])
	      tab_[i] = other.tab_[i]->clone();
	    else
	      tab_[i] = 0;
	  }
      }
      

      /*----------------------------------.
      | Generic expression implementation |
      `----------------------------------*/

      template<typename Visitor, typename Kind>
      inline void ExpImpl<Visitor, Kind>::accept(Visitor& v)
      {
	v.visit(args());
      }

      template<typename Visitor, typename Kind>
      inline ExpImpl<Visitor, Kind>* ExpImpl<Visitor, Kind>::attach(typename Kind::types i, Exp<Visitor>* e)
      {
	assert(e != 0);
	args().attach(i, e);
	return this;
      }
      
      template<typename V, typename Kind>
      inline ExpArgs<Exp<V>, Kind>& ExpImpl<V, Kind>::args()
      { return args_; }

      template<typename V, typename Kind>
      inline const ExpArgs<Exp<V>, Kind>& ExpImpl<V, Kind>::args() const
      { return args_; }

      template<typename V, typename Kind>
      inline Exp<V>* ExpImpl<V, Kind>::clone() const
      { return new ExpImpl<V, Kind>(*this); }

      

    }
  }
}


#endif // ! VCSN_VAUC_INCLUDE_LAZY_EXP_BASE_HXX
