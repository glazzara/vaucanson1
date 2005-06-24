// exception.cc: this file is part of the Vaucanson project.
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
#include "kern/exception.hh"
#include <list>
#include <utility>
#include <cassert>

namespace cppsh 
{

  ExceptionVisitor::~ExceptionVisitor()
  { }

  Exception::~Exception()
  { }

  namespace internals
  {
    class Exn : public Exception
    {
    public:
      Exn(const std::string&,
	  const std::string&,
	  const std::string&);

      virtual void add_trace(const std::string&,
			     const std::string&);

      virtual void accept(ExceptionVisitor& v) const;
      virtual void raccept(ExceptionVisitor& v) const;
      virtual const std::string& description() const;

      virtual ~Exn();

    protected:
      std::string description_;
      std::list<std::pair<std::string, std::string> > trace_;
    };

    inline Exn::Exn(const std::string& l, 
		    const std::string& a, 
		    const std::string& d)
      : description_(d) 
    {
      trace_.push_front(std::make_pair(l, a));
    }

    void Exn::add_trace(const std::string& s1,
			const std::string& s2)
    {
      trace_.push_back(std::make_pair(s1, s2));
    }

    void Exn::accept(ExceptionVisitor& v) const
    {
      for (std::list<std::pair<std::string, std::string> >::const_iterator i = trace_.begin();
	   i != trace_.end();
	   ++i)
	v.visitExceptionInfos(i->first, i->second);
    }

    void Exn::raccept(ExceptionVisitor& v) const
    {
      for (std::list<std::pair<std::string, std::string> >::const_reverse_iterator i = trace_.rbegin();
	   i != trace_.rend();
	   ++i)
	v.visitExceptionInfos(i->first, i->second);
    }

    const std::string& Exn::description() const
    { return description_; }

    Exn::~Exn()
    { }

  }

  void failwith(const std::string& first_location,
		const std::string& first_action,
		const std::string& description)
  {
    throw internals::Exn(first_location, first_action, description);
  }

  void rethrow(Exception& e)
  {
    throw *dynamic_cast<internals::Exn*>(&e);
  }

}

