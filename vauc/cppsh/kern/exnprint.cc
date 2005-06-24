// exnprint.cc: this file is part of the Vaucanson project.
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
#include "kern/exnprint.hh"

namespace cppsh 
{
  namespace internals
  {
    class ExnPrinter : public ExceptionVisitor
    {
    public:
      ExnPrinter(std::ostream& o)
	: max_loc_width_(0), 
	  print_mode_(false), 
	  o_(o)
      { }


      virtual void
      visitExceptionInfos(const std::string& loc,
			  const std::string& desc);

      virtual ~ExnPrinter();

      void set_print_mode()
      { print_mode_ = true; }

    protected:
      size_t max_loc_width_;
      bool print_mode_;
      std::ostream& o_;
    };

    void 
    ExnPrinter::visitExceptionInfos(const std::string& loc,
				    const std::string& action)
    {
      if (print_mode_)
	{
	  o_ << "in " << loc;
	  for (size_t l = 0; 
	       l < max_loc_width_ - loc.size();
	       ++l)
	    o_ << ' ';
	  o_ << " : " << action << std::endl;
	}
      else
	if (loc.size() > max_loc_width_)
	  max_loc_width_ = loc.size();
    }

    ExnPrinter::~ExnPrinter()
    { }

  }
  

  std::ostream& operator<<(std::ostream& o,
			   const Exception& e)
  {
    internals::ExnPrinter p(o);
    e.accept(p);
    p.set_print_mode();
    e.raccept(p);
    o << e.description() << std::endl;
    return o;
  }
}

