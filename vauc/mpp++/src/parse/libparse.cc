// libparse.cc: this file is part of the Vaucanson project.
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
#include <string>

#include "parse/libparse.hh"
#include "spec/class_spec.hh"
#include "parse/class_spec_parse.hh"

/*------------------.
| Scanner functions |
`------------------*/
void class_spec_scan_open(const std::string &filename);
void class_spec_scan_close();
void fun_spec_scan_open(const std::string &filename);
void fun_spec_scan_close();
void module_spec_scan_open(const std::string &filename);
void module_spec_scan_close();

/*-----------------.
| Parser functions |
`-----------------*/
void class_spec_parse();
void fun_spec_parse();
void module_spec_parse();

/*----------------------------.
| Global variables definition |
`----------------------------*/
spec::ClassSpec*	the_class_spec = 0;
spec::ModuleSpec*	the_module_spec = 0;
spec::FunSpec*		the_fun_spec = 0;
int			errors = 0;

extern int yydebug;

/*------------.
| class_parse |
`------------*/
spec::ClassSpec*
class_parse(const std::string &name)
{
  yydebug = 0;
  class_spec_scan_open(name);
  class_spec_parse();
  class_spec_scan_close();
  return the_class_spec;
}


/*------------.
| fun_parse |
`------------*/
spec::FunSpec*
fun_parse(const std::string &name)
{
  yydebug = 0;
  fun_spec_scan_open(name);
  fun_spec_parse();
  fun_spec_scan_close();
  return the_fun_spec;
}

/*-------------.
| module_parse |
`-------------*/
spec::ModuleSpec*
module_parse(const std::string &name)
{
  yydebug = 0;
  module_spec_scan_open(name);
  module_spec_parse();
  module_spec_scan_close();
  return the_module_spec;
}

