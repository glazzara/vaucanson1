// arg.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "arg.hh"

namespace toolbox {

  std::string OptionsValues::type_to_label(option_type_e e)
  {
    switch (e) 
      {
      case o_string: 
	return "[string]";
      case o_int:
	return "[int]"; 
      case o_none:
	return "";
      default:
	return "[any]"; 
      }
    return "[any]";
  }

  void OptionsValues::usage_msg(void) const
  {
    std::ostringstream	cmd;
    std::ostringstream  s;

    cmd << argv_[0] << " ";
    for (std::vector<Options>::const_iterator i = options_.begin();
	 i != options_.end();
	 ++i)
      if (i->optional)
	s << "\t" << i->name << "\t" << type_to_label(i->type) 
	  << "\t" << i->descr << std::endl;
      else
	cmd << i->name << " ";
    std::cerr << cmd.str() << std::endl << s.str() << std::endl;
  }

  OptionsValues::OptionsValues(const std::vector<Options>& options, 
			       unsigned argc, 
			       const char**argv):
    argv_(argv),
    argc_(argc),
    options_(options)
  {
    unsigned nb_non_optional = 0;
    for (std::vector<Options>::const_iterator i = options.begin();
	 i != options.end();
	 ++i)
      if (!i->optional)
	++nb_non_optional;
    if ((argc < 1 + nb_non_optional) || 
	((argc == 2) && (std::string("--help") == argv[1]))
	)
      {
	usage_msg();
	exit(EXIT_FAILURE);
      }
    
    for (unsigned i = 1; i < argc; ++i)
      for (std::vector<Options>::const_iterator o = options.begin();
	   o != options.end();
	   ++o)
	{
	  if (o->name == argv[i])
	  {
	    if (!o->optional)
	      nb_non_optional--;

	    if (o->type != o_none)
	      {
		if (i < argc - 1)
		  ++i;
		else
		  {
		    std::cerr << o->name << " expected an argument." 
			      << std::endl;
		    exit(EXIT_FAILURE);
		  }

		if (o->type == o_int) 
		  {
		    char *endptr;
		    int v = strtol(argv[i], &endptr, 10);
		    if (endptr == argv[i])
		      {
			std::cerr << o->name << " expected an integer." 
				  << std::endl;
			exit(EXIT_FAILURE);
		      }
		    option_value val;
		    val.type = o_int;
		    val.value.int_value = v;
		    values_[o->name] = val;
		    continue;
		  }
		if (o->type == o_string)
		  {
		    option_value val;
		    val.type = o_string;
		    val.value.string_value = new std::string(argv_[i]);
		    values_[o->name] = val;
		    continue;
		  }
	      }
	    else
	      {
		option_value val;
		val.type = o_none;
		values_[o->name] = val;
	      }
	  }
	else
	  remainder_.push_front(argv[i]);
	}
    if (nb_non_optional != 0)
      {
	for (std::vector<Options>::const_iterator o = options.begin();
	     o != options.end();
	     ++o)
	  if (values_.find(o->name) == values_.end())
	    std::cerr << o->name << " non optional." << std::endl;
	exit(EXIT_FAILURE);
      }
  }

  bool		OptionsValues::get(std::string name) const
  {
    std::map<std::string, option_value>::const_iterator i =
      values_.find(name);
    return (i != values_.end());
  }
  
  const int*	OptionsValues::get_int(std::string name) const
  {
    std::map<std::string, option_value>::const_iterator i =
      values_.find(name);
    if (i != values_.end())
      {
	if (i->second.type != o_int)
	  assert (! "not an int !");
	else
	  return &i->second.value.int_value;
      }
    return 0;
  }

  std::list<std::string> OptionsValues::get_remainder() const
  {
    return remainder_;
  }

  const std::string*   OptionsValues::get_string(std::string name) const
  {
    std::map<std::string, option_value>::const_iterator i =
      values_.find(name);
    if (i != values_.end())
      {
	if (i->second.type != o_string)
	  assert (! "not a string !");
	else
	  return &*i->second.value.string_value;
      }
    return 0;
  }


} // toolbox

