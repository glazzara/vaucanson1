// make_tool.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_MPP___SRC_MODULES_MAKE_TOOL_HH
# define VCSN_VAUC_MPP___SRC_MODULES_MAKE_TOOL_HH

# include <string>

# include "spec/cpp_code.hh"

namespace modules
{

  spec::CppParamCode
  load_template(const std::string& filename);  

  std::string
  get_include_name(const std::string & module_name, const std::string& param);

  std::string
  get_class_name(const std::string & module_name, const std::string& param);

  std::string
  get_class_zcppname(const std::string& current_module_name, const std::string& param);

} // modules

#endif // ! VCSN_VAUC_MPP___SRC_MODULES_MAKE_TOOL_HH
