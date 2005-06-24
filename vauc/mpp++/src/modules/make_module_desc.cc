// make_module_desc.cc: this file is part of the Vaucanson project.
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
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cassert>

// FIXME : this is a C include
# include <sys/stat.h>

# include "common.hh"
# include "parse/libparse.hh"
# include "modules/libmodules.hh"
# include "modules/make_tool.hh"
# include "spec/module_spec.hh"
# include "spec/cpp_code.hh"


/*------------.
| make_module |
`------------*/
void
modules::make_module(spec::ModuleSpec&	       	        module_desc)
{
  typedef spec::ModuleSpec					modulespec_t;
  typedef modulespec_t::param_value_t				param_value_t;
  typedef spec::CppParamCode					cpp_param_t;
  typedef spec::ModuleSpec::type_version_list_t			type_version_list_t;
  typedef spec::ModuleSpec::fun_version_list_t			fun_version_list_t;
  typedef spec::ModuleSpec::object_version_list_t	       	object_version_list_t;
  typedef spec::TypeVersion					type_version_t;
  typedef spec::FunSpec::signatures_t				signatures_t;
  typedef spec::ClassSpec::param_set_t				param_set_t;
  typedef std::list<std::string>				cs_list_t;
  typedef std::map<
    std::string, 
    std::pair<spec::ClassSpec*, type_version_t*> >	        cs_map_t;
  typedef std::map<std::string, std::string>			fun_sig_map_t;

  cs_map_t	class_spec;
  cs_list_t	cs_list;
  fun_sig_map_t	fun_class;
  std::string	prelude;
  param_value_t	current_param;

  /*-----------------.
  | init make module |
  `-----------------*/
  spec::CppParamCode module_template = load_template("module_spec_template_cc.cppp");
  /*--------------.
  | create subdir |
  `--------------*/
  std::string subdir = destination_dir + "/" + module_desc.name();
  if (verbose)
    std::cerr << "Create subdir : " << subdir << std::endl;
  if (mkdir(subdir.c_str(), 0755) == -1)
    {
      std::cerr << strerror(errno) << std::endl;
      //      exit(EXIT_FAILURE);
    }
  current_param["FUNCTION_INITIALIZERS"] = "";
  current_param["TYPE_INITIALIZERS"] = "";
  current_param["MODULE_DESCRIPTION"] = module_desc.description();

  /*--------------------------------------.
  | Substitute aliases to their real name |
  `--------------------------------------*/
  for (type_version_list_t::iterator t = module_desc.type_versions().begin();
       t !=  module_desc.type_versions().end();
       ++t)
    for (type_version_t::args_t::iterator a = t->args.begin(); a != t->args.end(); ++a)
      if (module_desc.aliases().find((*a).second) != module_desc.aliases().end())
	{
	  if (verbose)
	    std::cerr 
	      << " in    : " << t->name
	      << " alias : " << (*a).second << " becomes : " 
	      <<  module_desc.aliases()[(*a).second] << std::endl;
	  (*a).second = module_desc.aliases()[(*a).second];
	}
  for (fun_version_list_t::iterator f = module_desc.fun_versions().begin();
       f !=  module_desc.fun_versions().end();
       ++f)
    for (type_version_t::args_t::iterator a = f->args.begin(); a != f->args.end(); ++a)
      if (module_desc.aliases().find((*a).second) != module_desc.aliases().end())
	{
	  if (verbose)
	    std::cerr 
	      << " in    : " << f->name
	      << " alias : " << (*a).second << " becomes : " 
	      <<  module_desc.aliases()[(*a).second] << std::endl;
	  (*a).second = module_desc.aliases()[(*a).second];
	}

  /*--------------------------------------.
  | instanciate all declarations of types |
  `--------------------------------------*/
  std::string type_sources;

  if (verbose)
    std::cerr << "Number of types : " << module_desc.type_versions().size() << std::endl;

  // parsing
  for (type_version_list_t::const_iterator t = module_desc.type_versions().begin();
       t !=  module_desc.type_versions().end();
       ++t)
    {
      spec::ClassSpec*	cs = 
	class_parse(specification_dir + "/" + t->name + ".class");
      if (cs == 0)
	{
	  std::cerr << "error when loading : " 
		    << specification_dir + "/" + t->name + ".class"
		    << std::endl;
	  exit(EXIT_FAILURE);
	}
      class_spec[t->dynamic_name] = std::make_pair(cs, new type_version_t(*t));	
      cs_list.push_back(t->dynamic_name);
    }

  // parameters passing
  for (cs_list_t::iterator csn = cs_list.begin(); csn != cs_list.end(); ++csn)
    {  
      cs_map_t::iterator cs = class_spec.find(*csn);

      if (verbose)
	std::cerr << "make_module : getting parameters of " << (*cs).first << std::endl;
      type_version_t *t = (*cs).second.second;
      t->args["PARAM_VALUES"] = "";
      for (type_version_t::args_t::iterator p = t->args.begin(); 
	   p != t->args.end();
	   ++p)
	{
	  cs_map_t::iterator c = class_spec.find((*p).second);
	  if (verbose)
	    std::cerr << "Look for : " << (*p).second;
 	  if (c != class_spec.end())
	    {
	      (*p).second = (*c).second.first->class_param()["CPP_NAME"];
	      if (verbose)
		std::cerr << "Found and becomes : " << (*p).second << std::endl;
	    }
	}

      for (param_set_t::iterator p = (*cs).second.first->parameters().begin(); 
	   p != (*cs).second.first->parameters().end(); 
	   ++p)
	{
	  if (t->args.find(*p) == t->args.end())
	    {
	      std::cerr << "make_modules : error when looking for value of parameter :"
			<< *p << std::endl;
	      exit(EXIT_FAILURE);
	    }
	  if (verbose)
	    std::cerr << "Parameter : " << *p << ":" << t->args[*p] << std::endl;
	  t->args["PARAM_VALUES"] += get_class_name(module_desc.name(), t->args[*p]);
	}
      (void)(*cs).second.first->instanciate_class(t->args);
      
      if (verbose)
	std::cerr << "Nickname : " << (*cs).first << std::endl;

      // look for parameters value that are types of the current module.
      for (param_value_t::iterator p = (*cs).second.second->args.begin();
	   p != (*cs).second.second->args.end();
	   ++p)
	{
	  cs_map_t::iterator cs = class_spec.find((*p).second);
	  if (cs != class_spec.end())
	    (*p).second = (*cs).second.first->class_param()["CPP_NAME"];
	}

      (*cs).second.second->args["NICK_NAME"] = (*cs).first;
      (*cs).second.first->class_param()["ZCPP_NAME"] = 
	make_class_desc(module_desc.name(), 
			*(*cs).second.first, 
			(*cs).second.second->args);

//       prelude += 
// 	"#include \"" 
// 	+ (*cs).second.first->class_param()["ZCPP_NAME"] 
// 	+ ".hh\"\n";
      type_sources += 
	"t_" + (*cs).second.first->class_param()["ZCPP_NAME"] + ".hh " +
	"t_" + (*cs).second.first->class_param()["ZCPP_NAME"] + ".cc ";

      current_param["TYPE_INITIALIZERS"] += 
	"void " + module_desc.name() + "_t_" 
        + (*cs).second.first->class_param()["ZCPP_NAME"] 
	+ "(ModuleBase::types_t&);\n";
    }

  /*---------------.
  | Create db file |
  `---------------*/
  std::string filename =
    destination_dir + "/" + module_desc.name() + "/" + module_desc.name() + ".db";
  std::ofstream file(filename.c_str());
  assert(file.good());

  spec::ModuleDB mdb;
  for (cs_map_t::iterator cs = class_spec.begin(); cs != class_spec.end(); ++cs)
    mdb.insert((*cs).first, (*cs).second.first->class_param()["CPP_NAME"]);
  mdb.save(file);
  file.close();

  /*----------.
  | functions |
  `----------*/
  std::string fun_inst;
  std::string fun_include;
  std::string fun_sources;

  for (fun_version_list_t::iterator f = module_desc.fun_versions().begin();
       f !=  module_desc.fun_versions().end();
       ++f)
    {
      if (verbose)
	std::cerr << "make_modules : getting parameters of function " 
		  << f->dynamic_name << std::endl;
      spec::FunSpec* fs =
	fun_parse(specification_dir + "/" + f->name + ".fun");
      if (fs == 0)
	{
	  std::cerr << "make_modules : error when loading " 
		    << specification_dir + "/" + f->name + ".fun"
		    << std::endl;
	  exit(EXIT_FAILURE);
	}
      if (f->sigs.size() == 0)
	for (signatures_t::const_iterator sig = fs->signatures().begin();
	     sig != fs->signatures().end();
	     ++sig)
	  {
	    // look for parameters value that are types of the current module.
	    for (param_value_t::iterator p = f->args.begin();
		 p != f->args.end();
		 ++p)
	      {
		cs_map_t::iterator cs = class_spec.find((*p).second);
		if (cs != class_spec.end())
		  (*p).second = (*cs).second.first->class_param()["CPP_NAME"];
	      }

	    std::string fun_cpp_name = 
	      make_fun_version(module_desc.name(), f->dynamic_name, *fs, f->args, *sig);
	    fun_inst += 
	      module_desc.name() + "_f_" +
	      fun_cpp_name + "(" +
	      module_desc.name() + "_funs___);\n";

	    current_param["FUNCTION_INITIALIZERS"] +=
	      "void " +
	      module_desc.name() + "_f_" +
	      fun_cpp_name + "(ModuleBase::functions_t&);\n";

	    fun_sources += "f_" + fun_cpp_name + ".cc ";
	    //	    prelude += "#include \"" + fun_cpp_name + ".hh\"\n";
	  }
      else
	{
	  std::cerr << "Partial functions selections not implemented yet." << std::endl;
	  exit(EXIT_FAILURE);
	}
    } 
  // -> object
  spec::CppParamCode object_c = load_template("object_spec_template_cc.cppp");
  std::string obj_inst;
  std::string obj_instanciator;

  current_param["CONSTANT_INITIALIZERS"] = "";
  for (object_version_list_t::const_iterator o = module_desc.object_versions().begin();
       o !=  module_desc.object_versions().end();
       ++o)
    {
      current_param["CONSTANT_INITIALIZERS"] += 
	"void " +
	module_desc.name() + "_o_" +
	o->name + "(ModuleBase::constants_t&);\n";
	
      std::string	      filename = 
	destination_dir + "/" + module_desc.name() + "/o_" +  
	o->name
	+ ".cc";
      
      // Create the file
      if (verbose)
	std::cerr << "filename : " << filename << std::endl;
      std::ofstream file(filename.c_str());
      assert(file.good());
      param_value_t obj_param;
      obj_param["PRELUDE"]     = "";
      obj_param["MODULE_NAME"] = module_desc.name();
      obj_param["OBJECT_NAME"] = o->name;
      obj_param["CODE"]        = o->value;
      file << object_c.instanciated_code(obj_param) << std::endl;
      file.close();

      obj_inst +=
	module_desc.name() + "_o_" +
	o->name + "(" +
	module_desc.name() + "_consts___);\n";
    }  
  
  /*-----------------.
  | module interface |
  `-----------------*/
  current_param["MODULE_NAME"] = module_desc.name();
  std::string type_inst;

  //-> type instanciation
  for (cs_map_t::iterator cs = class_spec.begin(); cs != class_spec.end(); ++cs)
    {
      std::string class_name = (*cs).second.first->class_param()["ZCPP_NAME"];
      type_inst += 
	module_desc.name() + "_t_" + class_name + "(" +
	module_desc.name() + "_types___);\n";
    }

  current_param["TYPE_INSTANCIATION"] = type_inst;
  //-> function instanciation
  current_param["FUNCTION_INSTANCIATION"] = fun_inst;
  //-> object   instanciation
  current_param["OBJECT_INSTANCIATION"] = obj_inst;
  current_param["OBJECT_INSTANCIATOR"] = obj_instanciator;
  //-> prelude
  current_param["PRELUDE"] = prelude;
  
  filename = 
    destination_dir + "/" + module_desc.name() + "/" + module_desc.name() + "_module.cc";
  
  /*---------------.
  | Create cc file |
  `---------------*/
  std::cerr << filename << std::endl;
  file.open(filename.c_str());
  assert(file.good());

  // Generate c++
  file << module_template.instanciated_code(current_param);  
  file.close();

  /*---------------.
  | Create hh file |
  `---------------*/
  module_template = load_template("module_spec_template_hh.cppp");

  //-> forward declaration of types
  for (cs_map_t::iterator cs = class_spec.begin(); cs != class_spec.end(); ++cs)
    {
      std::string class_name = (*cs).second.first->class_param()["ZCPP_NAME"];
      current_param["PRELUDE"] += "#include \"" + class_name + ".hh\"\n";
      //      current_param["FORWARD_DEC"] += "class " + class_name + "Type;\n";
    }  
  //-> forward declaration of functions
  current_param["PRELUDE"] += fun_include;

  filename = 
    destination_dir + "/" + module_desc.name() + "/" + module_desc.name() + "_module.hh";
  std::cerr << filename << std::endl;
  file.open(filename.c_str());
  assert(file.good());

  // Generate c++
  file << module_template.instanciated_code(current_param);
  file.close();

  /*-----------------------.
  | Generation Makefile.am |
  `-----------------------*/
  filename = destination_dir + "/" + module_desc.name() + 
    "/Makefile.am";
  file.open(filename.c_str());
  assert(file.good());

  file << " INCLUDES = -I$(top_srcdir)/include -I.."  << std::endl
       << "lib_LTLIBRARIES = libv" << module_desc.name() << ".la" << std::endl
       << "libv" + module_desc.name() + "_la_SOURCES = " 
       << module_desc.name() + "_module.cc \\" 
       << std::endl;

  for (object_version_list_t::const_iterator o = module_desc.object_versions().begin();
       o !=  module_desc.object_versions().end();
       ++o)
    file << "o_" << o->name << ".cc ";
  file << fun_sources << "\\\n" << type_sources << std::endl;

  file << "libv" + module_desc.name() + "_la_LDFLAGS = -module" << std::endl;
  file << "libv" + module_desc.name() + "_la_LIBADD  = $(top_srcdir)/src/vcore/libvcore.la"
       << std::endl;
  file.close();
  
}

