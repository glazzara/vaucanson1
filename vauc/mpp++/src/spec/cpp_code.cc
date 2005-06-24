// cpp_code.cc: this file is part of the Vaucanson project.
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
# include <list>

# include "spec/cpp_code.hh"

namespace spec {

  CppParamCode::CppParamCode()
  {}

  CppParamCode::CppParamCode(const std::string& param_code)
  {
    std::string	current_param;
    bool	in_param_use = false;

    for (std::string::const_iterator c = param_code.begin();
	 c != param_code.end();
	 ++c)
      if ((*c == '#')  || (*c == '$'))
	{
	  if (in_param_use)
	    parameters_.push_back(current_param);
	  else
	    current_param.clear();
	  in_param_use = !in_param_use;
	}
      else if (in_param_use)
	current_param.push_back(*c);
//     if (in_param_use)
//       {
// 	std::cerr << "make_modules : unbalanced parameters." << std::endl;
// 	exit(EXIT_FAILURE);
//       }
    param_code_ = param_code;
  }

  static std::string
  formated_code(const std::string& str)
  {
    std::string output;
    for (std::string::const_iterator i = str.begin(); i != str.end(); ++i)
      switch (*i)
	{
	case '<': case '>': case ',' : case ':' : case '-' :
	  output += '_';
	  break;
	case '\n' : case '\t' : case ' ' :
	  break;
	default:
	  output += *i;
	}
    return output;
  }

  const CppParamCode::code_t      
  CppParamCode::instanciated_code(const param_value_t& values) const
  {
    std::string	current_param;
    std::string	return_code;
    bool	in_param_use = false;
    bool	formated = false;
    
    for (std::string::const_iterator c = param_code_.begin();
	 c != param_code_.end();
	 ++c)
      if (*c == '\\')
	{
	  ++c;
	  if (c != param_code_.end())
	    return_code += *c;
	}
      else if ((*c == '#') || (*c == '$'))
	{
	  formated = (*c == '$');
	  if (in_param_use)
	    {
	      param_value_t::const_iterator f = values.find(current_param);
	      if (f == values.end())
		{
		  std::cerr << "make_modules : this parameters is not defined '" 
			    << current_param << "'." << std::endl;
		  exit(EXIT_FAILURE);
		}
	      if (formated)
		return_code += formated_code(f->second);
	      else 
		return_code += f->second;
	    }
	  else
	    current_param.clear();
	  in_param_use = !in_param_use;
	}
      else if (!in_param_use)
	return_code += *c;
      else 
	current_param += *c;
    return return_code;
  }
  
} // spec

