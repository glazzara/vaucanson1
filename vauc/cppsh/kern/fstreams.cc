// fstreams.cc: this file is part of the Vaucanson project.
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
#include "kern/fstreams.hh"
#include "kern/exception.hh"
#include <fstream>

namespace cppsh
{
  namespace internals
  {
    struct FStreamSlot : StreamSlot
    {
      virtual access_type kind() const;
      virtual std::istream& as_istream();
      virtual std::ostream& as_ostream();
      virtual std::iostream& as_iostream();
      virtual const std::string& describe() const;
      FStreamSlot(const char* fname,
		  std::ios::openmode imode,
		  access_type t);
      bool is_open();

      virtual ~FStreamSlot();
    protected:
      std::string _description;
      std::fstream _file;
      access_type _type;
    };

    StreamSlot::access_type
    FStreamSlot::kind() const
    { return _type; }

    std::istream& 
    FStreamSlot::as_istream() 
    { return _file; }
    
    std::ostream& 
    FStreamSlot::as_ostream()
    { return _file; }

    std::iostream&
    FStreamSlot::as_iostream()
    { return _file; }

    const std::string& 
    FStreamSlot::describe() const
    { return _description; }

    FStreamSlot::FStreamSlot(const char* fname,
			     std::ios::openmode imode,
			     access_type t)
      : _description(std::string("file ") + fname),
	_file(fname, imode),
	_type(t)
    { }

    FStreamSlot::~FStreamSlot()
    { _file.close(); }
	
    bool
    FStreamSlot::is_open()
    { return _file.is_open(); }

  }

  ref<StreamSlot> sslot_fopen(const char *fname,
			      std::ios::openmode imode)
  {
    StreamSlot::access_type t = StreamSlot::input;

    if (imode | std::ios::out 
	&& imode | std::ios::in)
      t = StreamSlot::both;
    else if (imode | std::ios::out)
      t = StreamSlot::output;

    internals::FStreamSlot *s;
    try 
      {
	s = new internals::FStreamSlot(fname, imode, t);
      }
    catch(...)
      { 
	failwith("sslot_fopen", 
		 "attempting to open file", "fstream error"); 
      }

    if (!s->is_open())
      {
	delete s;
	failwith("sslot_fopen", 
		 "attempting to open file", "file won't open");
      }

    return s;
  }

}

