// make_tool.cc: this file is part of the Vaucanson project.
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
# include <string>
# include <fstream>

# include "common.hh"
# include "modules/make_tool.hh"
# include "spec/cpp_code.hh"
# include "spec/module_spec.hh"
# include "internal/mangling.hh"

namespace modules
{

  spec::CppParamCode
  load_template(const std::string& filename)
  {
    spec::CppParamCode	spec;
    std::string		template_filename;
    // -> loading template
    template_filename = template_dir + "/" + filename;
    std::ifstream template_file(template_filename.c_str());
    if (!template_file.good())
      {
	std::cerr << "can't open : " << template_filename.c_str() << std::endl;
	exit(EXIT_FAILURE);
      }
    std::string contains;
    while (!template_file.eof())
      {
	// FIXME !
	char buf[256];
	template_file.getline(buf, 256, '\n');
	contains += buf;
	contains += "\n";
      }
    template_file.close();
    spec = spec::CppParamCode(contains);    
    return spec;
  }

  std::string
  get_include_name(const std::string& current_module_name, const std::string& param)
  {
    size_t n = param.find_first_of(".");
    std::string class_name;
    std::string module_name;

    if (int(n) == -1)
      {
	module_name = current_module_name;
	class_name = param;
      }
    else
      {
	module_name = param.substr(0, n);
	class_name  = param.substr(n+1, param.size() - 1);   
      }

    if (module_name == current_module_name)
      {
	Mangler m;
	m.append(class_name);
	return module_name + "/t_" + m.escape(m.zip64(m.mangled()));
      }

    std::string filename = destination_dir + "/" + module_name + "/" + module_name + ".db";
    std::ifstream file(filename.c_str());
    if (!file.good())
      {
	std::cerr << "make_modules : " << filename 
		  << " is an invalid file. (perhaps not yet created.)" << std::endl;
	exit(EXIT_FAILURE);
      }
    spec::ModuleDB mdb;
    mdb.load(file);
    file.close();
    std::string ret = mdb.get_filename(class_name);
    if (ret == "undefined type")
      {
	std::cerr << "make_modules : can't find this class name : " 
		  << class_name << std::endl;
	exit(EXIT_FAILURE);
      }
    return module_name + "/t_" + mdb.get_filename(class_name);
  }

  /*---------------.
  | get_class_name |
  `---------------*/
  // Given a dynamic name, get the real (long) name of a class
  std::string
  get_class_name(const std::string& current_module_name, const std::string& param)
  {
    size_t n = param.find_first_of(".");
    std::string class_name;
    std::string module_name;

    if (int(n) == -1)
      {
	module_name = current_module_name;
	class_name = param;
      }
    else
      {
	module_name = param.substr(0, n);
	class_name  = param.substr(n+1, param.size() - 1);   
      }

    if (module_name == current_module_name)
      return class_name;

    std::string filename = destination_dir + "/" + module_name + "/" + module_name + ".db";
    std::ifstream file(filename.c_str());
    if (!file.good())
      {
	std::cerr << "make_modules : " << filename 
		  << " is an invalid file. (perhaps not yet created.)" << std::endl;
	if (module_name != current_module_name)
	  exit(EXIT_FAILURE);
	else 
	  return class_name;
      }
    spec::ModuleDB mdb;
    mdb.load(file);
    file.close();
    std::string ret = mdb.get_realname(class_name);
    if (ret == "undefined type")
      {
	std::cerr << "make_modules : can't find this class name : " 
		  << class_name << std::endl;
	exit(EXIT_FAILURE);
      }
    return mdb.get_realname(class_name);
  }

  std::string
  get_class_zcppname(const std::string& current_module_name, const std::string& param)
  {
    size_t n = param.find_first_of(".");
    if (int(n) != -1)
      {
	std::string module_name(param, 0, n);
	std::string class_name(param, n + 1, param.size() - 1);
	if (module_name == current_module_name)
	  {
	    Mangler m;
	    m.append(class_name);
	    return m.escape(m.zip64(m.mangled()));
	  }
	std::string filename = destination_dir + "/" + module_name + "/" + module_name + ".db";
	std::ifstream file(filename.c_str());
	if (!file.good())
	  {
	    std::cerr << "make_modules : " << filename << " is an invalid file." << std::endl;
	    exit(EXIT_FAILURE);
	  }
	spec::ModuleDB mdb;
	mdb.load(file);
	file.close();
	return mdb.get_filename(class_name);
      }
    Mangler m;
    m.append(param);
    return m.escape(m.zip64(m.mangled()));
  }

} // modules

