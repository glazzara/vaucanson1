// arg.cc
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

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

  void OptionsValues::usage_msg(void)
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

    if (argc < 1 + nb_non_optional)
      {
	usage_msg();
	exit(EXIT_FAILURE);
      }
    
    for (unsigned i = 1; i < argc; ++i)
      for (std::vector<Options>::const_iterator o = options.begin();
	   o != options.end();
	   ++o)
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
		    std::cerr << o->name << " expected an argument." << std::endl;
		    exit(EXIT_FAILURE);
		  }

		if (o->type == o_int) 
		  {
		    char *endptr;
		    int v = strtol(argv[i], &endptr, 10);
		    if (endptr == argv[i])
		      {
			std::cerr << o->name << " expected an integer." << std::endl;
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
  
  const int*	OptionsValues::get_int(std::string name)
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

  const std::string*   OptionsValues::get_string(std::string name)
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
