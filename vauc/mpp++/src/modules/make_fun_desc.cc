// make_fun_desc.cc: this file is part of the Vaucanson project.
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

# include "common.hh"
# include "modules/make_fun_desc.hh"
# include "modules/make_tool.hh"
# include "spec/fun_spec.hh"
# include "spec/cpp_code.hh"
# include "internal/mangling.hh"

static std::string
type_name(const std::string& input, const spec::FunSpec::param_value_t& param_value)
{
  spec::FunSpec::param_value_t::const_iterator  param;

  param = param_value.find(input);
  if ((param != param_value.end()) && ((*param).second != ""))
    return (*param).second;
  return input;
}

/*-----------------.
| make_fun_version |
`-----------------*/
// FIXME : this is of course non generic, template code must be
// enriched to support list of parameters for one parameters ...
// Return : the name of the c++ class created
std::string
modules::make_fun_version(const std::string&			module_name,
			  const std::string&			nick_name,
			  const spec::FunSpec&			fun_desc, 
			  const spec::FunSpec::param_value_t&   param_value,
			  const spec::FunSpec::signature_t&	sig)
{
  typedef spec::FunSpec			funspec_t;
  typedef spec::CppParamCode		cpp_param_t;
  typedef spec::FunSpec::param_value_t	param_value_t;
  typedef spec::FunSpec::signature_t	signature_t;
  typedef spec::FunSpec::args_t		args_t;
  typedef spec::FunSpec::param_set_t	param_set_t;

  funspec_t::param_value_t     current_param(param_value);
  std::string		       signature_inst;
  args_t::const_iterator       arg = sig.args.begin();
  args_t::const_iterator       end = sig.args.end();
  end--;

  if (verbose)
    std::cerr << "-> Generating function : " << fun_desc.name() << std::endl;

  /*---------------------------------------------.
  | Initialize current_param for code generation |
  `---------------------------------------------*/

  current_param["PRELUDE"]		   = fun_desc.prelude();
  current_param["POSTLUDE"]		   = fun_desc.postlude();
  current_param["FUN_NAME"]		   = fun_desc.name();
  current_param["MODULE_NAME"]		   = module_name;

  // Includes
  for (param_value_t::const_iterator pv = param_value.begin(); pv != param_value.end();
       ++pv)
    {
      current_param["PRELUDE"] += 
	"#include \"" +
	get_include_name(module_name, type_name((*pv).second, current_param)) +
	".hh\" // " + (*pv).second + "(" + type_name((*pv).second, current_param) + ")" + "\n";
    }

  // Signature and return type
  while (true)
    {
      if (verbose)
	std::cerr << "Look for this parameters value : " 
		  << (*arg).second << " " << type_name((*arg).second, current_param)
		  << std::endl;
      current_param["SIGNATURE"] += 
	get_class_name(module_name, type_name((*arg).second, current_param));
      //	get_class_name(module_name, (*arg).second);

      current_param["PRELUDE"] += 
	"#include \"" +
	get_include_name(module_name, type_name((*arg).second, current_param)) +
	".hh\" // " + (*arg).second + "(" + type_name((*arg).second, current_param) + ")" + "\n";
      
      if (arg != end)
	{
	  current_param["SIGNATURE"] += "->";
	  signature_inst += 
	    "signature().push_back(&" 
	    + get_class_zcppname(module_name, type_name((*arg).second, current_param))
	    + "().instance());\n";
	}
      else
	{
	  current_param["PRELUDE"] += 
	    "#include \"" +
	    get_include_name(module_name, type_name((*arg).second, current_param)) +
	    ".hh\" // " + (*arg).first + "(" + type_name((*arg).second, current_param) + ")" + "\n";
	  if (type_name((*arg).second, current_param) == "any")
	    current_param["RETURN_TYPE"] = "return \"\";";
	  else
	    current_param["RETURN_TYPE"] = "return typeid(" +
	      get_class_zcppname(module_name, type_name((*arg).second, current_param))
	      + ").name();\n";
	  break;
	}
      ++arg;
    }
  // FIXME : for the moment :
  current_param["OBJECT_NAME"] = "";
  current_param["NICK_NAME"] = nick_name;
  current_param["FUNCTION_DESCRIPTION"] = fun_desc.description();
  current_param["SIGNATURE_INSTANCIATION"] = signature_inst;
  spec::CppParamCode cpp_name("#FUN_NAME#_$SIGNATURE$");
  current_param["CPP_NAME"] = cpp_name.instanciated_code(current_param);
  Mangler m;
  m.append(current_param["CPP_NAME"]); 
  current_param["ZCPP_NAME"] = m.escape(m.zip64(m.mangled()));

  for (param_set_t::const_iterator p = fun_desc.parameters().begin();
       p != fun_desc.parameters().end();
       ++p)
    {
      current_param[*p] 
	= get_class_zcppname(module_name, type_name((*arg).second, current_param));	
      if (verbose)
	std::cerr << "Parameter : " << *p << ":" << current_param[*p] << std::endl;
    }

  if (verbose)
    std::cerr << "compressed name : " << current_param["ZCPP_NAME"] << std::endl
	      << "name		  : " << current_param["CPP_NAME"]  << std::endl;
  
  /*-----.
  | Call |
  `-----*/
  std::ostringstream  call;

  // -> arguments casting

  arg = sig.args.begin();
  unsigned count = 0;
  while (arg != end)
    {
      std::string type_arg = get_class_zcppname(module_name, type_name((*arg).second, param_value));
      call  
	<< type_arg + "::static_type_t *" 
	<< (*arg).first + "__ptr"
	<< "= argv[" << count <<  "].cast<"
	<< type_arg + "::static_type_t>();" 
	<< std::endl
	<< "assert(" + (*arg).first + "__ptr);" 
	<< std::endl
	<< type_arg + "::static_type_t &"
	<< (*arg).first
	<< "= *" + (*arg).first + "__ptr;" << std::endl;
      ++arg;
      ++count;
    }  

  // -> the call

  /*--------------------------------------------------.
  | for the call, parameters types are static types.  |
  `--------------------------------------------------*/
  current_param["PARAMETERS_TYPEDEFS"] = "";

  for (param_value_t::const_iterator pv = param_value.begin(); pv != param_value.end();
       ++pv)
    {
      current_param["PARAMETERS_TYPEDEFS"] += 
	"typedef " 
	+ get_class_zcppname(module_name, (*pv).second) 
	+ "::static_type_t " + (*pv).first + "_t;\n";
      current_param[(*pv).first] = (*pv).first + "_t";
    }

  call << sig.call.instanciated_code(current_param) << std::endl;
  current_param["CALL_CODE"] = call.str();

  /*---------.
  | .cc file |
  `---------*/
  std::string filename = 
    destination_dir + "/" + module_name + "/f_" + current_param["ZCPP_NAME"]
    + ".cc";
  if (verbose)
    std::cerr << "Filename : " << filename << std::endl;
  std::ofstream ccfile(filename.c_str());
  assert(ccfile.good());

  // -> c++ generation
  spec::CppParamCode fun_spec = load_template("fun_spec_template_cc.cppp");
  ccfile << fun_spec.instanciated_code(current_param);
  ccfile.close();
  return current_param["ZCPP_NAME"];
}

/*--------------.
| make_fun_desc |
`--------------*/
void
modules::make_fun_desc(const std::string&			module_name,
		       const std::string&			nick_name,
		       const spec::FunSpec&			fun_desc,
		       const spec::FunSpec::param_value_t&      param_value)
{
  typedef spec::FunSpec			funspec_t;
  typedef spec::CppParamCode		cpp_param_t;
  typedef spec::FunSpec::signature_t	signature_t;
  typedef spec::FunSpec::signatures_t	signatures_t;
  typedef spec::FunSpec::args_t		args_t;

  for (signatures_t::const_iterator sig = fun_desc.signatures().begin();
       sig != fun_desc.signatures().end();
       ++sig)
    {      
      (void)make_fun_version(module_name, nick_name, fun_desc, param_value, *sig);      
    }
}

