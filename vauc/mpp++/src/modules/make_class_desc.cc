// make_class_desc.cc: this file is part of the Vaucanson project.
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
# include <string>
# include <cassert>

# include "../common.hh"
# include "modules/make_class_desc.hh"
# include "modules/make_tool.hh"
# include "spec/class_spec.hh"
# include "spec/cpp_code.hh"
# include "internal/mangling.hh"


/*----------------.
| make_class_desc |
`----------------*/
std::string
modules::make_class_desc(const std::string&			module_name,
			 const spec::ClassSpec&			class_desc, 
			 const spec::ClassSpec::param_value_t&  param_value)
{
  typedef spec::ClassSpec::param_value_t	param_value_t;
  typedef spec::ClassSpec::param_set_t		param_set_t;

  spec::ClassSpec     iclass(class_desc);
  param_value_t	      pvalue(param_value);
  
  if (verbose)
    std::cerr << "-> Generating class : " << pvalue["NICK_NAME"] << std::endl;

  /*------------------------------------------------------------.
  | Initialize class_param() : parameters for the template code |
  `------------------------------------------------------------*/
  iclass.class_param()["TYPE_DESCRIPTION"]	= iclass.description();
  iclass.class_param()["PARAMETERS_TYPEDEFS"]   = "";
  iclass.class_param()["NICK_NAME"]		= pvalue["NICK_NAME"];
  for (param_set_t::const_iterator p = class_desc.parameters().begin();
       p != class_desc.parameters().end();
       ++p)
    {
      if (verbose)
	std::cerr << "Parameter : " << *p << ":" << pvalue[*p] << std::endl;
      iclass.class_param()["PRELUDE"] += 
	"#include \"" +
	get_include_name(module_name, pvalue[*p]) +
	".hh\"\n";
      iclass.class_param()["PARAMETERS_TYPEDEFS"] += 
	"typedef "  
	+ get_class_zcppname(module_name, pvalue[*p]) 
	+ "::static_type_t " 
	+ *p 
	+ "_t; // " 
	+ pvalue[*p] + " \n";
      pvalue[*p] = *p + "_t";
    }

  iclass.class_param()["MODULE_NAME"] = module_name;

  Mangler m;
  spec::CppParamCode class_spec = load_template("class_spec_template_hh.cppp");
  m.append(iclass.class_param()["CPP_NAME"]);
  iclass.class_param()["ZCPP_NAME"] = m.escape(m.zip64(m.mangled()));
  if (verbose)
    std::cerr << "compressed name : " << iclass.class_param()["ZCPP_NAME"] << std::endl
	      << "name		  : " << iclass.class_param()["CPP_NAME"]  << std::endl;

  /*------------------------------------.
  | Instanciate static type with pvalue |
  `------------------------------------*/

  (void)iclass.instanciate_class(pvalue);

  /*--------.
  | hh file |
  `--------*/
  std::string	      filename = 
    destination_dir + "/" + module_name + "/t_" +  
    iclass.class_param()["ZCPP_NAME"]
    + ".hh";

  // Create the file
  if (verbose)
    std::cerr << "filename : " << filename << std::endl;
  std::ofstream file(filename.c_str());
  assert(file.good());

  // Generate c++ implementation
  file << class_spec.instanciated_code(iclass.class_param());
  file.close();

  /*--------.
  | cc file |
  `--------*/
  class_spec = load_template("class_spec_template_cc.cppp");
  filename = 
    destination_dir + "/" + module_name + "/t_" +  
    iclass.class_param()["ZCPP_NAME"]
    + ".cc";
  
  // Create the file
  if (verbose)
    std::cerr << "filename : " << filename << std::endl;
  file.open(filename.c_str());
  assert(file.good());
  // Generate c++ implementation
  file << class_spec.instanciated_code(iclass.class_param());
  file.close();
  return iclass.class_param()["ZCPP_NAME"];
}

